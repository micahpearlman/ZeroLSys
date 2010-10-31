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
#include <cmath>
#include <sstream>
#include <VG/openvg.h>
#include <VG/vgu.h>

namespace ZeroLSys {
	
	static inline VGfloat radians (VGfloat degrees) {return degrees * M_PI/180.0f;}	
	static inline VGfloat degrees (VGfloat radians) {return radians * 180.0f/M_PI;}
	
	class TurtleViewer : public StateViewer {
	public:
		
		TurtleViewer() 
		:	StateViewer()
		,	_scale(1)
		,	_path(VG_INVALID_HANDLE)
		,	_paint(VG_INVALID_HANDLE)
		{
			_offset[0] = _offset[1] = 0;
			
			_turtleStateStack.push_back( TurtleState() );
		}
		
		virtual ~TurtleViewer();
		
		virtual void initialize();
		virtual void terminate();
		virtual void reset();
		//virtual void execute( const string& state );
		
		virtual void draw();
		
		VGfloat stepLength() {
			return currentTurtleState()._stepLength;
		}
		void setStepLength( VGfloat sl ) {
			currentTurtleState()._stepLength = sl;
		}
		
		VGfloat rotateRadians() {
			return currentTurtleState()._rotateRadians;
		}
		void setRotateRadians( VGfloat r ) {
			currentTurtleState()._rotateRadians = r;
		}
		void setRotateRadiansFromDegrees( VGfloat d ) {
			setRotateRadians( radians( d ) );
		}
		
		VGfloat width() {
			return currentTurtleState()._width;
		}
		void setWidth( VGfloat w ) {
			currentTurtleState()._width = w;
		}
		
		void setOffset( VGfloat* o ) {
			_offset[0] = o[0];
			_offset[1] = o[1];
		}
		
		VGfloat scale() const {
			return _scale;
		}
		void setScale( VGfloat s ) {
			_scale = s;
		}
		
		
		string description() {
			stringstream ss;
			ss << "TurtleViewer: \n";
			ss << currentTurtleState().description();
			return ss.str();
		}
		
		
		
	private:	// symbol handlers
		
		void DrawForward();		// F
		void MoveForward();		// f
		void TurnLeft();		// +
		void TurnRight();		// -
		void ChangeColor();		// C
		void PushState();		// [
		void PopState();		// ]
		
	private:	// drawing state
		
		
		VGPath		_path;
		VGPaint		_paint;
		
		// draw modifiers
		VGfloat		_offset[2];
		VGfloat		_scale;
		
		struct TurtleState {
			TurtleState() 
			:	_stepLength(10)
			,	_rotateRadians( radians(33) )
			,	_orientation(0) 
			{
				_position[0] = _position[1] = 100;
				_color[0] = _color[1] = _color[2] = _color[3] = 1.0f;
			}
			
			VGfloat		_position[2];
			VGfloat		_orientation;
			
			VGfloat		_stepLength;
			VGfloat		_rotateRadians;
			VGfloat		_width;
			
			VGfloat		_color[4];
			
			
			string description() {
				stringstream ss;
				ss	<< "state: \n"
					<<		"\tposition: " << _position[0] << ", " << _position[1] << "\n"
					<<		"\torientation: " << degrees(_orientation) << "\n"
					<<		"\tstepLength: " << _stepLength << "\n"
					<<		"\trotateDegrees: " << degrees(_rotateRadians) << "\n"
					<<		"\twidth: "	<< _width << "\n"
					<<		"\tcolor: " << _color[0] << ", " << _color[1] << ", " << _color[2] << ", " << _color[3] << "\n";
				return ss.str();
			}
		};
		
		vector<TurtleState>		_turtleStateStack;
		
		TurtleState& currentTurtleState() {
			return _turtleStateStack.back();
		}
		
		void pushTurtleState() {
			_turtleStateStack.push_back( currentTurtleState() );
		}
		void popTurtleState() {
			_turtleStateStack.pop_back();
		}

		void parseParameters( string::iterator& c );
		
	};
}

#endif // __TURTLE_VIEWER_H__

