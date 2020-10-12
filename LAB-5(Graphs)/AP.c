#include <stdio.h>
#include <stdlib.h>
#include <time.h>


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
// Undirected Graph
void AddEdge(struct Graph* g,int s,int d){
	struct Node* n = CreateNode(d);
	n->next = g->adjlists[s];
	g->adjlists[s] = n;
	
	struct Node* n1 = CreateNode(s);
	n1->next = g->adjlists[d];
	g->adjlists[d] = n1;
	
	
	printf("The Edge (%d,%d) is successfully created!\n",s,d);
}
// For printing the Graph
void printGraph(struct Graph* g){
	int i;
	printf("\nGRAPH : \n");
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
int t=0;
int min(int a,int b){
	return (a<b)?a:b;
}
void dfsAP(struct Graph* g,int u,int parent[],int disc[],int low[],int AP[]){
	int child = 0;
	g->visited[u] = 1;
	low[u] = disc[u] = ++t;
	struct Node* n = g->adjlists[u];
	while(n){
		int v = n->vertex;
		if (g->visited[v]==0){
			child++;
			parent[v] = u;
			dfsAP(g,v,parent,disc,low,AP);	
			// Check if the subtree rooted with v is connected to one of the ancestors of u
            		low[u] = min(low[u],low[v]); 
            		if (parent[u]!=-1 && low[v]>=disc[u])
            			AP[u] = 1;
            		if (parent[u] == -1 && child>1)
            			AP[u] = 1;
            			
		}
		// v is already visited but not the parent of u
		else if (v!=parent[u]){
			low[u] = min(low[u],disc[v]);		
		}	
	
		n = n->next;	
	}
}

void ArtPoints(struct Graph* g){
	int parent[g->V];
	int AP[g->V];
	int disc[g->V],low[g->V];
	//what is lowest level vertex x can climb to, in case its parent is removed from the graph	
	int i=0;
	unvisit(g);
	for(i=0;i<g->V;i++){
		parent[i] = -1;
		AP[i] = disc[g->V] = low[g->V]  = 0;
	}
	for(i=0;i<g->V;i++){
		if (g->visited[i]==0)
			dfsAP(g,i,parent,disc,low,AP);
	
	}
	int f=0;
	for(i=0;i<g->V;i++){
		if (AP[i] == 1){
			f=1;
			printf("%d\n",i);
		}
	}
	if (f==0)	
		printf("No Articulation Point! The Graph is Biconnected!\n\n");		
	
	else	
		printf("The graph is NOT Biconnected!\n\n");	
}

int main(){
	srand(time(NULL)); // to make sure each time an actual random no is generated 
	int i,V,x,y,k=0;	
	printf("Enter the number of vertices = ");
	scanf("%d",&V);
	if (V<=2){
		printf("Invalid Input!\n");
		exit(0);
	}		
	int degree = 1;
	struct Graph* g = CreateGraph(V);
	/*
	V = 5;
	struct Graph* g = CreateGraph(V);	
	AddEdge(g,1, 0); 
	AddEdge(g,0, 2); 
	AddEdge(g,2, 1); 
	AddEdge(g,0, 3); 
	AddEdge(g,3, 4); 
	*/	 
	// Creating a random Connected Graph	
	for(i=0;i<V;i++){
		k=0;
		while(k!=degree){
			x = rand()%V;
			if (!isEdge(g,i,x) && !isEdge(g,x,i) && x!=i){
				AddEdge(g,i,x);
				k++;
			} 		
		}	
	}
		
	printGraph(g);
	printf("\nThe Articulation Points in the graph : \n");
	ArtPoints(g);	
	return 0;
}
