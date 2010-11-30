/* A Bison parser, made by GNU Bison 2.4.2.  */

/* Skeleton implementation for Bison LALR(1) parsers in C++
   
      Copyright (C) 2002-2010 Free Software Foundation, Inc.
   
   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.
   
   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.
   
   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.
   
   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */


/* First part of user declarations.  */

/* Line 310 of lalr1.cc  */
#line 3 "zlsYaccParser.yy"
 /*** C/C++ Declarations ***/

#include <stdio.h>
#include <string>
#include <vector>

#include "zlsContext.h"
#include "zlsAbstractSyntaxTree.h"
#include "zlsParser.h"
using namespace ZLS;



/* Line 310 of lalr1.cc  */
#line 53 "zlsYaccParser.tab.cc"


#include "zlsYaccParser.tab.hh"

/* User implementation prologue.  */


/* Line 316 of lalr1.cc  */
#line 62 "zlsYaccParser.tab.cc"
/* Unqualified %code blocks.  */

/* Line 317 of lalr1.cc  */
#line 55 "zlsYaccParser.yy"

	// Prototype for the yylex function
	static int yylex(ZLS::BisonParser::semantic_type * yylval, ZLS::Context &context);



/* Line 317 of lalr1.cc  */
#line 74 "zlsYaccParser.tab.cc"

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* FIXME: INFRINGES ON USER NAME SPACE */
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#define YYUSE(e) ((void) (e))

/* Enable debugging if requested.  */
#if YYDEBUG

/* A pseudo ostream that takes yydebug_ into account.  */
# define YYCDEBUG if (yydebug_) (*yycdebug_)

# define YY_SYMBOL_PRINT(Title, Type, Value, Location)	\
do {							\
  if (yydebug_)						\
    {							\
      *yycdebug_ << Title << ' ';			\
      yy_symbol_print_ ((Type), (Value), (Location));	\
      *yycdebug_ << std::endl;				\
    }							\
} while (false)

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug_)				\
    yy_reduce_print_ (Rule);		\
} while (false)

# define YY_STACK_PRINT()		\
do {					\
  if (yydebug_)				\
    yystack_print_ ();			\
} while (false)

#else /* !YYDEBUG */

# define YYCDEBUG if (false) std::cerr
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_REDUCE_PRINT(Rule)
# define YY_STACK_PRINT()

#endif /* !YYDEBUG */

#define yyerrok		(yyerrstatus_ = 0)
#define yyclearin	(yychar = yyempty_)

#define YYACCEPT	goto yyacceptlab
#define YYABORT		goto yyabortlab
#define YYERROR		goto yyerrorlab
#define YYRECOVERING()  (!!yyerrstatus_)


/* Line 379 of lalr1.cc  */
#line 35 "zlsYaccParser.yy"
namespace ZLS {

/* Line 379 of lalr1.cc  */
#line 142 "zlsYaccParser.tab.cc"
#if YYERROR_VERBOSE

  /* Return YYSTR after stripping away unnecessary quotes and
     backslashes, so that it's suitable for yyerror.  The heuristic is
     that double-quoting is unnecessary unless the string contains an
     apostrophe, a comma, or backslash (other than backslash-backslash).
     YYSTR is taken from yytname.  */
  std::string
  BisonParser::yytnamerr_ (const char *yystr)
  {
    if (*yystr == '"')
      {
        std::string yyr = "";
        char const *yyp = yystr;

        for (;;)
          switch (*++yyp)
            {
            case '\'':
            case ',':
              goto do_not_strip_quotes;

            case '\\':
              if (*++yyp != '\\')
                goto do_not_strip_quotes;
              /* Fall through.  */
            default:
              yyr += *yyp;
              break;

            case '"':
              return yyr;
            }
      do_not_strip_quotes: ;
      }

    return yystr;
  }

#endif

  /// Build a parser object.
  BisonParser::BisonParser (ZLS::Context &context_yyarg)
    :
#if YYDEBUG
      yydebug_ (false),
      yycdebug_ (&std::cerr),
#endif
      context (context_yyarg)
  {
  }

  BisonParser::~BisonParser ()
  {
  }

#if YYDEBUG
  /*--------------------------------.
  | Print this symbol on YYOUTPUT.  |
  `--------------------------------*/

