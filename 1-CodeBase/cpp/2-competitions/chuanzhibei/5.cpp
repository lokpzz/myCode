#include<bits/stdc++.h>
using namespace std;

using ll=long long;
const int N=1e5+10;
ll arr[N];
ll num[N];
bool cmp(ll a,ll b){
		 return a>b;
}
int main(){
		ios::sync_with_stdio(0);
		cin.tie(0),cout.tie(0);
	  int n;cin>>n;
	  for(int i=1;i<=n;i++)cin>>arr[i];
	  sort(arr+1,arr+1+n,cmp);
	  int ca= INT_MAX;
	  for(int i=1;i<n;i++){
			  int cc=arr[i]-arr[i+1];
				ca=min(ca,cc);
				num[i]=cc;
		}
	  if(ca==1)cout<<1<<" "<<0;
		else if(ca==2){
				 for(int i=1;i<=n;i++){
				     if(num[i]%2){
						 cout<<1<<" "<<0;
						 return 0;
						 }
				 }
				 if(arr[1]%2)cout<<2<<" "<<1;
				 else cout<<2<<" "<<0;
		}
		else if(ca%2==0){
				 for(int i=1;i<=n;i++){
				     if(num[i]%2){
						 cout<<1<<" "<<0;
						 return 0;
						 }
				 }
				 if(arr[1]%2)cout<<2<<" "<<1;
				 else cout<<2<<" "<<0;
		}
		return 0;
} 








