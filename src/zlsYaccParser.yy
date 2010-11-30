

%{ /*** C/C++ Declarations ***/

#include <stdio.h>
#include <string>
#include <vector>

#include "zlsContext.h"
#include "zlsAbstractSyntaxTree.h"
#include "zlsParser.h"
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

%parse-param { ZLS::Context &context }
%lex-param { ZLS::Context &context }

/* verbose error messages */
%error-verbose


%code requires {
	// Forward-declare
	namespace ZLS {
		class Context;
		class ASTNode;
	}
}

%code {
	// Prototype for the yylex function
	static int yylex(ZLS::BisonParser::semantic_type * yylval, ZLS::Context &context);
}


%union {
    int					intVal;
    float				floatVal;
    std::string*		stringVal;
    ZLS::ASTNode*		astnode;
}

%token                  END          0  "end of file"
%token                  EOL             "end of line"
%token                  AXIOM           "axiom"
%token					PRODUCTION		"production"
%token <intVal>			INTEGER         "integer"
%token <floatVal>		DOUBLE          "double"
%token <stringVal>		STRING          "string"

/** Turtle Command Tokens **/
%token					MOVE_FORWARD	"f"
%token					DRAW_FORWARD	"F"
%token					TURN_LEFT		"+"
%token					TURN_RIGHT		"-"
%token					CHANGE_COLOR	"C"
%token					PUSH_STATE		"["
%token					POP_STATE		"]"

%type <astnode>  constant variable
%type <astnode>  atomexpr powexpr unaryexpr mulexpr addexpr expr
%type <astnode>  moveforward drawforward turnleft turnright pushstate popstate changecolor turtlecommand

%destructor { delete $$; } STRING
%destructor { delete $$; } constant variable
%destructor { delete $$; } atomexpr powexpr unaryexpr mulexpr addexpr expr


%% /*** Grammar Rules ***/


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
				cout << "STRING: " << *($1) << endl;

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
		| addexpr TURN_LEFT mulexpr
		  {
			  $$ = new ZLS::ASTAdd($1, $3);
		  }
		| addexpr TURN_RIGHT mulexpr
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
			 

/*	Turtle Commands
*******************/
			 
drawforward : DRAW_FORWARD '(' expr ')'
			{
				cout << "drawforward" << endl;
				$$ = new ZLS::ASTDrawForward( &context, $3 );
			}

moveforward : MOVE_FORWARD '(' expr ')'
			{
				$$ = new ZLS::ASTMoveForward( &context, $3 );
			}

turnleft : TURN_LEFT '(' expr ')'
			{
				$$ = new ZLS::ASTTurnLeft( &context, $3 );
			}

turnright : TURN_RIGHT '(' expr ')'
			{
				$$ = new ZLS::ASTTurnRight( &context, $3 );
			}

changecolor : CHANGE_COLOR '(' expr ')'
			{
				$$ = new ZLS::ASTTurnRight( &context, $3 );
			}
pushstate : PUSH_STATE
			{
				$$ = new ZLS::ASTPushState( &context );
			}
popstate : POP_STATE
			{
				$$ = new ZLS::ASTPopState( &context );
			}

				 
turtlecommand : drawforward
				| moveforward
				| turnleft
				| turnright
				| changecolor
				| pushstate
				| popstate

turtlecommand_sequence : /* empty */
				| turtlecommand_sequence turtlecommand
				{
					context._killme.push_back( $2 );
				}
				;
			 
				
start   : /* empty */
		| start ';'
		| start EOL
		| start assignment ';'
		| start assignment EOL
		| start assignment END
		| start turtlecommand_sequence
			{
				//context.parser()->setRoot( $2 );
				std::vector<ZLS::ASTNode*>::iterator it = context._killme.begin();
				for( ; it != context._killme.end(); it++ ) {
					(*it)->print(cout, 0);
				}
			}
		| start expr ';'
			{
				context.parser()->setRoot( $2 );
			}
		| start expr EOL
			{
			  //driver.calc.expressions.push_back($2);
			}
		| start expr END
			{
			  //driver.calc.expressions.push_back($2);
			}


%% /*** Additional Code ***/

// We have to implement the error function
void ZLS::BisonParser::error(const ZLS::BisonParser::location_type &loc, const std::string &msg) {
	std::cerr << "Error: " << msg << std::endl;
}

// Now that we have the Parser declared, we can declare the Scanner and implement
// the yylex function
#include "zlsScanner.h"
static int yylex(ZLS::BisonParser::semantic_type * yylval, ZLS::Context &context) {
	return context.parser()->scanner().yylex(yylval);
}
