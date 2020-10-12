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
int d[100],f[100],t=0;
void DFS(struct Graph* g,int u,struct Stack* s){
	int i=0;
	g->visited[u] = 1;
	d[u] = t++;
	struct Node* n = g->adjlists[u];
	while(n){
		int v = n->vertex;
		if (!g->visited[v]){
			g->visited[v] = 1;
			DFS(g,v,s);		
		}
		n = n->next;	
	}
	f[u] = t++;
	push(s,u);

}

void  TS(struct Graph* g){
	struct Stack* s = CreateS(g->V);
	int i = 0;
	for(i=0;i<g->V;i++){
		if (!g->visited[i]){
			DFS(g,i,s);
		}	
	
	}
	while(!isEmpty(s)){
		int v = pop(s);
		printf("%d ",v);	
	}
}
void indegree(struct Graph* g){
    int i=0;
    printf("\nThe indegrees of vertices\n");
    for(i=0;i<g->V;i++){
        printf("%d - %d\n",i,g->indegree[i]);
    }
    printf("\n");
}

void print(int t[],int n){
    int i=0;
    for(i=0;i<n;i++)
        printf("%d ",t[i]);
    printf("\n");

}

void AllTopSorts(struct Graph* g,int ts[],int k,int d[]){
    int flag = 0,i,v;
    for(i=0;i<g->V;i++){    
        if (!g->visited[i] && g->indegree[i]==0){
            struct Node* n = g->adjlists[i];
            indegree(g);
            while(n){
                v = n->vertex;
                g->indegree[v]--;
                n = n->next;
            
            }  
            indegree(g);      
            printf("\nk = %d\n",k);
            ts[k++] = i;
            print(ts,g->V);
            g->visited[i] = 1;
            AllTopSorts(g,ts,k,d);
            
            // reseting after returning of functions
            g->visited[i] = 0;
            k=0;
            //for(i=0;i<g->V;i++)
                //ts[i] = 0;
            //for(i=0;i<g->V;i++)
               // g->indegree[i] = d[i];
            printf("\ni = %d\n",i);
            n = g->adjlists[i];
            while(n){
                    v = n->vertex;
                    g->indegree[v]++;
                    n = n->next;
            
            } 
            indegree(g); 
            flag = 1;  
       }           
    
    }
    if (flag == 0){
        for(i=0;i<g->V;i++)
            printf("%d ",ts[i]);
        printf("\n");
    }
   

}

void TimeStamps(struct Graph* g){
	printf("\nThe Disovery and Finishing time of all vertices in Graph : \n");	
	printf("Vertex\t\tDiscovery\tFinish\n");
	int i=0;
	for(i=0;i<g->V;i++){
		printf("%d\t\t%d\t\t%d\n",i,d[i],f[i]);	
	}
	printf("\n");
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
	display(g);
	unvisit(g);
	printf("\nThe Topological Sort : \n");
	//TS(g);	
	struct Stack* s = CreateS(V);
	k=0;
	int ts[V],d[V];
	for(i=0;i<V;i++){
	    ts[i] = 0;
	    d[i] = g->indegree[i];
    }   
	AllTopSorts(g,ts,k,d);
	TimeStamps(g);
	return 0;
}


