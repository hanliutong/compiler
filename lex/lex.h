#include <iostream>
#include <stdlib.h>
#include <cmath>
#include "define.h"
using namespace std;
int NUM = 0;//INT8 INT10 INT16属性的全局变量
string IDN_NAME;//标识符属性的全局变量

bool isLetter(char input){
    if (input >= 'A' && input <= 'Z')
        return true;
    else if(input >='a' && input <= 'z')
        return true;
    else
        return false;
}

bool isNumber(char input){
    if (input >= '0' && input <= '9')
        return true;
    else
        return false;
}

bool is1to7(char input){
    if (input >= '1' && input <= '7')
        return true;
    else
        return false;
}

bool is1toF(char input){
    if (input >= '1' && input <= '9')
        return true;
    if (input >= 'a' && input <= 'f')
        return true;
    if (input >= 'A' && input <= 'F')
        return true;
    else
        return false;
}

int OCT2DEC(string oct){
	int dec = 0;
	for(int i = 0; i < oct.length(); i++){
		dec += ((int)oct.at(oct.length() - i - 1) - 48) * pow(8, i);
	}
	return dec;
}

int scan(char*& input){
    int state = 0;
    int index = 0;
    char cur = input[index];
    string buf;
    while(1){
        switch (state)
        {
        case 0:
            if(cur == ' ')
                state = 0;
            else if (cur == 'i')
                state = 15;
            else if (cur == 'd')
                state = 18;
            else if (cur == 'e')
                state = 21;
            else if (cur == 't')
                state = 26;
            else if (cur == 'w')
                state = 31;
            else if (isLetter(cur))
                state = 1;
            else if (cur == '0')
                state = 3;
            else if (isNumber(cur))
                state = 12;
            else if (cur == '+')
                state = 37;
            else if (cur == '-')
                state = 38;
            else if (cur == '*')
                state = 39;
            else if (cur == '/')
                state = 40;
            else if (cur == '<')
                state = 41;
            else if (cur == '>')
                state = 42;
            else if (cur == '(')
                state = 43;
            else if (cur == ')')
                state = 44;
            else if (cur == '=')
            	state = 45;
            else if (cur == ';')
            	state = 46;
            else if (cur == '{')
            	state = 47;
            else if (cur == '}')
            	state = 48;
            else
                state = 99;
            break;
        case 1:
            if (isLetter(cur) || (isNumber(cur)))
                state = 1;
            else{//state 2
                IDN_NAME = buf;
                cout << "<IDN," << buf << ">\n";
                input += index;
                state = 0;
                return 1;
            }
            break;
            
        case 2:

            break;
        case 3:
            if (cur == '0'){//state 5
                buf += cur;
                cout << "<INT8," << buf << ">\n";
                NUM = OCT2DEC(buf);
                buf = "";
                index++;
                input += index;
                return 8;
            }
            else if(is1to7(cur))
                state = 6;
            else if(cur == 'x' || cur == 'X')
                state = 8;
            else
            { // state 4;
                cout << "<INT10," << buf << ">\n";
                buf = "";
                input += index;
                return 10;
			}
            break;
        case 6:
            if (cur == '0' || is1to7(cur))
                state = 6;
            else
            {// state 7
                cout << "<INT8," << buf << ">\n";
                NUM = OCT2DEC(buf);
                buf = "";
                input += index;
                return 8;
            }
            break;
        case 8:
            if (cur == '0'){//state 9
                buf += cur;
                cout << "<INT16," << buf << ">\n";
                index++;
                input += index;
                return 16;
            }
            else if(is1toF(cur))
                state = 10;
            else
                state = 99;
            break;
        case 10:
            if(cur == '0' || is1toF(cur))
                state =10;
            else{//state 11
                cout << "<INT16," << buf << ">\n";
                buf = "";
                input += index;
                return 16;
            }
            break;
        case 12:
            if (cur == '0' || isNumber(cur))
                state = 12;
            else{// state 13
                cout << "<INT10," << buf << ">\n";
                buf = "";
                input += index;
                return 10;
            }
            break;
        case 15:
            if (cur == 'f')
                state = 16;
            else{
                state = 1;
                continue;
            }
            break;
        case 16:
            if (isLetter(cur) || isNumber(cur))
                state = 1;
            else{//state 17
                cout << "<IF,_>\n";
                buf = "";
                input += index;
                return IF;
            }
            break;
        case 18:
            if (cur == 'o')
                state = 19;
            else{
                state = 1;
                continue;
            }
            break;   
        case 19:
            if (isLetter(cur) || isNumber(cur)){
                state = 1;
            }
            else{//state 20
                cout << "<DO,_>\n";
                buf = "";
                input += index;
                return DO;
            }
            break; 
        case 21:
            if (cur == 'l')
                state = 22;
            else{
                state = 1;
				continue;
			}
            break;    
        case 22:
            if (cur == 's')
                state = 23;
            else{
                state = 1;
				continue;
			}
            break;   
        case 23:
            if (cur == 'e')
                state = 24;
            else{
                state = 1;
				continue;
			}
            break;  
        case 24:
            if (isLetter(cur) || isNumber(cur))
                state = 1;
            else{//state 25
                cout << "<ELSE,_>\n";
                buf = "";
                input += index;
                return ELSE;
            }
            break;
        case 26:
            if (cur == 'h')
                state = 27;
            else{
                state = 1;
				continue;
			}
            break;    
        case 27:
            if (cur == 'e')
                state = 28;
            else{
                state = 1;
				continue;
			}
            break;   
        case 28:
            if (cur == 'n')
                state = 29;
            else{
                state = 1;
				continue;
			}
            break;  
        case 29:
            if (isLetter(cur) || isNumber(cur))
                state = 1;
            else{//state 30
                cout << "<THEN,_>\n";
                buf = "";
                input += index;
                return THEN;
            }
            break;
        case 31:
            if (cur == 'h')
                state = 32;
            else{
                state = 1;
				continue;
			}
            break;    
        case 32:
            if (cur == 'i')
                state = 33;
            else{
                state = 1;
				continue;
			}
            break;   
        case 33:
            if (cur == 'l')
                state = 34;
            else{
                state = 1;
				continue;
			}
            break;
        case 34:
            if (cur == 'e')
                state = 35;
            else{
                state = 1;
				continue;
			}
            break;    
        case 35:
            if (isLetter(cur) || isNumber(cur))
                state = 1;
            else{//state 36
                cout << "<WHILE,_>\n";
                buf = "";
                input += index;
                return WHILE;
            }
            break;
        case 37:
            cout << "<+,_>\n";
            buf = "";
            input += index;
            return ADD;
            break;
        case 38:
            cout << "<-,_>\n";
            buf = "";
            input += index;
            return SUB;
            break;
        case 39:
            cout << "<*,_>\n";
            buf = "";
            input += index;
            return MUL;
            break;
        case 40:
            cout << "</,_>\n";
            buf = "";
            input += index;
            return DIV;
            break;
        case 41:
            cout << "<<,_>\n";
            buf = "";
            input += index;
            return LESS;
            break;
        case 42:
            cout << "<>,_>\n";
            buf = "";
            input += index;
            return MORE;
            break;
        case 43:
            cout << "<(,_>\n";
            buf = "";
            input += index;
            return LPAR;
            break;
        case 44:
            cout << "<),_>\n";
            buf = "";
            input += index;
            return RPAR;
            break;
        case 45:
            cout << "<=,_>\n";
            buf = "";
            input += index;
            return EQU;
            break;
        case 46:
            cout << "<;,_>\n";
            buf = "";
            input += index;
            return SEMI;
            break;
        case 47:
        	cout << "<{,_>\n";
            buf = "";
            input += index;
            return LCUR;
            break;
        case 48:
        	cout << "<},_>\n";
            buf = "";
            input += index;
            return RCUR;
            break;
        case 99:
        default:
            cout << "error\n";
            exit(1);
            break;
        }

    if (state != 0 && cur != ' ')
        buf += cur;
    if (cur)
        cur = input[++index];
    if (!cur && state == 0){
        input += index;
        break;
        }//while
    }
    return 0;
}
