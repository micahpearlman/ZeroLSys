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

namespace ZeroLSys {
	
	void TurtleViewer::initialize( ) {
		
		// add the symbol handlers
		addSymbolHandlerForSymbol( string("F"), (StateViewer::SymbolHandler)&TurtleViewer::DrawForward );
		addSymbolHandlerForSymbol( string("f"), (StateViewer::SymbolHandler)&TurtleViewer::MoveForward );
		addSymbolHandlerForSymbol( string("+"), (StateViewer::SymbolHandler)&TurtleViewer::TurnLeft );
		addSymbolHandlerForSymbol( string("-"), (StateViewer::SymbolHandler)&TurtleViewer::TurnRight );
		
		// setup openvg
		_paint = vgCreatePaint();
//		vgSetPaint(_paint, VG_STROKE_PATH );
		
		VGfloat color[4] = { 1.0f, 0.0f, 0.0f, 1.0f };
		vgSetParameterfv(_paint, VG_PAINT_COLOR, 4, &color[0]);
		
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
		_turtleState._position[0] = _turtleState._position[1] = 0;
		MoveForward();	// set the initial position
	}
	
	
	void TurtleViewer::draw() {
		
		if ( _isDirty && _state.length() > 0 ) {
			vgClearPath( _path, VG_PATH_CAPABILITY_ALL );
			MoveForward();	// set the initial position
			
			for ( string::const_iterator c = _state.begin(); c != _state.end(); c++ ) {
				StateViewer::SymbolHandler handler = _symbolHandlers[string(1, *c)];
				(this->*handler)();
			}

			_isDirty = false;
		}
		
		if ( _path == VG_INVALID_HANDLE ) {
			return;
		}
		
		vgSetf( VG_STROKE_LINE_WIDTH, _width );
		
		vgSeti(VG_MATRIX_MODE, VG_MATRIX_PATH_USER_TO_SURFACE);
		vgLoadIdentity();
		vgTranslate(_offset[0], _offset[1]);
		vgScale( _scale, _scale );
		
		vgSetPaint(_paint, VG_STROKE_PATH );
		vgDrawPath( _path, VG_STROKE_PATH );
		
	}
	
	// F
	void TurtleViewer::DrawForward() {
		cout << "DrawForward" << endl;
		
		_turtleState._position[0] = _turtleState._position[0] + _stepLength * cosf( _turtleState._orientation );
		_turtleState._position[1] = _turtleState._position[1] + _stepLength * sinf( _turtleState._orientation );
		
		static const VGubyte segments[1] = { VG_LINE_TO | VG_ABSOLUTE };
		vgAppendPathData( _path, 1, segments, _turtleState._position );
	}
	
	// f
	void TurtleViewer::MoveForward() {
		
		cout << "DrawForward" << endl;
		_turtleState._position[0] = _turtleState._position[0] + _stepLength * cosf( _turtleState._orientation );
		_turtleState._position[1] = _turtleState._position[1] + _stepLength * sinf( _turtleState._orientation );
		
		static const VGubyte segments[1] = { VG_MOVE_TO | VG_ABSOLUTE };
		vgAppendPathData( _path, 1, segments, _turtleState._position );
		
	}
	
	// +
	void TurtleViewer::TurnLeft() {
		_turtleState._orientation += _rotateRadians;
	}		
	
	// -
	void TurtleViewer::TurnRight() {
		_turtleState._orientation -= _rotateRadians;
	}		

	
	
}	// namespace ZeroLSys