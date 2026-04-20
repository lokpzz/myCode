#include<bits/stdc++.h>
using namespace std;

int ans=0;
int arr[20];
vector<pair<int,int>> tc(3);
int istc[3];
bool cmp(pair<int,int> a,pair<int,int> b){
		 if(a.second>b.second)return a.first>b.first;
}
bool is(){
		 if(istc[0]==tc[0].first
		 &&istc[1]==tc[1].first
		 &&istc[2]==tc[2].first){
		 ans++;
		 for(int i=0;i<3;i++)istc[i]=0;
		 }
}
int main(){
		
		int a,b,c;
		cin>>a>>b>>c;
		tc[0].first=a;
		tc[1].first=b;
		tc[2].first=c;
		int at,bt,ct;
		cin>>at>>bt>>ct;
		tc[0].second=at;
		tc[1].second=bt;
		tc[2].second=ct;
		sort(tc.begin(),tc.end(),cmp);
		int n;
		cin>>n;
		for(int i=0;i<n;i++){
						cin>>arr[i];
		}
		sort(arr,arr+n,greater<int>());
		for(int i=0;i<n;i++){
						int sum=0;
						int pos;
						while(sum+tc[pos].second>=arr[i]){
						for(pos=0;pos<3;pos++){
						//判断在arr[i]内，尽可能的塞进更多的品类 
										while(sum+tc[pos].second<=arr[i]
										&&istc[pos]<tc[pos].first){
										sum+=tc[pos].second;
										istc[pos]++;
										is();
										}
						}
						is();
						}
		}
	 	cout<<ans;
		return 0;
} 
