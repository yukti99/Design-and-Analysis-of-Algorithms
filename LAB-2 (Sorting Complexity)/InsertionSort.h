#include <stdio.h>

void InsertionSort(int a[],int n){

        int i,pos,temp;
        for(i=1;i<n;i++){
                temp = a[i];
                pos = i-1;
                while(pos>=0 && temp<a[pos]){
                        a[pos+1] = a[pos];
                        pos--;
                }
                a[pos+1] = temp;
                
        }

}

