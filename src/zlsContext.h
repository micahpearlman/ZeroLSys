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
#include "zlsProductionRule.h"

namespace ZeroLSys {
	
	using namespace std;
	
	
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