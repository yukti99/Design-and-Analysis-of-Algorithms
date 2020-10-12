#include <stdio.h>
#include <stdlib.h>


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
int start[100],end[100];
char color[100];
int time = 0;

// Recursive Depth-First Search
void DFS(struct Graph* g,int s){
	g->visited[s] = 1;	
	start[s] = time;
	printf("%d ",s);
	struct Node* n = g->adjlists[s];
	time = time+1;
	while(n){
		int a = n->vertex;
		if (g->visited[a]==0){
			g->visited[a] = 1;
			DFS(g,a);			
		}		
		n = n->next;	
	}
	end[s] = time;
	time = time+1;
}
int t = 0,d[100],f[100],parent[100];

void ClassifyEdge(struct Graph* g,int u){

	d[u] = t++;
	g->visited[u] = 1;
	color[u] = 'g';
	struct Node* n = g->adjlists[u];
	while(n){
		int v = n->vertex;
		// undiscovered
		if (color[v] == 'w'){
			// visited first time while dfs
			printf("(%d,%d) is a Tree Edge\n",u,v);
			parent[v] = u;
			ClassifyEdge(g,v);		
			
		}
		else if (color[v] == 'b'){
			// not tree edge but v descendant of u	
			if (d[u] < d[v])
				printf("(%d,%d) is a Forward Edge\n",u,v);
			// no ancestor-descendant relationship
			else
				printf("(%d,%d) is a Cross Edge\n",u,v);			
							
		}
		// u is descendant of v (v is already visited/grey)
		else if (color[v] == 'g'){			
			printf("(%d,%d) is a Back Edge\n",u,v);
		}			
		
		n = n->next;
	}
	f[u] = t++;
	color[u] = 'b';

}

// Analysing each Edge
void ColorEdges(struct Graph* g){
	int i=0;
	unvisit(g);
	for(i=0;i<g->V;i++){
		color[i] = 'w';//  initially marking all vertices white	done
	}
	for(i=0;i<g->V;i++){
		if (g->visited[i]==0)
			ClassifyEdge(g,i);
			
	}
}

// To create dfs-forest
void dfs_forest(struct Graph* g){
	int i=0;
	unvisit(g);
	for(i=0;i<g->V;i++){
		if (g->visited[i]==0){
			DFS(g,i);
		}
	}

}

void TimeStamps(struct Graph* g){
	printf("\nThe Disovery and Finishing time of all vertices in DFS : \n");	
	printf("Vertex\t\tDiscovery\tFinish\n");
	int i=0;
	for(i=0;i<g->V;i++){
		printf("%d\t\t%d\t\t%d\n",i,start[i],end[i]);	
	}
	printf("\n");
}
int isCyclic(struct Graph* g,int v,int parent){
	g->visited[v] = 1;
	struct Node *n = g->adjlists[v];
	while(n){
		int a = n->vertex;
		if (g->visited[a] == 0){
			if (isCyclic(g,a,v))
				return 1;
		}
		// a visited adjacent not a parent of current vertex
		else if (a!=parent){
			return 1;
		}
		n = n->next;	
	
	}
	return 0;

}

// Detection of Cycle in Graph
int CycleInGraph(struct Graph* g){
	int i=0,u;
	unvisit(g);
	for(i=0;i<g->V;i++){
		if (g->visited[i] == 0){
			if (isCyclic(g,i,-1))
				return 1;
		}
	
	}
	return 0;
}




int main(){
	int i,V,x,y,k=0;	
	printf("Enter the number of vertices = ");
	scanf("%d",&V);
	int degree = 2;
	if (V >=20)
		degree = V/3;
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
	/*
	V = 6;
	struct Graph* g = CreateGraph(V);
	AddEdge(g,0,4);AddEdge(g,4,5);AddEdge(g,4,1);AddEdge(g,1,3);AddEdge(g,1,2);AddEdge(g,0,2);AddEdge(g,0,1);AddEdge(g,5,3);*/	
	printGraph(g);
	int s=0;
	//printf("Enter the start for dfs Traversal = ");
	//scanf("%d",&s);
	//DFS(g,s);
	printf("\nThe DFS  Traversal of the given graph  :\n");
	dfs_forest(g);
	printf("\n");
	unvisit(g);
	TimeStamps(g);
	if (CycleInGraph(g)){
		printf("\nThe given graph contains cycle!\n");
	}
	else
		printf("\nThe given graph has NO cycles!\n");
	ColorEdges(g);		
	return 0;
}
