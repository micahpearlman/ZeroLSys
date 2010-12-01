/*
 *  zlsViewer.cpp
 *  ZeroLSys-OSX
 *
 *  Created by Micah Pearlman on 10/22/10.
 *  Copyright 2010 Zero Vision. All rights reserved.
 *
 */

#include "zlsStateViewer.h"

namespace ZLS {
	void StateViewer::setState( const string& s ) {
		_isDirty = true;
		_state = s;
		// remove white space
		_state.erase(std::remove_if(_state.begin(), _state.end(), std::isspace), _state.end());
	}
	
}