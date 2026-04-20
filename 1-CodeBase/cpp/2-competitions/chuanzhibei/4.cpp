#include<bits/stdc++.h>
using namespace std;

int main(){
		ios::sync_with_stdio(0);
		cin.tie(0),cout.tie(0);
		string s;cin>>s;
		int ans=0;
		for(int i=0;i<s.length();i++){
						int sum=1;
						while(s[i]==s[i+1])sum++,i++;
						ans=max(ans,sum);
		} 
		int r=s.length()-1,l=0;
		char ch=s[0];
		int tmp=0;
		if(s[0]==s[s.length()-1]){
			 for(;l<r;){
			     if(s[l]==ch)tmp++,l++;
			     if(s[r]==ch)tmp++,r--;
			     if(s[l]!=ch&&s[r]!=ch)break;
			 }
		}
		ans=max(ans,tmp);
		cout<<ans;
		return 0;
} 
