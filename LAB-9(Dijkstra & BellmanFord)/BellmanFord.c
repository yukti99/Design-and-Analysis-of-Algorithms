// BELLMANFORD ALGORITHM TO FIND SHORTEST DISTANCE FROM SINGLE SOURCE TO ALL VERTICES
// using Adjacency List representation

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#define INF INT_MAX


struct Edge{
	int s,d,w;
};

struct Graph{
	int V,E;
	struct Edge* edge;
};

struct Graph* CreateGraph(int V,int E){
	struct Graph* g = (struct Graph*)malloc(sizeof(struct Graph));
	g->V = V;
	g->E = E;
	g->edge = (struct Edge*)malloc(E*sizeof(struct Edge));
	return g;
}


char vertex(int x){
	return 'A'+x ;
}

void BellmanFord(struct Graph* g,int start){

	// taking arrays to store data
	int dist[g->V],set[g->V];
	char parent[g->V];

	int i,j,u,v,w,n=0;
	
	// initializing the vertices
	for(i=0;i<g->V;i++){
		dist[i] = INF;
		parent[i] = '$';
		set[i] = 0;
	}
	// starting vertex distance  = 0
	dist[start] = 0;
	// relax all edges V-1 times
	for(i=1;i<=g->V-1;i++){
		for(j=0;j<g->E;j++){
			u = g->edge[j].s;
			v = g->edge[j].d;
			w = g->edge[j].w;
			if (dist[u]!=INF && dist[u]+w < dist[v]){
				dist[v] = dist[u] + w;
				parent[v] = vertex(u);
			}
		}
	}
	
	// checking to detect negative cycle
	for (int i = 0; i <g->E; i++)	{ 
		u = g->edge[i].s; 
		v = g->edge[i].d; 
		w = g->edge[i].w; 
		if (dist[u] != INF && dist[u] + w < dist[v]){
			printf("Graph contains negative weight cycle\n");
			n=1;
			break; 
		}
	} 
	// printing the solution
	if (n==0){
		printf("\nNo negative cycle in graph!\n");
		printf("\nThe Shortest distance from %d to all other vertices : \n",start);
		printf("\nVERTEX\tDISTANCE\tPARENT\n");
		for(i=0;i<g->V;i++){
			printf("%c\t%d\t\t%c\n",vertex(i),dist[i],parent[i]);
			
		}
		printf("\n");
	}
}

int main(){

	
	int V,E,start=0,i;
	printf("Enter the number of vertices in the graph = ");
	scanf("%d",&V);
	printf("Enter the number of Edges = ");
	scanf("%d",&E);		
	printf("Enter the starting vertex : ");
	scanf("%d",&start);
	struct Graph* g = CreateGraph(V,E);
	/*for(i=0;i<E;i++){
		printf("\nEnter the edge %d Source,destination and weight : \n",i);
		scanf("%d",&g->edge[i].s);
		scanf("%d",&g->edge[i].d);
		scanf("%d",&g->edge[i].w);
		
	}*/
	g->edge[0].s= 0; 
	g->edge[0].d = 1; 
	g->edge[0].w = 2; 

	 
	g->edge[1].s = 1; 
	g->edge[1].d = 2; 
	g->edge[1].w = 2; 

	
	g->edge[2].s = 2; 
	g->edge[2].d = 4; 
	g->edge[2].w= -3; 

	
	g->edge[3].s= 3; 
	g->edge[3].d = 4; 
	g->edge[3].w = -4; 

	
	g->edge[4].s = 1; 
	g->edge[4].d = 3; 
	g->edge[4].w = 1; 

	g->edge[5].s = 3; 
	g->edge[5].d = 0; 
	g->edge[5].w = -4; 


	BellmanFord(g,start);

	return 0;
}


