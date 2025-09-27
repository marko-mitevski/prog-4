#include <bits/stdc++.h>
using namespace std;
int find_pair(vector<vector<int>> vect,int x,int y)
{
    for(int i=0;i<vect.size();i++)
    {
        if(vect[i][0]==x && vect[i][1]==y)
            return i;
    }
    return -1;
}
void floyd_warshall(vector<vector<int>> &list,int V)
{
    int d1,d2,ind;
    for(int k=0;k<V;k++)
    {
        cout<<"Rastojanijata vo iteracija "<<k<<":"<<endl;
        for(int i=0;i<V;i++)
        {
            for(int j=0;j<V;j++)
            {
                d1=10000000;
                d2=10000000;
                ind=find_pair(list,i,k);
                if(ind!=-1)
                    d1=list[ind][2];
                ind=find_pair(list,k,j);
                if(ind!=-1)
                    d2=list[ind][2];
                if(d1!=10000000 && d2!=10000000)
                {
                    ind=find_pair(list,i,j);
                    if(ind==-1)
                    {
                        list.push_back({i,j,d1+d2});
                        cout<<d1+d2<<" ";
                    }
                    else
                    {
                        list[ind][2]=min(list[ind][2],d1+d2);
                        cout<<list[ind][2]<<" ";
                    }
                }
                else
                    cout<<"INF ";
            }
            cout<<endl;
        }
        cout<<endl;
    }
}
void floyd_warshall_negative_cycle_check(vector<vector<int>> &list,int V)
{
    int d1,d2,ind;
    for(int i=0;i<V;i++)
    {
        for(int j=0;j<V;j++)
        {
            for(int k=0;k<V;k++)
            {
                d1=10000000;
                d2=10000000;
                ind=find_pair(list,i,k);
                if(ind!=-1)
                    d1=list[ind][2];
                ind=find_pair(list,k,j);
                if(ind!=-1)
                    d2=list[ind][2];
                if(d1!=10000000 && d2!=10000000 && list[k][2]<0)
                {
                    ind=find_pair(list,i,j);
                    list[ind][2]=-10000000;
                }
            }
        }
    }
}
int main()
{
    int V,E,a,b,c,ind;
    cin>>V>>E;
    vector<vector<int>> list(E+V,vector<int>(3));
    ind=V;
    for(int i=0;i<V;i++)
    {
        list[i]={i,i,0};
    }
    for(int i=0;i<E;i++)
    {
        cin>>a>>b>>c;
        if(a==b)
        {
            list[a][2]=min(list[a][2],c);
        }
        else
        {
            list[ind]={a,b,c};
            ind++;
        }
    }
    list.resize(ind);
    floyd_warshall(list,V);
    vector<vector<int>> l=list;
    floyd_warshall_negative_cycle_check(l,V);
    if(list!=l)
    {
        cout<<"Ima ciklus so negativna dolzina"<<endl;
        cout<<"Rastojanijata se"<<endl;
        for(int i=0;i<V;i++)
        {
            for(int j=0;j<V;j++)
            {
                ind=find_pair(l,i,j);
                if(ind==-1)
                {
                    cout<<"INF ";
                }
                else
                {
                    if(l[ind][2]==-10000000)
                        cout<<"-INF ";
                    else
                        cout<<l[ind][2]<<" ";
                }
            }
            cout<<endl;
        }
    }
    return 0;
}