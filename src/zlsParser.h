/*
 *  zlsParser.h
 *  ZeroLSys-OSX
 *
 *  Created by Micah Pearlman on 11/27/10.
 *  Copyright 2010 Zero Vision. All rights reserved.
 *
 */
#ifndef __ZLS_PARSER_H__
#define __ZLS_PARSER_H__

#include <vector>
#include <sstream>
#include "zlsScanner.h"
#include "zlsAbstractSyntaxTree.h"

namespace ZLS {
	using namespace std;
	class Context;
	class Parser {
	public:
		Parser( Context* ctx, std::istream * in = 0, std::ostream * out = 0 ) //: _parser(_scanner) 
		:	_scanner( in, out )
		,	_parser( *ctx )
		{
			
		}
		
		int parse() {
			return _parser.parse();
		}
		
		string description() {
			stringstream ss;
			if ( _rootASTNode ) {
				_rootASTNode->print(ss, 0);
			}
			
			return ss.str();
		}
		
		ASTNode* root() {
			return _rootASTNode;
		}
		void setRoot( ASTNode* root ) {
			_rootASTNode = root;
		}
		
		// private //
		ZLS::FlexScanner& scanner() {
			return _scanner;
		}
		
	private:
		ASTNode*			_rootASTNode;
		ZLS::FlexScanner	_scanner;
		ZLS::BisonParser	_parser;
	};
}

#endif // __ZLS_PARSER_H__