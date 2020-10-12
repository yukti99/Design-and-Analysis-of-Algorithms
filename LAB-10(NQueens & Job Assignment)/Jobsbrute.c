// Job assignment problem using brute force technique

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>
#define N 4

int min = INT_MAX;
char assign[N];
char assigned[N];
int cost=0;
bool done[N];

int JobAssign(int C[N][N],int c,int job){
	if (c == 0){
		if (cost < min){
			min = cost;
			for(int i=0;i<N;i++){
				assigned[i] = assign[i];
			}
			
		}
		return 0;	
		
	}	
	else{
		for(int i=0;i<N;i++){
			if (done[i] == false){
				done[i] = true;
				assign[i] = job + 'P';
				cost = cost +  C[i][job];
				//printf("\nbefore : Agent = %c,Job = %c,cost = %d,counter=%d\n",i+'A',job+'P',cost,c);
				JobAssign(C,c-1,job+1);				
				done[i] = false;	
				cost = cost - C[i][job];
				//printf("\nafter : Agent = %c,Job = %c,cost = %d,counter=%d\n",i+'A',job+'P',cost,c);	
			}
		}
	
	}
	
}
int main(){
	int i=0;
	for(i=0;i<N;i++){
		done[i] = false;
		assign[i] = '$';
	}
	
	int job = 0;
	int C[N][N] = { {11,12,18,40}, 
			{14,15,13,22}, 
			{11,17,19,23}, 
			{17,14,20,28} };
	 /*int C[N][N] = 
		    	{ 
			{9, 2, 7, 8}, 
			{6, 4, 3, 7}, 
			{5, 8, 1, 8}, 
			{7, 6, 9, 4} 
		    	};  */
        //c = N means no agent assigned job and c = 1 means all assigned, so it decrements when a job  is assigned
	JobAssign(C,N,job);
	printf("\n");	
	for(i=0;i<N;i++){
			printf("Job %c is assigned to %c\n",'A'+i,assigned[i]);
	}			
	printf("\nThe Optimal/Minimum Solution  = %d\n",min);

	return 0;
}	
