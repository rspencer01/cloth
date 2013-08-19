#pragma comment(lib,"glew32.lib")

#include <GL/glut.h>
#include <math.h>
#include <algorithm>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <time.h>
#include <utility>
#include <vector>
using namespace std;


void display(void);
void reshape(int,int);

typedef pair<float,float> pff;
typedef vector<vector<pff> > frame;

int frameCount;
int currFrame;
int width,height;
vector<vector<pff> > positions;

clock_t lastUpdate;

void loadData(string filePath)
{
	FILE* fp = fopen(filePath.c_str(),"r");
	fscanf(fp,"%d",&frameCount);
	fscanf(fp,"%d",&width);
	fscanf(fp,"%d",&height);
	for (int i = 0;i<frameCount;i++)
	{
		vector<pff> temp;
		temp.clear();
		for (int h = 0;h<height*width;h++)
		{
			pff t = make_pair(-1,-1);
			fscanf(fp,"%f %f ",&t.first,&t.second);
			printf("%f %f\n",t.first,t.second);
			temp.push_back(t);
		}
		positions.push_back(temp);
	}
	fclose(fp);
}

pff getPosition(int x,int y, int f)
{
	return positions[f][y*width+x];
}

void drawLine(pff from, pff to)
{
  glLineWidth(0.5);
  glBegin(GL_LINES);
  glVertex3f(from.second, from.first, 0.0);
  glVertex3f(to.second, to.first, 0);
  glEnd();
}

int main(int argc, char**argv)
{
	if (argc<2)
	{
		printf("Usage: clothV <inputFile>\n\ninputFile: The file to visualise\n");
		exit(0);
	}
	string inpFlName (argv[1]);
	loadData(inpFlName);
	printf("Number of frames : %d\n",frameCount);
	printf("Size of grid: %dx%d\n",width,height);

	srand(0);
	
	glutInit(&argc,argv);
	
	glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGBA|GLUT_DEPTH);
	glutInitWindowSize(500,500);
	glutInitWindowPosition(100,100);
	glutCreateWindow("Terrain");
	

	glEnable ( GL_COLOR_MATERIAL ) ;
	glEnable( GL_TEXTURE_2D );
	glEnable( GL_BLEND );
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	
	glShadeModel(GL_SMOOTH);

	glutDisplayFunc(display);
	glutIdleFunc(display);
	glutReshapeFunc(reshape);

	currFrame = 0;
	lastUpdate = clock();

	glutMainLoop();
}

void display(void)
{
	glClearColor (1.f,0.f,1.f,0.f);
	
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	
	glMatrixMode(GL_PROJECTION);

	glLoadIdentity();

	glOrtho(-1,1,-1,1,-1,1);
	
	glMatrixMode(GL_MODELVIEW);

	glLoadIdentity();

	for (int i = 0;i<width;i++)
	{
		for (int j = 0;j<height-1;j++)
		{
			drawLine(getPosition(i,j,currFrame),getPosition(i,j+1,currFrame));
		}
	}

	glutSwapBuffers();

	clock_t nw = clock();
	float diff = (((float)nw - (float)lastUpdate) / 1000000.0F ) * 1000;   
	if (diff>1000.0/24)
	{
		currFrame++;
		currFrame%=frameCount;
		lastUpdate = nw;
		printf("%d\n",currFrame);
	}
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

