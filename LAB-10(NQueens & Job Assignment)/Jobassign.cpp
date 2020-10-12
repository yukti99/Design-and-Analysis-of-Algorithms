// Job Assignment problem using branch and bound 

#include <bits/stdc++.h>
#define N 4 // No of agents and jobs
using namespace std;

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

struct compare{
	bool operator()(const Node *a , const Node *b){
		return a->cost > b->cost ;
	
	}
};

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
	printf("\nAgent %c assigned to job %c\n",m->agent+'A',m->job+'P');
	
}

int findMinCost(int M[N][N]){
        priority_queue<Node*, vector<Node*>, compare> h;
	bool assigned[N] = {false};
	struct Node* rootNode =  newNode(-1,-1,assigned,NULL);
	rootNode->pathCost = rootNode->cost = 0;
	rootNode->agent = -1;
	h.push(rootNode);
	int j=0;
	while(!h.empty()){
		struct Node* min = h.top();
		h.pop();
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
				h.push(child);				
			}
		}
	
	}
}
int main(){
	// Job-agent Matrix
	int c[N][N] = { {11,12,18,40}, 
			{14,15,13,22}, 
			{11,17,19,23}, 
			{17,14,20,28}}; 
	printf("\nThe Optimal/Minimum Solution  = %d\n",findMinCost(c));
	return 0;
}
