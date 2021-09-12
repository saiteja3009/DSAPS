#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

template <typename T>
class node{
    public:
    int row,col;
    T val;
    node(int r,int c,T v){
        row=r;
        col=c;
        val=v;
    }
};

template <typename T>
void addmatrix(node<T>* mat1[],node<T>* mat2[],int n,int m,int n1,int m1,int x,int y){
    //cout<<y;
    if(n!=n1 || m1!=m){
        cout<<"Addition is not possible\n";
        return;
    }
    int i=0,j=0,k=0;
    while(i<x || j<y){
        if(i==x)
            k++,j++;
        else if(j==y)
            k++,i++;
        else if(mat1[i]->row==mat2[j]->row && mat1[i]->col==mat2[j]->col){
            if((mat1[i]->val+mat2[j]->val)!=0)
                k++;
            i++;
            j++;
            //cout<<i<<j<<k<<"*1*";
            //cout<<mat1[i]->val<<"rt";
        }
        else if(mat1[i]->row<mat2[j]->row || (mat1[i]->row==mat2[j]->row && mat1[i]->col<mat2[j]->col))
        {i++,k++;
         //cout<<i<<j<<k<<"*2*";
        }
        else if(mat1[i]->row>mat2[j]->row || (mat1[i]->row==mat2[j]->row && mat1[i]->col>mat2[j]->col))
        {j++,k++;
         //cout<<i<<j<<k<<"*3*";
        }
        else
        {i++,j++;
         //cout<<i<<j<<k<<"*4*";
        }
    }

    node<T>* res[k];
    int p=0;
    i=0,j=0;
    while(i<x || j<y){
        if(i==x)
            {res[p]=new node<T>(mat2[j]->row,mat2[j]->col,mat2[j]->val);
            p++;
            j++;}
        else if(j==y)
            {res[p]=new node<T>(mat1[i]->row,mat1[i]->col,mat1[i]->val);
            p++;
            i++;}
        else if(mat1[i]->row==mat2[j]->row && mat1[i]->col==mat2[j]->col){
            if((mat1[i]->val+mat2[j]->val)!=0)
                res[p++]=new node<T>(mat1[i]->row,mat1[i]->col,mat1[i]->val+mat2[j]->val);
            //p++;
            i++;
            j++;
        }
        else if(mat1[i]->row<mat2[j]->row || (mat1[i]->row==mat2[j]->row && mat1[i]->col<mat2[j]->col))
        {
        res[p]=new node<T>(mat1[i]->row,mat1[i]->col,mat1[i]->val);
        p++;
        i++;}
        else if(mat1[i]->row>mat2[j]->row || (mat1[i]->row==mat2[j]->row && mat1[i]->col>mat2[j]->col))
        {
         res[p]=new node<T>(mat2[j]->row,mat2[j]->col,mat2[j]->val);
        p++;
        j++;}
    }

    cout<<"Result Matrix after Addition :\n";
    for(int i=0;i<k;i++){
        cout<<res[i]->row<<" "<<res[i]->col<<" "<<res[i]->val<<"\n";
    }
}

template <typename T>
void transpose(node<T>* mat1[],int n,int m,int x){
    int temp[x];
    int index[x];
    for(int i=0;i<x;i++){
        index[i]=0;
        temp[i]=0;
    }
    index[0]=1;
    int k;
    for(int i=0;i<x;i++){
        k=mat1[i]->col;
        temp[k]+=1;
    }
    for(int i=1;i<x;i++){
        index[i]=index[i-1]+temp[i-1];
    }
    node<T> *res[x];
    for(int i=0;i<x;i++){
        k=index[mat1[i]->col]-1;
        res[k]=new node<T>(mat1[i]->col,mat1[i]->row,mat1[i]->val);
        index[mat1[i]->col]+=1;
    }
    cout<<"Result Matrix after Transpose :\n";
    for(int i=0;i<x;i++)
    {
        cout<<res[i]->row<<" "<<res[i]->col<<" "<<res[i]->val<<"\n";
    }
    return;
}

