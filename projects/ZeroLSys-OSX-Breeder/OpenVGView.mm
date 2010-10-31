//
//  OpenVGView.mm
//  ZeroLSys-OSX-Breeder
//
//  Created by Micah Pearlman on 10/27/10.
//  Copyright 2010 Zero Vision. All rights reserved.
//

#import "OpenVGView.h"
#include <GLUT/glut.h>
#import <OpenGL/OpenGL.h>

@interface OpenVGView (Private)
- (CVReturn)getFrameForTime:(const CVTimeStamp*)outputTime;
@end


@implementation OpenVGView

@dynamic stateViewer;

static CVReturn MyDisplayLinkCallback(CVDisplayLinkRef displayLink, const CVTimeStamp* now, const CVTimeStamp* outputTime, CVOptionFlags flagsIn, CVOptionFlags* flagsOut, void* displayLinkContext);

- (StateViewer*) stateViewer {
	return (StateViewer*)_turtleViewer;
}

- (id)initWithCoder:(NSCoder *)aDecoder {
	if( self = [super initWithCoder:aDecoder] ) {
		_turtleViewer = new TurtleViewer();
		_turtleViewer->initialize();
		_turtleViewer->setRotateRadiansFromDegrees( 60.0f );
		_turtleViewer->setWidth( 1.0f );
		_scale = 1.0f;
		_offset[0] = _offset[1] = 0;
		
		// Synchronize buffer swaps with vertical refresh rate
		GLint swapInt = 1;
		[[self openGLContext] setValues:&swapInt forParameter:NSOpenGLCPSwapInterval]; 
		
		// Create a display link capable of being used with all active displays
		CVDisplayLinkCreateWithActiveCGDisplays(&_displayLink);
		
		// Set the renderer output callback function
		CVDisplayLinkSetOutputCallback(_displayLink, &MyDisplayLinkCallback, self);
		
		// Set the display link for the current renderer
		CGLContextObj cglContext = (CGLContextObj)[[self openGLContext] CGLContextObj];
		CGLPixelFormatObj cglPixelFormat = (CGLPixelFormatObj)[[self pixelFormat] CGLPixelFormatObj];
		CVDisplayLinkSetCurrentCGDisplayFromOpenGLContext(_displayLink, cglContext, cglPixelFormat);
		
	}
	return self;
}

#pragma mark -
#pragma mark Display Link

// This is the renderer output callback function
static CVReturn MyDisplayLinkCallback(CVDisplayLinkRef displayLink, const CVTimeStamp* now, const CVTimeStamp* outputTime, CVOptionFlags flagsIn, CVOptionFlags* flagsOut, void* displayLinkContext) {
    CVReturn result = [(OpenVGView*)displayLinkContext getFrameForTime:outputTime];
    return result;
}

- (CVReturn)getFrameForTime:(const CVTimeStamp*)outputTime {
    // Add your drawing codes here
	//[self setNeedsDisplay:YES];
	[[self openGLContext] makeCurrentContext];
	NSOpenGLContext	*currentContext = [self openGLContext];
	// must lock GL context because display link is threaded
	CGLLockContext((CGLContextObj)[currentContext CGLContextObj]);

	
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	//	viewer.setOffset( gRenderContext._offset );
	//	viewer.setScale( gRenderContext._scale );
	_turtleViewer->setOffset( _offset );
	_turtleViewer->setScale( _scale );
	_turtleViewer->draw();
    [[self openGLContext] flushBuffer];
	
	CGLUnlockContext((CGLContextObj)[currentContext CGLContextObj]);
	
    return kCVReturnSuccess;
}


- (void)prepareOpenGL {
	NSOpenGLContext	*currentContext = [self openGLContext];
	// must lock GL context because display link is threaded
	CGLLockContext((CGLContextObj)[currentContext CGLContextObj]);
	
	// openvg init
	vgCreateContextSH( self.bounds.size.width, self.bounds.size.height );

    // Activate the display link
    CVDisplayLinkStart(_displayLink);
	
	CGLUnlockContext((CGLContextObj)[currentContext CGLContextObj]);
}


- (void)reshape {
	NSOpenGLContext	*currentContext = [self openGLContext];
	// must lock GL context because display link is threaded
	CGLLockContext((CGLContextObj)[currentContext CGLContextObj]);
	
    const NSSize size = self.bounds.size;
	vgResizeSurfaceSH( size.width, size.height );
	
	CGLUnlockContext((CGLContextObj)[currentContext CGLContextObj]);
}

//- (void)drawRect:(NSRect)rect {
//    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//	
//    [[self openGLContext] flushBuffer];
//}

#pragma mark -
#pragma mark Event Handling

- (void)magnifyWithEvent:(NSEvent *)event {
	_scale *= (1.0f + [event magnification]);
}

- (void) mouseDown:(NSEvent *) theEvent { 
	NSPoint where = [self convertPoint:[theEvent locationInWindow] fromView:nil];
	_previousMouse = where;
	
	[self mouseDragged:theEvent]; 
}
- (void) mouseDragged:(NSEvent *)theEvent {
	NSPoint where = [self convertPoint:[theEvent locationInWindow] fromView:nil];
  	
	float delta[2] = {
		where.x - _previousMouse.x,
		where.y - _previousMouse.y 
	};
	
	_offset[0] += delta[0];
	_offset[1] += -delta[1];
	
	_previousMouse = where;
}



- (void)dealloc {
    // Release the display link
    CVDisplayLinkRelease(_displayLink);
	_turtleViewer->terminate();
	delete _turtleViewer;
	
    [super dealloc];
}

@end
