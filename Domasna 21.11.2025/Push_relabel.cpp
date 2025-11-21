#include <bits/stdc++.h>
using namespace std;
void initialize(int s,int V,map<int,int>& h,map<int,int>& excess,vector<vector<int>>& M)
{
    h[s]=V;
    for(int i=0;i<V;i++)
    {
        if(i!=s)
            h[i]=0;
        if(M[s][i]>0)
        {
            excess[i]=M[s][i];
            M[i][s]=M[s][i];
            M[s][i]=0;
        }
    }
}
int f(int s,int t,vector<vector<int>> M,int V,map<int,int> h,map<int,int> excess)
{
    int v;
    priority_queue<pair<int,int>> pq;
    for(int i=0;i<V;i++)
    {
        if(M[i][s]>0)
            pq.push({0,i});
    }
    while(!pq.empty())
    {
        v=pq.top().second;
        pq.pop();
        bool b=false;
        for(int i=0;i<V;i++)
        {
            if(h[v]>h[i] && M[v][i]>0)
            {
                b=true;
                if(excess[v]<=M[v][i])
                {
                    M[v][i]-=excess[v];
                    M[i][v]+=excess[v];
                    excess[i]+=excess[v];
                    excess[v]=0;
                    if(i!=s && i!=t)
                        pq.push({h[i],i});
                }
                else
                {
                    M[i][v]+=M[v][i];
                    excess[v]-=M[v][i];
                    excess[i]+=M[v][i];
                    M[v][i]=0;
                    pq.push({h[v],v});
                    if(i!=s && i!=t)
                        pq.push({h[i],i});
                }
            }
        }
        if(!b && v!=s && v!=t)
        {
            int x=-1;
            for(int i=0;i<V;i++)
            {
                if(M[v][i]>0)
                {
                    if(x==-1 || x>h[i])
                        x=h[i];
                }
            }
            h[v]=x+1;
            for(int i=0;i<V;i++)
            {
                if(h[v]>h[i] && M[v][i]>0)
                {
                    if(excess[v]<=M[v][i])
                    {
                        M[v][i]-=excess[v];
                        M[i][v]+=excess[v];
                        excess[i]+=excess[v];
                        excess[v]=0;
                        if(i!=s && i!=t)
                            pq.push({h[i],i});
                    }
                    else
                    {
                        M[i][v]+=M[v][i];
                        excess[v]-=M[v][i];
                        excess[i]+=M[v][i];
                        M[v][i]=0;
                        pq.push({h[v],v});
                        if(i!=s && i!=t)
                            pq.push({h[i],i});
                    }
                }
            }
        }
    }
    return excess[t];
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
    map<int,int> h;
    map<int,int> excess;
    initialize(0,V,h,excess,M);
    F=f(0,V-1,M,V,h,excess);
    cout<<"Maksimalniot protok e "<<F;
}