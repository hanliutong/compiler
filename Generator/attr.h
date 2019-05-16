#include <iostream>
#include "define.h"
using namespace std;
class Attr{ 
public:
    Attr* father;
    string code = "";
    void gen(string str){
        code += str;
        code += "\n";
    }
    virtual int getClass() = 0;//纯虚函数
};
class AttrP : public Attr{
public:
    AttrP(Attr* point){
        father = point;
    }
    int getClass(){
        return AttrP_;
    }
};

class AttrL : public Attr{
public:
    AttrL(Attr* point){
        father = point;
    }
    int getClass(){
        return AttrL_;
    }
};

class AttrS : public Attr{
public:
    AttrS(Attr* point){
        father = point;
    }
    int getClass(){
        return AttrS_;
    }
    Attr *father;
    int begin;
    int next;
};

class AttrC : public Attr{
public:
    AttrC(Attr* point){
        father = point;
    }
    int getClass(){
        return AttrC_;
    }
    int T;
    int F;
};

class AttrE: public Attr{
public:
    AttrE(Attr* point){
        father = point;
    }
    int getClass(){
        return AttrE_;
    }
    string place;
    //todo
};