#include <bits/stdc++.h>
using namespace std;
int main()
{
    int V,E;
    V=(rand()%48)+3;
    E=(rand()%1001)+V-1;
    cout<<V<<" "<<E<<endl;
    vector<int> vect(V);
    vector<int> random(V);
    for(int i=1;i<V-1;i++)
    {
        vect[i]=i;
    }
    auto it=vect.begin();
    for(int i=0;i<V-2;i++)
    {
        random[i]=vect[rand()%(vect.size()-2)+1];
        it=find(vect.begin(),vect.end(),random[i]);
        vect.erase(it);
    }
    for(int i=0;i<V-2;i++)
    {
        cout<<random[i]<<" "<<random[i+1]<<" "<<(rand()%100)+1<<endl;
    }
    for(int i=V-2;i<E-6;i++)
    {
        cout<<rand()%(V-2)+1<<" "<<rand()%(V-2)+1<<" "<<(rand()%100)+1<<endl;
    }
    for(int i=0;i<3;i++)
        cout<<0<<" "<<rand()%(V-2)+1<<" "<<(rand()%100)+1<<endl;
    for(int i=0;i<3;i++)
        cout<<rand()%(V-2)+1<<" "<<V-1<<" "<<(rand()%100)+1<<endl;
    return 0;
}