#include <bits/stdc++.h>
using namespace std;
vector<int> bellman_ford(int V,vector<vector<int>> edges)
{
    vector<int> distances(V,100000000);
    distances[0]=0;
    int u,v,w;
    for(int i=0;i<V;i++)
    {
        for(vector<int> edge : edges)
        {
            u=edge[0];
            v=edge[1];
            w=edge[2];
            if(distances[u]!=100000000 && (distances[v]>distances[u]+w))
            {
                if(i==V-1)
                    return {-1};
                distances[v]=distances[u]+w;
            }
        }
    }
    return distances;
}
int main()
{
    int V,E,a,b,c;
    cin>>V>>E;
    vector<vector<int>> edges(E,vector<int>(3));
    for(int i=0;i<E;i++)
    {
        cin>>a>>b>>c;
        edges[i][0]=a;
        edges[i][1]=b;
        edges[i][2]=c;
    }
    vector<int> res=bellman_ford(V,edges);
    if(res.size()==1 && res[0]==-1)
    {
        cout<<"Ima ciklus so negativna dolzina";
        return 0;
    }
    cout<<"Rastojanijata od 0 do drugite teminja se: ";
    for(int i=0;i<V;i++)
    {
        cout<<res[i]<<" ";
    }
    return 0;
}