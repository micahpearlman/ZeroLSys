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

- (StateViewer*) stateViewer {
	return (StateViewer*)_turtleViewer;
}

- (id)initWithCoder:(NSCoder *)aDecoder {
	if( self = [super initWithCoder:aDecoder] ) {
		_turtleViewer = new TurtleViewer();
		_turtleViewer->initialize();
		_turtleViewer->setRotateRadiansFromDegrees( 60.0f );
		_turtleViewer->setWidth( 1.0f );
	}
	return self;
}
- (id)initWithFrame:(NSRect)frame {
    self = [super initWithFrame:frame];
    if (self) {

    }
    return self;
}


// This is the renderer output callback function
static CVReturn MyDisplayLinkCallback(CVDisplayLinkRef displayLink, const CVTimeStamp* now, const CVTimeStamp* outputTime, CVOptionFlags flagsIn, CVOptionFlags* flagsOut, void* displayLinkContext) {
    CVReturn result = [(OpenVGView*)displayLinkContext getFrameForTime:outputTime];
    return result;
}



- (void)prepareOpenGL {
	
//    glShadeModel(GL_SMOOTH);
//    glEnable(GL_NORMALIZE);
//    glEnable(GL_DEPTH_TEST);
//    glEnable(GL_COLOR_MATERIAL);
//    glEnable(GL_LIGHTING);
//    glEnable(GL_LIGHT0);
//    glClearColor(0.2f, 0.1f, 0.1f, 0.0f);
//    GLfloat light_diffuse[] = { 1, 1, 1, 1 };
//    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
//    GLfloat light_position[] = { 0, 0, 5, 1 };
//    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	
	// openvg init
	// openvg init
	vgCreateContextSH( self.bounds.size.width, self.bounds.size.height );
	
	
    // Synchronize buffer swaps with vertical refresh rate
    GLint swapInt = 0;
    [[self openGLContext] setValues:&swapInt forParameter:NSOpenGLCPSwapInterval]; 
	
    // Create a display link capable of being used with all active displays
    CVDisplayLinkCreateWithActiveCGDisplays(&_displayLink);
	
    // Set the renderer output callback function
    CVDisplayLinkSetOutputCallback(_displayLink, &MyDisplayLinkCallback, self);
	
    // Set the display link for the current renderer
    CGLContextObj cglContext = (CGLContextObj)[[self openGLContext] CGLContextObj];
    CGLPixelFormatObj cglPixelFormat = (CGLPixelFormatObj)[[self pixelFormat] CGLPixelFormatObj];
    CVDisplayLinkSetCurrentCGDisplayFromOpenGLContext(_displayLink, cglContext, cglPixelFormat);
	
    // Activate the display link
    CVDisplayLinkStart(_displayLink);
	
}

- (CVReturn)getFrameForTime:(const CVTimeStamp*)outputTime {
    // Add your drawing codes here
	[self setNeedsDisplay:YES];
    return kCVReturnSuccess;
}

- (void)reshape {
    const NSSize size = self.bounds.size;
	vgResizeSurfaceSH( size.width, size.height );
//    glViewport(0,0,size.width,size.height);
//    glMatrixMode(GL_PROJECTION);
//    glLoadIdentity();
//    gluPerspective(45.0f,size.width/size.height,0.1f,100.0f);
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

- (void)dealloc {
    // Release the display link
    CVDisplayLinkRelease(_displayLink);
	_turtleViewer->terminate();
	delete _turtleViewer;
	
    [super dealloc];
}

@end
