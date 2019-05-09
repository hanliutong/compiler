#include <iostream>
#include <stdio.h>
#include "define.h"
#include "lex.h"
using namespace std;
char *test = "while a = b do c = f";
int getNext(){
    return scan(test);
}
int Token;
bool eat(int token){
    if (Token == token){
        Token = getNext();
        return true;
    }
    else
        return false;
}
bool L();
bool P();
bool S();
bool C();
bool E();


bool P(){
    
    if (L()){
        switch (Token)
        {
        case 0:
            return true;
            break;
        default:
            return P();
            break;
        }
    }
    else
        return false;
}

bool L(){
    return S();
}

bool S(){
    switch (Token)
    {
    case IF :
        if (!eat(IF))
            return 0;
        C();
        eat(THEN);
        S();
        break;
    case WHILE:
        eat(WHILE);
        C();
        eat(DO);
        S();
        break;
    case IDN:
        eat(IDN);
        eat(EQU);
        E();
        break;
    default:
        return false;
        break;
    }
    return true;
}

bool C(){
    E();
    switch (Token)
    {
    case LESS:
        eat(LESS);
        break;
    case MORE:
        eat(MORE);
        break;
    case EQU:
        eat(EQU);
        break;
    default:
        return false;
        break;
    }
    E();
    return true;
}

bool E(){
    return eat(IDN);
}

int main(){
    
    //char *test = "";
    // while(*test){
    //     cout << scan(test) << endl;
    // }
    Token = getNext();
    cout << P() << endl;
}