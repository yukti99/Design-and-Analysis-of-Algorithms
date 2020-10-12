// Fractional Knapsack Problem By Greedy Approach
#include <stdio.h>
#include <stdlib.h>


int W=0,N=0;

struct Item{
	int No;
	int weight;
	int value;
	float profit;
	
};
int KnapsackF(int N,int W,struct Item items[]){
	int i,j,X[N],profit=0;	
	for(i=0;i<N;i++){
		if (items[i].weight <= W){
			printf("Included whole of Item - %d with weight - %d and value - %d\n",items[i].No,items[i].weight,items[i].value);
			W = W-items[i].weight ;
			profit+=items[i].value;	
		}
		else
			break;
	
	}
	if(i<=N){
		float frac =  (float)W/items[i].weight ;
		profit += frac*((float)items[i].value);
		if (frac!=0)
			printf("Included %d/%d of Item - %d with weight - %d and value - %d\n",W,items[i].weight, items[i].No, items[i].weight, items[i].value);
	}	
	return profit;
}

int main(){	
    W = 50; 
    struct Item items[] = {{1,10,60},{2,20,100},{3,30,120}};
    N = sizeof(items)/sizeof(items[0]); 
    printf("No of objects = %d\n",N);     
    printf("Maximum Capacity of knapsack = %d\n",W);
    
    int i=0,j=0;
    for(i=0;i<N;i++){
    	items[i].profit = (float)(items[i].value)/items[i].weight ;    
    }
    //  sort in descending order
    for(i=0;i<N;i++){
	for(j=0;j<N-i-1;j++){
		if (items[j].profit < items[j+1].profit){
			struct Item t = items[j];
			items[j] = items[j+1];
			items[j+1] = t;		
		}
			
	}
    }        
    printf("\nMaximum Profit = %d\n", KnapsackF(N,W,items));
    
    return 0; 
}
