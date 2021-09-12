#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

template <typename T>
class node{
    public:
    int col;
    T val;
    node<T> *next;
    node(int c,T v){
        col=c;
        val=v;
        next=NULL;
    }
};

template <typename T>
void transpose(node<T> **a1,int n,int m){
    node<T>* a3[m];
    node<T>* x[m];
    node<T> *temp;
    for(int i=0;i<m;i++){
        a3[i]=NULL;
        x[i]=NULL;
    }
    for(int i=0;i<n;i++){
        node<T> *k=a1[i];
        while(k!=NULL){
            temp =new node<T>(i,k->val);
            if(a3[k->col]==NULL)
                a3[k->col]=temp;
            else
                x[k->col]->next=temp;
            x[k->col]=temp;
            k=k->next;
        }
    }
    cout<<"Resultant matrix after transpose :\n";
    for(int i=0;i<m;i++){
        node<T> *k=a3[i];
        while(k!=NULL){
            cout<<i<<" "<<k->col<<" "<<k->val<<"\n";
            k=k->next;
        }
    }return;
}

template <typename T>
void multiply(node<T>** a2,node<T>** a1,int n,int m,int n1,int m1){
    if(m!=n1){
        cout<<"Multiply not possible\n";
        return;
    }
    node<T>* a3[m1];
    node<T>* x[m1];
    node<T>* temp;
    for(int i=0;i<m1;i++){
        a3[i]=NULL;
        x[i]=NULL;
    }
    for(int i=0;i<n1;i++){
        node<T> *k=a1[i];
        while(k!=NULL){
            temp =new node<T>(i,k->val);
            if(a3[k->col]==NULL)
                a3[k->col]=temp;
            else
                x[k->col]->next=temp;
            x[k->col]=temp;
            k=k->next;
        }
    }

    node<T>* res[n];
    for(int i=0;i<n;i++)
        res[i]=NULL;
    for(int i=0;i<n;i++){
        node<T> *prev=NULL;
        for(int j=0;j<m1;j++){
            node<T> *t2=a3[j];
            node<T> *t1=a2[i];
            T ans=0;
            while(t1!=NULL && t2!=NULL){
                if(t1->col==t2->col){
                    ans+=t1->val*t2->val;
                    t1=t1->next;
                    t2=t2->next;
                }
                else if(t1->col<t2->col){
                    t1=t1->next;
                }
                else{
                    t2=t2->next;
                }
            }
            if(ans!=0){
            temp=new node<T>(j,ans);
            if(res[i]==NULL){
                res[i]=temp;
            }
            else{
                prev->next=temp;
            }
            prev=temp;
            }
        }
    }
    cout<<"Resultant matrix after multiplication :\n";
    for(int i=0;i<n;i++){
        node<T> *k=res[i];
        while(k!=NULL){
            cout<<i<<" "<<k->col<<" "<<k->val<<"\n";
            k=k->next;
        }
    }
    
}

template <typename T>
void addmatrix(node<T>** a1,node<T>** a2,int n,int m,int n1,int m1){
    if(n!=n1 or m!=m1){
        cout<<"Addition not possible\n";
        return;
    }
    node<T>* a3[n];
    //return a3;
    for(int i=0;i<n;i++){
        a3[i]=NULL;
    }
    for(int i=0;i<n;i++){
        node<T> *t1,*t2,*t3=NULL,*temp;
        t1=a1[i];
        t2=a2[i];
        while(t1!=NULL && t2!=NULL){
            //cout<<t1->col<<t2->col;
            if(t1->col==t2->col){
                temp=new node<T>(t1->col,t1->val+t2->val);
                t1=t1->next;
                t2=t2->next;
            }
            else if(t1->col<t2->col){
                temp=new node<T>(t1->col,t1->val);
                t1=t1->next;
            }
            else{
                temp=new node<T>(t2->col,t2->val);
                t2=t2->next;
            }
            if(a3[i]==NULL && temp->val!=0){
                a3[i]=temp;
                t3=temp;
            }
            else if(temp->val!=0){
                t3->next=temp;
                t3=temp;
            }
            
        }
        if(t1!=NULL){
            if(a3[i]==NULL)
                a3[i]=t1;
            else
                t3->next=t1;
        }
        if(t2!=NULL){
            if(a3[i]==NULL)
                a3[i]=t2;
            else
                t3->next=t2;
        }
    }
    cout<<"Resultant matrix after addition :\n";
    for(int i=0;i<n;i++){
        node<T> *k=a3[i];
        while(k!=NULL){
            cout<<i<<" "<<k->col<<" "<<k->val<<"\n";
            k=k->next;
        }
    }return;
}


int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */   
    int n,m;
    cin>>n>>m;
    int n1,m1;
    cin>>n1>>m1;
    double arr1[n][m];
    double arr2[n1][m1];
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            cin>>arr1[i][j];
        }
    }
    for(int i=0;i<n1;i++){
        for(int j=0;j<m1;j++){
            cin>>arr2[i][j];
        }
    }
    node<double>* a1[n];
    for(int i=0;i<n;i++){
        a1[i]=NULL;
    }
    node<double>* a2[n1];
    for(int i=0;i<n1;i++){
        a2[i]=NULL;
    }
    for(int i=0;i<n;i++){
        //cout<<"ok";
        node<double> *tail=NULL;
        for(int j=0;j<m;j++){
            if(arr1[i][j]!=0){
                //cout<<"xx";
                node<double> *temp=new node<double>(j,arr1[i][j]);
                if(a1[i]==NULL){
                    a1[i]=temp;
                }
                else{
                    tail->next=temp;
                }
                tail=temp;
            }
        }
    }
    for(int i=0;i<n1;i++){
        //cout<<"ok";
        node<double> *tail2=NULL;
        for(int j=0;j<m1;j++){
            if(arr2[i][j]!=0){
                node<double> *temp2=new node<double>(j,arr2[i][j]);
                if(a2[i]==NULL){
                    a2[i]=temp2;
                }
                else{
                    tail2->next=temp2;
                }
                tail2=temp2;
            }
        }
    }
    
//     for(int i=0;i<n;i++){
//         node *t=a1[i];
//         while(t!=NULL){
//             //cout<<"x";
//             cout<<t->val<<" "<<i<<" "<<t->col<<" ";
//             t=t->next;
//         }
//     }
        
//     for(int i=0;i<n1;i++){
//         node *k=a2[i];
//         while(k!=NULL){
//             cout<<k->val<<" "<<i<<" "<<k->col<<" ";
//             k=k->next;
//         }
//     }
    cout<<"Row Col Val \n";
    addmatrix(a1,a2,n,m,n1,m1);
    transpose(a2,n1,m1);
    multiply(a1,a2,n,m,n1,m1);
    
    
    return 0;
}
