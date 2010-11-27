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
#include <boost/shared_ptr.hpp>

namespace ZLS {
	
	using namespace boost;
	
	static inline VGfloat radians (VGfloat degrees) {return degrees * M_PI/180.0f;}	
	static inline VGfloat degrees (VGfloat radians) {return radians * 180.0f/M_PI;}
	
	class TurtleViewer : public StateViewer {
	public:
		
		TurtleViewer() 
		:	StateViewer()
		,	_scale(1)
		{
			_offset[0] = _offset[1] = 0;
			//reset();
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
		
				
		// draw modifiers
		VGfloat		_offset[2];
		VGfloat		_scale;
		
		struct TurtleState {
			
			typedef shared_ptr<TurtleState>	SmartPtr;
			static TurtleState::SmartPtr create() {
				return TurtleState::SmartPtr( new TurtleState() );
			}
			TurtleState() 
			:	_stepLength(10)
			,	_rotateRadians( radians(33) )
			,	_orientation(0)
			,	_width(1.0)
			,	_path(VG_INVALID_HANDLE)
			,	_paint(VG_INVALID_HANDLE)
			{
				_position[0] = _position[1] = 100;
				_color[0] = _color[1] = _color[2] = _color[3] = 1.0f;
				_color[0] = 1.0f;
				
				// setup openvg
				_paint = vgCreatePaint();
				vgSetParameterfv(_paint, VG_PAINT_COLOR, 4, &_color[0] );
				_path = vgCreatePath(VG_PATH_FORMAT_STANDARD, VG_PATH_DATATYPE_F,1,0,0,0, VG_PATH_CAPABILITY_ALL);
				
				static const VGubyte segments[1] = { VG_MOVE_TO | VG_ABSOLUTE };
				vgAppendPathData( _path, 1, segments, _position );
				
				
			}
			
			virtual ~TurtleState() {
				vgDestroyPath( _path );
				_path = VG_INVALID_HANDLE;
				vgDestroyPaint( _paint );
				_paint = VG_INVALID_HANDLE;
			}
			
			void copy( const TurtleState& other ) 
			{
				_orientation = other._orientation;
				_stepLength = other._stepLength;
				_rotateRadians = other._rotateRadians;
				_width = other._width;
				
				_position[0] = other._position[0];
				_position[1] = other._position[1];
				
				_color[0] = other._color[0];
				_color[1] = other._color[1];
				_color[2] = other._color[2];
				_color[3] = other._color[3];
				
				static const VGubyte segments[1] = { VG_MOVE_TO | VG_ABSOLUTE };
				vgAppendPathData( _path, 1, segments, _position );
				
				vgSetParameterfv( _paint, VG_PAINT_COLOR, 4, &_color[0] );
				
			}
			
			
			VGfloat		_position[2];
			VGfloat		_orientation;
			
			VGfloat		_stepLength;
			VGfloat		_rotateRadians;
			VGfloat		_width;
			
			VGfloat		_color[4];
			
			VGPaint		_paint;
			VGPath		_path;
			
			
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
			
			void draw() {
				if ( _path == VG_INVALID_HANDLE ) {
					return;
				}
				
				vgSetf( VG_STROKE_LINE_WIDTH, _width );
				
				
				vgSetPaint( _paint, VG_STROKE_PATH );
				vgDrawPath( _path, VG_STROKE_PATH );
				
			}
		};
		
		vector<TurtleState::SmartPtr>		_turtleStateStack;
		vector<TurtleState::SmartPtr>		_turtleStateDrawables;
		
		TurtleState& currentTurtleState() {
			return *_turtleStateStack.back();
		}
		
		void pushTurtleState() {
			TurtleState::SmartPtr new_state = TurtleState::create();
			new_state->copy( currentTurtleState() );
			_turtleStateStack.push_back( new_state );
			_turtleStateDrawables.push_back( new_state );
			
		}
		void popTurtleState() {
			_turtleStateStack.pop_back();
		}

		void parseParameters( string::iterator& c );
		
	};
}

#endif // __TURTLE_VIEWER_H__

