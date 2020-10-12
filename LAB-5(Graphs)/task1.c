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
int c=0;
void DFS(struct Graph* g,int s){
    g->visited[s] = 1;
    c++;
    struct Node* n = g->adjlists[s];
    while(n){
        int v = n->vertex;
        if (!g->visited[v]){
            g->visited[v] = 1;
            DFS(g,v);
     
        }
         n = n->next;    
    }


}

int main(){
	int i,V,x,y,k=0;	
	printf("Enter the number of vertices = ");
	scanf("%d",&V);
	int degree = V/3;
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
	printGraph(g);
	int max = 0;
	for(i=0;i<V;i++){
        c=0;
	    DFS(g,i);
	    if (max<c)
	        max = c;
	}
	
	if (max<V){
	    printf("The minimum number of edges needed to make a connected graph = %d",V-max);	
	}
	else{
	    printf("The Graph is Connected!\n");
	}
	
	
	
	return 0;
}
