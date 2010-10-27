/*
 *  zlsProductionRule.cpp
 *  ZeroLSys-OSX
 *
 *  Created by Micah Pearlman on 10/22/10.
 *  Copyright 2010 Zero Vision. All rights reserved.
 *
 */

#include "zlsProductionRule.h"
#include "tinyxml.h"

namespace ZeroLSys {
	void ProductionRule::read( istream& is ) {
		TiXmlDocument doc;
		is >> doc;
		
		TiXmlElement* rule = doc.FirstChildElement();
		
		TiXmlText* symbol = rule->FirstChildElement( "Symbol" )->FirstChild()->ToText();
		_symbol = symbol->Value();
		
		TiXmlText* transform = rule->FirstChildElement( "Transform" )->FirstChild()->ToText();
		_transform = transform->Value();
	}
	
	void ProductionRule::write( ostream& os ) {
		TiXmlElement* rule = new TiXmlElement( "Rule" );
		
		TiXmlElement* symbol = new TiXmlElement( "Symbol" );
		symbol->LinkEndChild( new TiXmlText( _symbol ) );
		rule->LinkEndChild( symbol );

		TiXmlElement* transform = new TiXmlElement( "Transform" );
		transform->LinkEndChild( new TiXmlText( _transform ) );
		rule->LinkEndChild( transform );
		
		os << *rule;
		
	}

}