  inline void
  BisonParser::yy_symbol_value_print_ (int yytype,
			   const semantic_type* yyvaluep, const location_type* yylocationp)
  {
    YYUSE (yylocationp);
    YYUSE (yyvaluep);
    switch (yytype)
      {
         default:
	  break;
      }
  }


  void
  BisonParser::yy_symbol_print_ (int yytype,
			   const semantic_type* yyvaluep, const location_type* yylocationp)
  {
    *yycdebug_ << (yytype < yyntokens_ ? "token" : "nterm")
	       << ' ' << yytname_[yytype] << " ("
	       << *yylocationp << ": ";
    yy_symbol_value_print_ (yytype, yyvaluep, yylocationp);
    *yycdebug_ << ')';
  }
#endif

  void
  BisonParser::yydestruct_ (const char* yymsg,
			   int yytype, semantic_type* yyvaluep, location_type* yylocationp)
  {
    YYUSE (yylocationp);
    YYUSE (yymsg);
    YYUSE (yyvaluep);

    YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

    switch (yytype)
      {
        case 8: /* "\"string\"" */

/* Line 479 of lalr1.cc  */
#line 80 "zlsYaccParser.yy"
	{ delete (yyvaluep->stringVal); };

/* Line 479 of lalr1.cc  */
#line 249 "zlsYaccParser.tab.cc"
	break;
      case 24: /* "constant" */

/* Line 479 of lalr1.cc  */
#line 81 "zlsYaccParser.yy"
	{ delete (yyvaluep->astnode); };

/* Line 479 of lalr1.cc  */
#line 258 "zlsYaccParser.tab.cc"
	break;
      case 25: /* "variable" */

/* Line 479 of lalr1.cc  */
#line 81 "zlsYaccParser.yy"
	{ delete (yyvaluep->astnode); };

/* Line 479 of lalr1.cc  */
#line 267 "zlsYaccParser.tab.cc"
	break;
      case 26: /* "atomexpr" */

/* Line 479 of lalr1.cc  */
#line 82 "zlsYaccParser.yy"
	{ delete (yyvaluep->astnode); };

/* Line 479 of lalr1.cc  */
#line 276 "zlsYaccParser.tab.cc"
	break;
      case 27: /* "powexpr" */

/* Line 479 of lalr1.cc  */
#line 82 "zlsYaccParser.yy"
	{ delete (yyvaluep->astnode); };

/* Line 479 of lalr1.cc  */
#line 285 "zlsYaccParser.tab.cc"
	break;
      case 28: /* "unaryexpr" */

/* Line 479 of lalr1.cc  */
#line 82 "zlsYaccParser.yy"
	{ delete (yyvaluep->astnode); };

/* Line 479 of lalr1.cc  */
#line 294 "zlsYaccParser.tab.cc"
	break;
      case 29: /* "mulexpr" */

/* Line 479 of lalr1.cc  */
#line 82 "zlsYaccParser.yy"
	{ delete (yyvaluep->astnode); };

/* Line 479 of lalr1.cc  */
#line 303 "zlsYaccParser.tab.cc"
	break;
      case 30: /* "addexpr" */

/* Line 479 of lalr1.cc  */
#line 82 "zlsYaccParser.yy"
	{ delete (yyvaluep->astnode); };

/* Line 479 of lalr1.cc  */
#line 312 "zlsYaccParser.tab.cc"
	break;
      case 31: /* "expr" */

/* Line 479 of lalr1.cc  */
#line 82 "zlsYaccParser.yy"
	{ delete (yyvaluep->astnode); };

/* Line 479 of lalr1.cc  */
#line 321 "zlsYaccParser.tab.cc"
	break;

	default:
	  break;
      }
  }

  void
  BisonParser::yypop_ (unsigned int n)
  {
    yystate_stack_.pop (n);
    yysemantic_stack_.pop (n);
    yylocation_stack_.pop (n);
  }

#if YYDEBUG
  std::ostream&
  BisonParser::debug_stream () const
  {
    return *yycdebug_;
  }

  void
  BisonParser::set_debug_stream (std::ostream& o)
  {
    yycdebug_ = &o;
  }


  BisonParser::debug_level_type
  BisonParser::debug_level () const
  {
    return yydebug_;
  }

