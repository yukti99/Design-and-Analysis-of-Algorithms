#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>


#include "BubbleSort.h"
#include "SelectionSort.h"
#include "InsertionSort.h"
#include "MergeSort.h"
#include "QuickSort.h"


void print(int a[],int n){
        int i=0;
        for(i=0;i<n;i++)
                printf("%d ",a[i]);
        printf("\n\n");
}

int main(){
        
        int n,i;
        printf("Enter the size of the array to be sorted = ");
        scanf("%d",&n);
        int a1[n],a2[n],a3[n],a4[n],a5[n];
        
        srand(time(0));
        FILE *f;
        f = fopen("Numbers.txt","w+");
        for(i=0;i<n;i++){
                fprintf(f,"%d ",rand()%100000);
        }
        fprintf(f,"\n");
        fclose(f); 
        
        f = fopen("Numbers.txt","r");
        printf("\nThe Numbers to be sorted : \n");
        for(i=0;i<n;i++){
                fscanf(f,"%d",&a1[i]);
                a2[i] = a1[i];
                a3[i] = a1[i];
                a4[i] = a1[i];                 
                a5[i] = a1[i];
                printf("%d ",a1[i]);
        }
        printf("\n\n");
        fclose(f);      
        
        long ts1,ts2,ts3,ts4,ts5,te1,te2,te3,te4,te5;
        struct timeval tv;
        ///////////////////////////////////////////////////////////////////////////
        gettimeofday(&tv,NULL);
        ts1 = (tv.tv_sec *1e+6) + tv.tv_usec;   
        
           
        BubbleSort(a1,n);
        printf("After Bubble Sort : \n");
        print(a1,n);
        
        gettimeofday(&tv,NULL);
        te1 = (tv.tv_sec *1e+6) + tv.tv_usec;        
        
        
        long t1 = te1-ts1;
        
        /////////////////////////////////////////////////////////////////////////
        
      
        
        gettimeofday(&tv,NULL);
        ts2 = (tv.tv_sec *1e+6) + tv.tv_usec;   
        
           
        SelectionSort(a2,n);
        printf("After Selection Sort : \n");
        print(a2,n);
        
        
        gettimeofday(&tv,NULL);
        te2 = (tv.tv_sec *1e+6) + tv.tv_usec;        
        
        
        long t2 = te2-ts2;
            
        ////////////////////////////////////////////////////////////////////////
        
      
        
        gettimeofday(&tv,NULL);
        ts3 = (tv.tv_sec *1e+6) + tv.tv_usec;   
        
           
        InsertionSort(a3,n);
        printf("After Insertion Sort : \n");
        print(a3,n);
        
        gettimeofday(&tv,NULL);
        te3 = (tv.tv_sec *1e+6) + tv.tv_usec;        
        
        
        long t3 = te3-ts3;
          
        //////////////////////////////////////////////////////////////////////
       
      
        
        gettimeofday(&tv,NULL);
        ts4 = (tv.tv_sec *1e+6) + tv.tv_usec;   
        
           
        MergeSort(a4,0,n-1);
        printf("After Merge Sort : \n");
        print(a4,n);
        
        
        gettimeofday(&tv,NULL);
        te4 = (tv.tv_sec *1e+6) + tv.tv_usec;        
        
        
        long t4 = te4-ts4;
        
        ////////////////////////////////////////////////////////////////////
        
        
        
        gettimeofday(&tv,NULL);
        ts5 = (tv.tv_sec *1e+6) + tv.tv_usec;   
        
        QuickSort(a5,0,n-1);
        printf("After Quick Sort : \n");
        print(a5,n);
        
        gettimeofday(&tv,NULL);
        te5 = (tv.tv_sec *1e+6) + tv.tv_usec;        
        
        
        long t5 = te5-ts5;
        
        ///////////////////////////////////////////////////////////////////// 
        
        printf("Total Execution time for Bubble Sort = %ld X 10^-6 sec\n",t1);   
        printf("Total Execution time for Selection Sort = %ld X 10^-6 sec\n",t2);
        printf("Total Execution time for Insertion Sort = %ld X 10^-6 sec\n",t3);  
        printf("Total Execution time for Merge Sort = %ld X 10^-6 sec\n",t4);          
        printf("Total Execution time for Quick Sort = %ld X 10^-6 sec\n",t5);    
        return 0;
}
