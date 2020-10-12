#include <stdio.h>
#include <stdlib.h>
#include <limits.h>


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

//---------------------------------------------------------------------------------------------
struct Node{
    int vertex;
    struct Node* next;
};

struct Node* CreateNode(int v){
    struct Node* n = (struct Node*)malloc(sizeof(struct Node));
    n->next = NULL;
    n->vertex = v;
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
    g->adjlists =  (struct Node**)malloc(sizeof(struct Node*)*V);
    int i=0;
    for(i=0;i<V;i++){
        g->visited[i] = 0;
        g->adjlists[i] = NULL;    
    }
    return g;
}
// directed graph
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
// -----------------------------------------------------------------------------------------------


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

int main(){
    int i,V,c,x,y,s;
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
    V = 5;
    struct Graph* g = CreateGraph(V);  
    AddEdge(g,0,1);
    AddEdge(g,0,4);
    AddEdge(g,1,3);
    AddEdge(g,2,1);
    AddEdge(g,3,2);
    AddEdge(g,4,1);
    display(g);
    printf("\nEnter starting point  : ");            	
    scanf("%d",&s);  
    printf("\nThe BFS Traversal of the Graph : \n");  
    BFS(g,s);	
    printf("\n");		  
    unvisit(g); 
    
}
