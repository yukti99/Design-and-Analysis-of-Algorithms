//  LONGEST COMMON SUBSEQUENCE PROBLEM USING BRUTE FORCE APPROACH
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int m=0,n=0;
char lcs[100];
int k=0;

int max(int a,int b){
	return (a>b)?a:b;
}
int LCS(char text1[],char text2[],int m,int n){
	if (m==0 || n==0)
		return 0;
	if (text1[m-1] == text2[n-1]){	
		return 1 + LCS(text1,text2,m-1,n-1);
			
	}
	else
		return max(LCS(text1,text2,m,n-1),LCS(text1,text2,m-1,n));
}
int main(){
	int i;
	char text1[100],text2[100];
	printf("Enter the text-1 : ");
	scanf("%s",text1);
	printf("Enter the text-2 : ");
	scanf("%s",text2);
	m = strlen(text1);
	n = strlen(text2);
	int l = LCS(text1,text2,m,n);
	printf("\nLength of Longest Common Subsequence = %d\n",l);
	return 0;
}
