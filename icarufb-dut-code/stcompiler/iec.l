%{
/*=========================================================================
                      C-libraries and Token definitions
=========================================================================*/
#include <string.h>     /* for strdup                       */
#include <stdlib.h>     /* for atoi                         */
#include "atributos.h"
#include "iec.tab.h"

void comment();
char *auxStr;
char lexstr[1000];
#include "errors.h"
%}

nlinha  [\n]
strend 	[\0\f]
under	[_]
novaL  {nlinha}
delim	[ \t\r]
simbolos	[|.:?!@#$%&*()_]
ws	{delim}+
digito	[0-9]

numOLD	{digito}+(\.{digito}*(E[+-]?{digito}+)?)?
num {digito}+|-{digito}+
numd {digito}+\.{digito}

integer {digito}+|-{digito}+
exponent [eE][+-]?{integer}
real {integer}("."{integer})?{exponent}?

letter  [A-Za-z]
ID {letter}({letter}|{digito}|{under})*
especial	\\[0nftr]
STRING	 ["]({letter}|{digito}|{ws}|{simbolos})*["]

D			[0-9]
L			[a-zA-Z_]
H			[a-fA-F0-9]
E			[Ee][+-]?{D}+
FS			(f|F|l|L)
IS			(u|U|l|L)*

%%
{ws}	{}
{novaL}                     {err_lineInc();}
"TO"					{return T_TO;}
"SET_REG"				{return T_BI_SET_REG;}
"GET_REG"				{return T_BI_GET_REG;}
"GET_REG_REAL"				{return T_BI_GET_REG_REAL;}
"->"					{return T_ARROW;}
"(*"					{comment();}
":=" 					{return T_ASSIGNMENT;}
":"						{return T_TWO_POINTS;}
";"						{return T_SEMICOLON;}
"("						{return T_OP;}
")"						{return T_CP;}
","						{return T_COMA;}
"."						{return T_POINT;}
"#"						{return T_HASH;}
"OR"					{return T_OR;}
"AND"					{return T_AND;}
"NOT"					{return T_NOT;}
"XOR"					{return T_XOR;}
">"						{return T_GT;}
">="						{return T_GE;}
"<"						{return T_LT;}
"<="					{return T_LE;}
"="						{return T_EQ;}
"+"						{return T_ADD;}
"-"						{return T_SUB;}
"*"						{return T_MUL;}
"/"						{return T_DIV;}
"AT"					{return T_AT;}
"ALGORITHM"				{return T_ALGORITHM;}
"END_ALGORITHM"			{return T_END_ALGORITHM;}
"IN"					{return T_IN;}
"EVENT_INPUT"			{return T_EVENT_INPUT;}
"EVENT_OUTPUT"			{return T_EVENT_OUTPUT;}
"END_EVENT"				{return T_END_EVENT;}
"EC_STATES"				{return T_EC_STATES;}
"END_STATES"			{return T_END_STATES;}
"EC_TRANSITIONS"		{return T_EC_TRANSITIONS;}
"END_TRANSITIONS"		{return T_END_TRANSITIONS;}
"EVENT_CONNECTIONS"		{return T_EVENT_CONNECTIONS;}
"DATA_CONNECTIONS"		{return T_DATA_CONNECTIONS;}
"END_CONNECTIONS"		{return T_END_CONNECTIONS;}
"FBS"					{return T_FBS;}
"END_FBS"				{return T_END_FBS;}
"DEVICE"				{return T_DEVICE;}
"END_DEVICE"			{return T_END_DEVICE;}
"SYSTEM"				{return T_SYSTEM;}
"END_SYSTEM"			{return T_END_SYSTEM;}
"FUNCTION_BLOCK"		{return T_FUNCTION_BLOCK;}
"END_FUNCTION_BLOCK"	{return T_END_FUNCTION_BLOCK;}
"VAR"					{return T_VAR;}
"VAR_INPUT"				{return T_VAR_INPUT;}
"VAR_OUTPUT"			{return T_VAR_OUTPUT;}
"END_VAR"				{return T_END_VAR;}
"RESOURCE"				{return T_RESOURCE;}
"END_RESOURCE"		{return T_END_RESOURCE;}
"ON"					{return T_ON;}
"TASK"					{return T_TASK;}
"WITH"				{return T_WITH;}
"IF"				{return T_IF;}
"THEN"			{return T_THEN;}
"END_IF"			{return T_END_IF;}
"ELSE"			{return T_ELSE;}
"ELSIF"			{return T_ELSIF;}
"WHILE"			{return T_WHILE;}
"DO"			{return T_DO;}
"END_WHILE"		{return T_END_WHILE;}

"ADD"			{return T_BI_ADD;}
"MUL"			{return T_BI_MUL;}
"DIV"			{return T_BI_DIV;}
"MOD"			{return T_BI_MOD;}
"SUB"			{return T_BI_SUB;}

"GT"			{return T_BI_GT;}
"GE"			{return T_BI_GE;}
"EQ"			{return T_BI_EQ;}
"LT"			{return T_BI_LT;}
"LE"			{return T_BI_LE;}
"NE"			{return T_BI_NE;}

"ASM"			{return T_ASM;}
"END_ASM"		{return T_END_ASM;}
"LOAD"			{return T_LOAD;}
"NISND"			{return T_NISND;}
"NIRCV"			{return T_NIRCV;}
"GOTO"			{return T_GOTO;}
"STORE"			{return T_STORE;}
"CONST"			{return T_CONST;}
"IFEQ"          {return T_IFEQ;}
"CUSTOM"          {return T_CUSTOM;}


FALSE			{yylval.intval = 0; yylval.size = 1; yylval.str = (char *) strdup("0"); return T_NUMBER;}
TRUE			{yylval.intval = 1; yylval.size = 1; yylval.str = (char *) strdup("1"); return T_NUMBER;}

T#{num}s	{yylval.intval = atoi( yytext+2 ); sprintf(lexstr, "%d", yylval.intval); yylval.str = (char *) strdup(lexstr); return T_NUMBER;}
T#{num}m	{yylval.intval = atoi( yytext+2 )*60; sprintf(lexstr, "%d", yylval.intval); yylval.str = (char *) strdup(lexstr); return T_NUMBER;}


{ID} 					{yylval.str = (char *) strdup(yytext);  return T_ID;}
{num}		 {yylval.intval = atoi( yytext ); if(yylval.intval > 255){yylval.type = TY_INT;}else{yylval.type = TY_BYTE;} yylval.str = strdup(yytext); return T_NUMBER;}

{real}         {yylval.floatval = atof(yytext); printf("Convert atof %s = %f\n", yytext,yylval.floatval); return T_NUMBER_REAL;}

%%

char *troca_special(char *str){
	int i,j;
	char *a;
	int val;
	val=' ';
	a = strdup(str);
	i =1;
	j=1;
	str[0] = a[0];
	while(a[i] != 34){
		if(a[i] == '\\'){
			switch(a[i+1]){
				case 'n': val = '\n'; break;
				case '0': val = '\0'; break;
				case 'f': val = '\f'; break;
				case 34: val = 34; break;
				case '\\': val = '\\'; break;
				case 'r': val = '\r'; break;
			}
			str[j] = val;
			i++;
		}else
			str[j] = a[i];
		i++;
		j++;
	}
	str[j] = a[i];


	return str;

}

void comment()
{
	char c, c1;

loop:
	while ((c = input()) != '*' && c != 0){}
		/*putchar(c);*/

	if ((c1 = input()) != ')' && c != 0)
	{
		unput(c1);
		goto loop;
	}

	if (c != 0){}
		/*putchar(c1);*/
}

char* getdoc(){
	char c, c1;
	int str_t=1;

loop:
	while ((c = input()) != '*' && c != 0){
		auxStr = realloc(auxStr, sizeof(char)*str_t);
		auxStr[str_t-1] = c;
		str_t++;
	}
	if ((c1 = input()) != '/' && c != 0)
	{
		unput(c1);
		goto loop;
	}

	if (c != 0){
		auxStr = realloc(auxStr, sizeof(char)*(str_t));
		auxStr[str_t-1] = c;
		str_t++;
	}
	auxStr[str_t-2]='\0';
	return auxStr;
}
