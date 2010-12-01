/*
 *  zlsParser.cpp
 *  ZeroLSys-OSX
 *
 *  Created by Micah Pearlman on 11/2/10.
 *  Copyright 2010 Zero Vision. All rights reserved.
 *
 */

#include "zlsParser.h"

#include <iostream>
#include <string>
#include <vector>
using namespace std;
#include <boost/fusion/include/adapt_struct.hpp>
#include <boost/spirit/include/phoenix.hpp>
#include <boost/spirit/include/phoenix_core.hpp>
#include <boost/spirit/include/phoenix_operator.hpp>
#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/qi_char.hpp>

using namespace boost;

namespace ZeroLSys {
	
	
	
	
	namespace spirit = boost::spirit;
	namespace qi = boost::spirit::qi;
	namespace ascii = boost::spirit::ascii;
	namespace phoenix = boost::phoenix;


	struct debugprint {
		string _name;
		debugprint( string n ) : _name(n) {}
		
		void operator()(int const& i, qi::unused_type, qi::unused_type) const {
			cout << _name << std::endl;
        }		
		
		
	};
	
	template <typename Iterator>
	struct lsystem_parser :  qi::grammar<Iterator, vector<unsigned> > {
		lsystem_parser()
		:	lsystem_parser::base_type(start) 
		{
			using qi::char_;
			using qi::float_;
			using qi::eps;
			using qi::lit;
			using qi::_1;
			using phoenix::ref;
			
			float_parameters = '(' >> (float_ >> *(',' >> float_)) >> ')';// >> *(',' >> float_);
			
			/// turtle grammar ///
			draw_forward = char_('F')[debugprint("draw_forward")];
			move_forward = char_('f')[debugprint("move_forward")];
			turn_left = char_('+')[debugprint("turn_left")];
			turn_right = char_('-')[debugprint("turn_right")];
			push_state = char_('[')[debugprint("push_state")];
			pop_state = char_(']')[debugprint("pop_state")];
			
			turtle_commands = draw_forward | move_forward | turn_left | turn_right | push_state | pop_state;
			
			
			start %= *turtle_commands;
		}
		qi::rule< Iterator, vector<unsigned> > start;
		qi::rule< Iterator, vector<float> > float_parameters;
		
		qi::rule< Iterator, unsigned() > draw_forward;
		qi::rule< Iterator, unsigned() > move_forward;
		qi::rule< Iterator, unsigned() > turn_left;
		qi::rule< Iterator, unsigned() > turn_right;
		qi::rule< Iterator, unsigned() > push_state;
		qi::rule< Iterator, unsigned() > pop_state;
		qi::rule< Iterator, unsigned() > turtle_commands;		
	};
	
	
	bool Parser::parse( istream& is ) {
		
		typedef std::string::const_iterator iterator_type;
		typedef lsystem_parser<iterator_type> parser_type;
		
		//const string test("F(1,2,3)f");
		string s;
		is >> s;
		parser_type parser;
		iterator_type begin(s.begin());
		iterator_type end(s.end());
		
		unsigned result;
		qi::phrase_parse( begin, end, parser, ascii::space, result );
		return true;
	}
}


