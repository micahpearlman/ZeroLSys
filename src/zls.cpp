/*
 *  zls.cpp
 *  ZeroLSys-OSX
 *
 *  Created by Micah Pearlman on 10/20/10.
 *  Copyright 2010 Zero Vision. All rights reserved.
 *
 */

#include "zls.h"

namespace ZeroLSys {
	
	static LSystemContext g_LSystemContext;
	LSystemContext& LSystemContext::singleton() {
		return g_LSystemContext;
	}
	void LSystemContext::initialize() {
		
	}
	
	void LSystemContext::reset() {
		_state = _start;
	}
	void LSystemContext::terminate() {
		
	}
	
	string& LSystemContext::iterate() {
		const char* s = _state.c_str();
		string newstate;
		
		while ( *s ) {
			ProductionRule* rule = ruleWithSymbol( string( 1, *s ) );
			if ( rule ) {
				newstate.append( rule->transform() );
			} else {
				newstate.append( string( 1, *s ) );
			}
			
			s++;
		}
		
		_state = newstate;
		
		return _state;
	}
	
}