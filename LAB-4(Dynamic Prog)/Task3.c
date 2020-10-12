#include <stdio.h>
#include <string.h>

// counting the number of strings starting with 'X' and ending with 'Y'
// Time complexity of this Algo  = O(n)

int main(){

        char Text[100];
        char x,y;
        
        
        printf("\nEnter the String : ");
        scanf("%[^\n]%*c",Text);     
        printf("\nEnter the starting & ending char : ");
        scanf("%c %c",&x,&y);
             
               
        printf("\nThe Text : %s\n",Text);
        
        int len = strlen(Text);
        int i,j,cx=0,no=0;
        for(i=0;i<len;i++){
                if (Text[i] == x){
                        cx++;
                }
                else if (Text[i] == y){
                        if (cx!=0){
                                no+=cx;
                        }
                }
        }
        printf("Number of substrings in given Text starting with \'%c\' and ending in \'%c\' are = %d\n",x,y,no);        
        return 0;

}

