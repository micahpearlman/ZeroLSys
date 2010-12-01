/*
 *  zlsParser.cpp
 *  ZeroLSys-OSX
 *
 *  Created by Micah Pearlman on 11/2/10.
 *  Copyright 2010 Zero Vision. All rights reserved.
 *
 */

#include "zlsParser.h"
#include "zlsAbstractSyntaxTree.h"
#include <iostream>
#include <string>
#include <vector>
using namespace std;
#include <boost/spirit/include/phoenix.hpp>
#include <boost/spirit/include/phoenix_core.hpp>
#include <boost/spirit/include/phoenix_operator.hpp>
#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/qi_char.hpp>
#include <boost/spirit/home/phoenix/object/new.hpp>
#include <boost/fusion/include/adapt_struct.hpp>


typedef vector<ZLS::ASTNode*> vector_astnode_t;

struct myresult {
	vector_astnode_t turtle_commands;
};

BOOST_FUSION_ADAPT_STRUCT
(
	 myresult,
	 (vector_astnode_t, turtle_commands)
)
;	

	
	
	
	namespace spirit = boost::spirit;
	namespace qi = boost::spirit::qi;
	namespace ascii = boost::spirit::ascii;
	namespace phoenix = boost::phoenix;


	struct debugprint {
		string _name;
		debugprint( string n ) : _name(n){}
		
		void operator()(int const& i, qi::unused_type, qi::unused_type) const {
			cout << _name << std::endl;
        }
		void operator()(qi::unused_type, qi::unused_type, qi::unused_type) const {
			cout << _name << std::endl;
        }		
		
		// todo: more of these for each type
		
	};
	
	
	template <typename Iterator>
	struct lsystem_parser :  qi::grammar<Iterator, vector_astnode_t() > {
		lsystem_parser( ZLS::Context* ctx )
		:	lsystem_parser::base_type(start) 
		,	_ctx( ctx )
		{
			using qi::char_;
			using qi::float_;
			using qi::eps;
			using qi::lit;
			using qi::_1;
			using qi::_val;
			using phoenix::ref;
			using phoenix::push_back;
			using phoenix::at_c;
			using phoenix::new_;
			
			float_parameters = '(' >> (float_ >> *(',' >> float_)) >> ')';
			
			/// turtle grammar ///
			//typedef (ZLS::ASTNode*)0 null_astnode_t;
			draw_forward	= ( char_('F')	[ _val = new_<ZLS::ASTDrawForward>(_ctx, (ZLS::ASTNode*)0)] )
											[debugprint("draw_forward")];
			
			move_forward	= ( char_('f')	[ _val = new_<ZLS::ASTMoveForward>(_ctx, (ZLS::ASTNode*)0)] )
											[debugprint("move_forward")];
			
			turn_left		= ( char_('+')	[ _val = new_<ZLS::ASTTurnLeft>(_ctx, (ZLS::ASTNode*)0)] )
											[debugprint("turn_left")];
			
			turn_right		= ( char_('-')	[ _val = new_<ZLS::ASTTurnRight>(_ctx, (ZLS::ASTNode*)0)] )
											[debugprint("turn_right")];
			
			push_state		= ( char_('[')	[ _val = new_<ZLS::ASTPushState>(_ctx)] )
											[debugprint("push_state")];
			
			pop_state		= ( char_(']')	[ _val = new_<ZLS::ASTPopState>(_ctx) ] )
											[debugprint("pop_state")];
			
			turtle_commands = (draw_forward
							| move_forward	
							| turn_left		
							| turn_right	
							| push_state	
							| pop_state)[_val = _1];		
			
			
			start = *turtle_commands >> qi::eps;
		}
		qi::rule< Iterator, vector_astnode_t() > start;
		qi::rule< Iterator, vector<float> > float_parameters;
		
		qi::rule< Iterator, ZLS::ASTNode*() > draw_forward;
		qi::rule< Iterator, ZLS::ASTNode*() > move_forward;
		qi::rule< Iterator, ZLS::ASTNode*() > turn_left;
		qi::rule< Iterator, ZLS::ASTNode*() > turn_right;
		qi::rule< Iterator, ZLS::ASTNode*() > push_state;
		qi::rule< Iterator, ZLS::ASTNode*() > pop_state;
		qi::rule< Iterator, ZLS::ASTNode*() > turtle_commands;
		
		ZLS::Context*	_ctx;
		
	};


	
namespace ZLS {
	
	bool Parser::parse( Context* ctx, istream& is ) {
		
		typedef std::string::const_iterator iterator_type;
		typedef lsystem_parser<iterator_type> parser_type;
		
		//const string test("F(1,2,3)f");
		string s;
		is >> s;
		vector_astnode_t result;
		parser_type parser(ctx);
		iterator_type begin(s.begin());
		iterator_type end(s.end());
		
		
		qi::phrase_parse( begin, end, parser, ascii::space, result );
		
		for ( vector<ASTNode*>::iterator it = result.begin(); it != result.end(); it++ ) {
			ASTNode* node = *it;
			node->print( cout, 0 );
		}
		return true;
	}
}


