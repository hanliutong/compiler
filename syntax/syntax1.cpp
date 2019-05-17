#include <iostream>
#include <stdio.h>
#include "define.h"
#include "lex.h"
using namespace std;
 char *test = "while (a3+15)>0xa do if x2 = 07 then while y<z do y = x * y / z; c=b*c+d; ";// no ADD 
// char *test = "while a = b do {c = e if e = f then g = h  if i = j then k = l else m = n while o = p do q = r} ";// true
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
bool N();
bool T();
bool G();
bool F();


bool P(){

    if (L()){
        switch (Token)
        {
        case 0:
            return true;
            break;
        case RCUR:
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

    if(!S())
        return false;
    if(!eat(SEMI))
        return false;

    return true;
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
    case LCUR:
        if(!eat(LCUR))
            return false;
        if(!P())
            return false;
        if(!eat(RCUR))
            return false;
        return true;
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


bool N()
{
	switch (Token)
	{
		case ADD:
			if(!eat(ADD))
				return 0;
//			eat(ADD);
			if(!T())
				return 0;
			if(!N())
				return 0;
			break; 
		case SUB:
			if(!eat(SUB))
				return 0;
			if(!T())
				return 0;
			if(!N())
				return 0;
			break;
//			N();
		default :
			return true;//express NULL
	}
	
//	N();
	return true;
	
}


bool E(){
//    return eat(IDN);
//	if(!T()){
//		return N();
//	}
//	else 
//		return false;
	if(!T())
		return 0;
	if(!N())
		return 0;
	return true;

}

bool T(){
//	if(F()){
//		return G();
//	}
//	else 
//		return false;
	if(!F())
		return 0;
	if(!G())
		return 0;
	return true;


} 

bool G(){
	switch (Token)
	{
		case MUL:
			if(!eat(MUL))
				return 0;
//			eat(MUL);
//			if(Token==SEMI){
//				return false;
//				break;
//			}
			if(!F())
				return 0;
			if(!G())
				return 0;
			break;
		case DIV:
			if(!eat(DIV))
				return 0;
//			eat(DIV);
			if(Token==SEMI){
				return false;
				break;
			}
			if(!F())
				return 0;
			if(!G())
				return false;
			break;
//		case SEMI:
//			if(!eat(SEMI))
//				return true;
			break;
//		case 0:
//			return true;
		default :
			return true;//express NULL
	} 
	return true;
}

bool F(){
	switch (Token)
	{
		case LPAR:
			if(!eat(LPAR))
				return 0;
			if (!E())
				return 0;
			if(!eat(RPAR))
				return 0;
			break;
		case IDN:
			return eat(IDN);
			break;
		case INT8:
			return eat(INT8);
			break;
		case INT10:
			return eat(INT10);
			break;
		case INT16:
			return eat(INT16);
			break;	
		default:
			return false;	
			break;
	}
	return true;
}

int main(){
    
    //char *test = "";
    // while(*test){
    //     cout << scan(test) << endl;
    // }
    Token = getNext();
  	cout << P() << endl;
}
