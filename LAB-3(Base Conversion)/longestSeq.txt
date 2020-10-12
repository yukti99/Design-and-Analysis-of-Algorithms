// C++ program to print the longest increasing subsequence in an array
#include <bits/stdc++.h>
using namespace std;

int main(){
	
	int i,j,n;
	cout<<"Enter the number of elements = ";
	cin>>n;
	int a[n],l[n];
	for(i=0;i<n;i++){
		cin>>a[i];
		l[i] = 1;
	}
	
	vector < vector<int> > L(n) ;
	L[0].push_back(a[0]);
	
	for(i=1;i<n;i++){
		for(j=0;j<i;j++){
			if (a[i] > a[j] && L[i].size() < L[j].size()+1){
				l[i] = l[j] + 1;
				L[i] = L[j];				
			}
		}
		L[i].push_back(a[i]);
	}
	int max = a[0];
	for(i=0;i<n;i++){
		if (max < l[i])
			max = l[i];
	}
	int m = L[0].size(),pos=0;
	for(i=0;i<n;i++){
		int p = L[i].size();
		if (m<p){
			pos = i;
			m = p;			
		}		
	}	
	cout<<"\nThe Longest Increasing Subsequence is of length =  "<<max<<endl;
	cout<<"\nThe Sequence is :\n";
	for(i=0;i<L[pos].size();i++){
		cout<<L[pos][i]<<" ";
	}
	cout<<endl;
	
}


