#include <bits/stdc++.h>
using namespace std;
int rabin_karp(int len,string s)
{
    if(len==0)
        return -1;
    long long int p=29;
    long long int m=1000000009;
    int l=s.size();
    vector<long long int> powers(l);
    powers[0]=1;
    for(int i=1; i<l; i++)
    {
        powers[i]=(powers[i-1]*p)%m;
    }
    vector<long long int> h(l+1);
    h[0]=0;
    for(int i=1; i<=l; i++)
    {
        h[i]=(h[i-1]+(s[i-1]-'a'+1)*powers[i-1])%m;
    }
    map<long long int,vector<int>> mp;
    for(int i=0;i<=l-len;i++)
    {
        long long int hash=(h[i+len]-h[i]+m)%m;
        hash=(hash*powers[l-i-1])%m;
        auto it=mp.find(hash);
        if(it!=mp.end())
        {
            for(int j : it->second)
            {
                if(s.substr(i,len)==s.substr(j,len))
                    return i;
            }
        }
        mp[hash].push_back(i);
    }
    return -1;
}
int main()
{
    string s;
    cin>>s;
    int S=s.length();
    int left=1,right=S-1,mid,best=0,bestPos=-1,pos;
    while(left<=right)
    {
        mid=(left+right)/2;
        pos=rabin_karp(mid,s);
        if(pos!=-1)
        {
            best=mid;
            bestPos=pos;
            left=mid+1;
        } 
        else
            right=mid-1;
    }
    if(bestPos==-1)
        cout<<"";
    else
        cout<<s.substr(bestPos,best);
}