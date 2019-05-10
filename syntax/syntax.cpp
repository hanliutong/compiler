#include <iostream>
#include <stdio.h>
#include "define.h"
#include "lex.h"
using namespace std;
extern string IDN_NAME;
extern int NUM;
char *test = "while a = b do c = e if e = f then g = h if i = j then k = l else m = n while o = p do q = r ";// true
// char *test = "if i = j then k = l  m < n while o = p do q = r "; //false because 'm < n' should be 'm = n'
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
            return false;
        if(!C()){
            return false;
        }
        if(!eat(THEN))
			return false;
        if (!S()){
            return false;
        } 
        switch (Token)
        {//ELSE | null
        case ELSE:
            if (!eat(ELSE))
                return false;
            return S();
            break;
        default:
            return true;
            break;
        }
        break;//case IF:
    case WHILE:
        if(!eat(WHILE))
			return false;
        if(!C()){
            return false;
        }
        if(!eat(DO))
			return false;
        return S();
        break;
    case IDN:
        if(!eat(IDN))
			return false;
        if(!eat(EQU))
			return false;
        return E();
        break;
    default:
        return false;
        break;
    }
    return true;
}

bool C(){
    if(!E())
        return false;
    switch (Token)
    {
    case LESS:
        if(!eat(LESS))
			return false;
        break;
    case MORE:
        if(!eat(MORE))
			return false;
        break;
    case EQU:
        if(!eat(EQU))
			return false;
        break;
    default:
        return false;
        break;
    }
    if(!E())
        return false;
    return true;
}

bool E(){
    return eat(IDN);
}

bool run(){
    Token = getNext();
    return P();
}