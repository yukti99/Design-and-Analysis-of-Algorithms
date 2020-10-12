// Job Assignment problem using branch and bound 

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#define N 4 // No of agents and jobs

// State Space Tree Node
struct Node{
	struct Node* parent;
	int pathCost;
	int cost;
	int agent;
	int job;
	bool assigned[N];
};

struct Node* newNode(int agent,int job,bool assigned[],struct Node* parent){
	
	struct Node* n = (struct Node*)malloc(sizeof(struct Node));
	int i=0;
	for(i=0;i<N;i++){
		n->assigned[i] = assigned[i];  
	}
	n->assigned[job] = true;
	n->parent = parent;
	n->agent = agent;
	n->job  = job;
}
//----------------------------------------------------------------------------
// Implementation of Minimum Heap structure
// Array Implementation


void swap(struct Node *a, struct Node *b){
	struct Node* t  = a;
	a = b;
	b = t;
}

// Array implemenatation of a Binary Heap
struct Minheap{
    struct Node **a;
    int capacity;
    int size ;
};

struct Minheap* Createheap(int capacity){
    struct Minheap* h = (struct Minheap*)malloc(sizeof(struct Minheap));
    h->size = 0;
    h->capacity = capacity;
    h->a = (struct Node**)malloc(sizeof(struct Node*)*capacity);
    return h;
}
int parent(int i){
    return ((i-1)/2);
}
int left(int i){
	return (2*i + 1);
}
int right(int i){
	return (2*i + 2);
}
void heapifyUp(struct Minheap *h,int i){
	
	while(i!= 0 && h->a[parent(i)] > h->a[i]){
        swap(h->a[parent(i)],h->a[i]);
        i = parent(i);
    }   
}

void insert(struct Minheap *h,struct Node* data){
    if (h->size == h->capacity){
        printf("\nOverflow Condition!!\n");
        return ;
    }
    h->size++;
    // Enter element at the end then heapify the tree
    int i = h->size - 1;
    h->a[i]  = data;
    // Heapify the tree if the heap condition is violated
    heapifyUp(h,i);
     
}
void heapifyDown(struct Minheap *h,int i){
	int l = left(i);
	int r = right(i);
	int smallest = i;
	if (l< h->size && h->a[l] < h->a[i])
		smallest = l;
	if (r<h->size && h->a[r] < h->a[smallest])
		smallest = r;
	if (smallest != i){
		swap(h->a[i],h->a[smallest]);
		heapifyDown(h,smallest);
	}	
}
void decreaseKey(struct Minheap *h,int i,struct Node* new_val){
	h->a[i] = new_val;
	//  restoring the heap property if violated
	heapifyUp(h,i);
}

struct Node* extractMin(struct Minheap* h){
	if (h->size <= 0)
		return NULL;
	if (h->size == 1){
		h->size--;
		return h->a[0];
	}
	struct Node* root = h->a[0];
	h->a[0] = h->a[h->size-1];
	h->size--;
	heapifyDown(h,0);
	return root ; 
}
struct Node* Delete(struct Minheap *h,int i){
	decreaseKey(h,i,NULL);
	return extractMin(h);	
}
struct Node* valueAt(struct Minheap *h,int i){
	return (h->a[i]);
}
bool isEmpty(struct Minheap* h){
	return (h->size == 0);
}
//----------------------------------------------------------------------------------------------------
// To calculate least cost after assigning an agent to a job
int calculateCost(int M[N][N],int agent,int job,bool assigned[]){
	int cost = 0,i=0,j=0;
	bool  available[N] = {true};
	// from next agent
	for(i = agent+1; i<N; i++){
	
		int min = INT_MAX;
		int minIndex = -1;
		for(j=0;j<N;j++){
			if (!assigned[j] && available[j] && M[i][j] < min){
				minIndex = j;
				min = M[i][j];
			}
		}
		cost += min;
		available[minIndex] = false;
	
	}
	return cost;
	
}
void display(struct Node* m){
	if (m->parent == NULL)
		return ;
	display(m->parent);
	printf("\nAgent %c assigned to job %d\n",m->agent+'A',m->job);
	
}

int findMinCost(int M[N][N]){
	struct Minheap* h = Createheap(100);
	bool assigned[N] = {false};
	struct Node* rootNode =  newNode(-1,-1,assigned,NULL);
	rootNode->pathCost = rootNode->cost = 0;
	rootNode->agent = -1;
	insert(h,rootNode);
	int j=0;
	while(!isEmpty(h)){
		struct Node* min = Delete(h,0);
		int i = min->agent + 1;
		// all workers are assigned
		if (i == N){
			display(min);
			return min->cost;		
		}
		// do for each job
		for(j=0;j<N;j++){
			if (!min->assigned[j]){
				struct Node* child = newNode(i,j,min->assigned,min);
				child->pathCost = min->pathCost + M[i][j];
				child->cost = child->pathCost + calculateCost(M,i,j,child->assigned);
				insert(h,child);				
			}
		}
	
	}
}
int main(){

	// Job-agent Matrix
	int c[N][N] = {{9, 2, 7, 8}, 
			{6, 4, 3, 7}, 
			{5, 8, 1, 8}, 
			{7, 6, 9, 4}}; 
	printf("The Optimal cost  = %d\n",findMinCost(c));
	return 0;
}
