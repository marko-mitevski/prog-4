#include <bits/stdc++.h>
using namespace std;
int main()
{
    int V,E;
    V=(rand()%51)+50;
    E=(rand()%1001)+V-1;
    cout<<V<<" "<<E<<endl;
    vector<int> vect(V);
    vector<int> random(V);
    for(int i=0;i<V;i++)
    {
        vect[i]=i;
    }
    auto it=vect.begin();
    for(int i=0;i<V;i++)
    {
        random[i]=vect[rand()%vect.size()];
        it=find(vect.begin(),vect.end(),random[i]);
        vect.erase(it);
    }
    for(int i=0;i<V-1;i++)
    {
        cout<<random[i]<<" "<<random[i+1]<<" "<<(rand()%201)-100<<endl;
    }
    for(int i=V-1;i<E;i++)
    {
        cout<<rand()%V<<" "<<rand()%V<<" "<<(rand()%201)-100<<endl;
    }
    return 0;
}