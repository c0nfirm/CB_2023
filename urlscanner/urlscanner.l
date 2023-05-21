%option noyywrap yylineno nounput noinput nodefault
STRING "\""[^\"]*"\""
%x ATAG
%x VALID_HREF

%{
  #include "urlscanner.h"
%}

%%
"<a" BEGIN(ATAG);
<ATAG>"href="{STRING} {
  yytext[strlen(yytext)-1] = '\0'; 
  yylval = yytext+6;
  BEGIN(VALID_HREF);
  return TOKEN_URL;
}
<VALID_HREF>"/a"[\t\n\r" "]*">" BEGIN(INITIAL);
<VALID_HREF>">"[^"<"]*"<" {
  yytext[strlen(yytext)-1] = '\0';
  yylval = yytext+1;
  return TOKEN_TEXT;
}
<VALID_HREF>.|[\t\n\r" "]
<ATAG>.|[\t\n\r" "]
.|[\t\n\r" "]
<<EOF>> return EOF;
