#include <bits/stdc++.h>
using namespace std;
bool compare(string s1,string s2)
{
    if(s1.length()>s2.length())
        return true;
    if(s1.length()<s2.length())
        return false;
    for(int i=0;i<s1.length();i++)
    {
        if(s1[i]>s2[i])
            return true;
        if(s1[i]<s2[i])
            return false;
    }
    return true;
}
string add(string s1,string s2)
{
    string res="";
    int d=s1.length()-s2.length();
    if(d<0)
        d=-d;
    if(s1.length()<s2.length())
    {
        for(int i=0;i<d;i++)
        {
            s1="0"+s1;
        }
    }
    else if(s1.length()>s2.length())
    {
        for(int i=0;i<d;i++)
        {
            s2="0"+s2;
        }
    }
    int c=0;
    for(int i=s1.length()-1;i>=0;i--)
    {
        res+=to_string((int(s1[i])+int(s2[i])-96+c)%10);
        c=(int(s1[i])+int(s2[i])-96+c)/10;
    }
    if(c>0)
    {
        res+=to_string(c);
    }
    reverse(res.begin(),res.end());
    return res;
}
string subtract(string s1,string s2)
{
    string res="";
    int d=s1.length()-s2.length();
    bool b;
    if(d<0)
        d=-d;
    b=(compare(s1,s2));
    if(s1.length()<s2.length())
    {
        for(int i=0;i<d;i++)
        {
            s1="0"+s1;
        }
    }
    else if(s1.length()>s2.length())
    {
        for(int i=0;i<d;i++)
        {
            s2="0"+s2;
        }
    }
    if(!b)
        swap(s1,s2);
    for(int i=s1.length()-1;i>=0;i--)
    {
        if(int(s1[i])>=int(s2[i]))
        {
            res+=to_string(int(s1[i])-int(s2[i]));
        }
        else
        {
            for(int j=i-1;j>=0;j--)
            {
                if(s1[j]!='0')
                {
                    s1[j]-=('1'-48);
                    break;
                }
                else
                {
                    s1[j]='9';
                }
            }
            res+=to_string(int(s1[i])+10-int(s2[i]));
        }
    }
    while(res.back()=='0')
        res=res.substr(0,res.length()-1);
    if(!b)
        res+='-';
    reverse(res.begin(),res.end());
    return res;
}
string multiply(string s1,string s2)
{
    int n1=s1.size(),n2=s2.size();
    if(n1==0 || n2==0)
        return "0";
    int nn=1,mm=1;
    if(s1[0]=='-')
        nn=-1;
    if(s2[0]=='-')
        mm=-1;

    int isNeg=nn*mm;
    vector<int> result(n1 + n2, 0);
    int i1 = 0; 
    int i2 = 0; 
    for(int i=n1-1;i>=0;i--)
    {
        if(s1[i]=='-')
            continue;
        int carry=0;
        int n1=s1[i]-'0';
        i2=0;
        for(int j=n2-1;j>=0;j--)
        {
            if(s2[j]=='-')
                continue;
            int n2=s2[j]-'0';
            int sum=n1*n2+result[i1+i2]+carry;
            carry=sum/10;
            result[i1 + i2] = sum % 10;
            i2++;
        }
        if(carry>0)
            result[i1+i2]+=carry;
        i1++;
    }
    int i=result.size()-1;
    while(i>=0 && result[i]==0)
        i--;
    if(i==-1)
        return "0";
    string s="";

    while(i>=0)
    s+=to_string(result[i--]);
    if(isNeg==-1)
        s="-"+s;
    return s;
}
string modulo(string s1,string m)
{
    while(compare(s1,m) && s1!=m)
    {
        s1=subtract(s1,m);
    }
    if(s1==m)
        return {"0"};
    return s1;
}
string divide(string s)
{
    string res="";
    int c=0;
    for(int i=0;i<s.length();i++)
    {
        c*=10;
        c+=(s[i]-'0');
        res+=char(c/2 + 48);
        c%=2;
    }
    if(res[0]=='0')
    {
        res=res.substr(1);
    }
    return res;
}
class Large_number{
private:
    string content;
public:
    Large_number(string str="0")
    {
        content=str;
    }
    string get()
    {
        return content;
    }
    void set(string s="0")
    {
        content=s;
    }
    void operator=(Large_number Lg)
    {
        content=Lg.get();
    }
    bool operator==(Large_number Lg)
    {
        return content==Lg.get();
    }
    bool operator>=(Large_number Lg)
    {
        return compare(content,Lg.get());
    }
    Large_number operator+(Large_number Lg)
    {
        Large_number L(add(content,Lg.get()));
        return L;
    }
    Large_number operator-(Large_number Lg)
    {
        Large_number L(subtract(content,Lg.get()));
        return L;
    }
    Large_number operator*(Large_number Lg)
    {
        Large_number L(multiply(content,Lg.get()));
        return L;
    }
    Large_number operator%(Large_number Lg)
    {
        Large_number L(modulo(content,Lg.get()));
        return L;
    }
};
int main()
{
    Large_number n("91072");
    vector<pair<Large_number,Large_number>> vect;
    Large_number L1("2");
    Large_number L2("4");
    Large_number m("4");
    vect.push_back({L1,L2});
    Large_number counter("3");
    while(n>=counter)
    {
        if(m>=counter && !(m==counter))
        {
            L1=counter;
            L2=L1*L1;
            vect.push_back({L1,L2});
        }
        else
        {
            for(int i=0;i<vect.size();i++)
            {
                if(vect[i].second==m)
                {
                    vect[i].second=vect[i].second+vect[i].first;
                }
            }
        }
        m=vect[0].second;
        for(int i=1;i<vect.size();i++)
        {
            if(m>=vect[i].second)
                m=vect[i].second;
        }
        counter=counter+Large_number("1");
    }
}