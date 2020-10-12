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
	int *indegree;
	struct Node** adjlists;
};

struct Graph* CreateGraph(int V){
	struct Graph* g = (struct Graph*)malloc(sizeof(struct Graph));
	g->V = V;
	g->visited = (int*)malloc(sizeof(int)*V);
	g->indegree = (int*)malloc(sizeof(int)*V);
	g->adjlists = (struct Node**)malloc(sizeof(struct Node*)*V);
	int i=0;	
	for(i=0;i<V;i++){
		g->visited[i] = 0;
		g->indegree[i] = 0;
		g->adjlists[i] = NULL;	
	}
	return g;
}

// directed graph
void AddEdge(struct Graph* g,int s,int d){
	struct Node* n = CreateNode(d);
	n->next = g->adjlists[s];
	g->adjlists[s] = n;
	g->indegree[d]++;
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
int isEdge(struct Graph* g,int x,int y){
	struct Node* n = g->adjlists[x];
	while(n){
		if (n->vertex == y)
			return 1;
		n = n->next;
	
	}
	return 0;

}

void dfs(struct Graph* g,int s,struct Stack* st){
	g->visited[s] = 1;
	struct Node* n = g->adjlists[s];
	while(n){
		int v = n->vertex;
		if (!g->visited[v]){
			g->visited[v] = 1;
			dfs(g,v,st);
		
		}
		n = n->next;
	
	}
	push(st,s);

}

void TS(struct Graph* g){
	unvisit(g);
	int i=0;
	struct Stack *s = CreateS(g->V);
	for(i=0;i<g->V;i++){
		if (!g->visited[i]){
			dfs(g,i,s);
		}
	
	}
	while(!isEmpty(s)){
		printf("%d ",pop(s));	
	}
	printf("\n");

}
/*
int isCyclic(struct Graph* g,int v,int parent){
	g->visited[v] = 1;
	struct Node *n = g->adjlists[v];
	while(n){
		int a = n->vertex;
		if (g->visited[a] == 0){
			if (isCyclic(g,a,v))
				return 1;
		}
		// a visited adjacent not a parent of current vertex
		else if (a!=parent){
			return 1;
		}
		n = n->next;	
	
	}
	return 0;

}

// Detection of Cycle in Graph
int CycleInGraph(struct Graph* g){
	int i=0,u;
	unvisit(g);
	for(i=0;i<g->V;i++){
		if (g->visited[i] == 0){
			if (isCyclic(g,i,-1))
				return 1;
		}
	
	}
	return 0;
}*/
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
	
	int V,i,k,x;
    /*
    // To create graph entered by user
    printf("Enter the no of vertices = ");
    scanf("%d",&V);
    struct Graph* g = CreateGraph(V);  
    while(1){
        printf("\n\n");
        printf("1. Insert an Edge\n");
        printf("2. Display Graph\n");
        printf("3. BFS Traversal \n");
        printf("4. Quit \n");
        printf("\n\n");
        printf("\nEnter your choice : \n");
        scanf("%d", &c);
        printf("\n");
        switch (c){
            case 1:
            	printf("Enter the vertices : ");
            	scanf("%d %d",&x,&y);
            	if (x<V && x>=0 && y<V && y>=0)
            	    AddEdge(g,x,y); 
                else
                    printf("\nWrong Edges!!\n");   	
            	break;
            case 2:
			    display(g); 
            	break;
            case 3:
                printf("\nEnter starting point  : ");
            	scanf("%d",&s);   
            	printf("\nThe BFS Traversal of the Graph : \n");  
            	BFS(g,s);			    
			    unvisit(g);
            	break; 
            case 4:
                printf("\nThank you!!\n");
                exit(0);
            default:
                printf("Wrong Choice!\n");      
     
       }
    }  */
    V = 6;
	struct Graph* g = CreateGraph(V);
	AddEdge(g,5,2); 
	AddEdge(g,5,0);
	AddEdge(g,4,0);
	AddEdge(g,4,1);
	AddEdge(g,2,3);
	AddEdge(g,3,1);
	//AddEdge(g,3,5);
	
	display(g);
	unvisit(g);
	if (DetectCycle(g))
		printf("Cycle in Graph ! Topological sort not possible!\n");
	else{
		printf("\nThe Topological Sort : \n");
		TS(g);	
	}
	
	return 0;
}