  void
  BisonParser::set_debug_level (debug_level_type l)
  {
    yydebug_ = l;
  }
#endif

  int
  BisonParser::parse ()
  {
    /// Lookahead and lookahead in internal form.
    int yychar = yyempty_;
    int yytoken = 0;

    /* State.  */
    int yyn;
    int yylen = 0;
    int yystate = 0;

    /* Error handling.  */
    int yynerrs_ = 0;
    int yyerrstatus_ = 0;

    /// Semantic value of the lookahead.
    semantic_type yylval;
    /// Location of the lookahead.
    location_type yylloc;
    /// The locations where the error started and ended.
    location_type yyerror_range[2];

    /// $$.
    semantic_type yyval;
    /// @$.
    location_type yyloc;

    int yyresult;

    YYCDEBUG << "Starting parse" << std::endl;


    /* Initialize the stacks.  The initial state will be pushed in
       yynewstate, since the latter expects the semantical and the
       location values to have been already stored, initialize these
       stacks with a primary value.  */
    yystate_stack_ = state_stack_type (0);
    yysemantic_stack_ = semantic_stack_type (0);
    yylocation_stack_ = location_stack_type (0);
    yysemantic_stack_.push (yylval);
    yylocation_stack_.push (yylloc);

    /* New state.  */
  yynewstate:
    yystate_stack_.push (yystate);
    YYCDEBUG << "Entering state " << yystate << std::endl;

    /* Accept?  */
    if (yystate == yyfinal_)
      goto yyacceptlab;

    goto yybackup;

    /* Backup.  */
  yybackup:

    /* Try to take a decision without lookahead.  */
    yyn = yypact_[yystate];
    if (yyn == yypact_ninf_)
      goto yydefault;

    /* Read a lookahead token.  */
    if (yychar == yyempty_)
      {
	YYCDEBUG << "Reading a token: ";
	yychar = yylex (&yylval, context);
      }


    /* Convert token to internal form.  */
    if (yychar <= yyeof_)
      {
	yychar = yytoken = yyeof_;
	YYCDEBUG << "Now at end of input." << std::endl;
      }
    else
      {
	yytoken = yytranslate_ (yychar);
	YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
      }

    /* If the proper action on seeing token YYTOKEN is to reduce or to
       detect an error, take that action.  */
    yyn += yytoken;
    if (yyn < 0 || yylast_ < yyn || yycheck_[yyn] != yytoken)
      goto yydefault;

    /* Reduce or error.  */
    yyn = yytable_[yyn];
    if (yyn <= 0)
      {
	if (yyn == 0 || yyn == yytable_ninf_)
	goto yyerrlab;
	yyn = -yyn;
	goto yyreduce;
      }

    /* Shift the lookahead token.  */
    YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

    /* Discard the token being shifted.  */
    yychar = yyempty_;

    yysemantic_stack_.push (yylval);
    yylocation_stack_.push (yylloc);

    /* Count tokens shifted since error; after three, turn off error
       status.  */
    if (yyerrstatus_)
      --yyerrstatus_;

    yystate = yyn;
    goto yynewstate;

  /*-----------------------------------------------------------.
  | yydefault -- do the default action for the current state.  |
  `-----------------------------------------------------------*/
  yydefault:
    yyn = yydefact_[yystate];
    if (yyn == 0)
      goto yyerrlab;
    goto yyreduce;

  /*-----------------------------.
  | yyreduce -- Do a reduction.  |
  `-----------------------------*/
  yyreduce:
    yylen = yyr2_[yyn];
    /* If YYLEN is nonzero, implement the default value of the action:
       `$$ = $1'.  Otherwise, use the top of the stack.

       Otherwise, the following line sets YYVAL to garbage.
       This behavior is undocumented and Bison
       users should not rely upon it.  */
    if (yylen)
      yyval = yysemantic_stack_[yylen - 1];
    else
      yyval = yysemantic_stack_[0];

    {
      slice<location_type, location_stack_type> slice (yylocation_stack_, yylen);
      YYLLOC_DEFAULT (yyloc, slice, yylen);
    }
    YY_REDUCE_PRINT (yyn);
    switch (yyn)
      {
	  case 2:

/* Line 677 of lalr1.cc  */
#line 89 "zlsYaccParser.yy"
    {
               (yyval.astnode) = new ZLS::ASTConstant((yysemantic_stack_[(1) - (1)].intVal));
           }
    break;

  case 3:

/* Line 677 of lalr1.cc  */
#line 93 "zlsYaccParser.yy"
    {
               (yyval.astnode) = new ZLS::ASTConstant((yysemantic_stack_[(1) - (1)].floatVal));
           }
    break;

  case 4:

/* Line 677 of lalr1.cc  */
#line 98 "zlsYaccParser.yy"
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
    break;

  case 5:

/* Line 677 of lalr1.cc  */
#line 111 "zlsYaccParser.yy"
    {
               (yyval.astnode) = (yysemantic_stack_[(1) - (1)].astnode);
           }
    break;

  case 6:

/* Line 677 of lalr1.cc  */
#line 115 "zlsYaccParser.yy"
    {
               (yyval.astnode) = (yysemantic_stack_[(1) - (1)].astnode);
           }
    break;

  case 7:

/* Line 677 of lalr1.cc  */
#line 119 "zlsYaccParser.yy"
    {
               (yyval.astnode) = (yysemantic_stack_[(3) - (2)].astnode);
           }
    break;

  case 8:

/* Line 677 of lalr1.cc  */
#line 124 "zlsYaccParser.yy"
    {
              (yyval.astnode) = (yysemantic_stack_[(1) - (1)].astnode);
          }
    break;

  case 9:

/* Line 677 of lalr1.cc  */
#line 128 "zlsYaccParser.yy"
    {
              (yyval.astnode) = new ZLS::ASTPower((yysemantic_stack_[(3) - (1)].astnode), (yysemantic_stack_[(3) - (3)].astnode));
          }
    break;

  case 10:

/* Line 677 of lalr1.cc  */
#line 133 "zlsYaccParser.yy"
    {
                (yyval.astnode) = (yysemantic_stack_[(1) - (1)].astnode);
            }
    break;

  case 11:

/* Line 677 of lalr1.cc  */
#line 137 "zlsYaccParser.yy"
    {
                (yyval.astnode) = (yysemantic_stack_[(2) - (2)].astnode);
            }
    break;

  case 12:

/* Line 677 of lalr1.cc  */
#line 141 "zlsYaccParser.yy"
    {
                (yyval.astnode) = new ZLS::ASTNegate((yysemantic_stack_[(2) - (2)].astnode));
            }
    break;

  case 13:

/* Line 677 of lalr1.cc  */
#line 146 "zlsYaccParser.yy"
    {
			  (yyval.astnode) = (yysemantic_stack_[(1) - (1)].astnode);
		  }
    break;

  case 14:

/* Line 677 of lalr1.cc  */
#line 150 "zlsYaccParser.yy"
    {
			  (yyval.astnode) = new ZLS::ASTMultiply((yysemantic_stack_[(3) - (1)].astnode), (yysemantic_stack_[(3) - (3)].astnode));
		  }
    break;

  case 15:

/* Line 677 of lalr1.cc  */
#line 154 "zlsYaccParser.yy"
    {
			  (yyval.astnode) = new ZLS::ASTDivide((yysemantic_stack_[(3) - (1)].astnode), (yysemantic_stack_[(3) - (3)].astnode));
		  }
    break;

  case 16:

/* Line 677 of lalr1.cc  */
#line 158 "zlsYaccParser.yy"
    {
			  (yyval.astnode) = new ZLS::ASTModulo((yysemantic_stack_[(3) - (1)].astnode), (yysemantic_stack_[(3) - (3)].astnode));
		  }
    break;

  case 17:

/* Line 677 of lalr1.cc  */
#line 163 "zlsYaccParser.yy"
    {
			  (yyval.astnode) = (yysemantic_stack_[(1) - (1)].astnode);
		  }
    break;

  case 18:

/* Line 677 of lalr1.cc  */
#line 167 "zlsYaccParser.yy"
    {
			  (yyval.astnode) = new ZLS::ASTAdd((yysemantic_stack_[(3) - (1)].astnode), (yysemantic_stack_[(3) - (3)].astnode));
		  }
    break;

  case 19:

/* Line 677 of lalr1.cc  */
#line 171 "zlsYaccParser.yy"
    {
			  (yyval.astnode) = new ZLS::ASTSubtract((yysemantic_stack_[(3) - (1)].astnode), (yysemantic_stack_[(3) - (3)].astnode));
		  }
    break;

  case 20:

/* Line 677 of lalr1.cc  */
#line 176 "zlsYaccParser.yy"
    {
              (yyval.astnode) = (yysemantic_stack_[(1) - (1)].astnode);
          }
    break;

  case 21:

/* Line 677 of lalr1.cc  */
#line 181 "zlsYaccParser.yy"
    {
//                 driver.calc.variables[*$1] = $3->evaluate();
//                 std::cout << "Setting variable " << *$1
//                           << " = " << driver.calc.variables[*$1] << "\n";
//                 delete $1;
//                 delete $3;
             }
    break;

  case 28:

/* Line 677 of lalr1.cc  */
#line 237 "zlsYaccParser.yy"
    {
				context.parser()->setRoot( (yysemantic_stack_[(3) - (2)].astnode) );
			  //driver.calc.expressions.push_back($2);
			}
    break;

  case 29:

/* Line 677 of lalr1.cc  */
#line 242 "zlsYaccParser.yy"
    {
			  //driver.calc.expressions.push_back($2);
			}
    break;

  case 30:

/* Line 677 of lalr1.cc  */
#line 246 "zlsYaccParser.yy"
    {
			  //driver.calc.expressions.push_back($2);
			}
    break;



/* Line 677 of lalr1.cc  */
#line 734 "zlsYaccParser.tab.cc"
	default:
          break;
      }
    YY_SYMBOL_PRINT ("-> $$ =", yyr1_[yyn], &yyval, &yyloc);

    yypop_ (yylen);
    yylen = 0;
    YY_STACK_PRINT ();

    yysemantic_stack_.push (yyval);
    yylocation_stack_.push (yyloc);

    /* Shift the result of the reduction.  */
    yyn = yyr1_[yyn];
    yystate = yypgoto_[yyn - yyntokens_] + yystate_stack_[0];
    if (0 <= yystate && yystate <= yylast_
	&& yycheck_[yystate] == yystate_stack_[0])
      yystate = yytable_[yystate];
    else
      yystate = yydefgoto_[yyn - yyntokens_];
    goto yynewstate;

  /*------------------------------------.
  | yyerrlab -- here on detecting error |
  `------------------------------------*/
  yyerrlab:
    /* If not already recovering from an error, report this error.  */
    if (!yyerrstatus_)
      {
	++yynerrs_;
	error (yylloc, yysyntax_error_ (yystate, yytoken));
      }

    yyerror_range[0] = yylloc;
    if (yyerrstatus_ == 3)
      {
	/* If just tried and failed to reuse lookahead token after an
	 error, discard it.  */

	if (yychar <= yyeof_)
	  {
	  /* Return failure if at end of input.  */
	  if (yychar == yyeof_)
	    YYABORT;
	  }
	else
	  {
	    yydestruct_ ("Error: discarding", yytoken, &yylval, &yylloc);
	    yychar = yyempty_;
	  }
      }

    /* Else will try to reuse lookahead token after shifting the error
       token.  */
    goto yyerrlab1;


  /*---------------------------------------------------.
  | yyerrorlab -- error raised explicitly by YYERROR.  |
  `---------------------------------------------------*/
  yyerrorlab:

    /* Pacify compilers like GCC when the user code never invokes
       YYERROR and the label yyerrorlab therefore never appears in user
       code.  */
    if (false)
      goto yyerrorlab;

    yyerror_range[0] = yylocation_stack_[yylen - 1];
    /* Do not reclaim the symbols of the rule which action triggered
       this YYERROR.  */
    yypop_ (yylen);
    yylen = 0;
    yystate = yystate_stack_[0];
    goto yyerrlab1;

  /*-------------------------------------------------------------.
  | yyerrlab1 -- common code for both syntax error and YYERROR.  |
  `-------------------------------------------------------------*/
  yyerrlab1:
    yyerrstatus_ = 3;	/* Each real token shifted decrements this.  */

    for (;;)
      {
	yyn = yypact_[yystate];
	if (yyn != yypact_ninf_)
	{
	  yyn += yyterror_;
	  if (0 <= yyn && yyn <= yylast_ && yycheck_[yyn] == yyterror_)
	    {
	      yyn = yytable_[yyn];
	      if (0 < yyn)
		break;
	    }
	}

	/* Pop the current state because it cannot handle the error token.  */
	if (yystate_stack_.height () == 1)
	YYABORT;

	yyerror_range[0] = yylocation_stack_[0];
	yydestruct_ ("Error: popping",
		     yystos_[yystate],
		     &yysemantic_stack_[0], &yylocation_stack_[0]);
	yypop_ ();
	yystate = yystate_stack_[0];
	YY_STACK_PRINT ();
      }

    yyerror_range[1] = yylloc;
    // Using YYLLOC is tempting, but would change the location of
    // the lookahead.  YYLOC is available though.
    YYLLOC_DEFAULT (yyloc, (yyerror_range - 1), 2);
    yysemantic_stack_.push (yylval);
    yylocation_stack_.push (yyloc);

    /* Shift the error token.  */
    YY_SYMBOL_PRINT ("Shifting", yystos_[yyn],
		     &yysemantic_stack_[0], &yylocation_stack_[0]);

    yystate = yyn;
    goto yynewstate;

    /* Accept.  */
  yyacceptlab:
    yyresult = 0;
    goto yyreturn;

    /* Abort.  */
  yyabortlab:
    yyresult = 1;
    goto yyreturn;

  yyreturn:
    if (yychar != yyempty_)
      yydestruct_ ("Cleanup: discarding lookahead", yytoken, &yylval, &yylloc);

    /* Do not reclaim the symbols of the rule which action triggered
       this YYABORT or YYACCEPT.  */
    yypop_ (yylen);
    while (yystate_stack_.height () != 1)
      {
	yydestruct_ ("Cleanup: popping",
		   yystos_[yystate_stack_[0]],
		   &yysemantic_stack_[0],
		   &yylocation_stack_[0]);
	yypop_ ();
      }

    return yyresult;
  }

