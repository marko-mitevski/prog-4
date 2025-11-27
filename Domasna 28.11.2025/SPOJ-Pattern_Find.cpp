#include <bits/stdc++.h>
using namespace std;
vector<int> rabin_karp(string s,string p,vector<long int>& powers,int x,long int m)
{
    int S,P;
    S=s.length();
    P=p.length();
    vector<long int> hs(S+1);
    long int hp=0;
    for(int i=0;i<P;i++)
    {
        hp=(hp+(p[i]-'a'+1)*powers[i])%m;
    }
    hs[0]=0;
    for(int i=1;i<=S;i++)
    {
        hs[i]=(hs[i-1]+(s[i-1]-'a'+1)*powers[i-1])%m;
    }
    vector<int> res={};
    for(int i=0;i<=S-P;i++)
    {
        if(hs[i+P]-hs[i]==(hp*powers[i])%m)
            res.push_back(i);
    }
    return res;
}
int main()
{
    int T;
    int p=29;
    long int m=1000000009;
    cin>>T;
    string A,B;
    vector<long int> powers(1000000);
    powers[0]=1;
    for(int i=1;i<1000000;i++)
        powers[i]=(powers[i-1]*p)%m;
    vector<vector<int>> results(T);
    for(int i=0;i<T;i++)
    {
        cin>>A>>B;
        results[i]=rabin_karp(A,B,powers,p,m);
    }
    for(int i=0;i<T;i++)
    {
        if(results[i].size()==0)
        {
            cout<<"Not Found"<<endl<<endl;
            continue;
        }
        cout<<results[i].size()<<endl;
        for(int j=0;j<results[i].size();j++)
            cout<<results[i][j]+1<<" ";
        cout<<endl<<endl;
    }
}