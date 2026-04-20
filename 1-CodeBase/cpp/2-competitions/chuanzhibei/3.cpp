#include<bits/stdc++.h>
using namespace std;

//97 65 32
//a  A  a-A;
bool arr[510];
bool is(int num){
		 int sum=0;
		 while(num){
			    if(num%2)sum++;
			    num/=2;
		 }
		 return sum%2;
}
void numlist(){
		 for(int i=0;i<=505;i++){
         if(is(i))arr[i]=true;
         else arr[i]=false;
		 }
}
void solve(){
		 string s;
		 cin>>s;
		 int len=s.length();
		 numlist(); 
		 for(int i=0;i<len;i++){
		     if(arr[i+1]){
				    char ch=s[i]-32;
			      cout<<ch; 
		     }
		     else cout<<s[i];
		 }
		 cout<<endl;
}
int main(){
		ios::sync_with_stdio(0);
		cin.tie(0),cout.tie(0);
		int n;cin>>n;
		while(n--)solve(); 

		return 0;
} 
