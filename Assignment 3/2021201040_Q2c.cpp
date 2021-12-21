#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <queue>
#include<climits>
using namespace std;

char g[1000][1000];
void bfs(int i,int j,int n,int m,vector<vector<int>>&dist){
    queue<pair<pair<int,int>,int>>q;
    q.push({{i,j},0});
    bool vis[n][m];
    for(int w=0;w<n;w++){
        for(int o=0;o<m;o++){
            vis[w][o]=false;
        }
    }
    vis[i][j]=true;
    while(!q.empty()){
        auto p=q.front();
        q.pop();
        int x=p.first.first;
        int y=p.first.second;
        int z=p.second;
        dist[x][y]=z;
        if(x-1>=1 && vis[x-1][y]==false && g[x-1][y]!='#')
        {
            q.push({{x-1,y},z+1});
            vis[x-1][y]=true;
        }
        if(x+1<n-1 && vis[x+1][y]==false &&  g[x+1][y]!='#')
        {
            q.push({{x+1,y},z+1});
            vis[x+1][y]=true;
        }
        if(y-1>=1 && vis[x][y-1]==false &&  g[x][y-1]!='#')
        {
            q.push({{x,y-1},z+1});
            vis[x][y-1]=true;
        }
        if(y+1<m-1 && vis[x][y+1]==false &&  g[x][y+1]!='#')
        {
            q.push({{x,y+1},z+1});
            vis[x][y+1]=true;
        }
    }return;
}

int main() {
    int n,m;
    cin>>n>>m;
    //cout<<n<<m;
    int posx=0,posy=0;
    //vector<vector<char>> g(n);
    vector<pair<int,int>> v;
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            cin>>g[i][j];
        }
    }
    int minR=INT_MAX;
    vector<vector<int>> dist(n,vector<int>(m,INT_MAX));
    bfs(1,0,n,m,dist);
    for(int i=0;i<n;i++)
    {for(int j=0;j<m;j++)
    {
        if(g[i][j]=='R'){
            minR=min(dist[i][j],minR);
        }
        if(g[i][j]=='A')
        {
            if(dist[i][j]<=minR){
                cout<<"Yes\n"<<dist[i][j];
            }
            else
                cout<<"No";
        }
    }
    }
    
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */   
    return 0;
}
