#include <iostream>
#include <stdio.h>
#include "define.h"
#include "lex.h"
#include "attr.h"
using namespace std;
extern string IDN_NAME;
extern int NUM;

char *test = 
"while (a3+15)>0xa do\n\tif x2 = 07 then\n\t\twhile y<z do\n\t\t\ty = x * y / z;\nc=b*c+d;\n";
// char *test = "while (a3+15)>0xa do if x2 = 07 then while y<z do y = x * y / z; c=b*c+d;";

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
bool E(AttrE &thisE);
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
        thisS.gen("L" + to_string(attrC.T)+ ": " + S1.code + "goto L" + to_string(thisS.begin));
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
    thisC.gen("if " + E1.place + op + E2.place + " goto L" + to_string(thisC.T));
    thisC.gen("goto L" + to_string(thisC.F));
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
        thisE.place = N1.place;
    thisE.code =T1.code + N1.code;
        
    return true;

}



bool T(AttrT &thisT){
	AttrF F1(&thisT);
	AttrG G1(&thisT);
	if(!F(F1))
		return 0;
	thisT.place = F1.place;
	if(!G(G1))
		return 0;
	if(!G1.place.empty())
        thisT.place = G1.place;  
    thisT.code=F1.code+G1.code;
	return true;
}

bool N(AttrN &thisN){
	AttrT T1(&thisN);
	AttrN N1(&thisN);
	AttrE E1(&thisN);
	string op;
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
    thisN.gen(thisN.place+" := "+ ((AttrE*)thisN.father)->place+op+T1.place);
    thisN.code += N1.code + T1.code;
    if(!N1.place.empty())
        thisN.place = N1.place;
    return true;
}

bool G(AttrG &thisG){
	AttrF F1(&thisG);
	AttrG G1(&thisG);
	AttrT T1(&thisG);
	string op;
	switch (Token)
	{
		case MUL:
            thisG.place="t"+to_string(newTemp());
			if(!eat(MUL))
				return 0;
			op='*';
			if(!F(F1))
				return 0;
			if(!G(G1))
				return 0;
			break;
		case DIV:
            thisG.place="t"+to_string(newTemp());
			if(!eat(DIV))
				return 0;
			op='/';
			if(!F(F1))
				return 0;
			if(!G(G1))
				return false;
			break;

		default :
			return true;//express NULL
		
	} 
	thisG.gen(thisG.place+" := "+ ((AttrT*)thisG.father)->place+op+F1.place);
    thisG.code += G1.code;
    if(!G1.place.empty())
        thisG.place = G1.place;
    return true;
}
//
bool F(AttrF &thisF){
	AttrE E1(&thisF);
	switch (Token)
	{
		case LPAR:
			if(!eat(LPAR))
				return 0;
			if (!E(E1))
				return 0;
			thisF.place=E1.place;
			thisF.code=E1.code;
            if(!eat(RPAR))
				return 0;
			break;
		case IDN:
			thisF.place = IDN_NAME;
			return eat(IDN);
			break;
		case INT8:
			thisF.place = to_string(NUM);
			return eat(INT8);
			break;
		case INT10:
			thisF.place = to_string(NUM);
			return eat(INT10);
			break;
		case INT16:
			thisF.place = to_string(NUM);
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

int main() {
    cout << "input : \n" << test << endl;
    cout << run() << endl;
    return 0;
}