  // Generate an error message.
  std::string
  BisonParser::yysyntax_error_ (int yystate, int tok)
  {
    std::string res;
    YYUSE (yystate);
#if YYERROR_VERBOSE
    int yyn = yypact_[yystate];
    if (yypact_ninf_ < yyn && yyn <= yylast_)
      {
	/* Start YYX at -YYN if negative to avoid negative indexes in
	   YYCHECK.  */
	int yyxbegin = yyn < 0 ? -yyn : 0;

	/* Stay within bounds of both yycheck and yytname.  */
	int yychecklim = yylast_ - yyn + 1;
	int yyxend = yychecklim < yyntokens_ ? yychecklim : yyntokens_;
	int count = 0;
	for (int x = yyxbegin; x < yyxend; ++x)
	  if (yycheck_[x + yyn] == x && x != yyterror_)
	    ++count;

	// FIXME: This method of building the message is not compatible
	// with internationalization.  It should work like yacc.c does it.
	// That is, first build a string that looks like this:
	// "syntax error, unexpected %s or %s or %s"
	// Then, invoke YY_ on this string.
	// Finally, use the string as a format to output
	// yytname_[tok], etc.
	// Until this gets fixed, this message appears in English only.
	res = "syntax error, unexpected ";
	res += yytnamerr_ (yytname_[tok]);
	if (count < 5)
	  {
	    count = 0;
	    for (int x = yyxbegin; x < yyxend; ++x)
	      if (yycheck_[x + yyn] == x && x != yyterror_)
		{
		  res += (!count++) ? ", expecting " : " or ";
		  res += yytnamerr_ (yytname_[x]);
		}
	  }
      }
    else
#endif
      res = YY_("syntax error");
    return res;
  }


  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
  const signed char BisonParser::yypact_ninf_ = -3;
  const signed char
  BisonParser::yypact_[] =
  {
        -3,     0,    -3,    -3,    -3,    -3,    23,    22,     9,     9,
      -3,    -3,    -3,    -3,    28,    -3,     5,    -2,     1,     2,
      22,    -3,    31,    28,    28,     9,    22,    22,    22,    22,
      22,    -3,    -3,    -3,    -3,    -3,    -3,    -3,    -3,    -3,
      -3,    -3,    -3,     5,     5
  };

