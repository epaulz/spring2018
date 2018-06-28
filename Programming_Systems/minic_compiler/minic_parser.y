/* bison input file */

%{
#include <stdio.h>
#include <ctype.h>
int yylex(void);
int yyerror(char *s);
%}

%token INT
%token VOID
%token MAIN
%token LPARENS
%token RPARENS
%token LBRACE
%token RBRACE
%token ASSIGN
%token SEMICOLON
%token COMMA
%token RETURN
%token NUM
%token IDE

%% /* Grammar Rules */

transunit: maindecl body;

maindecl: type MAIN arg;

type: INT | VOID;

arg: LPARENS type RPARENS;

body: LBRACE decl statseq RBRACE;

decl: /* empty */ | type variablelist SEMICOLON;
		
variablelist: variable | variable COMMA variablelist;

statseq: returnstat | commandseq SEMICOLON returnstat;

commandseq: command | commandseq SEMICOLON command;

command: variable ASSIGN expr;

variable: IDE;

expr: NUM;

returnstat: RETURN returnarg SEMICOLON;

returnarg: LPARENS IDE RPARENS | LPARENS NUM RPARENS;

%%