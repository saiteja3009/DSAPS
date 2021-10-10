#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <typeinfo>
#include <sstream>
#define m 100000
#define mod 100000007
using namespace std;
int size=0;

template <typename K,typename V>
class map{
public:
    class node{
    public:
    V val;
    K s;
    node *next;
    node(K y,V x){
        s=y;
        val=x;
        next=NULL;
        //right=NULL;
    }
};
string to_string(K key){
        ostringstream buffer;
        buffer << key;
        return buffer.str();
        }
node *arr[100000];
unsigned long long int GetHash(K st)
{string str=to_string(st);
 int len=str.length();
    unsigned long long int p = 41;
    unsigned long long int hash=0;
    
    for(int i=0;i<len;i++)
    {
        (hash) = (((hash)%mod) + (str[i]*((p)%mod))%mod)%mod;
        p = ((p%mod)*41)%mod;
    }
    
    return hash%m;
}

V operator[](K key){
    V y;
    auto hash=GetHash(key);
    if(arr[hash]!=NULL){
        node *temp=arr[hash];
        if(rabin(temp->s,key)==1){
            return temp->val;
        }
        else{
            while(temp!=NULL)
            {
                if(rabin(temp->s,key)==1){
                    return temp->val;
                }
                //rev=temp;p
                temp=temp->next;
            }
        }
    }return y;
}
    
void insert(K key,V val){
    auto hash=GetHash(key);
    node *temp1=findk(key);
    if(arr[hash]==NULL){
        //head[hash]=new node(key,val);
        arr[hash]=new node(key,val);
        size++;
    }
    
    else if(temp1!=NULL){
            temp1->val=val;
            
        }
    else{
        node *temp=new node(key,val);
        node *x=arr[hash];
        arr[hash]=temp;
        arr[hash]->next=x;
        size++;
    }
}

int rabin(K ax,K bx){
    string a=to_string(ax);
    string b=to_string(bx);
    unsigned long long int hash=0;
    unsigned long long int p = 41;
    for(int i=0;i<a.length();i++)
    {
        (hash) = (((hash)%mod) + (a[i]*((p)%mod))%mod)%mod;
        p = ((p%mod)*41)%mod;
    }
    p=41;
    unsigned long long int hash1=0;
    
    for(int i=0;i<b.length();i++)
    {
        (hash1) = (((hash1)%mod) + (b[i]*((p)%mod))%mod)%mod;
        p = ((p%mod)*41)%mod;
    }
    if(hash1==hash){
        return 1;
    }
    return 0;
}

void erase(K key){
    auto hash=GetHash(key);
    if(arr[hash]!=NULL){
        //head[hash]=new node(key,val);
        node *temp=arr[hash];
        node *prev=arr[hash];
        if(rabin(temp->s,key)==1){
            arr[hash]=arr[hash]->next;
            
        }
        else{
            while(temp!=NULL)
            {
                if(rabin(temp->s,key)==1){
                    prev->next=temp->next;
                    free(temp);
                }
                prev=temp;
                temp=temp->next;
            }
        }
        size--;
    }
}
          
node *findk(K key){
    auto hash=GetHash(key);
    if(arr[hash]!=NULL){
        node *temp=arr[hash];
        if(rabin(temp->s,key)==1){
            return temp;
        }
        else{
            while(temp!=NULL)
            {
                if(rabin(temp->s,key)==1){
                    return temp;
                }
                //rev=temp;p
                temp=temp->next;
            }
        }
    }return NULL;
}
    bool find(K key){
        node *temp=findk(key);
        return temp!=NULL;
    }

         };

int main() {
    map<int,int> mp;
    int k;
    cin>>k;
    int array[k];
    for(int i=0;i<k;i++){
        cin>>array[i];
    }
    int sub;
    cin>>sub;
    for(int i=0;i<sub;i++){
        int x=mp[(array[i])];
        if(x!=0){
            x++;
            mp.insert((array[i]),(x));
        }
        else{
            mp.insert((array[i]),(1));
        }
    }
    //cout<<mp["3"]<<mp["2"];
    cout<<size<<" ";
    for(int i=sub;i<k;i++){
        int x=mp[(array[i-sub])];
        // stringstream obj(x);
        // int pre = 0;
        // obj >> pre;
        if(x==1){
            mp.erase((array[i-sub]));
        }
        else{
            x--;
            mp.insert((array[i]),(x));
        }
        int y=mp[(array[i])];
        if(y!=0){
            y++;
            mp.insert((array[i]),(y));
        }
        else{
            mp.insert((array[i]),(1));
        }
        cout<<size<<" ";
        //std::fill_n(arr, 100000, NULL);
    }
    
    return 0;
}
