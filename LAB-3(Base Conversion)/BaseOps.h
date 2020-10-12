
int lookup(char a[],int n,char x){
        int i=0;
        for(i=0;i<n;i++){
                if (a[i] == x)
                        return i;
                
        }        
}

int initializeBase(FILE *fp1){        
        fp1 = fopen("chars.txt","r");
        if (!fp1){
                printf("\nError!! \"chars.txt\" File Opening Failed\n");
                exit(EXIT_FAILURE);
                
        }
        while(ch!=EOF){
                ch = fgetc(fp1);
                if (isalnum(ch)){
                        base[k++] = ch;
                        maxD++;
                }                              
            
                                
        }
        base[k] = '\0';
        fclose(fp1);
        return maxD;
}

