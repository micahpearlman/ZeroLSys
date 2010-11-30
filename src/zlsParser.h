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
#include "zlsAbstractSyntaxTree.h"
#include "zlsScanner.h"

namespace ZLS {
	using namespace std;
	class Parser {
	public:
		Parser( std::istream * in = 0, std::ostream * out = 0 ) //: _parser(_scanner) 
		:	_scanner( in, out )
		,	_parser( *this )
		{
			
		}
		
		int parse() {
			return _parser.parse();
		}
		
		void print() {
			_rootASTNode->print(cout, 0);
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