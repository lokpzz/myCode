#include<bits/stdc++.h>
using namespace std;

const int N=2e5+10;
const int M=3e5+10;
int vecs[N][N];
int main(){
		int n,m;
		cin>>n>>m;
		for(int i=1;i<=m;i++){
						int a,b;
						cin>>a>>b;
						vecs[a][b]++;
		}
		int cnt=0;
		for(int i=1;i<n;i++){
						for(int j=i+1;j<=n;j++){
										int a=i,b=j;
										if(vecs[b][i])cnt++;
						}
		} 
		cout<<cnt; 
		return 0;
} 
