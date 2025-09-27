#include <bits/stdc++.h>
using namespace std;
int floyd_warshall(vector<vector<int>> matrix,int L)
{
    int r=0;
    int V=matrix.size();
    for(int k=0;k<V;k++)
    {
        for(int i=0;i<V;i++)
        {
            for(int j=0;j<V;j++)
            {
                if(matrix[i][k]!=L && matrix[k][j]!=L)
                {
                    matrix[i][j]=min(matrix[i][j],matrix[i][k]+matrix[k][j]);
                }
            }
        }
    }
    for(int i=0;i<V;i++)
    {
        for(int j=0;j<V;j++)
        {
            r+=matrix[i][j];
        }
    }
    return r;
}
int main()
{
    int n,m,L,a,b,s,c=0,c1=0;
    cin>>n>>m>>L;
    vector<vector<int>> matrix(n,vector<int>(n,L));
    vector<vector<int>> edges(m);
    for(int i=0;i<n;i++)
        matrix[i][i]=0;
    for(int i=0;i<m;i++)
    {
        cin>>a>>b>>s;
        edges[i]={a-1,b-1,s};
        matrix[a-1][b-1]=min(matrix[a-1][b-1],s);
        matrix[b-1][a-1]=matrix[a-1][b-1];
    }
    c=floyd_warshall(matrix,L);
    for(int i=0;i<m;i++)
    {
        matrix[edges[i][0]][edges[i][1]]=L;
        matrix[edges[i][1]][edges[i][0]]=L;
        c1=max(c1,floyd_warshall(matrix,L));
        matrix[edges[i][0]][edges[i][1]]=edges[i][2];
        matrix[edges[i][1]][edges[i][0]]=edges[i][2];
    }
    cout<<c<<" "<<c1;
    return 0;
}