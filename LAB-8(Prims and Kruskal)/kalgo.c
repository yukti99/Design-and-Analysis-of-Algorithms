#include <stdio.h>
#include <stdlib.h>
#define MAX 5
 
typedef struct Edge{
	int u,v,w;
}edge;
 
typedef struct edgelist
{
	edge data[MAX];
	int n;
}edgelist;
 
int G[MAX][MAX],n;
edgelist elist;
edgelist spanlist;
 

void Union(int belongs[],int c1,int c2){
	int i;	
	for(i=0;i<n;i++)
		if(belongs[i]==c2)
			belongs[i]=c1;
}
 
void sort(){
	int i,j;
	edge temp;	
	for(i=0;i<elist.n;i++)
		for(j=0;j<elist.n-i-1;j++)
			if(elist.data[j].w > elist.data[j+1].w){
				temp = elist.data[j];
				elist.data[j] = elist.data[j+1];
				elist.data[j+1] = temp;
			}
}
int find(int belongs[],int vertexno){
	return(belongs[vertexno]);
}
 
 
void print(){
	int i,cost=0;	
	for(i=0;i < spanlist.n;i++){
		printf("\n%d\t%d\t%d",spanlist.data[i].v,spanlist.data[i].u,spanlist.data[i].w);
		cost += spanlist.data[i].w;
	} 
	printf("\n\nCost of the spanning tree = %d\n\n",cost);
}

void kruskal(){
	int belongs[MAX],i,j,cno1,cno2;
	elist.n=0;
	// to access elements below diagonal in matrix
	
	for(i=1;i<n;i++)
		for(j=0;j<i;j++){
			if(G[i][j]!=0){
				printf("i,j = %d,%d\n",i,j);
				elist.data[elist.n].u = i;
				elist.data[elist.n].v = j;
				elist.data[elist.n].w = G[i][j];
				elist.n++;
				printf("%d,%d,%d\n",i,j,G[i][j]);
				
			}
		}

	//sort();
	printf("\n");
	for(i=0;i<n;i++){		
		printf("%d,%d,%d\n",elist.data[i].u,elist.data[i].v,elist.data[i].w);
		
 	}
	
	
	for(i=0;i<n;i++)
		belongs[i]=i;
	
	spanlist.n=0;
	
	for(i=0;i<elist.n;i++){
		cno1 = belongs[elist.data[i].u];
		cno2 = belongs[elist.data[i].v];
		
		if(cno1 != cno2){
			spanlist.data[spanlist.n] = elist.data[i];
			spanlist.n++ ;
			Union(belongs,cno1,cno2);
		}
	}
	print();
}
 

 
void main(){
	int i,j,total_cost;	
	printf("\nEnter number of vertices = ");	
	scanf("%d",&n);	
	printf("\nEnter the adjacency matrix:\n");
	
	for(i=0;i<n;i++)
		for(j=0;j<n;j++)
			scanf("%d",&G[i][j]);
			
	kruskal();
	
}
/*
0 2 0 6 0
2 0 3 8 5
0 3 0 0 7
6 8 0 0 9 
0 5 7 9 0
*/
 


