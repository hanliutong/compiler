#include <iostream>
#include <stdlib.h>
#include "define.h"
#include "lex.h"
using namespace std;

extern string IDN_NAME;
extern int NUM;

int main(){
    char *t = "if i iff else e el els elses then t th the then0 while w wh whi whil whilee do d dowhile";
//    while(*t){
//        if (scan(t) == IDN){
//            cout << "IND:" << IDN_NAME << endl;
//        }
//    }
//    cout << "finished\n";
//
//    t = "+ - * / > < = ( ) ; { }";
//    while(*t){
//            cout << scan(t) << endl;
//    }
//    cout << "finished\n";
//
//    t = "10 0 123 456 7890 8 00 070 013 16 0x0 0xa 0xf 0x12f";
    t = "00 05 070 013 16";
    while(*t){
        cout << scan(t) << "," << NUM << endl;
    }
    cout << "finished\n";
    return 0;
}
