#include <stdio.h>
#include <limits.h>


void maxSubArray(int a[],int n,int l){

	if (l>=n)
		return ;

	int i,j,x,y,start=0,sum=0,max = INT_MIN;;
	for(i=l;i<n;i++){
		sum += a[i];
		if (max < sum){
			
			max = sum;
			x = start;
			y = i;
		}
		if (sum<0){
			sum = 0;
			start = i+1;
		}
		
	}
	printf("\nMaximum sum = %d from index %d to %d (both inclusive)",max,x,y);
	l+=y;
	maxSubArray(a,n,l);
		
	
}
int main(){
	int n,i;
	printf("Enter the no of elements : ");
	scanf("%d",&n);
	int a[n];
	printf("\nEnter the elements : \n");
	for(i=0;i<n;i++){
		scanf("%d",&a[i]);
	}
	//int a[] = {5 ,10, -20, 15, -20, 8, 4, 1, 2, -1};
	//int a[] = {-2, -3, 4, -1, -2, 1, 5, -3};
	//int n = sizeof(a)/sizeof(a[0]);
	int z = 0;
	maxSubArray(a,n,z);
	return 0;
}
