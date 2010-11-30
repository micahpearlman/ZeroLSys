/*
 *  zls.cpp
 *  ZeroLSys-OSX
 *
 *  Created by Micah Pearlman on 10/20/10.
 *  Copyright 2010 Zero Vision. All rights reserved.
 *
 */

#include "zlsContext.h"
#include "zlsStateViewer.h"
#include "zlsParser.h"

#include <string>
#include <iostream>
#include <algorithm>
#include <cctype>
#include <sstream>

using namespace std;

namespace ZLS {
	
	
	void Context::initialize() {
		
	}
	
	void Context::reset() {
		_state = _start;
	}
	void Context::terminate() {
		
	}
	
	void Context::setStartState( const string& start ) {
		_start = start;
		// remove white space
		_start.erase(std::remove_if(_start.begin(), _start.end(), ::isspace), _start.end());
		
	}
	
	void Context::read( istream& is ) {
		if ( _parser ) {
			delete _parser;
			_parser = 0;
		}
		_parser = new Parser( this, &is );
		_parser->parse();
	}
	
	void Context::write( ostream& os ) {
		// todo
	}
	
	string Context::description() {
		stringstream ss;
		if ( _parser ) {
			ss << _parser->description();
		}
		if ( _stateViewer ) {
			ss << _stateViewer->description();
		}
		
		return ss.str();
		
	}

	
	
	string& Context::iterate() {
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

