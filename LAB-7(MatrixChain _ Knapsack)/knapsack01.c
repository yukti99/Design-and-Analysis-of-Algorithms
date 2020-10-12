// 0/1 KNAPSACK PROBLEM using Dynamic Programming
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#define max(a,b) a>b?a:b 

int N=0,W=0;
// To print the items included in knapsack 
void printSolution(int k[N+1][W+1],int wt[],int val[]){
	int max = k[N][W];
	int i=0,w=W;
	printf("\nKnapsack 0-1 Solution : \n");
	for(i=N;i>0 && max>0;i--){
		if (max == k[i-1][w])
			continue;
		else{
			printf("Included weight-> %d with profit -> %d\n",wt[i-1],val[i-1]);
			max = max-val[i-1];
			w = w-wt[i-1];		
		}	
	
	}

}
// N - Number of objects
// W - Maximum capacity
// val[] - profits of all objects
// wt[]  - weight of all objects
int Knapsack01(int W,int wt[],int val[],int N){
	int i,w;
	int k[N+1][W+1];
	for(i=0;i<=N;i++){
		for(w=0;w<=W;w++){
			if (i==0 || w==0)
				k[i][w] = 0;
			else if (wt[i-1]<= W)
				k[i][w] = max(val[i-1] + k[i-1][w-wt[i-1]],k[i-1][w]);
		
			else
				k[i][w] = k[i-1][w];
	
		}
	}
	printSolution(k,wt,val);
	return k[N][W];

}


int main(){	
    int val[] = {1,2,4}; 
    int wt[] = {2,3,3}; 
    W = 6; 
    printf("Maximum Capacity of knapsack = %d\n",W); 
    N = sizeof(val)/sizeof(val[0]); 
    printf("\nMaximum Profit = %d\n", Knapsack01(W, wt, val, N));
    
    return 0; 
}
