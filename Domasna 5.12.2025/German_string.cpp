#include <iostream>
#include <cstring>
using namespace std;

class GermanString{
private:
    static const size_t short_string_size = 23;
    size_t length_;
    bool isSmall;

    union
    {
        char small[short_string_size + 1];
        char* content;
    };

    char* data()
    {
        return isSmall ? const_cast<char*>(small) : content;
    }

    const char* data() const
    {
        return isSmall ? small : content;
    }

    void set(const char* str, size_t len)
    {
        length_ = len;
        if(len <= short_string_size)
        {
            isSmall = true;
            memcpy(small, str, len + 1);
        }
        else
        {
            isSmall = false;
            content = new char[len + 1];
            memcpy(content, str, len + 1);
        }
    }

public:
    GermanString() : length_(0), isSmall(true)
    {
        small[0] = '\0';
    }

    GermanString(const char* str)
    {
        set(str, strlen(str));
    }

    GermanString(const GermanString& str)
    {
        set(str.data(), str.length_);
    }

    GermanString(GermanString&& str) : length_(str.length_), isSmall(str.isSmall)
    {
        if(isSmall)
        {
            memcpy(small, str.small, length_ + 1);
        }
        else
        {
            content = str.content;
            str.content = nullptr;
        }
        str.length_ = 0;
        str.isSmall = true;
        str.small[0] = '\0';
    }

    GermanString& operator=(const GermanString& str)
    {
        if(this == &str)
            return *this;

        if(!isSmall && content)
            delete [] content;

        set(str.data(), str.length_);
        return *this;
    }

    GermanString& operator=(GermanString&& str)
    {
        if(this == &str) return *this;

        if(!isSmall && content)
            delete [] content;

        length_ = str.length_;
        isSmall = str.isSmall;

        if(isSmall)
        {
            memcpy(small, str.small, length_ + 1);
        }
        else
        {
            content = str.content;
        }
        str.length_ = 0;
        str.isSmall = true;
        str.small[0] = '\0';
        return *this;
    }

    ~GermanString()
    {
        if(!isSmall && content)
            delete [] content;
    }

    size_t length() const
    {
        return length_;
    }

    char& operator[](size_t i)
    {
        return data()[i];
    }

    const char& operator[](size_t i) const
    {
        return data()[i];
    }

    bool operator==(const GermanString& str) const
    {
        if(length_ != str.length_)
            return false;
        return memcmp(data(), str.data(), length_) == 0;
    }

    GermanString operator+(const GermanString& str) const
    {
        size_t newLen = length_ + str.length_;
        GermanString result;

        if(!result.isSmall && result.content)
            delete [] result.content;

        if(newLen <= short_string_size)
        {
            result.isSmall = true;
            result.length_ = newLen;
            memcpy(result.small, data(), length_);
            memcpy(result.small + length_, str.data(), str.length_ + 1);
        }
        else
        {
            result.isSmall = false;
            result.length_ = newLen;
            result.content = new char[newLen + 1];
            memcpy(result.content, data(), length_);
            memcpy(result.content + length_, str.data(), str.length_ + 1);
        }
        return result;
    }

    friend ostream& operator<<(ostream& o, const GermanString& s)
    {
        return o << s.data();
    }
};

int main() {
    GermanString a("Hello");
    GermanString b(" World!");
    GermanString c = a + b;

    cout << c << endl;
    cout << c.length() << endl;

    c[6] = 'w';
    cout << c << endl;

    cout << (a == b) << endl;
    cout << (GermanString("Hi") == GermanString("Hi")) << endl;
    return 0;
}