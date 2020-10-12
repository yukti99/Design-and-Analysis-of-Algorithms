// GREEEDY ALGORITHM - KRUSKAL'S ALGORITHM TO FIND MINIMUM SPANNING TREE
// Adjacency Matrix representation

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#define V 5


typedef struct Edge{
	int u,v,w;

}Edge;

typedef struct EdgeList
{
	Edge data[V];  // array of edges (each element as an edge)
	int n;           // total no of edges
	
}EdgeList;

EdgeList l,MST;


void Union(int belongs[],int e1,int e2){
	int i;	
	for(i=0;i<V;i++)
		if(belongs[i] == e2)
			belongs[i] = e1;
}


void CreateMST(int graph[V][V]){
	int belongs[V];

	// creating the list of edges in the graph
	int i=0,j=0;
	for(i=1;i<V;i++){
		for(j=0;j<i;i++){
			if (graph[i][j] != 0){
				l.data[l.n].u = i;
				l.data[l.n].v = j;
				l.data[l.n].w = graph[i][j];
				l.n++;
			}
		
		}
	
	}
	
	// sorting the edges in ascending order
	for(i=1;i<l.n;i++){
		for(j=0;j<l.n-1;j++){
			if (l.data[j].w > l.data[j+1].w){
				int t = l.data[j+1].w;
				l.data[j+1].w = l.data[j].w;
				l.data[j].w = t; 
			}
		}
	}
	for(i=0;i<V;i++)
		belongs[i]=i;
	MST.n = 0;
	for(i=0;i<l.n;i++){
	
		int e1 = belongs[l.data[i].u];
		int e2 = belongs[l.data[i].v];
		
		if(e1 != e2){
			MST.data[MST.n] = l.data[i];
			MST.n = MST.n+1;
			Union(belongs,e1,e2);
		}
	}
	// To print the Minimum Spanning Tree
	int cost=0;	
	for(i=0;i<MST.n;i++){
		printf("\n%d\t%d\t%d",l.data[i].u, l.data[i].v, MST.data[i].w);
		cost = cost + MST.data[i].w;
	} 
	printf("\n\nCost of the spanning tree = %d\n",cost);	
	

}
int main(){

	// taking input graph for MST
	int graph[V][V] = { { 0,2,0,6,0},{2,0,3,8,5},{0,3,0,0,7},{6,8,0,0,9},{0,5,7,9,0}};
	CreateMST(graph);
	return 0;
}
