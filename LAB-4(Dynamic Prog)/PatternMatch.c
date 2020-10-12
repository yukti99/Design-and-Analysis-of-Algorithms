#include <stdio.h>
#include <string.h>

// KMP Algorithm
void LPS(char *pat,int m,int *lps){
	
	
	int len = 0,i = 1;
	lps[0] = 0;
	while(i<m){
		if (pat[i] == pat[len]){
			len++;
			lps[i] = len;	
			i++;			
		}
		else{
			if (len!=0){
				len = lps[len-1];
			}
			else{
				lps[i] = 0;
				i++;
			}
		}
	}	
}

void PatMatch(char *text,char *pat){
	int t=0,p=0;
	int n = strlen(text);
	int m = strlen(pat);
	int lps[m];
	LPS(pat,m,lps);
	while(t<n){
		if (text[t] == pat[p]){
			p++;
			t++;		
		}
		if (p == m){
			printf("Pattern appears in text at shift = %d\n",t-p);
			p = lps[p-1];
		}
		else if (t < n && pat[p] != text[t]){
			if (p!=0)
				p = lps[p-1];
			else
				t++;
								
		}
		
	}
}

int main(){
	int i=0,n=0,m=0;
	char text[50],pat[25];
	printf("Enter the text = ");
	scanf("%s",text);
	printf("Enter the Pattern = ");
	scanf("%s",pat);
	PatMatch(text,pat);
	
}
