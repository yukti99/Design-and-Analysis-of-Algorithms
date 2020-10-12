#include <stdio.h>

void Merge(int a[],int low,int mid,int high){
	int i,j,k;
	int n1 = mid-low+1;
	int n2 = high-mid;
	int n3 = n1+n2;
	
	int l[n1],r[n2];
	
	for(i=0;i<n1;i++)
		l[i] = a[low+i];
	
	for(j=0;j<n2;j++)
		r[j] = a[mid+1+j];
	
	i = 0;
	j = 0;
	k = low;
	
	while(i<n1 && j<n2){
		
		if (l[i]<r[j])
			a[k++] = l[i++];
		else 
			a[k++] = r[j++];
			
	}
	while(i<n1)
		a[k++] = l[i++];
	
	while(j<n2)
		a[k++] = r[j++];
	
}
void MergeSort(int a[],int l,int r){
	if (l<r){
		int m = (l+r)/2 ;
		MergeSort(a,l,m);
		MergeSort(a,m+1,r);
		Merge(a,l,m,r);
	}
}