  /* YYDEFACT[S] -- default rule to reduce with in state S when YYTABLE
     doesn't specify something else to do.  Zero means the default is an
     error.  */
  const unsigned char
  BisonParser::yydefact_[] =
  {
        22,     0,     1,    24,     2,     3,     4,     0,     0,     0,
      23,     5,     6,     8,    10,    13,    17,    20,     0,     0,
       0,     4,     0,    11,    12,     0,     0,     0,     0,     0,
       0,    30,    29,    28,    27,    26,    25,    21,     7,     9,
      14,    15,    16,    18,    19
  };

  /* YYPGOTO[NTERM-NUM].  */
  const signed char
  BisonParser::yypgoto_[] =
  {
        -3,    -3,    -3,    18,    17,    10,     3,    -3,     7,    -3,
      -3
  };

  /* YYDEFGOTO[NTERM-NUM].  */
  const signed char
  BisonParser::yydefgoto_[] =
  {
        -1,    11,    12,    13,    14,    15,    16,    17,    18,    19,
       1
  };

  /* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule which
     number is the opposite.  If zero, do what YYDEFACT says.  */
  const signed char BisonParser::yytable_ninf_ = -1;
  const unsigned char
  BisonParser::yytable_[] =
  {
         2,    31,    34,     3,    32,    35,     4,     5,     6,     7,
      29,    30,     8,     9,    22,     4,     5,    21,     7,    26,
      27,    28,    10,    33,    36,    23,    24,    37,     4,     5,
      21,     7,    43,    44,     8,     9,    40,    41,    42,    25,
      20,    38,     0,    39
  };

