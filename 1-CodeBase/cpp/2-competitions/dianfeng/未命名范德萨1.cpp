#include<bits/stdc++.h>
using namespace std;

int vecs[1000][1000];
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
										if(vecs[j][i])cnt++;
						}
		} 
		cout<<cnt; 
		return 0;
} 
