%option noyywrap yylineno nounput noinput nodefault
%{
#include "minako.h"
%}

%{
  YYSTYPE yylval;  // Declaration of yylval
%}

LETTER [a-zA-Z]
DIGIT [0-9]
INTEGER {DIGIT}+
FLOAT {INTEGER}"."{INTEGER}|"."{INTEGER}
ID {LETTER}+({DIGIT}|{LETTER})*
STRING "\""[^\n\"]*"\""
%x COMMENT

%%

"/*" {
  BEGIN(COMMENT);
}

<COMMENT>.|\n
<COMMENT>"*/" {
  BEGIN(INITIAL);
}

\/\/.*  {
  // Ignore comments starting with '//'
}

"&&" {
  return AND;
}
"||" {
  return OR;
}
"==" {
  return EQ;
}
"!=" {
  return NEQ;
}
"<=" {
  return LEQ;
}
">=" {
  return GEQ;
}
"<" {
  return LSS;
}
">" {
  return GRT;
}

"bool" {
  return KW_BOOLEAN;
}
"do" {
  return KW_DO;
}
"else" {
  return KW_ELSE;
}
"float" {
  return KW_FLOAT;
}
"for" {
  return KW_FOR;
}
"if" {
  return KW_IF;
}
"int" {
  return KW_INT;
}
"printf" {
  return KW_PRINTF;
}
"return" {
  return KW_RETURN;
}
"void" {
  return KW_VOID;
}
"while" {
  return KW_WHILE;
}

","|";"|"("|")"|"{"|"}"|"+"|"-"|"*"|"/"|"=" {
  return yytext[0];
}

{INTEGER} {
  yylval.intValue = atoi(yytext);
  return CONST_INT;
}

{FLOAT}([eE]([-+])?{INTEGER})?|{INTEGER}[eE]([-+])?{INTEGER} {
  return CONST_FLOAT;
}  

"true" {
  yylval.intValue = 1;
  return CONST_BOOLEAN;
}
"false" {
  yylval.intValue = 0;
  return CONST_BOOLEAN;
}

{ID} {
  yylval.string = strdup(yytext);  // Store a copy of the string
  return ID;
}

{STRING} {
  yytext[strlen(yytext)-1] = '\0';
  yylval.string = strdup(yytext+1);  // Store a copy of the string
  return CONST_STRING;
}

[\t\n\r" "] {
  // Ignore whitespace
}

. {
  printf("Scanning error: Unknown character [%c]\n",yytext[0]);
  exit(1);
  return 0;
};

<<EOF>> {
  return EOF;
}
