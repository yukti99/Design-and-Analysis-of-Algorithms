// N QUEEN'S PROBLEM - BACKTRACKING FOR PRINTING ALL SOLUTIONS

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h> // bool
#include <string.h> //  memset

int N=0,count=0;
void printBoard(int board[N][N]){
	printf("\n\a%d. CHESSBOARD : \n",count);
	int i,j;
	for(i=0;i<N;i++){
		for(j=0;j<N;j++){
			if (board[i][j] == 'Q')
				printf("%c ",board[i][j]);
			else
				printf("%d ",board[i][j]);		
		}
		printf("\n");	
	}
	printf("\n");	
}

// Queens placed in each column
int QueenisSafe(int board[N][N],int row,int col){
	int i=0,j=0;
	// checking rows 
	for(i=0;i<col;i++){
		if(board[row][i])
			return 0; // not safe
	}
	
	// checking upper left diagonal
	for(i=row,j=col;i>=0&&j>=0;i--,j--){
		if (board[i][j])
			return 0; // not safe
	}
	
	// checking lower left diagonal
	for(i=row,j=col;i<N&&j>=0;i++,j--){
		if (board[i][j])
			return 0; // not safe
	}
	return 1; // yes,safe
}
int flag = 0;
bool NQueens(int board[N][N],int col){

	if (col >= N){
		flag =1;
		count++;
		printBoard(board);
		return true;	
	}
	int i=0;
	bool ans = false;
	for(i=0;i<N;i++){
		// row = i
		if (QueenisSafe(board,i,col)){
			board[i][col] = 'Q';
			ans = NQueens(board,col+1);	
			board[i][col] = 0;
			
		}
	}
	return ans;
}

int main(){
   
    printf("Enter the the value of N : ");
    scanf("%d",&N);
    int board[N][N];
    memset(board,0,N*N*sizeof(board[0][0]));	    	
 
    NQueens(board,0);
    if (!flag){
    	printf("Solution does not exist for N = %d\n",N);
    }
    else{
    	printf("Number of Solutions = %d\n",count);
    }
    return 0;
}
