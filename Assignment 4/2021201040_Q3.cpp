#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;
class node{
    public:
    node *ar[2];
    node(){
        ar[0]=NULL;
        ar[1]=NULL;
    }
    
};
bool checkbit(long long int x,long long int i){
    if((x>>i)&1){
        return true;
    }
    return false;
}
long long int solve(node *root,long long int bits,long long int a){
    long long int ans=0;
    for(long long int i=63;i>=0;i--){
        long long int b=(checkbit(a,i)==true)?1:0;
        
        long long int k;
        if(b==0){
            b=1;
            k=0;
        }
        else{
            b=0;
            k=1;
        }
        //cout<<b<<k<<" ";
        if(root->ar[b]!=NULL){
            ans+=1<<(i);
            //cout<<ans<<"\n";
            root=root->ar[b];
        }
        else{
            root=root->ar[k];
        }
    }return ans;
}
void insert(node *root,long long int x,long long int bits){
    for(long long int i=bits;i>=0;i--){
        long long int b=(checkbit(x,i)==true)?1:0;
        //cout<<b<<"";
        if(root->ar[b]==NULL){
            root->ar[b]=new node();
        }
        root=root->ar[b];
    }
}
int main() {

        node *root=new node();
        long long int n,q;
        cin>>n>>q;
        long long int a[n];
        long long int m=0;
        for(long long int i=0;i<n;i++){
            cin>>a[i];
            m=max(m,a[i]);
        }
        long long int bits=log2(m);
        for(long long int i=0;i<n;i++){
            insert(root,a[i],63);
        }
        for(long long int i=0;i<q;i++){
        long long int x;
        cin>>x;
        long long int ans=0;
        ans=max(ans,solve(root,bits,x));
        cout<<ans<<"\n";
        }
    /* Enter your code here. Read input from STDIN. Prlong long int output to STDOUT */   
    return 0;
}
