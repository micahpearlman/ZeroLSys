/*
 *  zls.h
 *  ZeroLSys-OSX
 *
 *  Created by Micah Pearlman on 10/20/10.
 *  Copyright 2010 Zero Vision. All rights reserved.
 *
 */

#ifndef __ZLS_H__
#define __ZLS_H__

#include <string>
#include <vector>
#include <map>
#include <tr1/memory>

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
		void setSymbol( const string& symbol ) {
			_symbol = symbol;
		}
		
		const string& transform() const {
			return _transform;
		}
		void setTransform( const string& transform ) {
			_transform = transform;
		}
		
	private:
		
		string _symbol;
		string _transform;
	};
	
	inline ProductionRule operator>>( const string& symbol, const string& transform ) {
		return ProductionRule( symbol, transform );
	}
	
	
	class LSystemContext {
	public:
		static LSystemContext& singleton();
		void initialize();
		void reset();
		void terminate();
		
		void setStartState( const string& start ) {
			_start = start;
		}
		void addRule( const ProductionRule& rule ) {
			_rules[rule.symbol()] = rule;
		}
		
		ProductionRule* ruleWithSymbol( const string& symbol ) {
			map<string, ProductionRule>::iterator it = _rules.find(symbol);
			return &it->second;
		}
		
		string& state() {
			return _state;
		}
		
		string& iterate();
		
	private:
		string							_start;
		string							_state;
		map<string, ProductionRule>		_rules;
	};
}
#endif // __ZLS_H__