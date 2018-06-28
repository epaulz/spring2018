/* called by yyparse on error */
int yyerror(s)
	char *s;
{
	printf("%s\n", s);
	return(-1);
}