//init from steven macbook pro
//2017-10-21


#include<iostream>
#include<string>
using namespace std;

class cstring {
private:
    char *str;
    int len;
    int sta = 0;
public:
    cstring(const char*);
    cstring() :str(nullptr), len(0), sta(0) {}
    cstring(size_t c){
        len = c;
        sta = 0;
        str = new char[len + 1];
    }
    friend istream & operator >> (istream &, cstring &);
    friend ostream & operator << (ostream &, cstring &);
    int& length();
    int& find(const char ch);
    void printStr();
    ~cstring();
};
cstring::~cstring() {
    delete[] str;
    len = 0;
    str = nullptr;
}
cstring::cstring(const char* a) {
    len = strlen(a);
    sta = 0;
    str = new char[strlen(a) + 1];
    for (int i = 0; i < strlen(a) + 1; i++) {
        str[i] = a[i];
    }
}
istream& operator >> (istream& in, cstring& c){
    char tmp[100];
    if (in >> tmp){
        delete[] c.str;
        c.len = strlen(tmp);
        c.str = new char[c.len + 1];
        strcpy(c.str, tmp);
    }
    return in;
}
ostream & operator << (ostream & os, cstring &c) {
    if (c.str != NULL)
    {
        os << c.str;
    }
    return os;
}
void cstring::printStr() {
    cout << str << endl;
}
int& cstring::length() {
    if (!str) {
        len = 0;
    }
    else {
        char *a = str;
        for (; a[len] != '\0'; len++);
    }
    return len;
}
int& cstring::find(const char ch) {
    sta = 0;
    for (; sta < strlen(str); sta++) {
        if (str[sta] == ch) {
            return sta;
        }
    }
}
int main() {
    cout << "c = ";
    cstring c = "liu yong";
    c.printStr();
    cout << "重载 >> :\n";
    cstring b;
    cin >> b;
    cout << "b = ";
    b.printStr();
    cout << "重载 << : \nc = " << c << endl;
    return 0;
}




