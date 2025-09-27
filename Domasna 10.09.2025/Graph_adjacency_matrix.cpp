#include <bits/stdc++.h>
using namespace std;
void bfs(vector<vector<int>> list)
{
    queue<int> q;
    q.push(0);
    int marked[list.size()];
    memset(marked,0,sizeof(marked));
    int curr;
    while(!q.empty())
    {
        curr=q.front();
        q.pop();
        if(marked[curr]==0)
        {
            cout<<curr<<" ";
            marked[curr]=1;
            for(int x=0;x<list[curr].size();x++)
            {
                if(list[curr][x]==1 && marked[x]==0)
                    q.push(x);
            }
        }
    }
    cout<<endl;
}
void dfs(vector<vector<int>>& list, vector<int>& marked,int node)
{
    cout<<node<<" ";
    for(int x=0;x<list[node].size();x++)
    {
        if(list[node][x]==1 && marked[x]==0)
        {
            marked[x]=1;
            dfs(list,marked,x);
        }
    }
}
int main()
{
    int V,E;
    cin>>V>>E;
    int a,b;
    vector<vector<int>> list;
    list.resize(V,vector<int>(V,0));
    for(int i=0;i<E;i++)
    {
        cin>>a>>b;
        list[a][b]=1;
        list[b][a]=1;
    }
    vector<int> marked;
    marked.resize(V,0);
    marked[0]=1;
    cout<<"bfs: ";
    bfs(list);
    cout<<"dfs: ";
    dfs(list,marked,0);
    return 0;
}
