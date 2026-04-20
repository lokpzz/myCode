#include<bits/stdc++.h>
using namespace std;

const int N=2e5+10;
using ll=long long;
vector<pair<ll,ll>> arr(N+10);
bool cmp(pair<ll,ll> a,pair<ll,ll> b){
		 if(a.first==b.first){
         return a.second<b.second;
		 }
		 return a.first>b.first;
}
int main(){
		ios::sync_with_stdio(0);
		cin.tie(0),cout.tie(0);
		int n,k;
		cin>>n>>k;
		for(int i=1;i<=n;i++)cin>>arr[i].second;
		for(int i=1;i<=n;i++)cin>>arr[i].first;
		sort(arr.begin()+1,arr.begin()+n+1,cmp);
		ll tsum=0,ssum=0;
		for(int i=1;i<=k;i++){
						tsum+=arr[i].first;
						ssum+=arr[i].second;
		}
		cout<<ssum<<" "<<tsum;
		return 0;
} 
