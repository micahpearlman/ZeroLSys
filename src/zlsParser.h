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

namespace ZLS {
	class Parser {
	public:
		Parser( std::istream * in = 0, std::ostream * out = 0 ) //: _parser(_scanner) 
		:	_scanner( in, out )
		,	_parser( _scanner )
		{
			
		}
		
		int parse() {
			return _parser.parse();
		}
		
	private:
		ZLS::FlexScanner _scanner;
		ZLS::BisonParser _parser;
	};
}

#endif // __ZLS_PARSER_H__