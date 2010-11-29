/*
 *  zlsScanner.h
 *  ZeroLSys-OSX
 *
 *  Created by Micah Pearlman on 11/27/10.
 *  Copyright 2010 Zero Vision. All rights reserved.
 *
 */
#ifndef __ZLS_SCANNER_H__
#define __ZLS_SCANNER_H__
// Only include FlexLexer.h if it hasn't been already included
#if ! defined(yyFlexLexerOnce)
#include <FlexLexer.h>
#endif

// Override the interface for yylex since we namespaced it
#undef YY_DECL
#define YY_DECL int ZLS::FlexScanner::yylex()

// Include Bison for types / tokens
#include "zlsYaccParser.tab.hh"


namespace ZLS {
	class FlexScanner : public yyFlexLexer {
	public:
		
		// constructor accepts the input and output streams
		// 0 means std equivilant (stdin, stdout)
		FlexScanner(std::istream * in = 0, std::ostream * out = 0) : yyFlexLexer(in, out) { }
		
		// save the pointer to yylval so we can change it, and invoke scanner
		int yylex(ZLS::BisonParser::semantic_type * lval) { yylval = lval; return yylex(); }
		
	private:
		// Scanning function created by Flex; make this private to force usage
		// of the overloaded method so we can get a pointer to Bison's yylval
		int yylex();
		
		// point to yylval (provided by Bison in overloaded yylex)
		ZLS::BisonParser::semantic_type * yylval;
	};
}

#endif // __ZLS_SCANNER_H__