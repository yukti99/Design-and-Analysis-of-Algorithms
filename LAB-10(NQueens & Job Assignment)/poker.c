#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>

#define hand 5

// poker

int WScore = 0;
int BScore = 0;

// returns 1 for black
// returns 2 for white

void Sort(int a[],int n){
	int i=0,j=0;
	for(i=0;i<n;i++){
		for(j=0;j<n-i-1;j++){
			if (a[j] > a[j+1]){
				int t = a[j];
				a[j] = a[j+1];
				a[j+1] = t;
			}
		}
	}


}

void print(int a[],int n){
	int i=0;
	for(i=0;i<n;i++)
		printf("%d ",a[i]);
	printf("\n");
}




// High card
void HighCard(int B[],int W[],int i,int j){

	while(i>0 || j>0){
		if (B[i] > W[j]){
			BScore += 1;
				break;
		}
		
		else if (B[i]<W[j]){
			WScore += 1;
				break;
		}
		else{
			i--;
			j--;
		}
	}
	
}
// three of a kind
int CountofCards(int a[]){
	int i=0,count=0;
	for(i=0;i<=3;i++){
		if (a[i] == a[i+1])
			count++;
	}
	if (count)
		return count;
	else 
		return 0;

}
// count occurence of each card
int count(int a[],int x){
	int c=0,i;
	for(i=0;i<5;i++){
		if (a[i] == x)
			c++;
	}
	return c;
	
}

// find which card is repeated 3 times
int find3(int a[]){
	int i=0;
	for(i=0;i<5;i++){
		if (count(a,a[i]) == 3)
			return a[i];
	}
	return 0;
}
// find which card is repeated 2 times
int find2(int a[]){
	int i=0;
	for(i=0;i<5;i++){
		if (count(a,a[i]) == 2)
			return a[i];
	}
	return 0;
}


// finds no of pairs

int noPairs(int a[]){
	int i=0,pairs=0;
	while(i<4){
		if (count(a,a[i]) == 2){
			pairs++;
			while(a[i+1] == a[i] && i<5){
				i++;
				printf("i = %d\n",i);
				
			}
			
				
		}
	}
	return pairs;

}

int isPair(int a[]){
	int i=0,p=0;
	for(i=0;i<5;i++){
		if (count(a,a[i]) == 2){
			p=a[i];
			break;
		}
	}
	return p;
}

void Pair(int B[],int W[]){
	int b = isPair(B);
	BScore += b;
	int w = isPair(W);
	WScore += w;
	
}
// find if  3 same cards present
int isthree(int a[]){
	int i=0,t=0;
	for(i=0;i<5;i++){
		if (count(a,a[i]) == 3){
			t=1;
			break;
		}
	}
	return t;
}

int ThreeOfKind(int B[],int W[]){	
	int b = CountofCards(B);
	int w = CountofCards(B);
	if (b == 3 && w == 3){
		BScore += find3(B);
		WScore += find3(W);
	}
	return 1;

}

// Straight
bool Straight(int a[]){
	int i=0;
	for(i=0;i<hand-1;i++){
		if (a[i+1] == a[i]+1)
			continue;
		else
			return false;
	}
	return true;
}
// priority 5
int StraightHands(int B[],int W[]){
	int i=0;
	bool b = Straight(B);
	bool w = Straight(W);
	if (b == true && w == false)
		BScore += 5;
	else if (b == false && w == true)
		WScore += 5;
	else if (b==true && w == true){
		HighCard(B,W,4,4);
	}

}
// FLUSH
int isFlush(char a[]){
	int i=0;
	for(i=0;i<4;i++){
		if (a[i+1] == a[i])
			continue;
		else
			return 0;
		
	}
	return 1;
}

// priority 6
int Flush(int B[],int W[],char BS[],char WS[]){
	int b = isFlush(BS);
	int w = isFlush(WS);
	if (b && !w)
		BScore += 6;
	else if (!b && w)
		WScore += 6;
	else if (b==1 && w==1){
		HighCard(B,W,4,4);
	}
}

// FULL HOUSE 
int isFullHouse(int a[]){
	int t = isthree(a);
	int y=0;
	if (t){
		y = find3(a);
	}
	int p = isPair(a);
	if (t==1 && p==1){
		return y;
	}
	return 0;
}
void FullHouse(int B[],int W[]){
	int b = isFullHouse(B);
	BScore += b;
	int w = isFullHouse(W);
	WScore += w;
}

// Four of a kind

int isFour(int a[]){
	int i=0,f=0;
	for(i=0;i<5;i++){
		if (count(a,a[i]) == 4){
			f=a[i];
			break;
		}
	}
	return f;
	

}
void FourKind(int B[],int W[]){
	int b = isFour(B);
	BScore += b;
	int w = isFour(W);
	WScore += w;
	
}



