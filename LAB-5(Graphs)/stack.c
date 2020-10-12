#include <stdio.h>
#include <stdlib.h>
#include <limits.h>


struct Stack{
	
	int top;
	int size;
	int *a;
	
};

struct Stack *CreateS(int size){
	struct Stack *s = (struct Stack*)malloc(sizeof(struct Stack));
	s->top = -1;
	s->size = size;
	s->a = (int*)malloc(sizeof(int)*size);
	return s;
}

int isFullS(struct Stack *s){
	return (s->top == s->size -1) ;
}
	

int isEmptyS(struct Stack *s){
	return (s->top == -1);
}
	
	
void push(struct Stack *s,int item){	
	if (isFullS(s))
		return ;
	s->a[++s->top] = item;
		
}

int pop(struct Stack *s){
	if (isEmptyS(s))
		return INT_MAX;	
	return s->a[s->top--];
}
/*
void displayS(struct Stack *s){
	if (isEmptyS(s))	
		return ;	
	int c = s->top ;
	int i=0;
	for(i = s->top; i>=0 ; i--)
		printf("%d\n",s->a[i]->data);
	
	printf("\n");
}
int peekS(struct Stack *s){
	
	if (isEmptyS(s))
		return INT_MAX;
	return s->a[s->top];
}
*/

