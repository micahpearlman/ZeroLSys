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
#include <iostream>
#include <algorithm>
#include <cctype>

#include "zlsProductionRule.h"
#include "zlsStateViewer.h"


namespace ZLS {
	
	using namespace std;
	
	
	class LSystemContext {
	public:
		
		LSystemContext()
		:	_stateViewer( 0 )
		,	_start("empty")
		,	_state("empty")
		{
			
		}
		
		void initialize();
		void reset();
		void terminate();

		void read( istream& is );
		void write( ostream& os );
		
		string startState() const {
			return _start;
		}
		void setStartState( const string& start );
		
		void addRule( const ProductionRule& rule ) {
			_rules[rule.symbol()] = rule;
		}
		
		ProductionRule* ruleWithSymbol( const string& symbol ) {
			map<string, ProductionRule>::iterator it = _rules.find(symbol);
			if ( it != _rules.end() ) {
				return &it->second;
			}
			
			return 0;
		}
		
		string& state() {
			return _state;
		}
		
		string& iterate();
		
		StateViewer* stateViewer() {
			return _stateViewer;
		}
		void setStateViewer( StateViewer* sv ) {
			_stateViewer = sv;
		}
		
		
		
	private:
		typedef map<string, ProductionRule> ProductionRuleMap;
		string							_start;
		string							_state;
		ProductionRuleMap				_rules;
		StateViewer*					_stateViewer;
		
	};
}
#endif // __ZLS_H__