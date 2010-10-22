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

namespace ZeroLSys {
	
	class TurtleViewer : public StateViewer {
	public:
		
		virtual void execute( const string& state );
	};
}

#endif // __TURTLE_VIEWER_H__

