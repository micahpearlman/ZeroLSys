/*
 *  zls.cpp
 *  ZeroLSys-OSX
 *
 *  Created by Micah Pearlman on 10/20/10.
 *  Copyright 2010 Zero Vision. All rights reserved.
 *
 */

#include "zlsContext.h"
#include <string>
#include <iostream>
#include <algorithm>
#include <cctype>

using namespace std;

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include <boost/foreach.hpp>



namespace ZeroLSys {
	
	
	void LSystemContext::initialize() {
		
	}
	
	void LSystemContext::reset() {
		_state = _start;
	}
	void LSystemContext::terminate() {
		
	}
	
	void LSystemContext::setStartState( const string& start ) {
		_start = start;
		// remove white space
		_start.erase(std::remove_if(_start.begin(), _start.end(), ::isspace), _start.end());
		
	}
	
	
	using boost::property_tree::ptree;
	
	void LSystemContext::read( istream& is ) {
		ptree pt;
		
		read_xml( is, pt );
		_start = pt.get<string>( "LSystem.Start" );
		
		BOOST_FOREACH( ptree::value_type& v, pt.get_child( "LSystem.Rules" ) ) {
			stringstream rs;
			write_xml( rs, v.second );
			ProductionRule newrule;
			newrule.read( rs );
			addRule( newrule );
		}
		
		
	}
	
	void LSystemContext::write( ostream& os ) {
		
		ptree root;
		root.put( "LSystem.Start", _start );
		
		for ( ProductionRuleMap::iterator ruleIt = _rules.begin(); ruleIt != _rules.end(); ruleIt++ ) {
			stringstream rs;
			ruleIt->second.write( rs );
			ptree rule_pt;
			read_xml( rs, rule_pt );
			root.add_child( "LSystem.Rules.Rule", rule_pt );
		}
		
		write_xml( os, root );
		
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

