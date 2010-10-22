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
		
		// setup openvg
		_paint = vgCreatePaint();
//		vgSetPaint(_paint, VG_STROKE_PATH );
		
		VGfloat color[4] = { 1.0f, 0.0f, 0.0f, 1.0f };
		vgSetParameterfv(_paint, VG_PAINT_COLOR, 4, &color[0]);
		
		_path = vgCreatePath(VG_PATH_FORMAT_STANDARD, VG_PATH_DATATYPE_F,1,0,0,0, VG_PATH_CAPABILITY_ALL);
		
	}
	
	void TurtleViewer::terminate( ) {
		
	}
	
	void TurtleViewer::execute( const string& state ) {
		StateViewer::SymbolHandler handler = _symbolHandlers[string("F")];
		(this->*handler)();
	}
	
	// F
	void TurtleViewer::DrawForward() {
		cout << "DrawForward" << endl;
	}
	
	// f
	void TurtleViewer::MoveForward() {
		
	}
	
	// +
	void TurtleViewer::TurnLeft() {
		
	}		
	
	// -
	void TurtleViewer::TurnRight() {
		
	}		

	
	
}	// namespace ZeroLSys