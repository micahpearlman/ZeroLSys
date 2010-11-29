

%{ /*** C/C++ Declarations ***/

#include <stdio.h>
#include <string>
#include <vector>

#include "zlsAbstractSyntaxTree.h"
using namespace ZLS;

%}

/*** yacc/bison Declarations ***/

/* Require bison 2.3 or later */
%require "2.3"

/* add debug output code to generated parser. disable this for release
 * versions. */
%debug

/* start symbol is named "start" */
%start start

/* write out a header file containing the token defines */
%defines

/* use newer C++ skeleton file */
%skeleton "lalr1.cc"

/* namespace to enclose parser in */
%define namespace "ZLS"

/* set the parser's class identifier */
%define parser_class_name "BisonParser"

/* The driver is passed by reference to the parser and to the scanner. This
 * provides a simple but effective pure interface, not relying on global
 * variables. */
%parse-param { ZLS::FlexScanner &scanner }
%lex-param { ZLS::FlexScanner &scanner }

/* verbose error messages */
%error-verbose


%code requires {
	// Forward-declare the Scanner class; the Parser needs to be assigned a 
	// Scanner, but the Scanner can't be declared without the Parser
	namespace ZLS {
		class FlexScanner;
		class ASTNode;
	}
}

%code {
	// Prototype for the yylex function
	static int yylex(ZLS::BisonParser::semantic_type * yylval, ZLS::FlexScanner &scanner);
}

 /*** BEGIN EXAMPLE - Change the example grammar's tokens below ***/

%union {
    int					intVal;
    float				floatVal;
    std::string*		stringVal;
    ZLS::ASTNode*			astnode;
}

%token                  END          0  "end of file"
%token                  EOL             "end of line"
%token <intVal>			INTEGER         "integer"
%token <floatVal>		DOUBLE          "double"
%token <stringVal>		STRING          "string"

%type <astnode>  constant variable
%type <astnode>  atomexpr powexpr unaryexpr mulexpr addexpr expr

%destructor { delete $$; } STRING
%destructor { delete $$; } constant variable
%destructor { delete $$; } atomexpr powexpr unaryexpr mulexpr addexpr expr

 /*** END EXAMPLE - Change the example grammar's tokens above ***/

%{

//#include "driver.h"
//#include "scanner.h"

/* this "connects" the bison parser in the driver to the flex scanner class
 * object. it defines the yylex() function call to pull the next token from the
 * current lexer object of the driver context. */
//#undef yylex
//#define yylex driver.lexer->lex

%}

%% /*** Grammar Rules ***/

 /*** BEGIN EXAMPLE - Change the example grammar rules below ***/

constant : INTEGER
           {
               $$ = new ZLS::ASTConstant($1);
           }
         | DOUBLE
           {
               $$ = new ZLS::ASTConstant($1);
           }

variable : STRING
           {
               //if (!driver.calc.existsVariable(*$1)) {
//                   error(yyloc, std::string("Unknown variable \"") + *$1 + "\"");
//                   delete $1;
//                   YYERROR;
               //}
               //else {
               //    $$ = new CNConstant( driver.calc.getVariable(*$1) );
               //    delete $1;
               //}
           }

atomexpr : constant
           {
               $$ = $1;
           }
         | variable
           {
               $$ = $1;
           }
         | '(' expr ')'
           {
               $$ = $2;
           }

powexpr : atomexpr
          {
              $$ = $1;
          }
        | powexpr '^' atomexpr
          {
              $$ = new ZLS::ASTPower($1, $3);
          }

unaryexpr : powexpr
            {
                $$ = $1;
            }
          | '+' powexpr
            {
                $$ = $2;
            }
          | '-' powexpr
            {
                $$ = new ZLS::ASTNegate($2);
            }

mulexpr : unaryexpr
		  {
			  $$ = $1;
		  }
		| mulexpr '*' unaryexpr
		  {
			  $$ = new ZLS::ASTMultiply($1, $3);
		  }
		| mulexpr '/' unaryexpr
		  {
			  $$ = new ZLS::ASTDivide($1, $3);
		  }
		| mulexpr '%' unaryexpr
		  {
			  $$ = new ZLS::ASTModulo($1, $3);
		  }

addexpr : mulexpr
		  {
			  $$ = $1;
		  }
		| addexpr '+' mulexpr
		  {
			  $$ = new ZLS::ASTAdd($1, $3);
		  }
		| addexpr '-' mulexpr
		  {
			  $$ = new ZLS::ASTSubtract($1, $3);
		  }

expr    : addexpr
          {
              $$ = $1;
          }

assignment : STRING '=' expr
             {
//                 driver.calc.variables[*$1] = $3->evaluate();
//                 std::cout << "Setting variable " << *$1
//                           << " = " << driver.calc.variables[*$1] << "\n";
//                 delete $1;
//                 delete $3;
             }

start   : /* empty */
        | start ';'
        | start EOL
        | start assignment ';'
        | start assignment EOL
        | start assignment END
        | start expr ';'
          {
              //driver.calc.expressions.push_back($2);
          }
        | start expr EOL
          {
              //driver.calc.expressions.push_back($2);
          }
        | start expr END
          {
              //driver.calc.expressions.push_back($2);
          }

 /*** END EXAMPLE - Change the example grammar rules above ***/

%% /*** Additional Code ***/

// We have to implement the error function
void ZLS::BisonParser::error(const ZLS::BisonParser::location_type &loc, const std::string &msg) {
	std::cerr << "Error: " << msg << std::endl;
}

// Now that we have the Parser declared, we can declare the Scanner and implement
// the yylex function
#include "zlsScanner.h"
static int yylex(ZLS::BisonParser::semantic_type * yylval, ZLS::FlexScanner &scanner) {
	return scanner.yylex(yylval);
}
