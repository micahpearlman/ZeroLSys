/*
 *  zls.cpp
 *  ZeroLSys-OSX
 *
 *  Created by Micah Pearlman on 10/20/10.
 *  Copyright 2010 Zero Vision. All rights reserved.
 *
 */

#include "zlsContext.h"
#include <iostream>
#include "tinyxml.h"

namespace ZeroLSys {
	
	
	void LSystemContext::initialize() {
		
	}
	
	void LSystemContext::reset() {
		_state = _start;
	}
	void LSystemContext::terminate() {
		
	}
	
	void LSystemContext::read( istream& is ) {
		TiXmlDocument doc;
		is >> doc;
		
		TiXmlElement* root = doc.FirstChildElement();
		
		// start
		TiXmlText* start = root->FirstChildElement( "Start" )->FirstChild()->ToText();
		_start = start->Value();
		
		// rules
		TiXmlElement* rules = root->FirstChildElement( "Rules" );
		for ( TiXmlElement* rule = rules->FirstChildElement( "Rule" ); rule != 0; rule = rule->NextSiblingElement() ) {
			stringstream ruleStream;
			ruleStream << *rule;
			
			ProductionRule rule;
			rule.read( ruleStream );
			addRule( rule );
		}
	}
	
	void LSystemContext::write( ostream& os ) {
		TiXmlDocument doc;
		TiXmlDeclaration* decl = new TiXmlDeclaration( "1.0", "", "" );
		doc.LinkEndChild( decl );
		TiXmlElement* root = new TiXmlElement( "LSystem" );
		doc.LinkEndChild( root );
		
		TiXmlElement* start = new TiXmlElement( "Start" );
		start->LinkEndChild( new TiXmlText( _start ) );
		root->LinkEndChild( start );
		
		// write rules
		TiXmlElement* blahblah = new TiXmlElement( "blahblah" );
		stringstream rulestream;
		for ( ProductionRuleMap::iterator ruleIt = _rules.begin(); ruleIt != _rules.end(); ruleIt++ ) {
			ruleIt->second.write(rulestream);
		}
		rulestream >> *blahblah;
		TiXmlElement* rules = new TiXmlElement( "Rules" );
		rules->LinkEndChild( blahblah );
		root->LinkEndChild( rules );

		// setup for pretty print so we can hand edit
		TiXmlPrinter pretty_printer;
		pretty_printer.SetIndent( "\t" );
		doc.Accept( &pretty_printer );
		os << pretty_printer.Str();
		
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

