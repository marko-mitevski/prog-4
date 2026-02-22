#include <bits/stdc++.h>
using namespace std;
vector<vector<float>> multiply(vector<vector<float>>& v,vector<vector<float>> M)
{
    vector<vector<float>> R;
    R.resize(v.size());
    for(int i=0;i<R.size();i++)
        R[i].resize(3,0);
    for(int i=0;i<v.size();i++)
    {
        for(int j=0;j<M.size();j++)
        {
            for(int k=0;k<M.size();k++)
            {
                R[i][j]+=(v[i][k]*M[k][j]);
            }
        }
    }
    return R;
}
void translate(vector<vector<vector<float>>>& points,float X,float Y)
{
    vector<vector<float>> M={
        {1,0,0},
        {0,1,0},
        {X,Y,1}
    };
    for(int i=0;i<points.size();i++)
    {
        points[i]=multiply(points[i],M);
    }
}
void rotate(vector<vector<vector<float>>>& points,float X,float Y,float a)
{
    vector<vector<float>> M={
        {1,0,0},
        {0,1,0},
        {-X,-Y,1}
    };
    vector<vector<float>> M1={
        {cos(a),sin(a),0},
        {-sin(a),cos(a),0},
        {0,0,1}
    };
    vector<vector<float>> M2={
        {1,0,0},
        {0,1,0},
        {X,Y,1}
    };
    M=multiply(M,M1);
    M=multiply(M,M2);
    for(int i=0;i<points.size();i++)
    {
        points[i]=multiply(points[i],M);
    }
}
void scale(vector<vector<vector<float>>>& points,float X,float Y,float k)
{
    vector<vector<float>> M={
        {k,0,0},
        {0,k,0},
        {0,0,1}
    };
    for(int i=0;i<points.size();i++)
    {
        points[i]=multiply(points[i],M);
    }
}
int main()
{
    vector<vector<vector<float>>> square(4,vector<vector<float>>(1));
    int ind=0;
    ifstream I;
    I.open("square.obj");
    string str="",s="";
    while(!I.eof())
    {
        getline(I,str);
        str+=" ";
        if(str[0]=='v' && str[1]==' ')
        {
            for(int i=2;i<str.length();i++)
            {
                if(str[i]!=' ')
                    s+=str[i];
                else
                {
                    if(square[ind][0].size()<2)
                    {
                        square[ind][0].push_back(stof(s));
                        s="";
                    }
                    else
                    {
                        square[ind][0].push_back(1);
                        ind++;
                        s="";
                        break;
                    }
                }
            }
        }
    }
    cout<<"Koordinati na pocetok:"<<endl;
    for(int i=0;i<4;i++)
    {
        for(int j=0;j<2;j++)
        {
            cout<<square[i][0][j]<<" ";
        }
        cout<<endl;
    }
    rotate(square,0,0,M_PI/4);
    scale(square,0,0,0.25);
    translate(square,1,1.75);
    rotate(square,1,1.75,-M_PI/4);
    scale(square,0,0,0.5);
    cout<<"Koordinati na kraj:"<<endl;
    for(int i=0;i<4;i++)
    {
        for(int j=0;j<2;j++)
        {
            cout<<square[i][0][j]<<" ";
        }
        cout<<endl;
    }
}