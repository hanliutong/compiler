#include <iostream>
#include <stdio.h>
#include "define.h"
#include "lex.h"
#include "attr.h"
using namespace std;
extern string IDN_NAME;
extern int NUM;
//char *test = "while a>b do while y<z do y = x; c=b; "; // true
char *test = "while a>b do if x2 + c = x3 then while y<z do y = x; c=b+r-x+y; "; // true

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
int Temp = 0;
int newTemp(){
    return (++Temp);
}
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
bool F(AttrF &thisF);
bool G(AttrG &thisG);
bool N(AttrN &thisN);
bool T(AttrT &thisT);

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
        thisS.gen(IDplace + " := " + attrE.place);
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
    thisC.code = E1.code + E2.code;
    thisC.gen("if " + E1.place + op + E2.place + " goto(C.T) L" + to_string(thisC.T));
    thisC.gen("goto(C.F) L" + to_string(thisC.F));
    return true;
}

// bool E(AttrE &thisE){
//     thisE.place = IDN_NAME;
//     return eat(IDN);
// }

bool E(AttrE &thisE){
	AttrT T1(&thisE);
    AttrN N1(&thisE);
	// thisE.temp=newTemp();
	if(!T(T1))
		return 0;
    thisE.place = T1.place;
	if(!N(N1))
		return 0;
    if(!N1.place.empty())
        thisE.place = N1.place;//t(x)
    thisE.code=T1.code+N1.code;
	return true;

}



bool T(AttrT &thisT){
	AttrF F1(&thisT);
	AttrG G1(&thisT);
	// attrT.place=newTemp();
	if(!F(F1))
		return 0;
	if(!G(G1))
		return 0;
    thisT.place=F1.place+G1.place;
	thisT.code=F1.code+G1.code;
	return true;
}

bool N(AttrN &thisN){
	AttrT T1(&thisN);
	AttrN N1(&thisN);
	AttrE E1(&thisN);
	string op;
	//E1.temp=newTemp();
	switch (Token)
	{
		case ADD:
            thisN.place="t"+to_string(newTemp());
			if(!eat(ADD))
				return 0;
			op='+';
			if(!T(T1))
				return 0;
			if(!N(N1))
				return 0;
			break; 
		case SUB:
            thisN.place="t"+to_string(newTemp());
			if(!eat(SUB))
				return 0;
			op='-';
			if(!T(T1))
				return 0;
			if(!N(N1))
				return 0;
			break;
		default :
			return true;//express NULL
	}
	// N1.code=T1.code+N1.code;
	// thisN.gen("t"+to_string(E1.temp)+" := "+T1.place+op+N1.place);
    thisN.gen(thisN.place+": "+ ((AttrE*)thisN.father)->place+op+T1.place);
    thisN.code += N1.code;
    if(!N1.place.empty())
        thisN.place = N1.place;
    return true;
}
//
bool G(AttrG &thisG){
	AttrF F1(&thisG);
	AttrG G1(&thisG);
	AttrT T1(&thisG);
	string op;
	// T1.temp=newTemp();
	switch (Token)
	{
		case MUL:
            thisG.temp=newTemp();
			if(!eat(MUL))
				return 0;
//			eat(MUL);
//			if(Token==SEMI){
//				return false;
//				break;
//			}
			op='*';
			if(!F(F1))
				return 0;
			if(!G(G1))
				return 0;
			break;
		case DIV:
            thisG.temp=newTemp();
			if(!eat(DIV))
				return 0;

			if(Token==SEMI){
				return false;
				break;
			}
			op='*';
			if(!F(F1))
				return 0;
			if(!G(G1))
				return false;
			break;

		default :
			return true;//express NULL
	} 
	G1.code=F1.code+G1.code;
	thisG.gen("t"+to_string(T1.temp)+":="+G1.place+op+F1.place);
	return true;
}
//
bool F(AttrF &thisF){
	AttrE E1(&thisF);
	AttrF F1(&thisF);
	switch (Token)
	{
		case LPAR:
			if(!eat(LPAR))
				return 0;
			if (!E(E1))
				return 0;
			F1.place=E1.place;
			F1.code=E1.code;
			if(!eat(RPAR))
				return 0;
			break;
		case IDN:
			thisF.place = IDN_NAME;
			return eat(IDN);
			break;
		case INT8:
			thisF.place = NUM;
			return eat(INT8);
			break;
		case INT10:
			thisF.place = NUM;
			return eat(INT10);
			break;
		case INT16:
			thisF.place = NUM;
			return eat(INT16);
			break;	
		default:
			return false;	
			break;
	}
	return true;
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
