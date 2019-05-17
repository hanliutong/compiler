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
        if(!eat(WHILE))
        	return 0;
        C();
        if(!eat(DO))
        	return 0;
        S();
        break;
    case IDN:
        eat(IDN);
        if(!eat(EQU))
        	return 0;
        E();
        break;
    case 0:
    	return true;
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
			if(Token==SEMI){
				return false;
				break;
			}
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
		case SEMI:
			eat(SEMI);
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
			if(!E())
				return 0;
			if(!eat(RPAR))
				return 0;
			break;
//		case RPAR:
//			if(!eat(RPAR))
//				return 0;
//			break;
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
