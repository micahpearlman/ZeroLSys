/*
 *  zlsAbstractSyntaxTree.h
 *  ZeroLSys-OSX
 *
 *  Created by Micah Pearlman on 11/27/10.
 *  Copyright 2010 Zero Vision. All rights reserved.
 *
 */

#ifndef __ZLS_ABSTRACTSYNTAXTREE_H__
#define __ZLS_ABSTRACTSYNTAXTREE_H__
#include <map>
#include <vector>
#include <ostream>
#include <cmath>
#include <string>
#include "zlsStateViewer.h"

namespace ZLS {
	
	using namespace std;
	
	class ASTNode  {
	public:
		virtual ~ASTNode() {}
		virtual float evaluate() = 0;
		virtual void print( ostream& os, unsigned int depth = 0 ) const = 0;
		
		static inline string indent( unsigned int d ) {
			return string( d*2, ' ' );
		}
	};
	
	class ASTConstant : public ASTNode {
	public:
		
		explicit ASTConstant( float v )
		:	ASTNode()
		,	_value( v )
		{}
		
		virtual float evaluate() {
			return _value;
		}
		
		virtual void print( ostream& os, unsigned int depth ) const {
			os << indent(depth) << _value << endl;
		}
	private:
		float	_value;
	};
	
	class ASTNegate : public ASTNode {
	public:
		explicit ASTNegate( ASTNode* node )
		:	ASTNode()
		,	_node( node )
		{
			
		}
		
		
		virtual float evaluate() {
			return -_node->evaluate();
		}
		
		virtual void print(std::ostream &os, unsigned int depth) const {
			os << indent(depth) << "- negate" << std::endl;
			_node->print(os, depth+1);
		}		
		
	private:
		ASTNode*	_node;
	};
	
	class ASTAdd : public ASTNode {
	public:
		explicit ASTAdd( ASTNode* left, ASTNode* right )
		:	ASTNode()
		,	_left( left )
		,	_right( right )
		{}
		
		virtual ~ASTAdd() {
			delete _left;
			delete _right;
		}
		
		virtual float evaluate() {
			return _left->evaluate() + _right->evaluate();
		}
		
		virtual void print(std::ostream &os, unsigned int depth) const {
			os << indent(depth) << "+ add" << std::endl;
			_left->print(os, depth+1);
			_right->print(os, depth+1);
		}		
		
	private:
		ASTNode*	_left, *_right;
	};

	class ASTSubtract : public ASTNode {
	public:
		explicit ASTSubtract( ASTNode* left, ASTNode* right )
		:	ASTNode()
		,	_left( left )
		,	_right( right )
		{}
		
		virtual ~ASTSubtract() {
			delete _left;
			delete _right;
		}
		
		virtual float evaluate() {
			return _left->evaluate() - _right->evaluate();
		}
		
		virtual void print(std::ostream &os, unsigned int depth) const {
			os << indent(depth) << "- subtract" << std::endl;
			_left->print(os, depth+1);
			_right->print(os, depth+1);
		}		
		
	private:
		ASTNode*	_left, *_right;
	};

	class ASTMultiply : public ASTNode {
	public:
		explicit ASTMultiply( ASTNode* left, ASTNode* right )
		:	ASTNode()
		,	_left( left )
		,	_right( right )
		{}
		
		virtual ~ASTMultiply() {
			delete _left;
			delete _right;
		}
		
		virtual float evaluate() {
			return _left->evaluate() * _right->evaluate();
		}
		
		virtual void print(std::ostream &os, unsigned int depth) const {
			os << indent(depth) << "* multiply" << std::endl;
			_left->print(os, depth+1);
			_right->print(os, depth+1);
		}		
		
	private:
		ASTNode*	_left, *_right;
	};

	class ASTDivide : public ASTNode {
	public:
		explicit ASTDivide( ASTNode* left, ASTNode* right )
		:	ASTNode()
		,	_left( left )
		,	_right( right )
		{}
		