//Straight Flush
int isStraightFlush(char as[],int a[]){
	if (isFlush(as)){
		if (Straight(a)){
			return a[4];
		}
			
	
	}
	return 0;
}

int StraightFlush(int B[],int W[],char BS[],char WS[]){
	int b = isStraightFlush(BS,B);
	BScore += b;
	int w = isStraightFlush(WS,W);
	WScore += w;
	

} 


int WhoWins(int B[],int W[],char BS[],char WS[]){

	Sort(B,hand);
	//print(B,hand);
	Sort(W,hand);
	//print(W,hand);
	
	StraightFlush(B,W,BS,WS);
	FourKind(B,W);
	FullHouse(B,W);
	Flush(B,W,BS,WS);
	StraightHands(B,W);
	if(ThreeOfKind(B,W)!=1)
		HighCard(B,W,hand-1,hand-1);
	
	if (BScore > WScore)
		printf("Black Wins.\n");
	else if (BScore < WScore)
		printf("White Wins.\n");
	else
		printf("Tie\n");
	

}


void printScore(){
	printf("\nBLACK SCORE = %d\n",BScore);
	printf("WHITE SCORE = %d\n\n",WScore);
}

int main(){
	
	int B[hand],W[hand];
	char BS[hand],WS[hand];
	FILE *fp;
	fp = fopen("input.txt","r");
	char c[1000];
	int i=0;
	int b=0,w=0;	
	fscanf(fp,"%[^\n]", c);
	printf("\nHANDS : \n%s\n\n",c);
	int x,y,j;
	int u=0,v=0;
	for(i=0,j=1;i<=13;i=i+3,j=j+3){
		if (c[i] == 'A')
			x = 14;
		else if (c[i] == 'K')
			x = 13;
		else if (c[i] == 'Q')
			x = 12;
		else if (c[i] == 'J')
			x = 11;
		else if (c[i] == 'T')
			x = 10;
		else
			x = c[i]-48;		
		y = c[j];
		//printf("%d ",x);
		//printf("\n");
		//printf("%c ",y);
		B[b++] = x;
		BS[u++] = y;
	}
	for(i=15,j=16;i<=28;i=i+3,j+=3){
	
		if (c[i] == 'A')
			x = 14;
		else if (c[i] == 'K')
			x = 13;
		else if (c[i] == 'Q')
			x = 12;
		else if (c[i] == 'J')
			x = 11;
		else if (c[i] == 'T')
			x = 10;
		else
			x = c[i]-48;		
		
		y = c[j];
		//printf("%d ",x);
		//printf("\n");
		//printf("%c ",y);
		W[w++] = x;
		WS[v++] = y;
		
	}	
	for(i=0;i<5;i++){
		printf("%d ",B[i]);
	}
	printf("\n");
	for(i=0;i<5;i++){
		printf("%d ",W[i]);
	}
	printf("\n");
	WhoWins(B,W,BS,WS);
	printScore();
	
	
	return 0;
}
//char BS[] = {'D','H','H','H','H'};
//char WS[] = {'H','S','D','C','D'};
	

//printf("%d\n",HighCard(B,W,hand-1,hand-1));
	//printf("%d\n",noPairs(W));
	//ThreeOfKind(B,W);
	//printf("%d,%d\n",BScore,WScore);
	/*int a[] = {4,9,3,1,2};
	Sort(a,5);
	print(a,5);
	if (Straight(a))
		printf("yes\n");
	printf("%d\n",Straight(a));*/
	
	
	
	//StraightHands(B,W);
	//Flush(B,W,BS,BS);
	//FullHouse(B,W);
	//FourKind(B,W);
	//StraightFlush(B,W,BS,WS);
	//int a[] = {4,3,4,3,6};
	//Sort(a,5);
	//print(a,5);
	//printf("%d\n",noPairs(a));
	
	
	//int B[] = {2,4,4,2,4};
	//int W[] = {2,8,14,12,3,};
	//int B[] = {10,9,6,7,8};
	//int W[] = {1,2,5,4,3};
	
	/*
	2H 3D 5S 9C KD 2C 3H 4S 8C AH
	2H 4S 4C 2D 4H 2S 8S AS QS 3S
	2H 3D 5S 9C KD 2C 3H 4S 8C KH
	2H 3D 5S 9C KD 2D 3H 5C 9S KH
	*/

	//int B[] = {2,3,5,9,13};
	//int W[] = {2,3,4,8,14};
	//int B[] = {2,4,4,2,4};
	//int W[] = {2,8,14,12,3};
	//int B[] = {2,3,5,9,13};
	//int W[] = {2,3,4,8,13};
	//int B[] = {2,3,5,9,13};
	//int W[] = {2,3,5,9,13};
