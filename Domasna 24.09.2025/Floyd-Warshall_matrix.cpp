#include <bits/stdc++.h>
using namespace std;
void floyd_warshall(vector<vector<int>> &matrix)
{
    int V=matrix.size();
    for(int k=0;k<V;k++)
    {
        cout<<"Rastojanijata vo iteracija "<<k<<":"<<endl;
        for(int i=0;i<V;i++)
        {
            for(int j=0;j<V;j++)
            {
                if(matrix[i][k]!=10000000 && matrix[k][j]!=10000000)
                {
                    matrix[i][j]=min(matrix[i][j],matrix[i][k]+matrix[k][j]);
                }
                if(matrix[i][j]!=10000000)
                    cout<<matrix[i][j]<<" ";
                else
                    cout<<"-INF ";
            }
            cout<<endl;
        }
        cout<<endl;
    }
}
void floyd_warshall_negative_cycle_check(vector<vector<int>> &matrix)
{
    int V=matrix.size();
    for(int i=0;i<V;i++)
    {
        for(int j=0;j<V;j++)
        {
            for(int k=0;k<V;k++)
            {
                if(matrix[i][k]!=10000000 && matrix[k][j]!=10000000 && matrix[k][k]<0)
                {
                    matrix[i][j]=-10000000;
                }
            }
        }
    }
}
int main()
{
    int V,E,a,b,c;
    cin>>V>>E;
    vector<vector<int>> matrix(V,vector<int>(V,10000000));
    for(int i=0;i<V;i++)
        matrix[i][i]=0;
    for(int i=0;i<E;i++)
    {
        cin>>a>>b>>c;
        matrix[a][b]=min(matrix[a][b],c);
    }
    floyd_warshall(matrix);
    vector<vector<int>> vect=matrix;
    floyd_warshall_negative_cycle_check(vect);
    if(matrix!=vect)
    {
        cout<<"Ima ciklus so negativna dolzina"<<endl;
        cout<<"Rastojanijata se"<<endl;
        for(int i=0;i<V;i++)
        {
            for(int j=0;j<V;j++)
            {
                if(vect[i][j]!=10000000 && vect[i][j]!=-10000000)
                    cout<<vect[i][j]<<" ";
                else if(vect[i][j]==10000000)
                    cout<<"INF ";
                else
                    cout<<"-INF ";
            }
            cout<<endl;
        }
    }
    return 0;
}