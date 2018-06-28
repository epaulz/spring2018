#include "minic_parser.tab.c"
#include "lex.yy.c"
#include "yyerror.c"
#define YYERROR_VERBOSE

int main(){
	yyparse();
	return(1);
}