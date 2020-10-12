#include <stdio.h>


void SelectionSort(int a[],int n){
        int min=0,i,j;
        for(i=0;i<n;i++){
                min = i;
                for(j=i+1;j<n;j++){
                        if (a[j] < a[min]){
                                min = j;
                        }
                }
                if (min!=i){
                        int t = a[min];
                        a[min] = a[i];
                        a[i] = t;
                }
                
        }

}