  /* YYCHECK.  */
  const signed char
  BisonParser::yycheck_[] =
  {
         0,     0,     0,     3,     3,     3,     6,     7,     8,     9,
      12,    13,    12,    13,     7,     6,     7,     8,     9,    14,
      15,    16,    22,    22,    22,     8,     9,    20,     6,     7,
       8,     9,    29,    30,    12,    13,    26,    27,    28,    11,
      17,    10,    -1,    25
  };

  /* STOS_[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
  const unsigned char
  BisonParser::yystos_[] =
  {
         0,    33,     0,     3,     6,     7,     8,     9,    12,    13,
      22,    24,    25,    26,    27,    28,    29,    30,    31,    32,
      17,     8,    31,    27,    27,    11,    14,    15,    16,    12,
      13,     0,     3,    22,     0,     3,    22,    31,    10,    26,
      28,    28,    28,    29,    29
  };

#if YYDEBUG
  /* TOKEN_NUMBER_[YYLEX-NUM] -- Internal symbol number corresponding
     to YYLEX-NUM.  */
  const unsigned short int
  BisonParser::yytoken_number_[] =
  {
         0,   256,   257,   258,   259,   260,   261,   262,   263,    40,
      41,    94,    43,    45,    42,    47,    37,    61,    70,   102,
      91,    93,    59
  };
#endif

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
  const unsigned char
  BisonParser::yyr1_[] =
  {
         0,    23,    24,    24,    25,    26,    26,    26,    27,    27,
      28,    28,    28,    29,    29,    29,    29,    30,    30,    30,
      31,    32,    33,    33,    33,    33,    33,    33,    33,    33,
      33
  };

