#include <stdio.h>

void swap(int *a,int *b){
	
	int t = *a;
	*a = *b;
	*b = t;
}
int partition(int a[],int low,int high){
	
	int pivot = a[high];
	int i = low-1,j;
	for(j = low ; j<=high-1; j++){
		if (a[j]<=pivot){
			i++;
			swap(&a[j],&a[i]);
		}
	}
	swap(&a[i+1],&a[high]);
	return i+1;
}

void QuickSort(int a[],int low,int high){
	
	if (low < high){
		int pi = partition(a,low,high);   // partition index
		QuickSort(a,low,pi-1);
		QuickSort(a,pi+1,high);
	}
	
}
