//
// Created by Mac Of Steven on 2017/9/24.
//

class cstring {
private:
    char *str;
    int len;
    int sta = 0;

public:
    cstring(const char* str);
    void operator+(const cstring &other);
    bool operator==(const cstring &other);
    int& length();
    int& find(const char ch);
    void printStr();

    ~cstring();
};
