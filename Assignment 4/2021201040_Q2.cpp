#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include<fstream>
using namespace std;

class minheap{
    public:
    FILE *dummy;
    vector<pair<int,FILE *>> v;
    minheap(){
        pair<int,FILE *> x;
        x=make_pair(-1,dummy);
        v.push_back(x);
    }
    void insert(int x,FILE *y){
        v.push_back(make_pair(x,y));
        int p=v.size()-1;
        while(p>1){
            if(v[p/2].first>v[p].first){
            swap(v[p/2].first,v[p].first);
            swap(v[p/2].second,v[p].second);
            p=p/2;}
            // else if(v[p/2].first==v[p].first && v[p/2].second>v[p].second)
            // {
            // swap(v[p/2].first,v[p].first);
            // swap(v[p/2].second,v[p].second);
            // p=p/2;
            // }
            else{
                break;
            }
        }
    }
    pair<int,FILE *>getmin(){
       if(v.size()==1)
           cout<<"Empty"<<endl;
        return v[1];
    }
    bool empty(){
        return v.size()>1;
    }
    void delmin(){
        if(v.size()==1) return;
        if(v.size()==2){
            v.pop_back();
            return;
        }
        else{
            int p=v.size()-1;
            v[1].first=v[p].first;
            v[1].second=v[p].second;
            v.pop_back();
            int i=1;
            int c1=2*i,c2=2*i+1;
            while(c1<p || c2<p){
                int x=v[c1].first;
                int y=c2<p?v[c2].first:INT_MAX;
                int z=min(x,y);
                if(v[i].first<x && v[i].first<y)
                    break;
                if(z==x){
                    swap(v[i].first,v[c1].first);
                    swap(v[i].second,v[c1].second);
                    i=c1;
                }
                else{
                    swap(v[i].first,v[c2].first);
                    swap(v[i].second,v[c2].second);
                    i=c2;
                }
                c1=2*i,c2=2*i+1;
            }
        }
    }
};





int main(int argc, char *argv[]){
    //string input_file=argv[1];
    //string output_file=argv[2];
    vector<int> arr;
    ifstream File;
    int total_ints=1000000;
    File.open(string(argv[1]));
    if(!File.is_open())
    {
        cout<<"It failed"<<endl;
        return 0;
    }
    int x=1;
    int j=1;
    int count=0;
    ofstream myfile;
    int y=0;
    while(File>>x)
    {   
        count++;
        //cout<<x<<" ";
        if(y<total_ints)
        {
            arr.push_back(x);
            y++;
        }
        if(y==total_ints)
        {
            sort(arr.begin(),arr.end());
            int i=0;
            myfile.open(".\\data\\"+to_string(j)+".txt");
            while(y>0){
                myfile<<arr[i]<<" ";
                i++;
                y--;
            }
            arr.clear();
            myfile.close();
            j++;
            y=0;
        }
        if (File.peek() == ',')
            File.ignore();
        //cout<<count;
    }
    if(y!=0){
        sort(arr.begin(),arr.end());
            int i=0;
            myfile.open(".\\data\\"+to_string(j)+".txt");
            while(y>0){
                //cout<<"\n"<<arr[i]<<" ";
                myfile<<arr[i]<<" ";
                i++;
                y--;
            }
            arr.clear();
            myfile.close();
            j++;
    }
    File.close();
    FILE* output=fopen(argv[2],"w");
    // output.open(".\\hello\\output.txt");
    j-=1;
    FILE *fp[j];
    minheap *heap=new minheap();
    for(int i=0;i<j;i++){
        //cout<<i<<" ";
        fp[i]=fopen(("data/"+to_string(i+1)+".txt").c_str(),"r");
        int temp;
        fscanf(fp[i],"%d",&temp);
        //cout<<temp<<" ";
        //pair<int,FILE *>p= make_pair(temp,fp[i]);
        heap->insert(temp,fp[i]);
    }
    while(heap->empty())
    {
        int temp;
        pair<int,FILE *> cur;
        cur=heap->getmin();
        heap->delmin();
        //cout<<cur.first<<" ";
        fprintf(output,"%d,",cur.first);
        //cout<<"Hello";
        if(fscanf(cur.second,"%d ",&temp)!=EOF)
        {
            heap->insert(temp,cur.second);
        }
        else{
            fclose(cur.second);
        }
        //cout<<"Bye";
    }
    fclose(output);

    //cout<<count;
    for(int i=1;i<=j;i++){
        remove(("data/"+to_string(i)+".txt").c_str());
    }
    return 0;
}