#include<bits/stdc++.h>
using namespace std;
class node{
    public:
    int data;
    node *prev;
    node *next;
    node(int x){
        data=x;
        prev=NULL;
        next=NULL;
    }
};
unordered_map <int,pair<node *,int>> hm;
node *h=new node(0);
node *t=h;
int k;
    
void LRUCache(int capacity) {
        k=capacity;
    }
void helper(int key,int val){
    auto w=hm[key];
            node *x=w.first;
            
            if(x!=t){
                if(x==h->next){
                    node *o=new node(0);
                node *u=h->next->next;
                    o->next=u;
                    h=o;
            }
            node *p=x->prev;
            p->next=p->next->next;
            node *q=p;
            p=p->next;
            p->prev=q;
            t->next=x;
            x->prev=t;
            x->next=NULL;
            t=t->next;
            }
            hm[key]={t,val};
}
    
int get(int key){
    if(hm.find(key)==hm.end())
        return -1;
    auto w=hm[key];
    helper(key,w.second);
    return w.second;  
}
void put(int key,int val){
    if(k==0)
        return;
    if(hm.find(key)==hm.end() && hm.size()<k){
            node *p=new node(key);
            hm.insert({key,{p,val}});
            p->prev=t;
            t->next=p;
            t=t->next;
        }
        else if(hm.find(key)!=hm.end()){
            helper(key,val);
        }
        else{
            
            node *p=new node(key);
            int x=h->next->data;
            hm.erase(x);
            hm.insert({key,{p,val}});
            t->next=p;
            p->prev=t;
            t=t->next;
            h->next=h->next->next;
        }
}
int main(){
int y;
cin>>y;
LRUCache(y);
//n is the number of inputs to the problem
int n;
cin>>n;
for(int i=0;i<n;i++){
    string s;
    cin>>s;
    if(s=="get"){
        int a;
        cin>>a;
        cout<<get(a)<<"\n";
    }
    if(s=="put"){
    int a,b;
    cin>>a>>b;
    put(a,b);
    }    
}
}