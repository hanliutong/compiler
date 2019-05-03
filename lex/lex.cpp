#include <iostream>
#include <string.h>
using namespace std;

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

int scan(char* input){
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
            else if (isLetter(cur))
                state = 1;
            else if (cur == '0')
                state = 3;
            else if (isNumber(cur))
                state = 12;
            else
                state = 99;
            break;
        case 1:
            if (isLetter(cur) || (isNumber(cur)))
                state = 1;
            else{//state 2
                cout << "<IDT," << buf << ">\n";
                buf = "";
                index--;
                state = 0;
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
                cout << "<INT10," << buf << ">\n";
                buf = "";
                index--;
                state = 0;
            }
            break;
        case 6:
            if (cur == '0' || is1to7(cur))
                state = 6;
            else
            {// state 7
                cout << "<INT8," << buf << ">\n";
                buf = "";
                index--;
                state = 0;
            }
            break;
        case 8:
            if (cur == '0'){//state 9
                buf += cur;
                cout << "<INT16," << buf << ">\n";
                buf = "";
                state = 0;
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
                index--;
                state = 0;
            }
            break;
        case 12:
            if (cur == '0' || isNumber(cur))
                state = 12;
            else
            {// state 7
                cout << "<INT10," << buf << ">\n";
                buf = "";
                index--;
                state = 0;
            }
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
            break;
        }
    return 0;
}

int main(){
    char *test = "BEGIN DEC10 0 123 OCT8 00  070 HEX16 0x0 0xD1023 0X9F9 0x10a END ";
    scan(test);
}