  /* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
  const unsigned char
  BisonParser::yyr2_[] =
  {
         0,     2,     1,     1,     1,     1,     1,     3,     1,     3,
       1,     2,     2,     1,     3,     3,     3,     1,     3,     3,
       1,     3,     0,     2,     2,     3,     3,     3,     3,     3,
       3
  };

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
  /* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
     First, the terminals, then, starting at \a yyntokens_, nonterminals.  */
  const char*
  const BisonParser::yytname_[] =
  {
    "\"end of file\"", "error", "$undefined", "\"end of line\"",
  "\"axiom\"", "\"production\"", "\"integer\"", "\"double\"", "\"string\"",
  "'('", "')'", "'^'", "'+'", "'-'", "'*'", "'/'", "'%'", "'='", "'F'",
  "'f'", "'['", "']'", "';'", "$accept", "constant", "variable",
  "atomexpr", "powexpr", "unaryexpr", "mulexpr", "addexpr", "expr",
  "assignment", "start", 0
  };
#endif

#if YYDEBUG
  /* YYRHS -- A `-1'-separated list of the rules' RHS.  */
  const BisonParser::rhs_number_type
  BisonParser::yyrhs_[] =
  {
        33,     0,    -1,     6,    -1,     7,    -1,     8,    -1,    24,
      -1,    25,    -1,     9,    31,    10,    -1,    26,    -1,    27,
      11,    26,    -1,    27,    -1,    12,    27,    -1,    13,    27,
      -1,    28,    -1,    29,    14,    28,    -1,    29,    15,    28,
      -1,    29,    16,    28,    -1,    29,    -1,    30,    12,    29,
      -1,    30,    13,    29,    -1,    30,    -1,     8,    17,    31,
      -1,    -1,    33,    22,    -1,    33,     3,    -1,    33,    32,
      22,    -1,    33,    32,     3,    -1,    33,    32,     0,    -1,
      33,    31,    22,    -1,    33,    31,     3,    -1,    33,    31,
       0,    -1
  };

