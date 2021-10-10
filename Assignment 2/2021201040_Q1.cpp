#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

class customClass{
    bool operator < (customClass b){

    }

    bool operator > (customClass b){

    }
};

template <typename P>
class AVL{
    public:
    class Node{
        public:
        P data;     
        int count;
        int lcount;
        int rcount;
        int height;
        Node *left;
        Node *right;
        Node(P val){
            data=val;
            count=1;
            lcount=0;
            rcount=0;
            height=1;
            left=NULL;
            right=NULL;
        }
    };
    int getheight(Node *root){
        if(root==NULL)
            return 0;
        return root->height;
    }
    int bal(Node *root){
        if(root==NULL)
            return 0;
        return getheight(root->right)-getheight(root->left);
    }
    
    Node *leftRotate(Node *x)
    {
    Node *y = x->right;
    Node *w = y->left;
       // cout<<x->data<<" "<<y->data<<"L\n";
    y->left = x;
        if(w!=NULL){
            x->rcount=w->lcount+w->rcount+w->count;
        }
        else{
            x->rcount=0;
        }
    y->lcount=x->lcount+x->rcount+x->count;
    x->right = w;
    x->height = max(getheight(x->left),   
                    getheight(x->right)) + 1;
    y->height = max(getheight(y->left),
                    getheight(y->right)) + 1;
    return y;
    }
    
Node *rightRotate(Node *x)
{
    //cout<<x->data;
    Node *y = x->left;
    Node *w = y->right;
    // cout<<x->data<<" "<<y->data<<"R\n";
    y->right = x;
    x->left = w;
    if(w!=NULL){
            x->lcount=w->lcount+w->rcount+1;
        }
    else{
        x->lcount=0;
    }
    y->rcount=x->lcount+x->rcount+1;
    x->height = max(getheight(x->left),
                    getheight(x->right)) + 1;
    y->height = max(getheight(y->left),
                    getheight(y->right)) + 1;

    return y;
}
    bool search(Node *root,P value){
        if(root==NULL){
            return false;
        }
        if(root->data==value){
            return true;
        }
        else if(root->data>value){
            return search(root->left,value);
        }
        return search(root->right,value);
    }
    
    int countoccur(Node *root,P value){
        if(root==NULL){
            return 0;
        }
        if(root->data==value){
            return root->count;
        }
        else if(root->data>value){
            return search(root->left,value);
        }
        return search(root->right,value);
    }
    Node* low=NULL;
    void lower(Node *root,P value){
        if(root==NULL){
            return ;
        }
        if(root->data>value){
             lower(root->left,value);
        }
        else{
        low=root;
         lower(root->right,value);
        }
        return;
    }
    Node* up=NULL;
    void upper(Node *root,P value){
        if(root==NULL){
            return ;
        }
        if(root->data>=value){
            up=root;
             upper(root->left,value);
        }
        else{
        //low=root;
         upper(root->right,value);
        }
        return;
    }
    
    P closest(Node *root,P value){
        up=NULL;
        low=NULL;
        upper(root,value);
        lower(root,value);
        if(low==NULL)
            return up->data;
        else if(up==NULL)
            return low->data;
        else{
            if(up->data-value>low->data-value)
                return low->data;
            else
                return up->data;
        }
    }
    
    Node * maxval(Node* root)
{
    Node* temp = root;
    while (temp->right != NULL)
        temp = temp->right;
    return temp;
}
    
    Node* deletefun(Node* root, P value)
    {
    if (root == NULL)
        return root;
    if( value > root->data )
        root->right = deletefun(root->right, value);
    else if ( value < root->data )
        root->left = deletefun(root->left, value);
    else
    {
        if( (root->left == NULL) || (root->right == NULL) )
        {
            Node *temp = root->left ?root->left :root->right;
            if (temp == NULL)
            {   temp = root;
                root = NULL;
            }
            else 
                *root = *temp;
            free(temp);
        }
        else
        {
            Node* temp = maxval(root->left);
            root->data = temp->data;
            root->left = deletefun(root->left,temp->data);
        }
    }
    if (root == NULL)
        return root;
        root->height=1+max(getheight(root->left),getheight(root->right));
        int curbal=bal(root);
        
        if (curbal > 1 && bal(root->right)>=0)
        return leftRotate(root);
        
        if (curbal < -1 && bal(root->left)<=0)
        return rightRotate(root);
        
        if (curbal > 1 && bal(root->right)<0)
        {
        root->right = rightRotate(root->right);
        return leftRotate(root);
        }
 
        if (curbal < -1 && bal(root->left)>0)
        {
        root->left = leftRotate(root->left);
        return rightRotate(root);
        }
    return root;    
    }
    
    
    
    
    Node* insert(Node *root,P value){
        if(root==NULL){
            return new Node(value);
        }
        if(root->data==value){
            root->count+=1;
            return root;
        }
        else if(root->data<value){
            root->rcount+=1;
            root->right=insert(root->right,value);
        }
        else{
            root->lcount+=1;
            root->left=insert(root->left,value);
        }
        root->height=1+max(getheight(root->left),getheight(root->right));
        int curbal=bal(root);
        
        if (curbal > 1 && value > root->right->data)
        return leftRotate(root);
        
        if (curbal < -1 && value < root->left->data)
        return rightRotate(root);
        
        if (curbal > 1 && value < root->right->data)
        {
        root->right = rightRotate(root->right);
        return leftRotate(root);
        }
 
        if (curbal < -1 && value > root->left->data)
        {
        root->left = leftRotate(root->left);
        return rightRotate(root);
        }
    return root;    
    }
    
