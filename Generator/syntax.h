#include <iostream>
#include <stdio.h>
#include "define.h"
#include "lex.h"
#include "attr.h"
using namespace std;
extern string IDN_NAME;
extern int NUM;
//char *test = "while a>b do while y<z do y = x; c=b; "; // true
char *test = "while a>b do if x2 = x3 then while y<z do y = x; c=b; "; // true

/*
while a < b 
    do 
    while c>d 
        do 
        x = y;
e = f;
*/

// char *test = "if i = j then k = l  m < n while o = p do q = r "; //false because 'm < n' should be 'm = n'
int flag = 0;
int getNext(){
    return scan(test);
}
int Token;
int Lable = 0;
int newLable(){
    return (++Lable);
}
bool eat(int token){
    if (Token == token){
        Token = getNext();
        return true;
    }
    else
        cout <<" curT : "<< Token <<" expect : "<< token << endl;
        return false;
}
bool L(AttrL &thisL);
bool P(AttrP &thisP);
bool S(AttrS &thisS);
bool C(AttrC &thisC);
bool E(AttrE &thisE);

bool P(AttrP &thisP){
    AttrL attrL(&thisP);
    AttrP attrP(&thisP);
    if (L(attrL)){
        switch (Token)
        {
        case 0:
            thisP.code = attrL.code;
            return true;
            break;
        case RCUR:
            thisP.code = attrL.code;
            return true;
            break;
        default:
            if(!P(attrP))
                return false;
            thisP.code = attrL.code + attrP.code;
            return true;
            break;
        }
    }
    else
        return false;
}

bool L(AttrL &thisL){
    AttrS attrS(&thisL);
    if(!S(attrS))
        return false;
    if(!eat(SEMI))
        return false;
    thisL.code = attrS.code;
    return true;
}

bool S(AttrS &thisS){
    cout << thisS.father->getClass();
    AttrC attrC(&thisS);
    AttrS S1(&thisS);
    AttrS S2(&thisS);
    AttrE attrE(&thisS);
    AttrP attrP(&thisS);
    string IDplace;
    string str = "";
    switch (Token)
    {
    case IF :
        attrC.T = newLable();
        attrC.F = thisS.next;
        S1.begin = attrC.T;
        S1.next = thisS.next;

        if (!eat(IF))
            return false;
        if(!C(attrC)){
            return false;
        }
        if(!eat(THEN))
			return false;
        if (!S(S1)){
            return false;
        } 
        switch (Token)
        {//ELSE | null
        case ELSE:
            if (!eat(ELSE))
                return false;
            if (S(S2))
                return false;
            break;
        default:
            break;
        }
        thisS.code += attrC.code;
        thisS.gen("L" + to_string(attrC.T) + ": ");
        thisS.code += S1.code;
        return true;
        break;//case IF:
    case WHILE:
        if (thisS.father->getClass() != AttrS_){//非S嵌套
            thisS.begin = newLable();
            attrC.T = newLable();
        }
        else{//S嵌套
            attrC.T = newLable();
            //thisS.begin = attrC.T;
        }   
        attrC.F = thisS.next;
        S1.begin = attrC.T;
        S1.next = thisS.begin;
        if(!eat(WHILE))
			return false;
        if(!C(attrC)){
            
            return false;
        }
        if(!eat(DO))
			return false;
        if(!S(S1))
			return false;
        if (thisS.father->getClass() != AttrS_)
            str += "L" + to_string(thisS.begin) + ": ";
        str += attrC.code;
        thisS.gen(str);
        thisS.gen("L" + to_string(attrC.T)+ ": " + S1.code + "goto(S.b) L" + to_string(thisS.begin));
        //flag--;
        return true;
        break;
    case IDN:
        IDplace = IDN_NAME;
        if(!eat(IDN))
			return false;
        if(!eat(EQU))
			return false;
        if(!E(attrE))
			return false;
        if(thisS.father->getClass() == AttrL_){
            thisS.gen("L" + to_string(thisS.next) + ": ");
        }
        thisS.code += attrE.code;
        thisS.gen(IDplace + ":=" + attrE.place);
        return true;
        break;
    case LCUR:
        if(!eat(LCUR))
            return false;
        if(!P(attrP))
            return false;
        if(!eat(RCUR))
            return false;
        thisS.code = attrP.code;
        return true;
        break;
    default:
        return false;
        break;
    }
    return true;
}

bool C(AttrC &thisC){
    AttrE E1(&thisC);
    AttrE E2(&thisC);
    string op;
    if(!E(E1))
        return false;
    switch (Token)
    {
    case LESS:
        if(!eat(LESS))
			return false;
        op = "<";
        break;
    case MORE:
        if(!eat(MORE))
			return false;
        op = ">";
        break;
    case EQU:
        if(!eat(EQU))
			return false;
        op = "=";
        break;
    default:
        return false;
        break;
    }
    if(!E(E2))
        return false;
    
    thisC.gen("if " + E1.place + op + E2.place + " goto(C.T) L" + to_string(thisC.T));
    thisC.gen("goto(C.F) L" + to_string(thisC.F));
    return true;
}

bool E(AttrE &thisE){
    thisE.place = IDN_NAME;
    return eat(IDN);
}

bool run(){
    Token = getNext();
    AttrP BEGIN_P(NULL);
    if (P(BEGIN_P)){
        cout << endl << BEGIN_P.code << endl;
        return true;
    }
    else{
        cout <<"\tToken : "<< Token << endl;
        return false;
    }
}