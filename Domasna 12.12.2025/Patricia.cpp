#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

struct PatriciaNode;

struct Edge{
    string label;
    PatriciaNode* child;
};

struct PatriciaNode{
    bool isEnd=false;
    vector<Edge> edges;
};

class PatriciaTrie{
private:
    PatriciaNode* root;

    static size_t longest_common_prefix_length(const string& a,const string& b)
    {
        size_t i=0;
        while(i<a.size() && i<b.size() && a[i]==b[i])
            i++;
        return i;
    }

    void insert(PatriciaNode* node,const string& word)
    {
        for(auto& edge : node->edges)
        {
            size_t common=longest_common_prefix_length(edge.label,word);
            if(common==0)
                continue;
            if(common==edge.label.size())
            {
                insert(edge.child,word.substr(common));
                return;
            }

            PatriciaNode* splitNode=new PatriciaNode();

            splitNode->edges.push_back({edge.label.substr(common),edge.child});

            if(common<word.size())
            {
                PatriciaNode* newNode=new PatriciaNode();
                newNode->isEnd=true;
                splitNode->edges.push_back({word.substr(common),newNode});
            }
            else
            {
                splitNode->isEnd=true;
            }

            edge.label=edge.label.substr(0, common);
            edge.child=splitNode;
            return;
        }
        PatriciaNode* newNode=new PatriciaNode();
        newNode->isEnd=true;
        node->edges.push_back({word,newNode});
    }

public:
    PatriciaTrie()
    {
        root=new PatriciaNode();
    }

    void insert(const string& word)
    {
        if(!word.empty())
            insert(root, word);
    }

    bool search(const string& word)
    {
        const PatriciaNode* node=root;
        string remaining=word;
        while(!remaining.empty())
        {
            bool found=false;
            for(auto edge : node->edges)
            {
                if(edge.label.length()<=remaining.length() && remaining.substr(0,edge.label.length())==edge.label)
                {
                    remaining.erase(0,edge.label.size());
                    node=edge.child;
                    found=true;
                    break;
                }
            }
            if(!found)
                return false;
        }
        return node->isEnd;
    }
};

int main()
{
    ifstream I("English_words.txt");
    PatriciaTrie trie;
    string word;
    while(getline(I,word))
    {
        trie.insert(word);
    }
    cout<<(trie.search("example") ? "word is in list\n" : "word is not in list\n");
    cout<<(trie.search("him") ? "word is in list\n" : "word is not in list\n");
    return 0;
}