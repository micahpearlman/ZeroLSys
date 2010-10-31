/*
 *  zlsProductionRule.h
 *  ZeroLSys-OSX
 *
 *  Created by Micah Pearlman on 10/22/10.
 *  Copyright 2010 Zero Vision. All rights reserved.
 *
 */

#ifndef __ZLS_PRODUCTION_RULE_H__
#define __ZLS_PRODUCTION_RULE_H__

#include <string>
#include <iostream>
#include <algorithm>
#include <cctype>

namespace ZeroLSys {
	
	using namespace std;
	
	class ProductionRule {
	public:
		ProductionRule()
		{}
		
		ProductionRule( const string& symbol, const string& transform ) 
		:	_symbol( symbol )
		,	_transform( transform ) 
		{}
		
		ProductionRule( const ProductionRule& other ) 
		:	_symbol( other._symbol )
		,	_transform( other._transform ) 
		{}
		
		
		const string& symbol() const {
			return _symbol;
		}
		void setSymbol( const string& symbol );
		
		const string& transform() const {
			return _transform;
		}
		void setTransform( const string& transform );

		// IO
		void read( istream& is );
		void write( ostream& os );
		
	private:
		
		string _symbol;
		string _transform;
		
	};

	inline ProductionRule operator>>( const string& symbol, const string& transform ) {
		return ProductionRule( symbol, transform );
	}
	
}

#endif // __ZLS_PRODUCTION_RULE_H__