#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

const string ALPHABET[33]=
{
    "а","б","в","г","д","ѓ","е","ж","з","ѕ",
    "и","ј","к","л","љ","м","н","њ","о","п",
    "р","с","т","ќ","у","ф","х","ц","ч","џ",
    "ш","ѐ","ѝ"
};

string next_utf8_char(const string& s,size_t& pos)
{
    unsigned char c=s[pos];
    size_t len=1;

    if((c & 0xE0)==0xC0)
        len=2;
    else if((c & 0xF0)==0xE0)
        len=3;
    else if((c & 0xF8)==0xF0)
        len=4;

    string ch=s.substr(pos,len);
    pos+=len;
    return ch;
}

int letterIndex(const string& ch)
{
    for(int i=0;i<33;i++)
    {
        if(ALPHABET[i]==ch)
            return i;
    }
    return -1;
}

struct TrieNode
{
    TrieNode* children[33]{};
    bool isEndOfWord=false;
};

class Trie{
private:
    TrieNode* root;
public:
    Trie()
    {
        root=new TrieNode();
    }

    void insert(const string& word)
    {
        TrieNode* node=root;
        size_t pos=0;

        while(pos<word.size())
        {
            string ch=next_utf8_char(word,pos);
            int idx=letterIndex(ch);
            if(idx==-1)
                continue;
            if(!node->children[idx])
            {
                node->children[idx]=new TrieNode();
            }
            node=node->children[idx];
        }
        node->isEndOfWord=true;
    }

    bool search(const string& word)
    {
        TrieNode* node=root;
        size_t pos=0;
        while(pos<word.size())
        {
            string ch=next_utf8_char(word,pos);
            int idx=letterIndex(ch);
            if(idx==-1 || !node->children[idx])
                return false;
            node=node->children[idx];
        }
        return node->isEndOfWord;
    }
};

int main()
{
    ifstream I("MK-dict.txt");
    Trie trie;
    string line;
    while(getline(I, line))
    {
        if(!line.empty())
            trie.insert(line);
    }
    cout<<(trie.search("македонија") ? "zborot e vo listata\n" : "zborot ne e vo listata\n");
    cout<<(trie.search("сѐ") ? "zborot e vo listata\n" : "zborot ne e vo listata\n");
    return 0;
}