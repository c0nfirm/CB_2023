%define parse.error verbose
%define parse.trace

%code requires {
	#include <stdio.h>
	#include <stflib.h>
	extern void yyerror(const char*);
	extern FILE *yyin;
}

%code {
	extern int yylex();
	extern int yylineno;
}

%union {
	char *string;
	double floatValue;
	int intValue;
}

%token AND           "&&"
%token OR            "||"
%token EQ            "=="
%token NEQ           "!="
%token LEQ           "<="
%token GEQ           ">="
%token LSS           "<"
%token GRT           ">"
%token KW_BOOLEAN    "bool"
%token KW_DO         "do"
%token KW_ELSE       "else"
%token KW_FLOAT      "float"
%token KW_FOR        "for"
%token KW_IF         "if"
%token KW_INT        "int"
%token KW_PRINTF     "printf"
%token KW_RETURN     "return"
%token KW_VOID       "void"
%token KW_WHILE      "while"
%token CONST_INT     "integer literal"
%token CONST_FLOAT   "float literal"
%token CONST_BOOLEAN "boolean literal"
%token CONST_STRING  "string literal"
%token ID            "identifier"

// definition of association and precedence of operators
%left '+' '-' OR
%left '*' '/' AND
%nonassoc UMINUS

// workaround for handling dangling else
// LOWER_THAN_ELSE stands for a not existing else
%nonassoc LOWER_THAN_ELSE
%nonassoc KW_ELSE

%%

program:
            /* empty */
			| program declassignment ';'
			| program functiondefinition
    ;

functiondefinition:
			type id '(' parameterlist_ext ')' '{' statementlist '}'
	;

parameterlist_ext:
			/* empty */
			| parameterlist
	;

parameterlist:
			type id parameter_ext
	;

parameter_ext:
			/* empty */
			| parameter_ext ',' type id
	;

functioncall:
			id '(' parameter ')'
			|	error {yyerror();}
	;

parameter:
			/* empty */
			| assignment parameter_opt
	;

parameter_opt:
			/* empty */
			| parameter_opt ',' assignment
			|	error {yyerror();}
	;

statementlist:
			/* empty */
			| block statementlist
	;

block:
			'{' statementlist '}'
			| statement
	;

statement:
			ifstatement
			| forstatement
			| whilestatement
			| returnstatement ';'
			| dowhilestatement ';'
			| printf ';'
			| declassignment ';'
			| statassignment ';'
			| functioncall ';'
	;


ifstatement:
			KW_IF '(' assignment ')' statementlist statblock_ext
	;

statblock_ext:
			/* empty */
			| KW_ELSE statementlist
	;

forstatement:
			KW_FOR '(' for_ext ';' expr ';' statassignment ')' statementlist
	;

for_ext:
			statassignment
			| declassignment
	;

dowhilestatement:
			KW_DO block KW_WHILE '(' assignment ')'
	;

whilestatement:
			KW_WHILE '(' assignment ')' statementlist
	;

returnstatement:
			KW_RETURN return_ext
	;

return_ext:
			/* empty */
			| assignment
	;

printf:
			KW_PRINTF '(' printf_ext ')'

	;

printf_ext:
			assignment
			| CONST_STRING
	;

declassignment:
			type id declassignment_ext
	;

declassignment_ext:
			/* empty */
			| '=' assignment
	;

type:
			KW_BOOLEAN
			| KW_FLOAT
			| KW_INT
			| KW_VOID
	;

statassignment:
			id '=' assignment
			| 	error {yyerror();}
	;

assignment:
			id '=' assignment
			| expr
	;

expr:
			simpexpr expr_ext
	;

expr_ext:
			/* empty */
			| EQ simpexpr
			| NEQ simpexpr
			| LEQ simpexpr
			| GEQ simpexpr
			| LSS simpexpr
			| GRT simpexpr
	;

simpexpr:	simpexpr_ext simpexpr_opt

	;

simpexpr_ext:
			'-' term	%prec UMINUS
			| term
	;

