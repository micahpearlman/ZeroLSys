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

#if 1
namespace ZeroLSys {
	
	void test_function() {
		cout << "test function!" << endl;
	}
	struct test_handler {
		void test() {
			cout << "test handler!" << endl;
		}
	};
	
	
	namespace spirit = boost::spirit;
	namespace qi = boost::spirit::qi;
	namespace ascii = boost::spirit::ascii;
	namespace phoenix = boost::phoenix;

	
	template <typename Iterator>
	struct lsystem_parser :  qi::grammar<Iterator, unsigned() > {
		lsystem_parser()
		:	lsystem_parser::base_type(start) 
		{
			using qi::char_;
			using qi::float_;
			using qi::eps;
			using qi::lit;
			using qi::_1;
			using phoenix::ref;
			
			float_parameters %= '(' >> (float_ >> *(',' >> float_)) >> ')';// >> *(',' >> float_);
			draw_forward %= 'F' -float_parameters;
			
			start %= draw_forward[&test_function];
		}
		qi::rule< Iterator, unsigned() > start;
		qi::rule< Iterator, vector<float> > float_parameters;
		qi::rule< Iterator, unsigned() > draw_forward;
		
	};
	
	
	bool Parser::parse( istream& is ) {
		
		typedef std::string::const_iterator iterator_type;
		typedef lsystem_parser<iterator_type> parser_type;
		
		const string test("F(1,2,3)f");
		
		parser_type parser;
		iterator_type begin(test.begin());
		iterator_type end(test.end());
		
		unsigned result;
		qi::phrase_parse( begin, end, parser, ascii::space, result );
		return true;
	}
}
#endif 


