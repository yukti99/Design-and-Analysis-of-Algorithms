// DIJKSTRA'S ALGORITHM TO FIND SHORTEST DISTANCE FROM SINGLE SOURCE TO ALL VERTICES
// using Adjacency matrix representation

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#define V 9
#define INF INT_MAX


void display(int graph[V][V]){
	int i,j;
	printf("\nGRAPH : \n");
	for(i=0;i<V;i++){
		for(j=0;j<V;j++)
			printf("%d ",graph[i][j]);
		printf("\n");
	}
	printf("\n");
	
}

int findMinV(int graph[V][V],int set[],int dist[]){
	int i=0,min = INF,j=0;
	for(i=0;i<V;i++){
		if (!set[i] && dist[i] <= min){
			min = dist[i];
			j = i;
		}
		
	}
	return j;

}
char vertex(int x){
	return 'A'+x ;
}

void DijstraAlgo(int graph[V][V],int start){

	// taking arrays to store data
	int dist[V],set[V];
	char parent[V];

	int i,v,j;
	// initializing the vertices
	for(i=0;i<V;i++){
		dist[i] = INF;
		parent[i] = '$';
		set[i] = 0;
	}
	// starting vertex distance  = 0
	dist[start] = 0;
	for(i=0;i<V-1;i++){
		int u = findMinV(graph,set,dist);
		set[u] = 1;
		for(v=0;v<V;v++){
			if (!set[v] && graph[u][v] && dist[u]!=INF && dist[u] + graph[u][v] < dist[v]){
				dist[v] = dist[u] + graph[u][v] ;	
				parent[v] = vertex(u);		
				
			}
		}
	
	}
	// printing the solution
	printf("\nThe Shortest distance from %d to all other vertices : \n",start);
	printf("\nVERTEX\tDISTANCE\tPARENT\n");
	for(i=0;i<V;i++){
		printf("%c\t%d\t\t%c\n",vertex(i),dist[i],parent[i]);
		
	}
	printf("\n");

}

int main(){

	/*
	// To take graph input from user
	printf("\nEnter number of vertices = ");	
	scanf("%d",&V);	
	printf("\nEnter the adjacency matrix:\n");	
	for(i=0;i<V;i++)
		for(j=0;j<V;j++)
			scanf("%d",&graph[i][j]);
	*/
	
	/*int graph[V][V] = {{0, 4, 0, 0, 0, 0, 0, 8, 0}, 
						{4, 0, 8, 0, 0, 0, 0, 11, 0}, 
						{0, 8, 0, 7, 0, 4, 0, 0, 2}, 
						{0, 0, 7, 0, 9, 14, 0, 0, 0}, 
						{0, 0, 0, 9, 0, 10, 0, 0, 0}, 
						{0, 0, 4, 14, 10, 0, 2, 0, 0}, 
						{0, 0, 0, 0, 0, 2, 0, 1, 6}, 
						{8, 11, 0, 0, 0, 0, 1, 0, 7}, 
						{0, 0, 2, 0, 0, 0, 6, 7, 0} 
						}; 
	
	
	*/
	int graph[V][V] = 	{{0,4,0,0,0,0,0,8,0}, 
						{0,0,8,0,0,0,0,11,0}, 
						{0,8,0,7,0,4,0,0,2}, 
						{0,0,7,0,9,14,0,0,0}, 
						{0,0,0,9,0,10,0,0,0}, 
						{0,0,4,14,10,0,2,0,0}, 
						{0,0,0,0,0,2,0,1,6}, 
						{8,11,0,0,0,0,1,0,7}, 
						{0,0,2,0,0,0,6,7,0} 
						}; 
	
	display(graph);
	int start=0;
	printf("Enter the starting vertex : ");
	scanf("%d",&start);
	DijstraAlgo(graph,start);

	return 0;
}

/*
	Vertex   Distance from Source
0                0
1                4
2                12
3                19
4                21
5                11
6                9
7                8
8                14

*/
