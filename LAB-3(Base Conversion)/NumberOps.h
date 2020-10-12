

struct Number{
        int base;
        int converted;
        char *value;
};
int countLines(FILE *fp){
        int c = 0;
        char ch;
        for (ch = getc(fp); ch != EOF; ch = getc(fp)) 
                if (ch == '\n')
                        c++;
        return c;
}
int ToDecimal(struct Number *n){
	int i=0,b = n->base;
	int l = strlen(n->value);
	int d = 0,k=0;
	for(i=l-1;i>=0;i--){
		int v = lookup(base,maxD,n->value[i]);		
		d += pow(b,k++)*v;		
	}
	return d;
}

char* reverse(char* ch){
	char* rev = (char*)malloc(sizeof(char)*50);
	int i=0,k=0;
	for(i=strlen(ch)-1;i>=0;i--){
		rev[k++] = ch[i];
	}
	rev[k] = '\0';
	return rev;
}
void printNumber(struct Number* n){
	printf("%s(%d)",n->value,n->base);
}

struct Number* convert(struct Number *n, int to_base){	
	int r=0,i=0;
	int b = to_base;
	int d = ToDecimal(n);
	char ch[50];	
	
	struct Number *c = (struct Number*)malloc(sizeof(struct Number));
	c->base = to_base;
	c->converted = d;
	
	while(d>0){
		r = d%b;
		d = d/b;
		ch[i++] = base[r];	
	}
	ch[i] = '\0';
	char* rev = reverse(ch);
		
	c->value = rev;	
	return c;	
}
struct Number* add(struct Number* a, struct Number* b){
	printf("\nAdding %s and %s\n",a->value,b->value);
	struct Number* temp = (struct Number*)malloc(sizeof(struct Number));
	
	int sum = a->converted + b->converted ;
	
	int r=0,bs = a->base,i=0;
	temp->base = bs;
	
	char ch[50];
	while(sum>0){
		r = sum%bs;
		sum = sum/bs;
		ch[i++] = base[r];
				
	}
	ch[i] = '\0';
	char* rev = reverse(ch);
	temp->value = rev;
	temp->converted = sum;
	
	return temp;	
}
struct Number* subtract(struct Number* a, struct Number* b){
	printf("\nSubtracting %s and %s\n",a->value,b->value);
	struct Number* temp = (struct Number*)malloc(sizeof(struct Number));
	
	int diff = abs(a->converted - b->converted);
	
	int r=0,bs = a->base,i=0;
	temp->base = bs;
	
	char ch[50];
	while(diff>0){
		r = diff%bs;
		diff = diff/bs;
		ch[i++] = base[r];
				
	}
	ch[i] = '\0';
	char* rev = reverse(ch);
	temp->value = rev;
	temp->converted = diff;
	
	return temp;	
}
struct Number* AnalyseOperation(){

	
	struct Number *n1 = (struct Number*)malloc(sizeof(struct Number));
        struct Number *n2 = (struct Number*)malloc(sizeof(struct Number)); 
        n1->value = (char*)malloc(sizeof(char)*50);
        n1->converted = 0;
        n2->value = (char*)malloc(sizeof(char)*50);
        n2->converted = 0;
        
        
        char s[50],v1[20],v2[20];
        int i,b1,b2,c=2;


        fscanf(fp2,"%s",s);
        
        while(c!=0){       	
        	fscanf(fp2,"%d %s",&b1,v1);
        	fscanf(fp2,"%d %s",&b2,v2); 	
        	c--;         
        }
        if (b1 > maxD || b2 > maxD){
        	printf("Error! Base of the number is greater than maximum base allowed!\n");
        	exit(EXIT_FAILURE);
        }
        n1->base = b1;
        n2->base = b2;
        n1->value = v1;
        n2->value = v2;
        
        struct Number *x = NULL;
        struct Number *y = NULL;
        struct Number *result  = NULL;
        
        // Converting smaller to larger base
        if (b1>b2){
        	x = convert(n2,b1);
        	y = convert(n1,b1);    	
        	
       	}
        else{
        	x = convert(n1,b2);
        	y = convert(n2,b2);
        	
       	} 
       	
       	if (s[0] == 'a'){
       		result = add(x,y);
       		fprintf(fout,"\n\t%s(%d) + %s(%d) = %s(%d)\n",n1->value,n1->base,n2->value,n2->base,result->value,result->base);
       		printNumber(n1);
       		printf(" + ");
       		printNumber(n2);
       		printf(" = ");
       		printNumber(result);
       		printf("\n"); 
       	}		
       	 
        else{
        	
        	result = subtract(x,y);
        	fprintf(fout,"\n\t%s(%d) - %s(%d) = %s(%d)\n",n1->value,n1->base,n2->value,n2->base,result->value,result->base);
        	printNumber(n1);
       		printf(" - ");
       		printNumber(n2);
       		printf(" = ");
       		printNumber(result);
       		printf("\n"); 
        }   
   
}

void createNumber(){  
                
        int count=0;        
        fp2 = fopen("Input.txt","r");
        if (!fp2){
                printf("\nError!! \"Input.txt\" File Opening Failed\n");
                exit(EXIT_FAILURE);
        }  
        
        count = countLines(fp2);
        count /= 3;
	fseek(fp2,0,SEEK_SET);	
       	fout = fopen("Output.txt","w");
        while(count!=0){         	
        	AnalyseOperation(fp2);	     	              
                count--;     
        } 
        fclose(fout); 
 }
