/*
 *  turtle_viewer.h
 *  ZeroLSys-OSX
 *
 *  Created by Micah Pearlman on 10/21/10.
 *  Copyright 2010 Zero Vision. All rights reserved.
 *
 */

#ifndef __TURTLE_VIEWER_H__
#define __TURTLE_VIEWER_H__

#include "zlsStateViewer.h"
#include <VG/openvg.h>
#include <VG/vgu.h>

namespace ZeroLSys {
	
	class TurtleViewer : public StateViewer {
	public:
		
		virtual void initialize();
		virtual void terminate();
		
		virtual void execute( const string& state );
		
	private:
		
		void DrawForward();		// F
		void MoveForward();		// f
		
	private:
		VGPath		_path;
		VGPaint		_paint;
		
		VGfloat		_position;
		VGfloat		_orientation;
	};
}

#endif // __TURTLE_VIEWER_H__

