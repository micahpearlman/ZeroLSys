

%{ 
	#include <string>
	#include "zlsScanner.h"
	#include "zlsAbstractSyntaxTree.h"
	typedef ZLS::BisonParser::token token;
	typedef ZLS::BisonParser::token_type token_type;
%}

%option nodefault yyclass="FlexScanner" noyywrap c++

%% /*** Regular Expressions Part ***/


[0-9]+ {
    yylval->intVal = atoi(yytext);
    return token::INTEGER;
}

[0-9]+"."[0-9]* {
    yylval->floatVal = atof(yytext);
    return token::DOUBLE;
}

[A-Za-z][A-Za-z0-9_,.-]* {
    yylval->stringVal = new std::string(yytext, yyleng);
    return token::STRING;
}

 /* gobble up white-spaces */
[ \t\r]+ {
    //yylloc->step();
}

 /* gobble up end-of-lines */
\n {
    //yylloc->lines(yyleng); yylloc->step();
    return token::EOL;
}

 /* pass all other characters up to bison */
. {
    return static_cast<token_type>(*yytext);
}

