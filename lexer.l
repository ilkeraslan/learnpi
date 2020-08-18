%option noyywrap nodefault yylineno
%{

%}

%%
"+"     { return ADDITION; }
"-"     { return SUBTRACTION; }
"*"     { return MULTIPLICATION; }
"/"     { return DIVISION; }
"%"     { return MODULUS; }
"("     { return OPEN_PARANTHESIS; }
")"     { return CLOSE_PARANTHESIS; }
"["     { return OPEN_BRACKET; }
"]"     { return CLOSE_BRACKET; }
"{"     { return OPEN_BRACE; }
"}"     { return CLOSE_BRACE; }
"."     { return DOT; }
","     { return COMMA; }
"="     { return ASSIGN; }

"OR"|"or"     { return OR_OPEPARTION; }
"AND"|"and"   { return AND_OPEPARTION; }
"NOT"|"not"   { return NOT_OPEPARTION; }

. { yyerror("Mystery character %c\n", *yytext); exit(1); }
%%

int main(int argc, char **argv) {
	if(argc > 2) {
		if(!(yyin = fopen(argv[1], "r"))) {
			fprintf(stderr, "Cannot open file: %s\n", argv[1]);
			exit(1);
		}

        // Check file ending suffix
		if(checkSuffix(, ".learnpi") == 1) {
			// TODO: passed a file with correct suffix

            yyparse();
		    fclose(yyin);
		    yyrestart(stdin);
		    return yyparse();
        }
		
	} else if(argc == 2) {
        if(checkSuffix(, ".learnpi") == 1) {
			// TODO: passed a file with correct suffix
			if(!(yyin = fopen(argv[1], "r"))) {
				fprintf(stderr, "Cannot open file: %s\n", argv[1]);
				exit(1);
			}
			return yyparse();
		}
	} else {
		return yyparse();
	}
}

int checkSuffix(const char *str, const char *suffix) {
    if (!str || !suffix)
        return 0;
    size_t lenstr = strlen(str);
    size_t lensuffix = strlen(suffix);
    if (lensuffix >  lenstr)
        return 0;
    return strncmp(str + lenstr - lensuffix, suffix, lensuffix) == 0;
}