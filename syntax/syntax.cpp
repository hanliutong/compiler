#include <iostream>
#include <stdio.h>
#include "define.h"
#include "lex.h"
using namespace std;
char *test = "while (a3+15)>0xa do if x2 = 07 then while y<z do y = x * y / z; c=b*c+d; ";// no ADD 
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

//bool M()
//{
//	switch (Token)
//	{
//	case ELSE :
//		if(!eat(ELSE))
//			return 0;
//		S();
//	}
//	default :
//		return flase;//express NULL;
//}

bool N()
{
	switch (Token)
	{
		case ADD:
			if(!eat(ADD))
				return 0;
//			eat(ADD);
			T();
			N();
			break; 
		case SUB:
			if(!eat(SUB))
				return 0;
			T();
			N();
			break;
//			N();
		default :
			return false;//express NULL
	}
	
//	N();
	
}

bool S(){
    switch (Token)
    {
    case IF :
        if (!eat(IF))
            return 0;
        C();
        if (!eat(THEN))
            return 0;
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
//    return eat(IDN);
//	if(!T()){
//		return N();
//	}
//	else 
//		return false;
	T();
	N();

}

bool T(){
//	if(F()){
//		return G();
//	}
//	else 
//		return false;
	F();
	G();


} 

bool G(){
	switch (Token)
	{
		case MUL:
			if(!eat(MUL))
				return 0;
//			eat(MUL);
			if(Token==SEMI){
				return false;
				break;
			}
			F();
			G();
			break;
		case DIV:
			if(!eat(DIV))
				return 0;
//			eat(DIV);
			if(Token==SEMI){
				return false;
				break;
			}
			F();
			G();
			break;
		case ADD:
			eat(ADD);
			T();
			N();
			break;
		case SUB:
			eat(SUB);
			T();
			N();
			break;
		case SEMI:
			eat(SEMI);
		default :
			return false;//express NULL
	} 
	return true;
}

bool F(){
	switch (Token)
	{
		case LPAR:
			if(!eat(LPAR))
				return 0;
			E();
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
}

int main(){
    
    //char *test = "";
    // while(*test){
    //     cout << scan(test) << endl;
    // }
    Token = getNext();
  	cout << P() << endl;
}
