// MATRIX CHAIN MULTIPLICATION 
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

// recursive approach - Exponential time taken (brute force)
int n=0,v=0;
int MatrixChain(int p[],int i,int j,int S[n][n]){
	if (i==j)
		return 0;
		
	int k=0,count=0,min=INT_MAX;
	
	for(k=i;k<=j-1;k++){
		count = MatrixChain(p,i,k,S) + MatrixChain(p,k+1,j,S) + p[i-1]*p[k]*p[j] ;
		if (count < min){
			min = count;
			S[i][j] = k; //for printing brackets
		}
	}
	return min;
} 
void print(int S[n][n],int i,int j){
	if (i==j)
		printf("%c",65+(v++));
	else{
		printf("(");
		print(S,i,S[i][j]);
		print(S,S[i][j]+1,j);
		printf(")");
	
	}

}

int main(){

	int i=0,j=0;
	int p[] = {30,35,15,5,10,20,25};
	n = sizeof(p)/sizeof(p[0]);
	int S[n][n];
	for(i=0;i<n;i++){
		for(j=0;j<n;j++)
			S[i][j] = 0;
	}
	printf("\nMinimum number of multiplications is %d\n",MatrixChain(p,1,n-1,S)); 
	/*for(i=0;i<n;i++){
		for(j=0;j<n;j++)
			printf("%d \t",S[i][j]);
		printf("\n");
	}*/
	printf("\nBracket Order : \n");
	print(S,1,n-1);
	printf("\n\n");
	return 0;
}
