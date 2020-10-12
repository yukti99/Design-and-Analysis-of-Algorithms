// GREEEDY ALGORITHM - PRIM'S ALGORITHM TO FIND MINIMUM SPANNING TREE
// Adjacency Matrix representation

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#define V 5



// To print the Minimum Spanning Tree
int print(int MST[],int graph[V][V]){
	printf("\nThe Minimum Spanning Tree of given graph : \n");
	int i=0;
	printf("Edge \tWeight\n");
	for(i=1;i<V;i++){
		printf("%d -- %d \t %d\n",MST[i],i,graph[i][MST[i]]);
	}	

}
// To find the vertex with minimum key
int minKey(int key[],int mset[]){
	int m = INT_MAX,i;
	int min_i;
	for(i=0;i<V;i++){
		if (mset[i] == 0 && key[i] < m){
			m = key[i];
			min_i = i;		
		}
	
	}
	return min_i;
}


void CreateMST(int graph[V][V]){
	int MST[V],key[V],mset[V];
	int  i=0,v=0;
	for(i=0;i<V;i++){
		key[i] = INT_MAX;   //  initializing all the keys as infinity
		mset[i] = 0;			// mst array has no vertex initially 
	}
	key[0] = 0; //  including first vertex in mst
	MST[0] = -1; // first node is the root of MST
	
	for(i=0;i<V-1;i++){
		int u = minKey(key,mset);
		//printf("\nu = %d\n",u);
		mset[u] = 1;
		for(v=0;v<V;v++){
			
			if (graph[u][v] != 0 && mset[v]==0 && graph[u][v] < key[v]){
				//printf("\n\tv = %d\n",v);
				MST[v] = u ;  // u is the parent of MST in the Min Spanning Tree
				key[v] = graph[u][v];
			}
		}
		
	}
	print(MST,graph);

}



int main(){

	// taking input graph for MST
	int graph[V][V] = { { 0,2,0,6,0},{2,0,3,8,5},{0,3,0,0,7},{6,8,0,0,9},{0,5,7,9,0}};
	CreateMST(graph);
	return 0;
}
