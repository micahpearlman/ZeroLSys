/*
 *  zlsProductionRule.cpp
 *  ZeroLSys-OSX
 *
 *  Created by Micah Pearlman on 10/22/10.
 *  Copyright 2010 Zero Vision. All rights reserved.
 *
 */

#include "zlsProductionRule.h"

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>

namespace ZeroLSys {
	
	using boost::property_tree::ptree;
	
	void ProductionRule::read( istream& is ) {
		
		ptree pt;
		read_xml( is, pt );
		_symbol = pt.get<string>( "Symbol" );
		_transform = pt.get<string>( "Transform" );
	}
	
	void ProductionRule::write( ostream& os ) {
		ptree pt;
		pt.put( "Symbol", _symbol );
		pt.put( "Transform", _transform );
		write_xml( os, pt );
		
	}

}