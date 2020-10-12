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

// Queue implementation for BFS

struct Queue{
	int f,r;
	int size;
	int *a;
};

struct Queue* CreateQ(int size){
	struct Queue* q = (struct Queue*)malloc(sizeof(struct Queue));
	q->f = q->r = -1;
	q->size = size;
	q->a = (int*)malloc(sizeof(int)*size);
	return q;
}
int isEmptyQ(struct Queue* q){
	return (q->f == -1);
}
int isFullQ(struct Queue* q){
	return (q->r == q->size-1);
}
void Enqueue(struct Queue* q,int item){
	if (isFullQ(q))
		return ;
	if (q->f == -1)
		q->f = 0;
	q->a[++q->r] = item;

}
int Dequeue(struct Queue* q){
	if (isEmptyQ(q))
		return INT_MAX;
	int x = q->a[q->f++];
	if (q->f > q->r)
		q->f = q->r = -1;
	return x;
}
void displayQ(struct Queue* q){
	int i=0;
	printf("Queue : \n");
	for(i=q->f;i<=q->r;i++){
		printf("%d ",q->a[i]);	
	}
	printf("\n");

}
//---------------------------------------------------------------------------------------------


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
	
	struct Node* n1 = CreateNode(s);
	n1->next = g->adjlists[d];
	g->adjlists[d] = n1;	
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
int t = 0;
int d[100],f[100];
char color[100];

void dfs_visit(struct Graph* g,int u){
	g->visited[u] = 1;
	color[u] = 'G';
	d[u] = t++;
	struct Node* n = g->adjlists[u];
	while(n){
		int v = n->vertex;
		if (color[v] == 'W'){
			printf("(%d,%d) is a Tree Edge\n",u,v);
			dfs_visit(g,v);
		}
		else if (color[v] == 'G')
			printf("(%d,%d) is a Back Edge\n",u,v);		
		
		else if (color[v] == 'B'){
			if (d[u] < d[v])
				printf("(%d,%d) is a Forward Edge\n",u,v);
			
			else 
				printf("(%d,%d) is a Cross Edge\n",u,v);
		}	
		
		n = n->next;
	} 
	f[u] = t++;
	color[u] = 'B';

}

void ClassifyEdges(struct Graph* g){
	printf("\n\n");
	unvisit(g);
	int i=0;
	for(i=0;i<g->V;i++)
		color[i] = 'W';	
	
	for(i=0;i<g->V;i++){
		if (!g->visited[i]){
			dfs_visit(g,i);
		}	
	}
	unvisit(g);
}

// recursive DFS
void dfs(struct Graph* g,int s){
	g->visited[s] = 1;
	printf("%d ",s);
	d[s] = t++;
	struct Node* n = g->adjlists[s];
	while(n){
		int v = n->vertex;
		if (!g->visited[v]){
			g->visited[v] = 1;
			dfs(g,v);
		}
		n = n->next;	
	}
	f[s] = t++;
}



void dfsrec(struct Graph* g){
	int i=0;
	printf("\nDFS Traversal using Recursion : \n");
	for(i=0;i<g->V;i++){
		if (g->visited[i] == 0){
			dfs(g,i);
			printf("\n");
		}
			
	}
	unvisit(g);


}

	
	
// dfs using Stack
void DFS_stack(struct Graph* g,int s){
	printf("\nDFS Traversal using Stack : \n");
	struct Stack* st = CreateS(g->V);
	g->visited[s] = 1;
	push(st,s);	
	while(!isEmpty(st)){
		int v = pop(st);
		printf("%d ",v);		
		struct Node* n = g->adjlists[v];
		while(n){
			int a = n->vertex;
			if  (!g->visited[a]){
				g->visited[a] = 1;
				push(st,a);				
			}
			n = n->next;			
		}	
	}
	unvisit(g);

}
void TimeStamps(struct Graph* g){
	printf("\nThe Disovery and Finishing time of all vertices in DFS : \n");	
	printf("Vertex\t\tDiscovery\tFinish\n");
	int i=0;
	for(i=0;i<g->V;i++){
		printf("%d\t\t%d\t\t%d\n",i,d[i],f[i]);	
	}
	printf("\n");
}

//BFS using Queue
void BFS(struct Graph* g,int s){
	printf("\nBFS Traversal using Queue : \n");
	g->visited[s] = 1;
	struct Queue* q = CreateQ(g->V);
	Enqueue(q,s);
	while(!isEmptyQ(q)){
		int v = Dequeue(q);
		printf("%d ",v);
		struct Node* n = g->adjlists[v];
		while(n){
			int a = n->vertex;
			if (!g->visited[a]){
				g->visited[a] =1;
				Enqueue(q,a);
			}
			n = n->next;		
		}	
	}
	unvisit(g);

}
// Cycle detection
char c[100];
int isCyclic(struct Graph* g,int u){
	g->visited[u] = 1;
	c[u] = 'G';
	struct Node* n = g->adjlists[u];
	while(n){
		int v = n->vertex;
		if (!g->visited[v]){
			g->visited[v] = 1;
			if (isCyclic(g,v))
				return 1;
			
		}
		// back edge discovered
		else if (c[v] == 'G')
			return 1;
	
		n = n->next;	
	
	}
	c[u] = 'B';
	return 0;

}

int DetectCycle(struct Graph* g){
	int i=0;
	for(i=0;i<g->V;i++)
		c[i] = 'W';
	for(i=0;i<g->V;i++){
		if (!g->visited[i])
			if (isCyclic(g,i))
				return 1;
	
	}
	return 0;

}




int main(){
	srand(time(NULL));
	int V,i,k,x;
	printf("Enter the no of vertices = ");
	scanf("%d",&V);
	
	struct Graph* g = CreateGraph(V);	
	// Creating a random Connected Graph
	int degree = 1;
	for(i=0;i<V;i++){
		k=0;
		while(k!=degree){
			x = rand()%V;			
			if (!isEdge(g,i,x) && !isEdge(g,x,i) && x!=i){
				AddEdge(g,i,x);
				k++;
			} 
		}		
			
	}
	/*
	V = 5;
	AddEdge(g,0,1);
	AddEdge(g,1,2);
	AddEdge(g,3,4);
	AddEdge(g,0,3);
	
	*/
	display(g);
	dfsrec(g);
	//DFS_stack(g,0);
	TimeStamps(g);
	BFS(g,0);
	ClassifyEdges(g);	
	printf("\n");
	
	if (DetectCycle(g))
		printf("Yes! cyclic\n");
	else
		printf("No! Acyclic\n");
	unvisit(g);
	return 0;
}

