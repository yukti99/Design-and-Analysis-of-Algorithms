#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <time.h>



// Stack def for DFS
//------------------------------------------------------------------------------------------
struct Stack{
	int top;
	int size;
	int *a;
};

struct Stack* CreateS(int size){
	struct Stack* s = (struct Stack*)malloc(sizeof(struct Stack));
	s->size = size;
	s->top = -1;
	s->a = (int*)malloc(sizeof(int)*size);
	return s;
}
int isEmpty(struct Stack* s){
	return (s->top == -1);
}
int isFull(struct Stack*s){
	return (s->top == s->size-1);
}
void push(struct Stack* s,int item){
	if (isFull(s))
		return ;
	s->a[++s->top] = item;
}

int pop(struct Stack* s){
	if (isEmpty(s))
		return INT_MAX;
	int p = s->a[s->top];
	s->top--;
	return p;
}
int peek(struct Stack* s){
	return s->a[s->top];
}
void displayS(struct Stack* s){
	int i=0;
	printf("Stack : \n");
	for(i=0;i<=s->top;i++){
		printf("%d ",s->a[i]);	
	}
	printf("\n");

}
//------------------------------------------------------------------------------------------------------------------

struct Node{
	int vertex;
	struct Node* next;
};
struct Node* CreateNode(int v){
	struct Node* n = (struct Node*)malloc(sizeof(struct Node));
	n->vertex = v;
	n->next = NULL;
	return n;
}
struct Graph{
	int V;
	int *visited;
	struct Node** adjlists;
};

struct Graph* CreateGraph(int V){
	struct Graph* g = (struct Graph*)malloc(sizeof(struct Graph));
	g->V = V;
	g->visited = (int*)malloc(sizeof(int)*V);
	g->adjlists = (struct Node**)malloc(sizeof(struct Node*)*V);
	int i=0;	
	for(i=0;i<V;i++){
		g->visited[i] = 0;
		g->adjlists[i] = NULL;	
	}
	return g;
}

// undirected graph
void AddEdge(struct Graph* g,int s,int d){
	struct Node* n = CreateNode(d);
	n->next = g->adjlists[s];
	g->adjlists[s] = n;	
	
}
void unvisit(struct Graph* g){
	int i=0;
	for(i=0;i<g->V;i++){
		g->visited[i] = 0;
	}
}

void display(struct Graph* g){
	int i=0;
	printf("\nGRAPH : \n");
	for(i=0;i<g->V;i++){
		struct Node* temp = g->adjlists[i];
		printf("The Adjacency list of vertex %d :\n",i);
		while(temp){
			printf("%d -> ",temp->vertex);
			temp = temp->next;		
		}
		printf("NULL\n");	
	}
	printf("\n");

}
int isEdge(struct Graph* g,int s,int d){
	struct Node* n = g->adjlists[s];
	while(n){
		if (n->vertex == d)
			return 1;
		n = n->next;	
	}
	return 0;

}

// SCC components
int d[100],f[100],t=0;
void dfs(struct Graph* g,int u,struct Stack* s){
	g->visited[u] = 1;
	d[u] = t++;
	struct Node* n = g->adjlists[u];
	while(n){
		int v = n->vertex;
		if (!g->visited[v]){
			g->visited[v] = 1;
			dfs(g,v,s);		
		}
		n = n->next;	
	}
	f[u] = t++;
	push(s,u);
}

void dfs_rec(struct Graph* g,struct Stack* s){
	unvisit(g);
	int i=0;
	for(i=0;i<g->V;i++){
		if (!g->visited[i])
			dfs(g,i,s);
	
	}
}


struct Graph* CreateGT(struct Graph* g){
	int i=0;
	struct Graph* gt = CreateGraph(g->V);
	for(i=0;i<g->V;i++){
		struct Node* n = g->adjlists[i];
		while(n){
			int v = n->vertex;
			AddEdge(gt,v,i);
			n = n->next;
		}
	}
	unvisit(g);
	return gt;
}

void DFS(struct Graph* g,int u){
	g->visited[u] = 1;
	printf("%d ",u);
	struct Node* n = g->adjlists[u];
	while(n){
		int v = n->vertex;
		if (!g->visited[v]){
			g->visited[v] = 1;
			DFS(g,v);
		}
		n = n->next;	
	}

}

void findSCC(struct Graph* g){
	struct Stack* s = CreateS(g->V);
	int i=0;
	dfs_rec(g,s);
	unvisit(g);
	struct Graph* gt = CreateGT(g);
	printf("\nThe Strongly Connected Components of the Graph are : \n");
	while(!isEmpty(s)){
		int v = pop(s);
		if (!gt->visited[v]){
			DFS(gt,v);
			printf("\n");
		}
	
	}

}



int main(){
	srand(time(NULL));
	int V,i,k,x;
	/*
	printf("Enter the no of vertices = ");
	scanf("%d",&V);	
	struct Graph* g = CreateGraph(V);	
	// Creating a random Connected Graph
	int degree = 1;
	for(i=0;i<V;i++){
		k=0;
		while(k!=degree){
			x = rand()%V;			
			if (!isEdge(g,i,x) && x!=i){
				AddEdge(g,i,x);
				k++;
			} 
		}		
			
	}
	*/
	
	V = 5;
    	struct Graph* g = CreateGraph(V);
    	AddEdge(g,2,1);
    	AddEdge(g,1,0);
    	AddEdge(g,0,2);
    	AddEdge(g,0,3);
    	AddEdge(g,3,4);
    
	display(g);
	findSCC(g);
	
	return 0;
}


