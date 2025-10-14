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
int main()
{
    int V,E,a,b,c,F;
    cin>>V>>E;
    vector<vector<int>> M(V,vector<int>(V,-1));
    for(int i=0;i<E;i++)
    {
        cin>>a>>b>>c;
        M[a][b]=c;
        M[b][a]=0;
    }
    F=f(0,V-1,M,V);
    cout<<"Maksimalniot protok e "<<F;
}