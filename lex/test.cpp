#include <iostream>
#include <stdlib.h>
#include "lex.h"
using namespace std;
extern int AAA1;
int main(){
    char *test = "BEGIN 0 123";
    char *test1 = "BEGIN 0 123";
    cout << scan(test) << endl;
    cout << scan(test) << endl;
    cout << scan(test) << endl;
    cout << scan(test) << endl;
    cout << scan(test1) << endl;
    cout << AAA1;
    return 0;
}