/*
 *  zlsParser.h
 *  ZeroLSys-OSX
 *
 *  Created by Micah Pearlman on 11/2/10.
 *  Copyright 2010 Zero Vision. All rights reserved.
 *
 */

#ifndef __ZLSPARSER_H__
#define __ZLSPARSER_H__

#include <iostream>

namespace ZLS {
	using namespace std;
	class Context;
	class Parser  {
	public:
		bool parse( Context* ctx, istream& is );
		//template< typename Functor > void addHandler( const string& symbol, Functor handler );
	};
}

#endif // __ZLSPARSER_H__