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
- (id)initWithFrame:(NSRect)frame {
    self = [super initWithFrame:frame];
    if (self) {

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
	_turtleViewer->draw();
    [[self openGLContext] flushBuffer];
	
	CGLUnlockContext((CGLContextObj)[currentContext CGLContextObj]);
	
    return kCVReturnSuccess;
}

- (void) awakeFromNib {
//    // Activate the display link
//    CVDisplayLinkStart(_displayLink);
}

- (void)prepareOpenGL {
	NSOpenGLContext	*currentContext = [self openGLContext];
	// must lock GL context because display link is threaded
	CGLLockContext((CGLContextObj)[currentContext CGLContextObj]);
	
	// openvg init
	vgCreateContextSH( self.bounds.size.width, self.bounds.size.height );
	
	CGLUnlockContext((CGLContextObj)[currentContext CGLContextObj]);
	
    // Activate the display link
    CVDisplayLinkStart(_displayLink);
	
}


- (void)reshape {
	NSOpenGLContext	*currentContext = [self openGLContext];
	// must lock GL context because display link is threaded
	CGLLockContext((CGLContextObj)[currentContext CGLContextObj]);
	
    const NSSize size = self.bounds.size;
	vgResizeSurfaceSH( size.width, size.height );
	
	CGLUnlockContext((CGLContextObj)[currentContext CGLContextObj]);
}

- (void)drawRect:(NSRect)rect {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
//	viewer.setOffset( gRenderContext._offset );
//	viewer.setScale( gRenderContext._scale );
	_turtleViewer->draw();
	
//    glMatrixMode(GL_MODELVIEW);
//    glLoadIdentity();
//    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//    glTranslatef(0.0f,0.0f,-6);
//    glRotatef(20,0,0,1);
//    glRotatef(20,1,0,0);
//    glColor3f(1,0,0);
//    glutSolidCube(2);
    [[self openGLContext] flushBuffer];
}

#pragma mark -
#pragma mark Event Handling
-(void)magnifyWithEvent:(NSEvent *)event {
	NSLog(@"magnification = %f", [event magnification] );
}

- (void)dealloc {
    // Release the display link
    CVDisplayLinkRelease(_displayLink);
	_turtleViewer->terminate();
	delete _turtleViewer;
	
    [super dealloc];
}

@end
