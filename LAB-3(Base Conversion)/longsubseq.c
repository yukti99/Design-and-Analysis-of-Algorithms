#include <stdio.h>


// Longest Increasing Subsequence

int max(int x,int y){
	return x>y?x:y ;	
}

void LongestSubSeq(int a[],int n){
	int i,j;
	int l[n];
	for(i=0;i<n;i++)
		l[i] = 1;
	
	for(i=1;i<n;i++){
		for(j=0;j<i;j++){
			if (a[i] > a[j]){
				l[i] = max(l[j]+1,l[i]) ;
			}
		}
	}
	int m = l[0];
	for(i=1;i<n;i++){
		if (m < l[i]){
			m = l[i];			
		}
	}
	printf("\nThe Longest Increasing Subsequence is of length = %d\n",m);
}

int main(){
	
	// Taking Array input from the user
	int i,n;
	printf("\nEnter the number of elements in the array = ");
	scanf("%d",&n);
	int a[n];
	for(i=0;i<n;i++)
		scanf("%d",&a[i]);
	printf("\nEntered Array : \n");
	for(i=0;i<n;i++)
		printf("%d ",a[i]);
	printf("\n");
	
	LongestSubSeq(a,n);
	
	return 0;
}