simpexpr_opt:
			/* empty */
			| '+' term simpexpr_opt
			| '-' term simpexpr_opt
			| OR term simpexpr_opt
	;

term:
			factor term_ext

	;

term_ext:
			/* empty */
			| '*' factor term_ext
			| '/' factor term_ext
			| AND factor term_ext
	;

factor:
			CONST_INT
			| CONST_FLOAT
			| CONST_BOOLEAN
			| functioncall
			| id
			| '(' assignment ')'
	;

id:
			ID;functiondefinition:
			type id '(' parameterlist_ext ')' '{' statementlist '}'
	;

parameterlist_ext:
			/* empty */
			| parameterlist
	;

parameterlist:
			type id parameter_ext
	;

parameter_ext:
			/* empty */
			| parameter_ext ',' type id
	;

functioncall:
			id '(' parameter ')'
			|	error {yyerror();}
	;

parameter:
			/* empty */
			| assignment parameter_opt
	;

parameter_opt:
			/* empty */
			| parameter_opt ',' assignment
			|	error {yyerror();}
	;

statementlist:
			/* empty */
			| block statementlist
	;

block:
			'{' statementlist '}'
			| statement
	;

statement:
			ifstatement
			| forstatement
			| whilestatement
			| returnstatement ';'
			| dowhilestatement ';'
			| printf ';'
			| declassignment ';'
			| statassignment ';'
			| functioncall ';'
	;


ifstatement:
			KW_IF '(' assignment ')' statementlist statblock_ext
	;

statblock_ext:
			/* empty */
			| KW_ELSE statementlist
	;

forstatement:
			KW_FOR '(' for_ext ';' expr ';' statassignment ')' statementlist
	;

for_ext:
			statassignment
			| declassignment
	;

dowhilestatement:
			KW_DO block KW_WHILE '(' assignment ')'
	;

whilestatement:
			KW_WHILE '(' assignment ')' statementlist
	;

returnstatement:
			KW_RETURN return_ext
	;

return_ext:
			/* empty */
			| assignment
	;

printf:
			KW_PRINTF '(' printf_ext ')'

	;

printf_ext:
			assignment
			| CONST_STRING
	;

declassignment:
			type id declassignment_ext
	;

declassignment_ext:
			/* empty */
			| '=' assignment
	;

type:
			KW_BOOLEAN
			| KW_FLOAT
			| KW_INT
			| KW_VOID
	;

statassignment:
			id '=' assignment
			| 	error {yyerror();}
	;

assignment:
			id '=' assignment
			| expr
	;

expr:
			simpexpr expr_ext
	;

expr_ext:
			/* empty */
			| EQ simpexpr
			| NEQ simpexpr
			| LEQ simpexpr
			| GEQ simpexpr
			| LSS simpexpr
			| GRT simpexpr
	;

simpexpr:	simpexpr_ext simpexpr_opt

	;

simpexpr_ext:
			'-' term	%prec UMINUS
			| term
	;

simpexpr_opt:
			/* empty */
			| '+' term simpexpr_opt
			| '-' term simpexpr_opt
			| OR term simpexpr_opt
	;

term:
			factor term_ext

	;

term_ext:
			/* empty */
			| '*' factor term_ext
			| '/' factor term_ext
			| AND factor term_ext
	;

factor:
			CONST_INT
			| CONST_FLOAT
			| CONST_BOOLEAN
			| functioncall
			| id
			| '(' assignment ')'
	;

id:
			ID;

%%

int main(int argc, char *argv[]) {
	yydebug = 1;

	if (argc != 2) {
		yyin = stdin;
	} else {
		yyin = fopen(argv[1], "r");
		if (yyin == 0) {
			fprintf(stderr, "Fehler: Konnte Datei %s nicht zum lesen oeffnen.\n", argv[1]);
			exit(-1);
		}
	}

	return yyparse();
}

void yyerror(const char *msg) {
	fprintf(stderr, "Line %d: %s\n", yylineno, msg);
}
