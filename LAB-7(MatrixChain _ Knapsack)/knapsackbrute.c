// 0/1 KNAPSACK PROBLEM using Brute Force
#include <stdio.h>
#include <stdlib.h>

#define max(a,b) a>b?a:b 

int N=0,W=0;

// N - Number of objects
// W - Maximum capacity
// val[] - profits of all objects
// wt[]  - weight of all objects
int Knapsack(int W,int wt[],int val[],int N){
	if (W == 0 || N == 0)
		return 0;
	if ( W < wt[N-1]){
		return Knapsack(W,wt,val,N-1);
	}
	else 
		return max(val[N-1]+ Knapsack(W-wt[N-1],wt,val,N-1),Knapsack(W,wt,val,N-1));

}

int main(){	
    int val[] = {1,2,4}; 
    int wt[] = {2,3,3}; 
    W = 6; 
    printf("Maximum Capacity of knapsack = %d\n",W); 
    N = sizeof(val)/sizeof(val[0]); 
    printf("Maximum Profit = %d\n", Knapsack(W, wt, val, N));
    
    return 0; 
}
