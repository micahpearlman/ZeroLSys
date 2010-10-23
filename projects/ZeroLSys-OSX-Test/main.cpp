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
using namespace ZeroLSys;

#include <stdlib.h>
#include <iostream>

#include <GLUT/glut.h>

TurtleViewer viewer;

void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	viewer.draw();
    
    glutSwapBuffers();
}

void reshape(int width, int height)
{
    glViewport(0, 0, width, height);
}

void idle(void)
{
    glutPostRedisplay();
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowSize(640, 480);
    
    glutCreateWindow("GLUT Program");
    
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutIdleFunc(idle);
	
	// openvg init
	vgCreateContextSH( 640, 480 );
	
	// l system init
	LSystemContext& ctx = LSystemContext::singleton();
	ctx.initialize();
	ctx.setStartState( string("F") );
    ctx.addRule( string("F") >> string("F+F--F+F") );
	//ctx.addRule( string("f") >> string("Ff") );
	
	ctx.reset();
	
	cout << ctx.iterate() << endl;
	cout << ctx.iterate() << endl;
	cout << ctx.iterate() << endl;
	cout << ctx.iterate() << endl;
	cout << ctx.iterate() << endl;
	
	
	viewer.initialize();
	viewer.setRotateRadiansFromDegrees( 60.0f );
	viewer.setWidth( 1.0 );
	viewer.execute( ctx.iterate() );
	//viewer.execute( string("FFF+FFF+FFF+FFF") );
	
    glutMainLoop();
	
	ctx.terminate();
	
    return EXIT_SUCCESS;
}