template <typename T>
void multiply(node<T> *mat2[],node<T> *mat1[],int n,int m,int n1,int m1,int y, int x){
    if(m!=n1){
        cout<<"Multiplication matrices is not possible\n";
        return;
    }
    int temp[x];
    int index[x];
    for(int i=0;i<x;i++){
        index[i]=0;
        temp[i]=0;
    }
    index[0]=1;
    int k;
    for(int i=0;i<x;i++){
        k=mat1[i]->col;
        temp[k]+=1;
    }
    for(int i=1;i<x;i++){
        index[i]=index[i-1]+temp[i-1];
    }
    node<T> *res[x];
    for(int i=0;i<x;i++){
        k=index[mat1[i]->col]-1;
        res[k]=new node<T>(mat1[i]->col,mat1[i]->row,mat1[i]->val);
        index[mat1[i]->col]+=1;
    }

    int p=0;
    int apos, bpos;
    for (apos = 0; apos < y;)
        {
            int r = mat2[apos]->row;
            for (bpos = 0; bpos < x;)
            {
                int c = res[bpos]->row;
                int tempa = apos;
                int tempb = bpos;
                T sum = 0;
                while (tempa < y && mat2[tempa]->row == r &&
                       tempb < x && res[tempb]->row == c)
                {
                    if (mat2[tempa]->col < res[tempb]->col)
                        tempa++;
                    else if (mat2[tempa]->col > res[tempb]->col)
                        tempb++;
                    else
                        sum += mat2[tempa++]->val * res[tempb++]->val ;
                }
                if (sum != 0)
                    p++;
                while (bpos <x && res[bpos]->row == c)
                    bpos++;
            }
            while (apos <y && mat2[apos]->row == r)
                apos++;
        }
    //cout<<p;
    node<T> *mulres[p];
    int o=0;
    for (apos = 0; apos < y;)
        {
            int r = mat2[apos]->row;
            for (bpos = 0; bpos < x;)
            {
                int c = res[bpos]->row;
                int tempa = apos;
                int tempb = bpos;
                T sum = 0;
                while (tempa < y && mat2[tempa]->row == r &&
                       tempb < x && res[tempb]->row == c)
                {
                    if (mat2[tempa]->col < res[tempb]->col)
                        tempa++;
                    else if (mat2[tempa]->col > res[tempb]->col)
                        tempb++;
                    else
                        sum += mat2[tempa++]->val * res[tempb++]->val ;
                }
                if (sum != 0)
                    mulres[o++]=new node<T>(r,c,sum);
                while (bpos <x && res[bpos]->row == c)
                    bpos++;
            }
            while (apos <y && mat2[apos]->row == r)
                apos++;
        }
    cout<<"Result Matrix after Multiplication :\n";
        for(int i=0;i<p;i++)
    {
        cout<<mulres[i]->row<<" "<<mulres[i]->col<<" "<<mulres[i]->val<<"\n";
    }
}

int main() {
    /* Enter your code here-> Read input from STDIN-> Print output to STDOUT */   
    int n,m;
    cin>>n>>m;
    int n1,m1;
    cin>>n1>>m1;
    double arr1[n][m];
    double arr2[n1][m1];
    int x=0;
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            cin>>arr1[i][j];
            //cout<<arr1[i][j]<<" ";
            if(arr1[i][j]!=0)
                x++;
        }
    }
    int mg=0;
    for(int i=0;i<n1;i++){
        for(int j=0;j<m1;j++){
            //cout<<i<<j<<" ";
            cin>>arr2[i][j];
            if(arr2[i][j]!=0)
                mg++;
        }
    }
    // cout<<n1<<m1;
    // int y=0;
    // int mg=0;
    // for(int i=0;i<n1;i++)
    // {
    //     for(int j=0;j<m1;j++)
    //     {cout<<arr2[i][j];
    //     if(arr2[i][j]!=0)
    //     {cout<<"Hello";
    //         //y+=1;
    //      mg=mg+1;
    //     }}
    // }
    //int y=0;
    //cout<<x<<mg;
    node<double>* mat1[x];
    node<double>* mat2[mg];
    int o=0;
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            if(arr1[i][j]!=0 && o<x){
                mat1[o]=new node<double>(i,j,arr1[i][j]);
                o++;
            }
        }
    }
    //cout<<n<<" "<<m<<" "<<n1<<" "<<m1;
    o=0;
    for(int i=0;i<n1;i++){
        for(int j=0;j<m1;j++){
            if(arr2[i][j]!=0 && o<mg){
                mat2[o]=new node<double>(i,j,arr2[i][j]);
                o++;
            }
        }
    }
    cout<<"Row Col Value \n";
    //cout<<n<<" "<<m<<" "<<n1<<" "<<m1;
     // for(int i=0;i<x;i++)
     //     cout<<mat1[i]->row<<" "<<mat1[i]->col<<" "<<mat1[i]->val<<"\n";
    //  for(int i=0;i<mg;i++)
    //      cout<<mat2[i]->row<<" "<<mat2[i]->col<<" "<<mat2[i]->val<<"\n";
    // //cout<<mg;
    addmatrix(mat1,mat2,n,m,n1,m1,x,mg);
    transpose(mat2,n1,m1,mg);
    multiply(mat1,mat2,n,m,n1,m1,x,mg);
    return 0;
}
