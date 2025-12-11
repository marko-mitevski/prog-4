#include <bits/stdc++.h>
using namespace std;
struct Node{
    Node* children[53];
    bool leaf;
    Node()
    {
        leaf=true;
        for(int i=0;i<53;i++)
        {
            children[i]=NULL;
        }
    }
};
int index(char c)
{
    if(97<=int(c) && int(c)<=122)
    {
        return int(c)-97;
    }
    else if(65<=int(c) && int(c)<=90)
    {
        return int(c)-39;
    }
    else
    {
        return 52;
    }
}
void add_to_Trie(Node* root,string str)
{
    int idx;
    for(int i=0;i<str.length();i++)
    {
        idx=index(str[i]);
        if(root->children[idx]==NULL)
        {
            root->leaf=false;
            root->children[idx]=new Node();
        }
        root=root->children[idx];
    }
}
bool in_Trie(Node* root,string str)
{
    int idx;
    for(int i=0;i<str.length();i++)
    {
        idx=index(str[i]);
        if(root->children[idx]!=NULL)
        {
            root=root->children[idx];
        }
        else
            return false;
    }
    return root->leaf;
}
int main()
{
    Node* root=new Node();
    ifstream I("English_words.txt");
    string s;
    while(getline(I,s))
    {
        if(s[0]!='#')
        {
            add_to_Trie(root,s);
        }
    }
}