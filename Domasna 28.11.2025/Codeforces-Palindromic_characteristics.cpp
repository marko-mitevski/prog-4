#include <bits/stdc++.h>
using namespace std;
long long int calculate_left_hash(int l,int r,vector<long long int> left_hashes,vector<long long int> powers,long long int m)
{
    int res=(left_hashes[r+1]-left_hashes[l]+m)%m;
    res=(res*powers[powers.size()-r-1])%m;
    return res;
}
long long int calculate_right_hash(int l,int r,vector<long long int> right_hashes,vector<long long int> powers,long long int m)
{
    int res=(right_hashes[r+1]-right_hashes[l]+m)%m;
    res=(res*powers[powers.size()-r-1])%m;
    return res;
}
bool palindrome(int l,int r,vector<long long int> left_hashes,vector<long long int> right_hashes,vector<long long int> powers,long long int m)
{
    return calculate_left_hash(l,r,left_hashes,powers,m)==calculate_right_hash(powers.size()-r-1,powers.size()-l-1,right_hashes,powers,m);
}
int main()
{
    string s;
    cin>>s;
    long long int S=s.length(),p=29;
    long int m=1000000009;
    vector<long long int> left_hashes(S+1);
    vector<long long int> right_hashes(S+1);
    vector<long long int> powers(S);
    vector<long int> results(S);
    powers[0]=1;
    for(int i=1;i<S;i++)
    {
        powers[i]=(powers[i-1]*p)%m;
    }
    left_hashes[0]=0;
    for(int i=1;i<=S;i++)
    {
        left_hashes[i]=(left_hashes[i-1]+((s[i-1]-'a'+1)*powers[i-1])%m)%m;
    }
    reverse(s.begin(),s.end());
    right_hashes[0]=0;
    for(int i=1;i<=S;i++)
    {
        right_hashes[i]=(right_hashes[i-1]+((s[i-1]-'a'+1)*powers[i-1])%m)%m;
    }
    vector<vector<int>> dp(S,vector<int>(S));
    vector<long int> answers(S,0);
    for(int len=1;len<=S;len++)
    {
        for(int i=0;i<=S-len;i++)
        {
            int j=i+len-1;
            if(!palindrome(i,j,left_hashes,right_hashes,powers,m))
                continue;
            dp[len-1][i]=1;
            int half=len/2;
            if(half>0 && palindrome(i,i+half-1,left_hashes,right_hashes,powers,m))
            {
                dp[len-1][i]=dp[half-1][i]+1;
            }
            answers[dp[len-1][i]-1]++;
        }
    }
    for(int i=S-1;i>=1;i--)
    {
        answers[i-1]+=answers[i];
    }
    for(int i=0;i<S;i++)
    {
        cout<<answers[i]<<" ";
    }
}