/*
#include<iostream>
#include<iomanip>

using namespace std;
class complex
{
public:
    complex(double r = 0, double i = 0) :real(r), imag(i) {}
    complex(const complex &c) :real(c.real), imag(c.imag) {}
    friend complex operator *(const complex &, const complex &);
    friend complex operator *(const complex &, const double &);
    friend complex operator *(const double &, const complex &);
    friend complex operator /(const complex &, const complex &);
    friend complex operator /(const complex &, const double &);
    friend complex operator /(const double &, complex &);
    void print() {
        cout << '(' << setprecision(2) << real << ',' << setprecision(2) << imag << ')' << endl;
    }
private:
    double real, imag;
};
complex operator * (const complex &a, const complex &b) { return complex(a.real*b.real - a.imag*b.imag, a.imag*b.real + b.imag*a.real); }
complex operator *(const complex &a, const double &c) { return complex(a.real*c, a.imag*c);
}
complex operator *(const double &c, const complex &a) {
    return complex(c*a.real, c*a.imag); }
complex operator /(const complex &a, const complex &b) {
    if (b.imag == 0 && b.real == 0){ throw 0; }
    return complex((a.real*b.real + a.imag*b.imag) / (b.real*b.real + b.imag*b.imag),
                   (a.imag*b.real - b.imag*a.real) / (b.real*b.real + b.imag*b.imag));
}
complex operator /(const complex &a, const double &c) {
    if (c == 0){ throw 1; }
    return complex(a.real / c, a.imag / c);
}
complex operator /(const double &c, complex &a) {
    if (a.imag == 0 && a.real == 0){ throw 2; }
    return complex((a.real*c) / (a.real*a.real + a.imag*a.imag),
                   (a.imag*c) / (a.real*a.real + a.imag*a.imag));
}
int main() {
    complex a(3.6, 6), b(4, 8);
    double c = 2.8;
    cout << "a * b = ";
    (a*b).print();
    cout << "c * a = ";
    (c*a).print();
    cout << "a * c = ";
    (a*c).print();
    try{
        cout << "a / b = ";
        (a / b).print();
        cout << "a / c = ";
        (a / c).print();
        cout << "c / a = ";
        (c / a).print();
    }catch (int e){
        if (e == 0){
            perror("|b| = 0");
            exit(1);
        }
        if (e == 1) {
            perror("c = 0");
            exit(1);
        }
        if (e == 2) {
            perror("|a| = 0");
            exit(1);
        }
    }
    return 0;
}



/*#include<iostream>
using namespace std;
class cstring {
private:
    char *str;
    int len;
    int sta = 0;

public:
    cstring(const char* str);
    cstring() :str(nullptr), len(0), sta(0) {}
    cstring(size_t c){
        len = c;
        sta = 0;
        str = new char[len + 1];
    }
    friend cstring operator + (const cstring &, const cstring &);
    cstring & operator += (const cstring &);
    int& length();
    int find(const char ch);
    void printStr();
    ~cstring();
};

cstring::~cstring() {
    delete [] str;
    len = 0;
}
cstring::cstring(const char* a) {
    len = strlen(a);
    sta = 0;
    str = new char[len + 1];
    strcpy(str, a);
}

//重载 + 运算符
cstring operator + (const cstring & a, const cstring & b) {
    cstring c;
    c.len = a.len + b.len;
    c.str = new char[c.len + 1];
    strcpy(c.str, a.str);
    strcat(c.str, b.str);
    c.sta = 0;
    return c;
}
//重载 += 运算符
cstring & cstring::operator+= (const cstring &other) {
    if (other.str == nullptr){
        return *this;
    }
    len = len + other.len;
    char * cpstr = str;
    str = new char[len + 1];
    strcpy(str, cpstr);
    strcat(str, other.str);
    return *this;
}

void cstring::printStr() {
    cout << str << endl;
}

int& cstring::length() {
    if (!str) {
        len = 0;
    }
    else {
        char *a = str;
        for (; a[len] != '\0'; len++);
    }
    return len;
}

int cstring::find(const char ch) {
    sta = 0;
    for (; sta < strlen(str); sta++) {
        if (str[sta] == ch) {
            return sta;
        }
    }
    return 0;
}

int main() {
    cstring c1 = "liu ";
    cstring c2 = "yong ";
    cout << "c1 = liu \n";
    cout << "c2 = yong \n";
    cstring c3;
    cout << "c3 = c1 :\n";
    c3 = c1;
    c3.printStr();
    cstring a = c1 + c2;
    cout << "a = c1 + c2 :\n";
    a.printStr();
    cstring c4 = "liuyong";
    cout << "c4 = liuyong!\n";
    a += c4;
    cout << "a += c4 :\n";
    a.printStr();
    return 0;
}

/*#include<iostream>
using namespace std;
class newCstring{
public:
    newCstring();
    ~newCstring();
    void putstr();
};
newCstring::newCstring() {}
newCstring::~newCstring() {}
void newCstring::putstr() {}
class cstring {
private:
    char *str;
    int len;
    int sta = 0;
public:
    friend class newCstring;
    cstring(const char* str);
    cstring() :str(nullptr), len(0), sta(0) {}
    cstring(size_t c){
        len = c;
        sta = 0;
        str = new char[len + 1];
    }
    cstring(const cstring & a);
    cstring(cstring && a);
    void printStr();
    ~cstring();
};
cstring::~cstring() {
    delete[] str;
    len = 0;
    str = nullptr;
}
cstring::cstring(const char* a) {
    len = strlen(a);
    sta = 0;
    str = new char[strlen(a)];
    for (int i = 0; i < strlen(a) + 1; i++) {
        str[i] = a[i];
    }
}
cstring::cstring(const cstring &a) {
    str = new char[a.len + 1];
    len = a.len;
    sta = 0;
    for (int i = 0; i < a.len + 1; i++) {
        str[i] = a.str[i];
    }
}
cstring::cstring(cstring && a) {
    len = a.len;
    sta = a.sta;
    str = a.str;
    a.str = nullptr;
}
int main() {
    cout << "c =cpp work " << endl;
    cstring c = "cpp work";
    cstring a(c);
    cout << "a = cpp work";
    return 0;
}

/*
 #include<iostream>
using namespace std;

class cstring {
private:
    char *str;
    int len;
    int sta = 0;

public:
    cstring(const char* str);
    cstring() :str(nullptr), len(0), sta(0) {}
    cstring(size_t c){
        len = c;
        sta = 0;
        str = new char[len + 1];
    }
    cstring(const cstring & a);
    cstring(cstring && a);
    int& length();
    int& find(const char ch);
    void printStr();
    ~cstring();
};
cstring::cstring(const char* a){
    len = strlen(a);
    sta = 0;
    str = new char[strlen(a)];
    for (int i = 0; i < strlen(a) + 1; i++) {
        str[i] = a[i];
    }
}
cstring::~cstring() {
    delete[] str;
    len = 0;
    sta = 0;
    str = nullptr;
}
cstring::cstring(const cstring &a) {
    str = new char[a.len + 1];
    len = a.len;
    sta = 0;
    for (int i = 0; i < a.len + 1; i++){
        str[i] = a.str[i];
    }
}

cstring::cstring(cstring && a) {
    len = a.len;
    sta = a.sta;
    str = a.str;
    a.str = nullptr;
}

void cstring::printStr() {
    cout << str << endl;
}

int& cstring::length() {
    if (!str) {
        len = 0;
    }
    else {
        char *a = str;
        for (; a[len] != '\0'; len++);
    }

    return len;
}

int& cstring::find(const char ch) {
    sta = 0;
    for (; sta < strlen(str); sta++) {
        if (str[sta] == ch) {
            return sta;
        }
    }
}

int main() {
    cout << "c = ";
    cstring c = "cpp work";
    c.printStr();
    cstring a(c);
    cout << "a = ";
    a.printStr();
    return 0;
}*/