  /* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
     YYRHS.  */
  const unsigned char
  BisonParser::yyprhs_[] =
  {
         0,     0,     3,     5,     7,     9,    11,    13,    17,    19,
      23,    25,    28,    31,    33,    37,    41,    45,    47,    51,
      55,    57,    61,    62,    65,    68,    72,    76,    80,    84,
      88
  };

  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
  const unsigned char
  BisonParser::yyrline_[] =
  {
         0,    88,    88,    92,    97,   110,   114,   118,   123,   127,
     132,   136,   140,   145,   149,   153,   157,   162,   166,   170,
     175,   180,   230,   231,   232,   233,   234,   235,   236,   241,
     245
  };

  // Print the state stack on the debug stream.
  void
  BisonParser::yystack_print_ ()
  {
    *yycdebug_ << "Stack now";
    for (state_stack_type::const_iterator i = yystate_stack_.begin ();
	 i != yystate_stack_.end (); ++i)
      *yycdebug_ << ' ' << *i;
    *yycdebug_ << std::endl;
  }

  // Report on the debug stream that the rule \a yyrule is going to be reduced.
  void
  BisonParser::yy_reduce_print_ (int yyrule)
  {
    unsigned int yylno = yyrline_[yyrule];
    int yynrhs = yyr2_[yyrule];
    /* Print the symbols being reduced, and their result.  */
    *yycdebug_ << "Reducing stack by rule " << yyrule - 1
	       << " (line " << yylno << "):" << std::endl;
    /* The symbols being reduced.  */
    for (int yyi = 0; yyi < yynrhs; yyi++)
      YY_SYMBOL_PRINT ("   $" << yyi + 1 << " =",
		       yyrhs_[yyprhs_[yyrule] + yyi],
		       &(yysemantic_stack_[(yynrhs) - (yyi + 1)]),
		       &(yylocation_stack_[(yynrhs) - (yyi + 1)]));
  }
#endif // YYDEBUG

  /* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
  BisonParser::token_number_type
  BisonParser::yytranslate_ (int t)
  {
    static
    const token_number_type
    translate_table[] =
    {
           0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,    16,     2,     2,
       9,    10,    14,    12,     2,    13,     2,    15,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,    22,
       2,    17,     2,     2,     2,     2,     2,     2,     2,     2,
      18,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    20,     2,    21,    11,     2,     2,     2,     2,     2,
       2,     2,    19,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8
    };
    if ((unsigned int) t <= yyuser_token_number_max_)
      return translate_table[t];
    else
      return yyundef_token_;
  }

  const int BisonParser::yyeof_ = 0;
  const int BisonParser::yylast_ = 43;
  const int BisonParser::yynnts_ = 11;
  const int BisonParser::yyempty_ = -2;
  const int BisonParser::yyfinal_ = 2;
  const int BisonParser::yyterror_ = 1;
  const int BisonParser::yyerrcode_ = 256;
  const int BisonParser::yyntokens_ = 23;

  const unsigned int BisonParser::yyuser_token_number_max_ = 263;
  const BisonParser::token_number_type BisonParser::yyundef_token_ = 2;


/* Line 1053 of lalr1.cc  */
#line 35 "zlsYaccParser.yy"
} // ZLS

/* Line 1053 of lalr1.cc  */
#line 1190 "zlsYaccParser.tab.cc"


/* Line 1055 of lalr1.cc  */
#line 252 "zlsYaccParser.yy"
 /*** Additional Code ***/

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