		virtual ~ASTDivide() {
			delete _left;
			delete _right;
		}
		
		virtual float evaluate() {
			return _left->evaluate() / _right->evaluate();
		}
		
		virtual void print(std::ostream &os, unsigned int depth) const {
			os << indent(depth) << "/ divide" << std::endl;
			_left->print(os, depth+1);
			_right->print(os, depth+1);
		}		
		
	private:
		ASTNode*	_left, *_right;
	};
	

	class ASTModulo : public ASTNode {
	public:
		explicit ASTModulo( ASTNode* left, ASTNode* right )
		:	ASTNode()
		,	_left( left )
		,	_right( right )
		{}
		
		virtual ~ASTModulo() {
			delete _left;
			delete _right;
		}
		
		virtual float evaluate() {
			return std::fmod(_left->evaluate(), _right->evaluate());
		}
		
		virtual void print(std::ostream &os, unsigned int depth) const {
			os << indent(depth) << "/ divide" << std::endl;
			_left->print(os, depth+1);
			_right->print(os, depth+1);
		}		
		
	private:
		ASTNode*	_left, *_right;
	};

	class ASTPower : public ASTNode {
	public:
		explicit ASTPower( ASTNode* left, ASTNode* right )
		:	ASTNode()
		,	_left( left )
		,	_right( right )
		{}
		
		virtual ~ASTPower() {
			delete _left;
			delete _right;
		}
		
		virtual float evaluate() {
			return std::pow(_left->evaluate(), _right->evaluate());
		}
		
		virtual void print(std::ostream &os, unsigned int depth) const {
			os << indent(depth) << "/ divide" << std::endl;
			_left->print(os, depth+1);
			_right->print(os, depth+1);
		}		
		
	private:
		ASTNode*	_left, *_right;
	};
	
	///////////////////// L-System Commands /////////////////////
	
	//	void DrawForward();		// F( distance )
	//	void MoveForward();		// f( distance )
	//	void TurnLeft();		// +( degrees )
	//	void TurnRight();		// -( degrees )
	//	void ChangeColor();		// C( R, G, B, A )
	//	void PushState();		// [
	//	void PopState();		// ]
	
	class ASTDrawForward : public ASTNode {
	public:
		explicit ASTDrawForward( StateViewer* sv, ASTNode* parameter )
		:	ASTNode()
		,	_stateViewer( sv )
		,	_parameter( parameter )
		{}
		
		virtual float evaluate() {
			_stateViewer->addParameter( _parameter->evaluate() );
			_stateViewer->executeHandlerForSymbol( string("F") );
			return 0;
		}
		
		virtual void print(std::ostream &os, unsigned int depth) const {
			os << indent(depth) << "F DrawForward" << std::endl;
			_parameter->print(os, depth+1);
		}		
		
	private:
		StateViewer*	_stateViewer;
		ASTNode*		_parameter;
	};

	class ASTMoveForward : public ASTNode {
	public:
		explicit ASTMoveForward( StateViewer* sv, ASTNode* parameter )
		:	ASTNode()
		,	_stateViewer( sv )
		,	_parameter( parameter )
		{}
		
		virtual float evaluate() {
			_stateViewer->addParameter( _parameter->evaluate() );
			_stateViewer->executeHandlerForSymbol( string("f") );
			return 0;
		}
		
		virtual void print(std::ostream &os, unsigned int depth) const {
			os << indent(depth) << "f MoveForward" << std::endl;
			_parameter->print(os, depth+1);
		}		
		
	private:
		StateViewer*	_stateViewer;
		ASTNode*		_parameter;
	};

	class ASTTurnLeft : public ASTNode {
	public:
		explicit ASTTurnLeft( StateViewer* sv, ASTNode* parameter )
		:	ASTNode()
		,	_stateViewer( sv )
		,	_parameter( parameter )
		{}
		
