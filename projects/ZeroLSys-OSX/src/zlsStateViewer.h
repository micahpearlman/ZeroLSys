/*
 *  zlsViewer.h
 *  ZeroLSys-OSX
 *
 *  Created by Micah Pearlman on 10/22/10.
 *  Copyright 2010 Zero Vision. All rights reserved.
 *
 */

#ifndef __ZLS_VIEWER_H__
#define __ZLS_VIEWER_H__

#include <string>

namespace ZeroLSys {
	
	using namespace std;
	
	class StateViewer {
	public:
		virtual void execute( const string& state ) = 0;
	};
	
	
}	
#endif // __ZLS_VIEWER_H__
