//
//  OpenVGView.h
//  ZeroLSys-OSX-Breeder
//
//  Created by Micah Pearlman on 10/27/10.
//  Copyright 2010 Zero Vision. All rights reserved.
//

#import <Cocoa/Cocoa.h>
#import <CoreVideo/CoreVideo.h>
#import <QuartzCore/QuartzCore.h>
#import "../../src/zlsTurtleViewer.h"

using namespace ZeroLSys;

@interface OpenVGView : NSOpenGLView {
@private
	CVDisplayLinkRef _displayLink; //display link for managing rendering thread
	
@private
	TurtleViewer*		_turtleViewer;
	float				_scale;
	float				_offset[2];
	
@private
	NSPoint				_previousMouse;
}

@property (readonly) TurtleViewer* stateViewer;


@end
