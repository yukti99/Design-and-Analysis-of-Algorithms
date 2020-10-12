#include <stdio.h>

#define N 8

int steps=0;
void print(int m[N][N]){
	printf("\n");
	int i,j;
	for(i=0;i<N;i++){
		for(j=0;j<N;j++){
			printf("%d ",m[i][j]);
		}
		printf("\n");
	}
	printf("\n");
}
int allZeroes(int m[N][N],int col){
	int i=0;
	for(i=0;i<N;i++)
		if (m[i][col]!=0)
			return 0;
	return 1;
}
int allTwos(int m[N][N],int col){
	int i=0;
	for(i=0;i<N;i++)
		if (m[i][col]!=2)
			return 0;
	return 1;
}
int lowestNo(int m[N][N],int col){
	int i=0,min = m[0][col];
	for(i=0;i<N;i++){
		int x =  m[i][col];
		if (min > x &&  x>2)
			min = m[i][col];
	
	}
	//printf("Min in column-%d of matrix = %d\n",col,min);
	return min;
}
void MultiplyRow2(int m[N][N],int row){
	int i=0;
	for(i=0;i<N;i++){
		m[row][i] *= 2;
	}
	
}
int OneinCol(int m[N][N],int col){
	int i=0;
	for(i=0;i<N;i++){
		if (m[i][col] == 1){
			printf("Multiplying row-%d by 2\n",i);
			MultiplyRow2(m,i);
			steps++;
			print(m);
		}
			
			
	}
}
void TwotoZero(int m[N][N],int col){
	int y=0,x=0;
	for(y=0;y<2;y++){
		printf("Subtracting 1 from col-%d\n",col);
		for(x=0;x<N;x++){
				m[x][col] -= 1;
				steps++;
				
		}
		print(m);
	}
}
void ToZeroes(int m[N][N]){
	int row=N,col=N,i,j,x,y;
	for(i=0;i<N;i++){
			OneinCol(m,i);
			if (allTwos(m,i))
				TwotoZero(m,i);
			while(!allZeroes(m,i)){
				// find lowest num in column which is >2
				int min = lowestNo(m,i);				
				// subtracting this column min-1 times
				for(x=0;x<min-1;x++){		
					for(j=0;j<N;j++){
						if (m[j][i] > 2){
							m[j][i] = m[j][i]-1;
							steps++;
						}
							
						
						// after subtraction if any 1 in column multiply row by 2
						OneinCol(m,i);
						if (allTwos(m,i))
							TwotoZero(m,i);
						
						
					}
				}				
						
			} 		
	}
	printf("\nNo of Steps = %d\n",steps);
}

int main(){
	int i=0;
	int m[8][8] = {
		   {2,22,1,3,2,2,4,3},
		   {1,2,2,2,4,3,2,4},
		   {2,3,4,1,2,5,2,1},
		   {1,4,3,2,1,6,2,3},
		   {3,2,1,4,3,3,2,1},
		   {2,21,1,3,2,2,4,3},
		   {1,2,2,2,4,3,2,4},
		   {2,3,4,1,2,5,2,1}
		   };

	//int m[N][N] = {{2,4},{1,2}};
	//int m[N][N] = {{2,4,1,3},{1,2,2,2},{2,3,4,1},{1,4,3,2}};
	
	printf("\nThe matrix : \n");
	print(m);
	ToZeroes(m);
	
	return 0;
}


