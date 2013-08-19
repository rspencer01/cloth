#pragma comment(lib,"glew32.lib")

#include <GL/glut.h>
#include <math.h>
#include <algorithm>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>


void display(void);
void reshape(int,int);

int main(int argc, char**argv)
{
	srand(0);
	
	glutInit(&argc,argv);
	
	glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGBA|GLUT_DEPTH);
	glutInitWindowSize(500,500);
	glutInitWindowPosition(100,100);
	glutCreateWindow("Terrain");
	


	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

	glEnable ( GL_COLOR_MATERIAL ) ;
	glEnable( GL_TEXTURE_2D );
	glEnable( GL_BLEND );
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	
    glAlphaFunc ( GL_GREATER, (GLclampf)0.1 ) ;
    glEnable ( GL_ALPHA_TEST ) ;
	
	glShadeModel(GL_SMOOTH);

	glutDisplayFunc(display);
	glutIdleFunc(display);
	glutReshapeFunc(reshape);

	glutMainLoop();
}

void display(void)
{
	glClearColor (1.f,0.f,1.f,0.f);
	
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	
	glLoadIdentity();
	
	glMatrixMode(GL_MODELVIEW);
	
	glutSwapBuffers();
}

void reshape(int width,int height)
{
	glViewport(0,0,(GLsizei)width,(GLsizei)height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//FOV, Aspect Ratio, Near pane and far plane
	gluPerspective(60,(GLfloat)width/(GLfloat)height,1.0,1500.0);
	glMatrixMode(GL_MODELVIEW);
}

