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
#include "zlsContext.h"
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
		explicit ASTDrawForward( Context* ctx, ASTNode* parameter )
		:	ASTNode()
		,	_context( ctx )
		,	_parameter( parameter )
		{}
		
		virtual float evaluate() {
			_context->stateViewer()->addParameter( _parameter->evaluate() );
			_context->stateViewer()->executeHandlerForSymbol( string("F") );
			return 0;
		}
		
		virtual void print(std::ostream &os, unsigned int depth) const {
			os << indent(depth) << "F DrawForward" << std::endl;
			_parameter->print(os, depth+1);
		}		
		
	private:
		Context*	_context;
		ASTNode*		_parameter;
	};

	class ASTMoveForward : public ASTNode {
	public:
		explicit ASTMoveForward( Context* ctx, ASTNode* parameter )
		:	ASTNode()
		,	_context( ctx )
		,	_parameter( parameter )
		{}
		
		virtual float evaluate() {
			_context->stateViewer()->addParameter( _parameter->evaluate() );
			_context->stateViewer()->executeHandlerForSymbol( string("f") );
			return 0;
		}
		
		virtual void print(std::ostream &os, unsigned int depth) const {
			os << indent(depth) << "f MoveForward" << std::endl;
			_parameter->print(os, depth+1);
		}		
		
	private:
		Context*	_context;
		ASTNode*	_parameter;
	};

	class ASTTurnLeft : public ASTNode {
	public:
		explicit ASTTurnLeft( Context* ctx, ASTNode* parameter )
		:	ASTNode()
		,	_context( ctx )
		,	_parameter( parameter )
		{}
		
		virtual float evaluate() {
			_context->stateViewer()->addParameter( _parameter->evaluate() );
			_context->stateViewer()->executeHandlerForSymbol( string("+") );
			return 0;
		}
		
		virtual void print(std::ostream &os, unsigned int depth) const {
			os << indent(depth) << "+ TurnLeft" << std::endl;
			_parameter->print(os, depth+1);
		}		
		
	private:
		Context*	_context;
		ASTNode*		_parameter;
	};

	class ASTTurnRight : public ASTNode {
	public:
		explicit ASTTurnRight( Context* ctx, ASTNode* parameter )
		:	ASTNode()
		,	_context( ctx )
		,	_parameter( parameter )
		{}
		
		virtual float evaluate() {
			_context->stateViewer()->addParameter( _parameter->evaluate() );
			_context->stateViewer()->executeHandlerForSymbol( string("-") );
			return 0;
		}
		
		virtual void print(std::ostream &os, unsigned int depth) const {
			os << indent(depth) << "- TurnRight" << std::endl;
			_parameter->print(os, depth+1);
		}		
		
	private:
		Context*	_context;
		ASTNode*		_parameter;
	};

	class ASTChangeColor : public ASTNode {
	public:
		explicit ASTChangeColor( Context* ctx, ASTNode* r, ASTNode* g, ASTNode* b, ASTNode* a )
		:	ASTNode()
		,	_context( ctx )
		,	_r( r )
		,	_g( g )
		,	_b( b )
		,	_a( a )
		{}
		
		virtual float evaluate() {
			_context->stateViewer()->addParameter( _r->evaluate() );
			_context->stateViewer()->addParameter( _g->evaluate() );
			_context->stateViewer()->addParameter( _b->evaluate() );
			_context->stateViewer()->addParameter( _a->evaluate() );
			_context->stateViewer()->executeHandlerForSymbol( string("C") );
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
		Context*	_context;
		ASTNode*		_r, *_g, *_b, *_a;
	};
	
	class ASTPushState : public ASTNode {
	public:
		explicit ASTPushState( Context* ctx )
		:	ASTNode()
		,	_context( ctx )
		{}
		
		virtual float evaluate() {
			_context->stateViewer()->executeHandlerForSymbol( string("[") );
			return 0;
		}
		
		virtual void print(std::ostream &os, unsigned int depth) const {
			os << indent(depth) << "[ PushState" << std::endl;
		}		
		
	private:
		Context*	_context;
	};

	class ASTPopState : public ASTNode {
	public:
		explicit ASTPopState( Context* ctx )
		:	ASTNode()
		,	_context( ctx )
		{}
		
		virtual float evaluate() {
			_context->stateViewer()->executeHandlerForSymbol( string("]") );
			return 0;
		}
		
		virtual void print(std::ostream &os, unsigned int depth) const {
			os << indent(depth) << "] PopState" << std::endl;
		}		
		
	private:
		Context*	_context;
	};
	
	
}
#endif // __ZLS_ABSTRACTSYNTAXTREE_H__