		virtual float evaluate() {
			_stateViewer->addParameter( _parameter->evaluate() );
			_stateViewer->executeHandlerForSymbol( string("+") );
			return 0;
		}
		
		virtual void print(std::ostream &os, unsigned int depth) const {
			os << indent(depth) << "+ TurnLeft" << std::endl;
			_parameter->print(os, depth+1);
		}		
		
	private:
		StateViewer*	_stateViewer;
		ASTNode*		_parameter;
	};

	class ASTTurnRight : public ASTNode {
	public:
		explicit ASTTurnRight( StateViewer* sv, ASTNode* parameter )
		:	ASTNode()
		,	_stateViewer( sv )
		,	_parameter( parameter )
		{}
		
		virtual float evaluate() {
			_stateViewer->addParameter( _parameter->evaluate() );
			_stateViewer->executeHandlerForSymbol( string("-") );
			return 0;
		}
		
		virtual void print(std::ostream &os, unsigned int depth) const {
			os << indent(depth) << "- TurnRight" << std::endl;
			_parameter->print(os, depth+1);
		}		
		
	private:
		StateViewer*	_stateViewer;
		ASTNode*		_parameter;
	};

	class ASTChangeColor : public ASTNode {
	public:
		explicit ASTChangeColor( StateViewer* sv, ASTNode* r, ASTNode* g, ASTNode* b, ASTNode* a )
		:	ASTNode()
		,	_stateViewer( sv )
		,	_r( r )
		,	_g( g )
		,	_b( b )
		,	_a( a )
		{}
		
		virtual float evaluate() {
			_stateViewer->addParameter( _r->evaluate() );
			_stateViewer->addParameter( _g->evaluate() );
			_stateViewer->addParameter( _b->evaluate() );
			_stateViewer->addParameter( _a->evaluate() );
			_stateViewer->executeHandlerForSymbol( string("C") );
			return 0;
		}
		
		virtual void print(std::ostream &os, unsigned int depth) const {
			os << indent(depth) << "C ChangeColor" << std::endl;
			_r->print(os, depth+1);
			_g->print(os, depth+1);
			_b->print(os, depth+1);
			_a->print(os, depth+1);
		}		
		
	private:
		StateViewer*	_stateViewer;
		ASTNode*		_r, *_g, *_b, *_a;
	};
	
	class ASTPushState : public ASTNode {
	public:
		explicit ASTPushState( StateViewer* sv )
		:	ASTNode()
		,	_stateViewer( sv )
		{}
		
		virtual float evaluate() {
			_stateViewer->executeHandlerForSymbol( string("[") );
			return 0;
		}
		
		virtual void print(std::ostream &os, unsigned int depth) const {
			os << indent(depth) << "[ PushState" << std::endl;
		}		
		
	private:
		StateViewer*	_stateViewer;
	};

	class ASTPopState : public ASTNode {
	public:
		explicit ASTPopState( StateViewer* sv )
		:	ASTNode()
		,	_stateViewer( sv )
		{}
		
		virtual float evaluate() {
			_stateViewer->executeHandlerForSymbol( string("]") );
			return 0;
		}
		
		virtual void print(std::ostream &os, unsigned int depth) const {
			os << indent(depth) << "] PopState" << std::endl;
		}		
		
	private:
		StateViewer*	_stateViewer;
	};
	
	///////////////////// AST Context /////////////////////
	class ASTContext {
		
	public:
		bool doesVariableExist( const string& varname ) {
			return _variables.find( varname ) != _variables.end();
		}
		float variableValue( const string& varname ) {
			map<string, float>::iterator vi = _variables.find( varname );
			if ( vi != _variables.end() ) {
				return vi->second;
			}
			return 0;	// error
		}
	private:
		map<string, float>	_variables;
		vector<ASTNode*>	_expressions;
	};
	
}
#endif // __ZLS_ABSTRACTSYNTAXTREE_H__
