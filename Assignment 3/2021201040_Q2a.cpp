#include <bits/stdc++.h>

using namespace std;

class minheap{
    public:
    vector<pair<int,int>> v;
    minheap(){
        v.push_back({-1,-1});
    }
    void insert(int x,int y){
        v.push_back(make_pair(x,y));
        int p=v.size()-1;
        while(p>1){
            if(v[p/2].first>v[p].first){
            swap(v[p/2].first,v[p].first);
            swap(v[p/2].second,v[p].second);
            p=p/2;}
            else if(v[p/2].first==v[p].first && v[p/2].second>v[p].second)
            {
            swap(v[p/2].first,v[p].first);
            swap(v[p/2].second,v[p].second);
            p=p/2;
            }
            else{
                break;
            }
        }
    }
    pair<int,int> getmin(){
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
    void print(){
        for(int i=0;i<v.size();i++){
            cout<<v[i].first<<" "<<v[i].second<<"\n";
        }
    }
};

void djk(vector<vector<pair<int,int>>> &G,int s){
    int n=G.size();
    int ds[n];
    
    for(int i=0;i<n;i++)
        ds[i]=INT_MAX;
    ds[s]=0;
    minheap*p=new minheap();
    //priority_queue<pair<int,int>,vector<pair<int,int>>,greater<pair<int,int>>> pq;
    //pq.push(make_pair(0,s));
    vector<vector<int>> res(n);
    res[s].push_back(-1);
    p->insert(0,s);
    while(p->empty()){
        
        pair<int,int> z=p->getmin();
        p->delmin();
        int d=z.first;
        int u=z.second;
        if(d==ds[u]){
        for(auto val:G[u]){
            int v=val.first;
            int w=val.second;
            int cd=ds[v];
            int nd=d+w;
            if(nd<cd){
                ds[v]=nd;
                if(res[v].size()>0)
                    res[v].pop_back();
                res[v].push_back(u);
                p->insert(nd,v);//(make_pair(nd,v));
            }
            else if(nd==cd && res[v].size()>0 && to_string(res[v][0])>to_string(u)){
                res[v].pop_back();
                res[v].push_back(u);
            }
        }
        }
    }
    // for(int i=0;i<n;i++){
    //     if(i!=s){
    //         int k=ds[i]==INT_MAX?-1:ds[i];
    //         cout<<k<<" ";}
    // }
    // cout<<"\n";
    vector<int> ans;
        for(int i=0;i<n;i++){
            if(i!=s){
                int j=i;
                ans.push_back(j);
                while(res[j][0]!=-1){
                    ans.push_back(res[j][0]);
                    j=res[j][0];
                }
                for(j=0;j<ans.size();j++)
                    cout << ans[j] << " ";
                cout << "\n";
                ans.clear();
            }
        }
    return;
}
int main(void){
    int t;
    cin>>t;
    while(t--){
        int n,m;
        cin>>n>>m;
        vector<vector<pair<int,int>>> G(n);
        while(m--){
            int u,v,w;
            cin>>u>>v>>w;
            G[u].push_back(make_pair(v,w));
            G[v].push_back(make_pair(u,w));
        }
        int s;
        cin>>s;
        djk(G,s);
    }
    return 0;
}


