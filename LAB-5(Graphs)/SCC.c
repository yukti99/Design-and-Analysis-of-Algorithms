#include <stdio.h>
#include <stdlib.h>
#include "stack.c"

// Applying Kosaraju's Algorithm to determine Strongly Connected Components of the Graph
// Graph Node

struct Node{
	int vertex;
	struct Node* next;
};

struct Node* CreateNode(int v){
	struct Node* n = (struct Node*)malloc(sizeof(struct Node));
	n->vertex = v;
	n->next = NULL;
	return n;
}

struct Graph{
	int V;
	int *visited;
	struct Node** adjlists;
};

struct Graph* CreateGraph(int v){
	struct Graph* g = (struct Graph*)malloc(sizeof(struct Graph));
	g->V = v;
	g->visited = (int*)malloc(sizeof(int)*v);
	g->adjlists = (struct Node**)malloc(sizeof(struct Node*)*v);
	int i=0;
	for(i=0;i<v;i++){
		g->visited[i] = 0;
		g->adjlists[i] = NULL;
	}
	return g;
};
void unvisit(struct Graph* g){
	int i=0;
	for(i=0;i<g->V;i++){
		g->visited[i] = 0;
		
	}
}
// Directed Graph
void AddEdge(struct Graph* g,int s,int d){
	struct Node* n = CreateNode(d);
	n->next = g->adjlists[s];
	g->adjlists[s] = n;
	printf("The Edge (%d,%d) is successfully created!\n",s,d);
}
// To check if an edge is already present
int isEdge(struct Graph* g,int x,int y){
	struct Node* temp = g->adjlists[x];
	while(temp){
		if (temp->vertex == y)
			return 1;
		temp = temp->next;	
	}
	return 0;
}
// For printing the Graph
void printGraph(struct Graph* g){
	int i;
	for(i=0;i<g->V;i++){
		struct Node* n = g->adjlists[i] ; 
		printf("\nThe adjacency List of vertex = %d\n",i);
		while(n){
			printf("%d -> ",n->vertex);
			n = n->next;
		}
		printf("NULL\n");	
	}
	printf("\n");
}

// Step-1 : DFS Traversal to keep track of finish times of all nodes
int d[100],f[100];
int time=0;

void DFS(struct Graph *g,int s,struct Stack* stack){
	g->visited[s] = 1;
	struct Node* n = g->adjlists[s];
	d[s] = time;
	time++;
	while(n){
		int a = n->vertex;
		if (g->visited[a]==0){
			g->visited[a] = 1;
			DFS(g,a,stack);
		}
		n = n->next;	
	}
	f[s] = time;
	time++;
	push(stack,s);
}

void dfs_rec(struct Graph* g,struct Stack *s){
	unvisit(g);
	int i=0;
	for(i=0;i<g->V;i++){
		if (!g->visited[i])
			DFS(g,i,s);
	
	}

}
// Step-2 : Finding the Transpose of the given graph (reversing edges)
struct Graph* GTranspose(struct Graph* g){
	unvisit(g);
	int i=0;
	struct Graph* gt = CreateGraph(g->V);	
	for(i=0;i<g->V;i++){
		struct Node* n = g->adjlists[i];
		while(n){
			int v = n->vertex;			
			AddEdge(gt,v,i);			
			n = n->next;
		}		
	}
	unvisit(g);
	return gt;
}
// Step-3 : DFS on the reversed graph with vertices taken in decreasing order of finishing times

void dfsTranspose(struct Graph* g,int s){	
	struct  Stack* st = CreateS(100);
	g->visited[s] = 1;
	printf("%d ",s);
	struct Node* n = g->adjlists[s];
	while(n){
		int a = n->vertex;
		if (g->visited[a]==0){
			g->visited[a] = 1;
			dfsTranspose(g,a);
		}
		n = n->next;	
	}
	
}


void SCC(struct Graph* g,struct Graph *gt){	
	struct Stack* stack  = CreateS(100);
	// filling stack with nodes in decreasing order of finishing time 
	dfs_rec(g,stack);
	unvisit(g);
	int i=0;
	printf("\nThe Strongly Connected Components of the Graph are : \n");
	while(!isEmptyS(stack)){	
		int v = pop(stack);	
		if (gt->visited[v] == 0){
			dfsTranspose(gt,v);
			printf("\n");
		}		
			
	}
}
void TimeStamps(struct Graph* g){
	printf("\nThe Disovery and Finishing time of all vertices in DFS : \n");	
	printf("Vertex\t\tDiscovery\tFinish\n");
	int i=0;
	for(i=0;i<g->V;i++){
		printf("%d\t\t%d\t\t%d\n",i,d[i],f[i]);	
	}
	printf("\n");
}

int main(){
	int i,V,x,y,k=0;	
	printf("Enter the number of vertices = ");
	scanf("%d",&V);
	int degree = 1;
	struct Graph* g = CreateGraph(V);
	// Creating a random Connected Graph	
	for(i=0;i<V;i++){
		k=0;
		while(k!=degree){
			x = rand()%V;
			if (!isEdge(g,i,x) && x!=i){
				AddEdge(g,i,x);
				k++;
			} 		
		}	
	}
	
	//V = 6;
	//struct Graph* g = CreateGraph(V);
	//AddEdge(g,0,4);AddEdge(g,4,5);AddEdge(g,4,1);AddEdge(g,1,3);AddEdge(g,1,2);AddEdge(g,0,2);AddEdge(g,0,1);AddEdge(g,5,3);	
	/*
    	V = 5;
    	struct Graph* g = CreateGraph(V);
    	AddEdge(g,2,1);
    	AddEdge(g,1,0);
    	AddEdge(g,0,2);
    	AddEdge(g,0,3);
    	AddEdge(g,3,4);
    	
    	*/
    	printf("\nGraph:\n");
	printGraph(g);
	struct Graph* gt = GTranspose(g);
	printf("\nThe Transpose of the Graph :\n");
	printGraph(gt);	
	SCC(g,gt);
	TimeStamps(g);
	
	
	
	return 0;
}
