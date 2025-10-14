#include <bits/stdc++.h>
using namespace std;
int bfs(int s,int t,vector<vector<int>>& M,int V,vector<int>& parent)
{
    queue<pair<int,int>> q;
    q.push({s,100000000});
    vector<int> marked(V,0);
    marked[s]=1;
    int curr,f;
    while(!q.empty())
    {
        curr=q.front().first;
        f=q.front().second;
        q.pop();
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
    return f;
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
        flow+=F;
        fill(parent.begin(),parent.end(),-1);
    }
    return flow;
}
pair<int,pair<int,int>> minimal_flow(vector<vector<int>> M,int n)
{
    int min=100000000,t,F;
    pair<int,int> edge={-1,-1};
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<n;j++)
        {
            if(M[i][j]>0)
            {
                t=M[i][j];
                M[i][j]=0;
                F=f(0,n-1,M,n);
                if(min>F)
                {
                    min=F;
                    edge={i,j};
                }
                M[i][j]=t;
            }
        }
    }
    return {min,edge};
}
int main()
{
    int n,m,L,a,b,s;
    cin>>n>>m>>L;
    vector<vector<int>> M(n,vector<int>(n,0));
    for(int i=0;i<m;i++)
    {
        cin>>a>>b>>s;
        M[a-1][b-1]=s;
    }
    pair<int,pair<int,int>> p=minimal_flow(M,n);
    cout<<"Minimalniot protok e "<<p.first<<" so otstranuvanje na ("<<p.second.first<<","<<p.second.second<<")";
}