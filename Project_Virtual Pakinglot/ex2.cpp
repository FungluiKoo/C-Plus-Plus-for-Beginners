#include "Group.h"
#include <iostream>
#include <cmath>
#include <ctime>

void TimeStep(int n) {
	glutTimerFunc(10, TimeStep, 0); glutPostRedisplay();
}

void glDraw() {
	Total static ICP(1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	ICP.draw();
	ICP.script();
	glutSwapBuffers();
	glFlush();
}

void ex2(int argc, char * argv[]) {
	srand((unsigned)time(nullptr));
	glutInit(&argc, argv);
	glutInitWindowSize(500,500);
	glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
	glutCreateWindow("Interstellar car park");
	glClearColor(1,1,1,0);
	glClear(GL_COLOR_BUFFER_BIT);
	glutDisplayFunc(glDraw);
	glutTimerFunc(10, TimeStep, 0);
	glutMainLoop();
}
