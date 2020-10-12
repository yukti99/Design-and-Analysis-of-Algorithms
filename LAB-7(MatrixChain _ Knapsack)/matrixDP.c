// MATRIX CHAIN MULTIPLICATION 
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

// Dynamic Programming approach
int n=0,v=0;

void printBrackets(int s[n][n],int i,int j){
	if (i==j){
		printf("%c",65+(v++));
		return ;
	}
	else{
		printf("(");
		printBrackets(s,i,s[i][j]);
		printBrackets(s,s[i][j]+1,j);
		printf(")");
	
	}

}

int MatrixChain(int p[],int n){
	int m[n][n],s[n][n];
	int i,j,k,d,cost=0;
	for(i=0;i<n;i++)
		for(j=0;j<n;j++){
			m[i][j] = 0;
			s[i][j] = 0;
		}	
			
	
	for(d=2;d<n;d++){
		for(i=1;i<n-d+1;i++){
			j = i+d-1;
			m[i][j] = INT_MAX;
			for(k=i;k<=j-1;k++){
				cost = m[i][k] + m[k+1][j] + p[i-1]*p[k]*p[j];
				if (cost < m[i][j]){
					m[i][j] = cost; 
					s[i][j] = k;
				}
								
			
			}		
		}	
	} 
	printf("\nMatrix M : \n");
	for(i=0;i<n;i++){
		for(j=0;j<n;j++){
			printf("%d\t",m[i][j]);
		}
		printf("\n");
	}
	printf("\nMatrix S : \n");
	for(i=0;i<n;i++){
		for(j=0;j<n;j++){
			printf("%d\t",s[i][j]);
		}
		printf("\n");
	}
	printf("\nBracket Order : \n");
	printBrackets(s,1,n-1);
	return m[1][n-1];
}   


int main(){

	int i=0;
	int p[] = {30,35,15,5,10,20,25};
	n = sizeof(p)/sizeof(p[0]);
	printf("\n\nMinimum number of multiplications required =  %d\n",MatrixChain(p,n)); 
	return 0;
}
