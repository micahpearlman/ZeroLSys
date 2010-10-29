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
		,	_stepLength(10)
		,	_rotateRadians( radians(33) )
		,	_scale(1)
		,	_path(VG_INVALID_HANDLE)
		,	_paint(VG_INVALID_HANDLE)
		{
			_offset[0] = _offset[1] = 0;
		}
		
		virtual ~TurtleViewer();
		
		virtual void initialize();
		virtual void terminate();
		virtual void reset();
		//virtual void execute( const string& state );
		
		virtual void draw();
		
		VGfloat stepLength() const {
			return _stepLength;
		}
		void setStepLength( VGfloat sl ) {
			_stepLength = sl;
		}
		
		VGfloat rotateRadians() const {
			return _rotateRadians;
		}
		void setRotateRadians( VGfloat r ) {
			_rotateRadians = r;
		}
		void setRotateRadiansFromDegrees( VGfloat d ) {
			setRotateRadians( radians( d ) );
		}
		
		VGfloat width() const {
			return _width;
		}
		void setWidth( VGfloat w ) {
			_width = w;
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
			ss << _turtleState.description();
			return ss.str();
		}
		
	private:	// symbol handlers
		
		void DrawForward();		// F
		void MoveForward();		// f
		void TurnLeft();		// +
		void TurnRight();		// -
		
	private:	// drawing state
		
		
		VGPath		_path;
		VGPaint		_paint;
		VGfloat		_stepLength;
		VGfloat		_rotateRadians;
		VGfloat		_width;
		
		// draw modifiers
		VGfloat		_offset[2];
		VGfloat		_scale;
		
		struct TurtleState {
			TurtleState() {
				_position[0] = _position[1] = 100;
				_orientation = 0;
			}
			VGfloat		_position[2];
			VGfloat		_orientation;
			
			string description() {
				stringstream ss;
				ss	<< "state: \n"
					<<		"\tposition: " << _position[0] << ", " << _position[1] << "\n"
					<<		"\torientation: " << degrees(_orientation) << "\n";
				return ss.str();
			}
		};
		
		TurtleState		_turtleState;
		
	};
}

#endif // __TURTLE_VIEWER_H__

