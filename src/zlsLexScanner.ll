

%{ 
	#include <string>
	#include <vector>
	#include "zlsScanner.h"
	#include "zlsAbstractSyntaxTree.h"
	typedef ZLS::BisonParser::token token;
	typedef ZLS::BisonParser::token_type token_type;
%}

%option nodefault yyclass="FlexScanner" noyywrap c++

%% /*** Regular Expressions Part ***/

 /* gobble up white-spaces */
[ \t\r\n]+ {
    //yylloc->step();
}


[0-9]+ {
    yylval->intVal = atoi(yytext);
    return token::INTEGER;
}

[0-9]+"."[0-9]* {
    yylval->floatVal = atof(yytext);
    return token::DOUBLE;
}


"w" {
	return token::AXIOM;
}

"P"[0-9]+ {

	yylval->stringVal = new std::string(yytext, yyleng);
	cout << "lex PRODUCTION: ";	
	cout << *yylval->stringVal << endl;
	
	return token::PRODUCTION;
}

">>" {
	cout << "TRANSFORM" << endl;
	return token::TRANSFORM;
}

"f" {
	return token::MOVE_FORWARD;
}

"F" {
	cout << "F" << endl;
	return token::DRAW_FORWARD;
}

"+" {
	cout << "+" << endl;
	return token::TURN_LEFT;
}

"-" {
	cout << "-" << endl;
	return token::TURN_RIGHT;
}

"C" {
	return token::CHANGE_COLOR;
}

"[" {
	return token::PUSH_STATE;
}

"]" {
	return token::POP_STATE;
}

[A-Za-z][A-Za-z0-9_,.-]* {
    yylval->stringVal = new std::string(yytext, yyleng);
    return token::STRING;
}


 /* gobble up end-of-lines 
\n {
    return token::EOL;
}
 */


 /* pass all other characters up to bison */
. {
    return static_cast<token_type>(*yytext);
}

%%
