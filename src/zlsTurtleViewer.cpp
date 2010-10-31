/*
 *  turtle_viewer.cpp
 *  ZeroLSys-OSX
 *
 *  Created by Micah Pearlman on 10/21/10.
 *  Copyright 2010 Zero Vision. All rights reserved.
 *
 */

#include "zlsTurtleViewer.h"
#include <iostream>
#include <algorithm>
#include <boost/foreach.hpp>
#include <boost/tokenizer.hpp>
#include <boost/lexical_cast.hpp>

using namespace boost;

namespace ZeroLSys {
	
	void TurtleViewer::initialize( ) {
		
		// add the symbol handlers
		addSymbolHandlerForSymbol( string("F"), (StateViewer::SymbolHandler)&TurtleViewer::DrawForward );
		addSymbolHandlerForSymbol( string("f"), (StateViewer::SymbolHandler)&TurtleViewer::MoveForward );
		addSymbolHandlerForSymbol( string("+"), (StateViewer::SymbolHandler)&TurtleViewer::TurnLeft );
		addSymbolHandlerForSymbol( string("-"), (StateViewer::SymbolHandler)&TurtleViewer::TurnRight );
		addSymbolHandlerForSymbol( string("C"), (StateViewer::SymbolHandler)&TurtleViewer::ChangeColor );
		addSymbolHandlerForSymbol( string("["), (StateViewer::SymbolHandler)&TurtleViewer::PushState );
		addSymbolHandlerForSymbol( string("]"), (StateViewer::SymbolHandler)&TurtleViewer::PopState );
		
		// setup openvg
		_paint = vgCreatePaint();
		VGfloat c[4] = {
			1,1,1,1
		};
		vgSetParameterfv(_paint, VG_PAINT_COLOR, 4, &c[0] );
		
		_path = vgCreatePath(VG_PATH_FORMAT_STANDARD, VG_PATH_DATATYPE_F,1,0,0,0, VG_PATH_CAPABILITY_ALL);
	}
	
	void TurtleViewer::terminate( ) {
		vgDestroyPath( _path );
		_path = VG_INVALID_HANDLE;
		vgDestroyPaint( _paint );
		_paint = VG_INVALID_HANDLE;
	}
	
	TurtleViewer::~TurtleViewer() {
		terminate();
	}	
	
	void TurtleViewer::reset() {
		vgClearPath( _path, VG_PATH_CAPABILITY_ALL );
		currentTurtleState()._position[0] = currentTurtleState()._position[1] = 0;
		MoveForward();	// set the initial position
	}
	
	
	void TurtleViewer::parseParameters( string::iterator& c ) {
		_currentParameters.clear();
		// get parameters if they are there
		if ( *(c+1) == '(' ) {		// NOTE:  assumes that whitespace has been removed...
			c++;
			size_t cur_pos = distance( _state.begin(), c );
			size_t close_pos = _state.find_first_of(")", cur_pos);
			if ( close_pos != string::npos ) {
				string parameter_string( c+1, _state.begin() +  close_pos );
				char_separator<char> sep(",");
				tokenizer< char_separator<char> > tokens(parameter_string, sep);
				BOOST_FOREACH(string t, tokens) {
					_currentParameters.push_back( lexical_cast<float>( t ) );
				}
				
				// reset the iterator past the parameters
				c = _state.begin() + close_pos;
			}
		}
		
	}
	
	void TurtleViewer::draw() {
		
		if ( _isDirty && _state.length() > 0 ) {
			vgClearPath( _path, VG_PATH_CAPABILITY_ALL );
			MoveForward();	// set the initial position
			
			for ( string::iterator c = _state.begin(); c != _state.end(); c++ ) {
				
				const char k = *c;
				
				parseParameters( c );
				StateViewer::SymbolHandler handler = handlerForSymbol( string(1,k) );
				if ( handler ) {
					(this->*handler)();
				}
				
			}
			
			_isDirty = false;
		}
		
		if ( _path == VG_INVALID_HANDLE ) {
			return;
		}
		
		vgSetf( VG_STROKE_LINE_WIDTH, currentTurtleState()._width );
		
		vgSeti(VG_MATRIX_MODE, VG_MATRIX_PATH_USER_TO_SURFACE);
		vgLoadIdentity();
		vgTranslate(_offset[0], _offset[1]);
		vgScale( _scale, _scale );
		
		vgSetPaint(_paint, VG_STROKE_PATH );
		vgDrawPath( _path, VG_STROKE_PATH );
		
	}
	
	// F
	void TurtleViewer::DrawForward() {
		
		if ( _currentParameters.empty() == false ) {
			setStepLength( nextParameter() );
		}
		
		currentTurtleState()._position[0] = currentTurtleState()._position[0] + currentTurtleState()._stepLength * cosf( currentTurtleState()._orientation );
		currentTurtleState()._position[1] = currentTurtleState()._position[1] + currentTurtleState()._stepLength * sinf( currentTurtleState()._orientation );
		
		static const VGubyte segments[1] = { VG_LINE_TO | VG_ABSOLUTE };
		vgAppendPathData( _path, 1, segments, currentTurtleState()._position );
	}
	
	// f
	void TurtleViewer::MoveForward() {
		
		if ( _currentParameters.empty() == false ) {
			setStepLength( nextParameter() );
		}
		
		currentTurtleState()._position[0] = currentTurtleState()._position[0] + currentTurtleState()._stepLength * cosf( currentTurtleState()._orientation );
		currentTurtleState()._position[1] = currentTurtleState()._position[1] + currentTurtleState()._stepLength * sinf( currentTurtleState()._orientation );
		
		static const VGubyte segments[1] = { VG_MOVE_TO | VG_ABSOLUTE };
		vgAppendPathData( _path, 1, segments, currentTurtleState()._position );
		
	}
	
	// +
	void TurtleViewer::TurnLeft() {
		if ( _currentParameters.empty() == false ) {
			setRotateRadiansFromDegrees( nextParameter() );
		}
		
		//cout << "TurnLeft: " << currentTurtleState()._rotateRadians << endl;
		
		currentTurtleState()._orientation += currentTurtleState()._rotateRadians;
	}		
	
	// -
	void TurtleViewer::TurnRight() {
		
		if ( _currentParameters.empty() == false ) {
			setRotateRadiansFromDegrees( nextParameter() );
		}
		
		//cout << "TurnRight: " << currentTurtleState()._rotateRadians << endl;

		currentTurtleState()._orientation -= currentTurtleState()._rotateRadians;
	}	
	
	// C
	void TurtleViewer::ChangeColor() { 
		if ( _currentParameters.empty() == false ) {
			currentTurtleState()._color[0] = nextParameter();
			currentTurtleState()._color[1] = nextParameter();		
			currentTurtleState()._color[2] = nextParameter();
			currentTurtleState()._color[3] = nextParameter();			
		}
		
		cout << currentTurtleState().description() << endl;
		
		vgSetParameterfv(_paint, VG_PAINT_COLOR, 4, &currentTurtleState()._color[0] );
	}
	
	// [
	void TurtleViewer::PushState() {
		pushTurtleState();
	}	
	// ]
	void TurtleViewer::PopState() {
		popTurtleState();
	}		



	
	
}	// namespace ZeroLSys