    void preorder(Node *root)
    {
    if(root != NULL)
    {   int x=root->count;
        while(x>0){
            cout << root->data << " ";
            x--;}
        preorder(root->left);
        preorder(root->right);
    }
    }
    
     P kth(Node* root,int k,int c){
        int y;
        while(root!=NULL){
            c=k-(root->rcount);
            if(c<=0)
                root=root->right;
            else if(c<=root->count)
                return root->data;
            else{
                k-=(root->count+root->rcount);
                root=root->left;
            }
        }
        return y;
    }
    
    // int kth(Node* root,int k,int cur){
    //     //cout<<root->data;
    //     if(root==NULL)
    //         return -1;
    //     //cout<<root->data<<" "<<root->lcount<<" "<<root->rcount<<" "<<k<<" "<<cur<<"\n";
    //     if(k==cur+1)
    //         return root->data;
    //     if(root->lcount==k-1){
    //         return root->data;
    //     }
    //     else if(root->lcount>=k){
    //         return kth(root->left,k,cur);
    //     }
    //     else{
    //         if(cur==-999)
    //             cur=root->lcount+1;
    //         else
    //             cur+=root->lcount+1;
    //         return kth(root->right,k,cur);
    //     }
        
    //}
    int ans=0;
    void upperb(Node* root,P value){
        if(root==NULL){
            return;
        }//nt ans=0;
        if(root->data>=value){
             upperb(root->left,value);
        }
        else{
        //low=root;
            ans+=root->count+root->lcount;
            //return ans;
         upperb(root->right,value);
        }//return ans;
    }
    
    void lowerb(Node*root,P value){
         if(root==NULL){
            return ;
        }//int ans=0;
        if(root->data>value){
            ans+=root->count+root->rcount;
             lowerb(root->left,value);
        }
        else{
         lowerb(root->right,value);
        }//return ans;
    }
    
    
    int countRange(Node *root,P leftv,P rightv){
        if(root==NULL){
            return 0;
        }
        ans=0;
        upperb(root,leftv);
        int x=ans;
        ans=0;
        lowerb(root,rightv);
        int y=ans;
        //cout<<x<<y<<"\n";
        return (root->count+root->lcount+root->rcount)-x-y;
    }

    
};



int main() {
    AVL<double> tree;
    AVL<double>::Node *root = NULL;

     root = tree.insert(root, 10.23);
    //cout<<root->lcount<<root->rcount<<root->height<<root->data<<"\n";
    root = tree.insert(root, 20.32);
    //cout<<root->lcount<<root->rcount<<root->height<<root->data<<"\n";
    root = tree.insert(root, 30);
   // cout<<root->lcount<<root->rcount<<root->height<<root->data<<"\n";
    root = tree.insert(root, 40.54);
    //cout<<root->lcount<<root->rcount<<root->height<<root->data<<"\n";
    root = tree.insert(root, 50);
    //cout<<root->lcount<<root->rcount<<root->height<<root->data<<"\n";
    root = tree.insert(root, 25.22);
    //cout<<root->lcount<<root->rcount<<root->height<<root->data<<"\n";
    tree.preorder(root);
    //cout<<root->lcount<<root->rcount<<root->height<<"\n";
    cout<<tree.kth(root,6,-999)<<"\n";
    root = tree.insert(root, 9.21);
    root = tree.insert(root, 5);
    root = tree.insert(root, 10);
    root = tree.insert(root, 0.21);
    root = tree.insert(root, 6);
    root = tree.insert(root, 12.322);
    root = tree.insert(root, 20);
    root = tree.insert(root, 10);
    root = tree.insert(root, 12.123);
    //root = tree.insert(root, -1);
    root = tree.insert(root, 1);
    root = tree.insert(root, 2.1221);
    tree.preorder(root);
    cout<<"\n";
    cout<<tree.countRange(root,10,100)<<"\n";
    cout<<tree.kth(root,1,0)<<"\n";
    cout<<tree.kth(root,2,0)<<"\n";
    cout<<tree.kth(root,3,0)<<"\n";
    cout<<tree.kth(root,4,0)<<"\n";
    cout<<tree.kth(root,5,0)<<"\n";
    cout<<tree.kth(root,6,0)<<"\n";
    cout<<tree.kth(root,7,0)<<"\n";
    cout<<tree.kth(root,8,0)<<"\n";
    cout<<tree.kth(root,9,0)<<"\n";
    cout<<tree.kth(root,10,0)<<"\n";
    cout<<tree.kth(root,11,0)<<"\n";
    cout<<tree.kth(root,12,0)<<"\n";
    cout<<tree.kth(root,13,0)<<"\n";
    
    tree.preorder(root);
    cout<<" "<<root->data<<"\n";
    root=tree.deletefun(root,1);
    tree.preorder(root);
    cout<<" "<<root->data<<"\n";
    root=tree.deletefun(root,50);
    tree.preorder(root);
    cout<<" "<<root->data<<"\n";
    cout<<tree.closest(root,1)<<"\n";
    root=tree.deletefun(root,11);
    tree.preorder(root);
    cout<<" "<<root->data<<"\n";
    root=tree.deletefun(root,25);
    tree.preorder(root);
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */   
    return 0;
}
