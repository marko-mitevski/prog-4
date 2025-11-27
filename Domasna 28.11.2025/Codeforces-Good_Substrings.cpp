#include <bits/stdc++.h>
using namespace std;
int main()
{
    string s,t;
    cin>>s>>t;
    int k,S=s.length();
    cin>>k;
    long long int p=29,m=1000000009;
    vector<long long int> h(S+1);
    vector<int> prefix(S+1);
    vector<long long int> powers(S);
    powers[0]=1;
    for(int i=1;i<S;i++)
    {
        powers[i]=(powers[i-1]*p)%m;
    }
    h[0]=0;
    prefix[0]=0;
    for(int i=1;i<=S;i++)
    {
        h[i]=(h[i-1]+((s[i-1]-'a'+1)*powers[i-1])%m)%m;
        prefix[i]=prefix[i-1]+t[s[i-1]-'a']-'0';
    }
    set<long long int> st;
    for(int i=0;i<S;i++)
    {
        for(int j=i+1;j<=S;j++)
        {
            if(j-i-(prefix[j]-prefix[i])<=k)
            {
                if(st.count((((h[j]-h[i]+m)%m)*powers[S-j])%m)==0)
                {
                    st.insert((((h[j]-h[i]+m)%m)*powers[S-j])%m);
                }
            }
            else
                break;
        }
    }
    cout<<st.size();
}