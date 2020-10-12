#include <stdio.h>
#include <stdlib.h>

int sizeofArray = 0;
int Occupied = 0;

struct Node{

        int data;
        struct Node* next;
        int isFull;
};
struct Node* head = NULL;

struct Node* Create(int data){

        struct Node* n = (struct Node*)malloc(sizeof(struct Node));
        n->next = NULL;
        n->data = data;
        n->isFull = 0;
}
void insertNode(int item){
        struct Node* new_node = Create(item);
	struct Node* last = head;
	if (NULL == head){		
		head = new_node;
		return ;
	}
	while(NULL != last->next)
		last = last->next;
	last->next = new_node;	
}
struct Node* CreateArray(int x){
        int i;
        for(i=0;i<x;i++){
                insertNode(0);
        }
        sizeofArray+= x;
}
void printList(){
        printf("\n");
        struct Node* temp = head;
        while(temp!=NULL){
                if (!temp->isFull)
                        printf("NULL | ");
                else
                        printf("%d    | ",temp->data);
                temp = temp->next;
        }
        printf("\n");        
}

void insertElement(int item){
	struct Node* last = head;
	//printf("\nNo of elements occupied = %d\n",Occupied);
	//printf("\nSize = %d\n",sizeofArray);
	if (Occupied == 0){		
		head->data = item;
		head->isFull = 1;
		Occupied=1;
		return ;
	}
	else if (Occupied < sizeofArray){
	        while(0 != last->isFull)
		        last = last->next;
	        last->data = item;
		last->isFull = 1;
		Occupied++;
		return ;
	}
	else if (Occupied >= sizeofArray){
	        CreateArray(sizeofArray);
	        printList();
	        insertElement(item);        
	}	        
}
void deletePos(int position){
	int i=0;
	if (head == NULL)
		return ;	
	struct Node* temp = head;
	
	// head to be deleted
	if (position == 0){
		head = temp->next;
		free(temp);
		return ;
	}
	// find previous node of the node to  be deleted
	for(i=0; temp != NULL && i<position-1 ;i++)
		temp = temp->next;
	
	// if positon is more than number of nodes
	if (temp==NULL && temp->next== NULL)
		return;
	
	struct Node* next = temp->next->next ;
	free(temp->next);
	temp->next = next;
	return ;
	
}

void removeExtra(){
        //printf("\nRemoving Extras : \n");
        struct Node* temp = head,*prev = NULL;
        int x = sizeofArray/2,pos = 0;              
        while(sizeofArray > x || temp == NULL){
                //printf("size= %d,x = %d,pos =%d\n",sizeofArray,x,pos);  
                if (sizeofArray == pos)
                        break;             
                if (temp->isFull == 0){
                        deletePos(pos);
                        sizeofArray--;
                        pos--;
                        //printList();      
                }
                temp = temp->next;
                pos++;              
        }
        
}

struct Node* delete(int item){
        
        struct Node* temp = head,*prev = NULL;
        if (head == NULL)
                return NULL;        
  
        else if (Occupied >= sizeofArray/2){
                while(temp!=NULL && temp->data!=item){
                        prev = temp;
                        temp = temp->next;          
                           
                }
                if (temp == NULL){
                        printf("\nThe element does not exist in the array!!\n");
                        return NULL;
                }
                temp->data = 0;
                temp->isFull = 0; 
                Occupied--;     
        }
        if (Occupied == sizeofArray/2){ 
                printList();                
                removeExtra();
        }
        printf("\n%d Deleted : \n",item);
}
int main(){
        CreateArray(4);
        int c = 0,x;
        while(1){
                printf("\nEnter any choice : \n");
                printf("1. Insert \n");
                printf("2. Delete \n");
                printf("3. Print \n");
                printf("4. Quit \n\n");
                scanf("%d",&c);
                switch(c){
                        case 1 :
                                printf("\nEnter the element to insert = ");
                                scanf("%d",&x);
                                insertElement(x);
                                printf("\nAfter Inserting %d : \n",x);
                                printList();
                                break;
                        case 2 :
                                printf("\nEnter the element to delete = ");
                                scanf("%d",&x);
                                delete(x);
                                printList();
                                break;
                        case 3 :
                                printList();
                                break;
                        case 4 :
                                printf("\nThank You!!!\n");
                                return 0;
                        default:
                                printf("\nWrong Choice!\n");                          
                                
                              
                 }
        }
        return 0;
}
