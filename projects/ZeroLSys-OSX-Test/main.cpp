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

void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
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
	
	// l system init
	LSystemContext& ctx = LSystemContext::singleton();
	ctx.initialize();
	
    ctx.addRule( string("F") >> string("f") );
	ctx.addRule( string("f") >> string("Ff") );
	ctx.setStartState( string("F") );
	ctx.reset();
	
	cout << ctx.iterate() << endl;
	cout << ctx.iterate() << endl;
	cout << ctx.iterate() << endl;
	cout << ctx.iterate() << endl;
	cout << ctx.iterate() << endl;
	
	
	TurtleViewer viewer;
	viewer.initialize();
	viewer.execute( ctx.iterate() );
	
    glutMainLoop();
	
	ctx.terminate();
	
    return EXIT_SUCCESS;
}
