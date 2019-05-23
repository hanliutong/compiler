
%{

	#include <stdio.h>

	#include <stdlib.h> 

	int count = 0;

%} 

INT8 0[0-7]*

INT10 0|[1-9][0-9]*

INT16 0x[0-9|a-f][0-9|a-f]*

IF if

THEN then

ELSE else

WHILE while

DO do

ADD \+

SUB -

MUL \*

DIV \/

LESS <

MORE >

LPAR \(

RPAR \)

EQU =

SEMI ;

LCUR \{

RCUR \}

IDN  [A-Za-z]([A-Za-z]|[0-9])*

delim [\n\t]
whitespace {delim}+

%% 

{INT8} { count++;printf("%d\t(8,‘%s’)\n",count,yytext); }

{INT10} {count++;printf("%d\t(10,‘%s’)\n",count,yytext);}

{INT16} {count++;printf("%d\t(16,‘%s’)\n",count,yytext);}

{IF} {count++;printf("%d\t(11,‘%s’)\n",count,yytext);} 

{THEN} {count++;printf("%d\t12,‘%s’)\n",count,yytext);} 

{ELSE} {count++;printf("%d\t(13,‘%s’)\n",count,yytext);}  

{WHILE} {count++;printf("%d\t(14,‘%s’)\n",count,yytext);}

{DO} {count++;printf("%d\t(15,‘%s’)\n",count,yytext);}  

{ADD} {count++;printf("%d\t(17,‘%s’)\n",count,yytext);} 

{SUB} {count++;printf("%d\t(18,‘%s’)\n",count,yytext);} 

{MUL} {count++;printf("%d\t(19,‘%s’)\n",count,yytext);} 

{DIV} {count++;printf("%d\t(20,‘%s’)\n",count,yytext);} 

{LESS} {count++;printf("%d\t(21,‘%s’)\n",count,yytext);}

{MORE} {count++;printf("%d\t(22,‘%s’)\n",count,yytext);}  

{LPAR} {count++;printf("%d\t(23,‘%s’)\n",count,yytext);} 

{RPAR} {count++;printf("%d\t(24,‘%s’)\n",count,yytext);} 

{EQU} {count++;printf("%d\t(25,‘%s’)\n",count,yytext);} 

{SEMI} {count++;printf("%d\t(26,‘%s’)\n",count,yytext);} 

{LCUR} {count++;printf("%d\t(27,‘%s’)\n",count,yytext);} 

{RCUR} {count++;printf("%d\t(28,‘%s’)\n",count,yytext);} 

{IDN} {count++;printf("%d\t(1,‘%s’)\n",count,yytext);}

{whitespace} { /* do    nothing*/ } 
%% 

void main() 

{

    printf("词法分析器输出类型说明:\n");

	printf("1：IDN\n");

	printf("8：INT8\n");

	printf("10：INT10\n");

	printf("11：IF\n");

	printf("12：THEN\n");

	printf("13：ELSE\n");

	printf("14：WHILE\n");

	printf("15：DO\n");

	printf("16：INT16\n");

	printf("17：ADD\n");

	printf("18：SUB\n");

	printf("19：MUL\n");

	printf("20：DIV\n");

	printf("21：LESS\n");

	printf("22：MORE\n");

	printf("23：LPAR\n");

	printf("24：RPAR\n");

	printf("25：EQU\n");

	printf("26：SEMI\n");
	printf("27：LCUR\n");
	printf("28：RCUR\n");
	printf("\n");

	yyin=fopen("example.txt","r"); 

    	yylex(); /* start the analysis*/ 

	fclose(yyin);

	system("PAUSE");/*暂停停,  使DOS窗口停住*/

} 

 int yywrap() 

 { 

 	return 1; 

 } 
