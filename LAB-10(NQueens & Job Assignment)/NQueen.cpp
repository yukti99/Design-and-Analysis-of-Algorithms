// N Queen's Problem 

#include <bits/stdc++.h>
using namespace std;


char grid[11][11];
int n;


bool isSafe(int row,int col){
	int i,j;
	// checking row
	for(i=0;i<col;i++){
		if (grid[row][i] == 'Q')
			return false;
	}
	// checking upper left diagonal
	for(i=row,j=col;i>=0 && j>=0;i--,j--){
		if (grid[i][j] == 'Q')
			return false;
	}
	// checking lower left diagonal
	for(i=row,j=col;i<n && j>=0;i++,j--){
		if (grid[i][j] == 'Q')
			return false;
	}
	return true;
}
void NQueen(int col){
	if (col>=n){
		cout<<"[";
		for(int i=0;i<n;i++){
			for(int j=0;j<n;j++){
				if (grid[i][j] == 'Q')
					cout<<j+1<<" ";
			}
		}
		cout<<"]";		
		return ;	
	}
	for(int i=0;i<n;i++){
		if (isSafe(i,col)){
			grid[i][col] = 'Q';
			NQueen(col+1);
			grid[i][col] = '0';
		}
			
	}	

}
void printSol(int n){
	if (n==1){
		cout<<"[1 ]"<<endl;
		return ;
	}
	if (n==2 || n==3){
		cout<<-1<<endl;
		return ;
	}
	NQueen(0);
	
}
int main() {
	int t;
	cin>>t;
	while(t--){
		cin>>n;
		memset(grid,'0',sizeof(grid));
		printSol(n);
	}	
	return 0;
}
