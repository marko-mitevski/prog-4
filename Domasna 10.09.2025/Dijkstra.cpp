#include <bits/stdc++.h>
using namespace std;
vector<int> dijkstra(vector<vector<pair<int,int>>> list,int V)
{
    vector<int> distances(V,10000000);
    int marked[V];
    memset(marked,0,sizeof(marked));
    distances[0]=0;
    priority_queue<pair<int,int>> pq;
    pq.push({0,0});
    while(!pq.empty())
    {
        int city=pq.top().second;
        pq.pop();
        if(marked[city]==0)
        {
            marked[city]=1;
            for(pair<int,int> x : list[city])
            {
                int next=x.first;
                int distance=x.second;
                if(distances[next]>distances[city]+distance)
                {
                    distances[next]=distances[city]+distance;
                    pq.push({-distances[next],next});
                }
            }
        }
    }
    return distances;
}
int main()
{
    int V,E;
    cin>>V>>E;
    int a,b,c;
    vector<vector<pair<int,int>>> list;
    list.resize(V);
    for(int i=0;i<E;i++)
    {
        cin>>a>>b>>c;
        list[a].push_back({b,c});
        list[b].push_back({a,c});
    }
    vector<int> res=dijkstra(list,V);
    cout<<"Rastojanijata od 0 do drugite teminja se: ";
    for(int i=0;i<V;i++)
    {
        cout<<res[i]<<" ";
    }
    return 0;
}