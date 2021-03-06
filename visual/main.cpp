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

typedef pair<pair<float,float>, float> pff;
typedef vector<vector<pff> > frame;

int frameCount;
int currFrame;
int numPoints,numLinks;
vector<vector<pff > > positions;
vector<pair<int,int> > links;
vector<bool> linksToNotDraw;
vector<vector<int> > linkDeletions;
bool* keyStates = new bool[256];
float psi = 0;
float phi = 3.1415/2;
float r = 2;

clock_t lastUpdate;

void keyPressed(unsigned char,int,int);
void keyUp(unsigned char, int, int);
void keyOperations(void);
float DownlookDist = 0;
int speed = 1;
void renderCamera(void);

void loadData(string filePath)
{
	FILE* fp = fopen(filePath.c_str(),"r");
	fscanf(fp,"%d",&frameCount);
	fscanf(fp,"%d",&numPoints);
	fscanf(fp,"%d",&numLinks);
  linksToNotDraw.resize(numLinks);
  for (int i = 0;i<numLinks;i++)
  {
    pair<int,int> t;
    fscanf(fp,"%d %d\n",&t.first,&t.second);
    links.push_back(t);
    linksToNotDraw[i] = false;
  }
	for (int i = 0;i<frameCount;i++)
	{
		vector<pff> temp;
		for (int h = 0;h<numPoints;h++)
		{
			pff t = make_pair(make_pair(-1,-1),-1);
			fscanf(fp,"%f %f %f",&t.first.first,&t.first.second, &t.second);
			temp.push_back(t);
		}
		positions.push_back(temp);
    vector<int> toDel;
    int numD;
    fscanf(fp,"%d ",&numD);
    toDel.resize(numD);
		for (int j = 0;j<numD;j++)
      fscanf(fp,"%d",&toDel[j]);
    linkDeletions.push_back(toDel);
	}

	fclose(fp);
}

pff getPosition(int x, int f)
{
  return positions[f][x];
}

void drawLine(pff from, pff to)
{
  glLineWidth(1.0);
  glBegin(GL_LINES);
  glVertex3f(from.first.first, from.first.second, from.second);
  glVertex3f(to.first.first, to.first.second, to.second);
  glEnd();
}

void updateDeletedLinks(int frameNumber)
{
  for (int i = 0;i<linkDeletions[frameNumber].size();i++)
    linksToNotDraw[linkDeletions[frameNumber][i]] = true;
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
	printf("Number of points : %d\n",numPoints);
	printf("Number of links  : %d\n",numLinks);
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
  glutKeyboardFunc(keyPressed);
  glutKeyboardUpFunc(keyUp);


	currFrame = 0;
	lastUpdate = clock();

	glutMainLoop();
}

void display(void)
{
  keyOperations();
	glClearColor (1.f,0.f,1.f,0.f);
	
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
  renderCamera();

  updateDeletedLinks(currFrame);

	for (int i = 0;i<numLinks;i++)
    if (linksToNotDraw[i] == false)
			drawLine(getPosition(links[i].first,currFrame),getPosition(links[i].second,currFrame));
	
  
  glutSwapBuffers();

	clock_t nw = clock();
	float diff = (((float)nw - (float)lastUpdate) / 1000000.0F ) * 1000;   
	if (diff>1.0/24)
	{
		currFrame++;
		currFrame%=frameCount;
    if (currFrame==0)
      for (int i = 0;i<numLinks;i++)
        linksToNotDraw[i] = false;
		lastUpdate = nw;
    if (currFrame%240==0)
  		printf("%d\n",currFrame);
	}
}

void reshape(int width,int height)
{
	glViewport(0,0,(GLsizei)width,(GLsizei)height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//FOV, Aspect Ratio, Near pane and far plane
	gluPerspective(60,(GLfloat)width/(GLfloat)height,0.1,1500.0);
	glMatrixMode(GL_MODELVIEW);
}
void keyPressed(unsigned char key,int x,int y)
{
	keyStates[key] = true;
}

void keyUp(unsigned char key,int x,int y)
{
	keyStates[key] = false;
}

void keyOperations(void)
{
	if (keyStates['a'])
    phi -= 0.01;
	if (keyStates['d'])
    phi += 0.01;
	if (keyStates['w'])
    psi += 0.01;
	if (keyStates['s'])
    psi -= 0.01;
  if (keyStates['e'])
    r += 0.01;
  if (keyStates['q'])
    r -= 0.01;
}

void renderCamera()
{
  gluLookAt(r*cos(phi)*cos(psi),r*sin(psi),r*sin(phi),0,0,0,0,1,0);
}