/*
#include <iostream>
using namespace std;

class cstring {
private:
    char *str;
    int len;
    int sta = 0;
public:
    cstring(const char *str);

    cstring() : str(nullptr), len(0), sta(0) {}

    cstring(size_t c){
        len = c;
        sta = 0;
        str = new char[len + 1];
    }
    int &length();
    int &find(const char ch);
    void printStr();
    ~cstring();
    };

    cstring::~cstring() {
        delete[] str;
        len = 0;
        str = nullptr;
        sta = 0;
    }

    cstring::cstring(const char *a) {
        str = new char[strlen(a) + 1];
        for (int i = 0; i < strlen(a) + 1; i++) {
            str[i] = a[i];
        }
    }
    void cstring::printStr() {
        cout << str << endl;
    }
    int &cstring::length() {
        if (!str) {
            len = 0;
        } else {
            char *a = str;
            for (; a[len] != '\0'; len++);
        }
        return len;
    }

    int &cstring::find(const char ch) {
        sta = 0;
        for (; sta < strlen(str); sta++) {
            if (str[sta] == ch) {
                return sta;
            }
        }
    }

int main() {
    cstring cstring1 = "cpp work";
    cout << "cstring1 = ";
    cstring1.printStr();
    system("stop");
    return 0;
}
*/
/*class cstring {
private:
    char *str;		//保存字符串
    int len;
    int sta = 0;

public:
    cstring::cstring(const char* str = NULL);				//构造函数
    void operator+(const cstring &other);					//operator+
    bool operator==(const cstring &other);				    //operator==
    int& length();
    //只查找字符 匹配第一个查找到的字符，并返回字符的位置
    int& find(const char ch);
    void printStr();

    cstring::~cstring();

    cstring& operator += () {
        //Todo +=
    }
    friend cstring operator + (const cstring& c1, const cstring& c2);
};
cstring operator + (const cstring& c1, const cstring& c2) {
    return cstring();
}*/


/*class carnivore {
protected:
    string name;
public:
    static int counter;
    carnivore (string n = "carnivore") {name = n;}
    void prey () {cout << name << "prey" << endl;}
    string what ()const {return name;}
};

int carnivore::counter = 0;

class felid :public carnivore {
protected:
    bool slitPupil;
public:
    felid(string n = "tiger", bool s = false) {
        name = n;
        slitPupil = s;
        ++carnivore::counter;
    }
};

class tiger :public felid {
public:
    tiger(string n = "tiger",bool s = false) {name = n;slitPupil = s;}
    void roar() {
        cout << name << "roar" <<endl;
        ++carnivore::counter;
    }

};

int main() {
    tiger t;
    t.roar();
    cout << carnivore::counter << endl;
    return 0;
}*/

/*class Student  //基类的声明
{
public:
    Student()
    {
        num = 1;
        name = 'Z';
        sex = 'm';
    }
    void myshow()
    {
        cout<<"num:"<<num<<endl<<"name:"<<name<<endl<<"sex:"<<sex<<endl;
    }
private:
    int num;
    char name;
    char sex;
};
class Student1:public Student //派生类的声明
{
public:
    Student1()
    {
        age = 16;
    }
    void myshow1()
    {
        myshow();
        cout<<"age:"<<age<<endl;
    }
private:
    int age;
};
int main()
{
    Student stu;
    stu.myshow();
    Student1 stu1;
    stu1.myshow1();
    getchar();
    return 0;
}*/
/*
class String {
private:
    int type;
public:
    String() {type = 1;}
    void play() {
       cout << "strings is" << type << endl;
    }
};

class violin: public String {
public:
    violin() {strings = 4;}
    void playviolin() {
        cout << "violin is" << strings << endl;
    }

private:
    int strings;
};

int main() {
    String string1;
    string1.play();
    violin violin1;
    violin1.playviolin();
    getchar();
    return 0;
}*/