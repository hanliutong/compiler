#include <iostream>
#include <stdlib.h>
//#include <string.h>
using namespace std;
int AAA1 = 100;

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

bool isOperator(char input){
    if (input == '+' |
        input == '-' |
        input == '*' |
        input == '/' |
        input == '>' |
        input == '<' |
        input == '=' |
        input == '(' |
        input == ')' |
        input == ';')
        return true;
    else
        return false;
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
            else
                state = 99;
            break;
        case 1:
            if (isLetter(cur) || (isNumber(cur)))
                state = 1;
            else{//state 2
            	//buf 赋值;
                input += index;
                return 1;
            }
            break;
            
        case 2:

            break;
        case 3:
            if (cur == '0'){//state 5
                buf += cur;
                cout << "<INT8," << buf << ">\n";
                buf = "";
                state = 0;
            }
            else if(is1to7(cur))
                state = 6;
            else if(cur == 'x' || cur == 'X')
                state = 8;
            else
            { // state 4;
                //cout << "<INT10," << buf << ">\n";
                //buf = "";
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
                //buf = "";
                //index--;
                //state = 0;
                return 8; 
            }
            break;
        case 8:
            if (cur == '0'){//state 9
                buf += cur;
                cout << "<INT16," << buf << ">\n";
                //buf = "";
                //state = 0;
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
                //buf = "";
                //index--;
                //state = 0;
                return 16;
            }
            break;
        case 12:
            if (cur == '0' || isNumber(cur))
                state = 12;
            else{// state 7
                cout << "<INT10," << buf << ">\n";
                //buf = "";
                input += index;
                return 10;
            }
            break;
        case 15:
            if (cur == 'f')
                state = 16;
            else
                state = 1;
            break;
        case 16:
            if (isLetter(cur) || isNumber(cur))
                state = 1;
            else{//state 17
                cout << "<IF,_>\n";
                //buf = "";
                //index--;
                //state = 0;
            
            }
            break;
        case 18:
            if (cur == 'o')
                state = 19;
            else
                state = 1;
            break;   
        case 19:
            if (isLetter(cur) || isNumber(cur))
                state = 1;
            else{//state 20
                cout << "<DO,_>\n";
                //buf = "";
                //index--;
                //state = 0;
            }
            break; 
        case 21:
            if (cur == 'l')
                state = 22;
            else
                state = 1;
            break;    
        case 22:
            if (cur == 's')
                state = 23;
            else
                state = 1;
            break;   
        case 23:
            if (cur == 'e')
                state = 24;
            else
                state = 1;
            break;  
        case 24:
            if (isLetter(cur) || isNumber(cur))
                state = 1;
            else{//state 24
                cout << "<ELSE,_>\n";
                buf = "";
                index--;
                state = 0;
            }
            break;
        case 26:
            if (cur == 'h')
                state = 27;
            else
                state = 1;
            break;    
        case 27:
            if (cur == 'e')
                state = 28;
            else
                state = 1;
            break;   
        case 28:
            if (cur == 'n')
                state = 29;
            else
                state = 1;
            break;  
        case 29:
            if (isLetter(cur) || isNumber(cur))
                state = 1;
            else{//state 30
                cout << "<THEN,_>\n";
                buf = "";
                index--;
                state = 0;
            }
            break;
        case 31:
            if (cur == 'h')
                state = 32;
            else
                state = 1;
            break;    
        case 32:
            if (cur == 'i')
                state = 33;
            else
                state = 1;
            break;   
        case 33:
            if (cur == 'l')
                state = 34;
            else
                state = 1;
            break;
        case 34:
            if (cur == 'e')
                state = 35;
            else
                state = 1;
            break;    
        case 35:
            if (isLetter(cur) || isNumber(cur))
                state = 1;
            else{//state 36
                cout << "<WHILE,_>\n";
                //buf = "";
                //index--;
                //state = 0;
            }
            break;
        case 37:
            //cout << "<+,_>\n";
            buf = "";
            index--;
            state = 0;
            return 2;
            break;
        case 38:
            cout << "<-,_>\n";
            buf = "";
            index--;
            state = 0;
            break;
        case 39:
            cout << "<*,_>\n";
            buf = "";
            index--;
            state = 0;
            break;
        case 40:
            cout << "</,_>\n";
            buf = "";
            index--;
            state = 0;
            break;
        case 41:
            cout << "<<,_>\n";
            buf = "";
            index--;
            state = 0;
            break;
        case 42:
            cout << "<>,_>\n";
            buf = "";
            index--;
            state = 0;
            break;
        case 43:
            cout << "<(,_>\n";
            buf = "";
            index--;
            state = 0;
            break;
        case 44:
            cout << "<),_>\n";
            buf = "";
            index--;
            state = 0;
            break;
        case 45:
            cout << "<=,_>\n";
            buf = "";
            index--;
            state = 0;
            break;
        case 46:
            cout << "<;,_>\n";
            buf = "";
            index--;
            state = 0;
            break;
        case 99:
        default:
            cout << "error\n";
            exit(1);
            break;
        }

    if (state != 0)
        buf += cur;
    if (cur)
        cur = input[++index];
    else
        break;//while
    }
    return 0;
}

// int main(){
// 	printf("词法分析器输出类型说明:\n");

// 	printf("1：标识符\n");

// 	printf("2：运算符\n");
	
// 	printf("3：关键字\n");

// 	printf("8：八进制数\n");

// 	printf("10：十进制数\n");

// 	printf("16：十六进制数\n");
	
// 	printf("\n");
//     char *test = "BEGIN 0 123";
//     //char *test = "if () do ; else then ; while() while1 whilee whill wwhile";
//     while(*test != 0){
//         cout << scan(test) << endl;
		
// 	}
	
	
// }
