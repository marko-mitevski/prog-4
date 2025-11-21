#include <bits/stdc++.h>
using namespace std;
int bfs(int s,int t,vector<vector<int>>& M,int V,vector<int>& parent)
{
    queue<pair<int,int>> q;
    q.push({s,100000000});
    vector<int> marked(V,0);
    marked[s]=1;
    int curr,f,m=-1;
    while(!q.empty())
    {
        curr=q.front().first;
        f=q.front().second;
        q.pop();
        if(curr==t && m<f)
            m=f;
        for(int i=0;i<V;i++)
        {
            if(M[curr][i]>0 && marked[i]==0)
            {
                parent[i]=curr;
                marked[i]=1;
                q.push({i,min(f,M[curr][i])});
            }
        }
    }
    if(parent[t]==-1)
        return 0;
    return m;
}
int f(int s,int t,vector<vector<int>> M,int V)
{
    int flow=0,F,c;
    vector<int> parent(V,-1);
    vector<int> path;
    while(F=bfs(s,t,M,V,parent))
    {
        c=t;
        path.clear();
        while(c!=s)
        {
            path.push_back(c);
            M[parent[c]][c]-=F;
            M[c][parent[c]]+=F;
            c=parent[c];
        }
        path.push_back(s);
        cout<<"Pat ";
        for(int i=path.size()-1;i>=0;i--)
        {
            cout<<path[i]<<" ";
        }
        cout<<endl;
        flow+=F;
        fill(parent.begin(),parent.end(),-1);
    }
    return flow;
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
    int V,E,a,b,c,F;
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
    F=f(0,V-1,M,V);
    cout<<"Maksimalniot protok e "<<F;
}