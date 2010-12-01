/*
 *  main.cpp
 *  ZeroLSys-OSX-Test
 *
 *  Created by Micah Pearlman on 10/20/10.
 *  Copyright 2010 Zero Vision. All rights reserved.
 *
 */

#include "main.h"
#include "../../src/zlsContext.h"
#include "../../src/zlsTurtleViewer.h"
#include "../../src/zlsParser.h"
using namespace ZeroLSys;

#include <stdlib.h>
#include <iostream>

#include <GLUT/glut.h>

struct RenderContext {
	VGfloat _scale;
	VGfloat _offset[2];
	bool	_isMouseDown;
	float	_mousePrevious[2];
	
	RenderContext()
	:	_scale(1.0f)
	,	_isMouseDown(false)
	{
		_offset[0] = _offset[1] = 0;
		
	}
};

static RenderContext gRenderContext;
static TurtleViewer viewer;
LSystemContext ctx;

void display(void) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	viewer.setOffset( gRenderContext._offset );
	viewer.setScale( gRenderContext._scale );
	viewer.draw();
    
    glutSwapBuffers();
}

void reshape(int width, int height) {
    glViewport(0, 0, width, height);
	vgResizeSurfaceSH( width, height );
}

void idle(void) {
    glutPostRedisplay();
}

void keyboard(unsigned char key, int x, int y) {
	
	
	switch (key) {
		case 's':
			gRenderContext._scale -= 0.1f;
			break;
		case 'S':
			gRenderContext._scale += 0.1f;
			break;
		case 'i':
			viewer.setState( ctx.iterate() );
			break;
		case 'r':
			ctx.reset();
			viewer.reset();
			break;

		default:
			break;
	}
}

void mouse_button(int button, int state, int x, int y) {
	if ( state == GLUT_DOWN ) {
		gRenderContext._isMouseDown = true;
		gRenderContext._mousePrevious[0] = x;
		gRenderContext._mousePrevious[1] = y;
	} else {
		gRenderContext._isMouseDown = false;
	}
}

void mouse_drag(int x, int y) {
	if ( gRenderContext._isMouseDown ) {
		float delta[2] = {
			x - gRenderContext._mousePrevious[0],
			y - gRenderContext._mousePrevious[1] 
		};
		
		gRenderContext._offset[0] += delta[0];
		gRenderContext._offset[1] += delta[1];
		
		gRenderContext._mousePrevious[0] = x;
		gRenderContext._mousePrevious[1] = y;
		
	}
	
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowSize(640, 480);
    
    glutCreateWindow("GLUT Program");
    
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutIdleFunc(idle);
	glutKeyboardFunc(keyboard);
	glutMouseFunc(mouse_button);
	glutMotionFunc(mouse_drag);
	
	// openvg init
	vgCreateContextSH( 640, 480 );
	
	// l system init
	ctx.initialize();
	ctx.setStartState( string("F") );
    ctx.addRule( string("F") >> string("F+F--F+F") );
	ctx.addRule( string("f") >> string("Ff") );
	
	ctx.reset();

	
//	stringstream ss;
//	ctx.write(ss);
//	
//	cout << ss.str() << endl;
//	
//	LSystemContext killme;
//	killme.initialize();
//	killme.read( ss );
	stringstream ss;
	ss << "F+F--F+F";
	Parser parser;
	parser.parse( ss );
	
	viewer.initialize();
	viewer.setRotateRadiansFromDegrees( 60.0f );
	viewer.setWidth( 1.0 );
	//viewer.execute( ctx.iterate() );
	//viewer.execute( string("FFF+FFF+FFF+FFF") );
	
    glutMainLoop();
	
	ctx.terminate();
	
    return EXIT_SUCCESS;
}
