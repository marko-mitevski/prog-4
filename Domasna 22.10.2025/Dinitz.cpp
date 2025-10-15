#include <bits/stdc++.h>
using namespace std;
bool bfs(vector<vector<int>>& M,map<int,int>& level,int V)
{
    bool b=false;
    queue<pair<int,int>> q;
    q.push({0,0});
    int curr;
    vector<int> marked(V,0);
    marked[0]=1;
    while(!q.empty())
    {
        curr=q.front().first;
        level[curr]=q.front().second;
        q.pop();
        if(curr==V-1)
            b=true;
        for(int i=0;i<V;i++)
        {
            if(M[curr][i]>0 && marked[i]==0)
            {
                marked[i]=1;
                q.push({i,level[curr]+1});
            }
        }
    }
    return b;
}
void dfs(vector<vector<int>>& M,map<int,int> level,map<int,bool>& mp,int V,int node,vector<int> path,int bottleneck,int& flow,int& c)
{
    if(c==1)
        return;
    path.push_back(node);
    if(node==V-1)
    {
        for(int i=0;i<path.size()-1;i++)
        {
            M[path[i]][path[i+1]]-=bottleneck;
            M[path[i+1]][path[i]]+=bottleneck;
        }
        flow+=bottleneck;
        c=1;
        return;
    }
    bool b=false;
    for(int i=0;i<V;i++)
    {
        if(M[node][i]>0 && (level[i]==level[node]+1 || i==V-1) && mp[i]==0)
        {
            b=true;
            dfs(M,level,mp,V,i,path,min(bottleneck,M[node][i]),flow,c);
        }
    }
    if(!b)
        mp[node]=1;
}
void add_node(vector<vector<int>>& M,int V,int x,int y,int c)
{
    vector<vector<int>> A(V+1,vector<int>(V+1,0));
    for(int i=0;i<V-1;i++)
    {
        if(i!=x && i!=y)
        {
            for(int j=0;j<V-1;j++)
            {
                A[i][j]=M[i][j];
            }
            A[i][V]=M[i][V-1];
        }
        else if(i==x)
        {
            for(int j=0;j<V-1;j++)
            {
                A[x][j]=M[x][j];
            }
            A[x][V-1]=c;
            A[x][V]=M[x][V-1];
        }
        else
        {
            for(int j=0;j<V-1;j++)
            {
                A[y][j]=M[y][j];
            }
            A[y][V]=M[y][V-1];
        }
    }
    A[V-1][y]=c;
    M.resize(V+1);
    for(int i=0;i<V+1;i++)
    {
        M[i]=A[i];
    }
}
int main()
{
    int V,E,a,b,c;
    cin>>V>>E;
    vector<vector<int>> M(V,vector<int>(V,0));
    vector<pair<pair<int,int>,int>> edges;
    for(int i=0;i<E;i++)
    {
        cin>>a>>b>>c;
        if(M[a][b]==0)
        {
            if(M[b][a]==0)
            {
                M[a][b]=c;
            }
            else
            {
                edges.push_back({{a,b},c});
            }
        }
        else
            M[a][b]+=c;
    }
    for(int i=0;i<edges.size();i++)
    {
        a=edges[i].first.first;
        b=edges[i].first.second;
        c=edges[i].second;
        add_node(M,V,a,b,c);
        V++;
    }
    map<int,int> level;
    map<int,bool> mp;
    int flow=0;
    int ctr;
    while(bfs(M,level,V))
    {
        for(int i=0;i<V;i++)
        {
            mp[i]=0;
        }
        ctr=0;
        dfs(M,level,mp,V,0,{},100000000,flow,ctr);
    }
    cout<<"Maksimalniot protok e "<<flow;
}