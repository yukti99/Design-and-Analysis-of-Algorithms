//  LONGEST COMMON SUBSEQUENCE PROBLEM USING DYNAMIC PROGRAMMING APPROACH

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int m=0,n=0,c=0;

void printLCS(char B[m+1][n+1],char text[],int i,int j){
	if (B[i][j] == '$'){
		return ;		
	}		
	else if (B[i][j] == '\\'){
		printLCS(B,text,i-1,j-1);
		c++;
		printf("%c",text[i-1]);	
	}
	else if (B[i][j] == '|')
		printLCS(B,text,i-1,j);
	else
		printLCS(B,text,i,j-1);

}

void LCS(char text1[],char text2[]){
	m = strlen(text1);
	n = strlen(text2);
	int i,j;
	int C[m+1][n+1];
	char B[m+1][n+1];
	for(i=0;i<=m;i++){
		for(j=0;j<=n;j++){
			if (i==0 || j == 0){
				C[i][j] = 0;
				B[i][j] = '$';
			}
			else if (text1[i-1] == text2[j-1]){
				C[i][j] = 1 + C[i-1][j-1];
				B[i][j] = '\\';				
			}
			
			else if (C[i-1][j] >= C[i][j-1]){
				C[i][j] = C[i-1][j];
				B[i][j] = '|';			
			}
			else{
				C[i][j] = C[i][j-1];
				B[i][j] = '-';			
			}			
		
		}	
	}
	// for printing
	printf("\nThe Longest Common Subsequence is : ");
	printLCS(B,text1,m,n);
	printf("\nLength = %d\n",c);
	printf("\nThe LCS and B table : \n");
	for(i=0;i<=m;i++){
		for(j=0;j<=n;j++){
			printf("(%d,%c)\t",C[i][j],B[i][j]);	
		}
		printf("\n");
	}
	printf("\n\n");
}

int main(){
	
	char text1[100],text2[100];
	printf("Enter the text-1 : ");
	scanf("%s",text1);
	printf("Enter the text-2 : ");
	scanf("%s",text2);
	LCS(text1,text2);
	return 0;
}
