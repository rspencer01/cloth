#include <math.h>
#include <algorithm>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <time.h>
#include <utility>
#include <vector>
#include "vector2d.h"
#include "pointMass.h"
#include "constraint.h"
#include "sphere.h"
using namespace std;

#define FRAME_COUNT 2000
#define WIDTH 40
#define HEIGHT 40
#define POINT_MASS 1 
#define TIMESTEP 0.5
#define K 0.2
#define FRICTIONAL_CONSTANT 0.01
#define constraintLength 0.02

typedef vector<vector<pointMass> > frame;


FILE* fp;
frame currFrame;
vector<constraint> springs;
sphere sph (vector2D(-1,-0.1),0.1);

void openFile()
{
  fp = fopen("output.inp~","w");
}

void closeFile()
{
  fclose(fp);
}

void writeHeader()
{
  fprintf(fp,"%d\n",FRAME_COUNT);
  fprintf(fp,"%d\n",WIDTH*HEIGHT);
  fprintf(fp,"%d\n",(WIDTH)*(HEIGHT-1) + (WIDTH-1)*(HEIGHT));
  for (int i = 1;i<HEIGHT;i++)
    for (int j = 0;j<WIDTH;j++)
      fprintf(fp,"%d %d ",(i-1)*WIDTH+j,i*WIDTH+j);
  for (int i = 0;i<HEIGHT;i++)
    for (int j = 1;j<WIDTH;j++)
      fprintf(fp,"%d %d ",i*WIDTH+j,i*WIDTH+j-1);
  fprintf(fp,"\n");

}

void initialiseFrame()
{
  currFrame.clear();
  for (int i = 0;i<HEIGHT;i++)
  {
    float y = 0.9-i*constraintLength;
    vector<pointMass> tem;
    for (int j=0;j<WIDTH;j++)
    {
      float x = (j-WIDTH/2.0)*constraintLength;
      tem.push_back(pointMass(vector2D(x,y)));
    }
    currFrame.push_back(tem);
  }
}

void initialiseSprings()
{
  for (int i = 1;i<HEIGHT;i++)
    for (int j = 0;j<WIDTH;j++)
      springs.push_back(constraint(&currFrame[i][j],
                                   &currFrame[i-1][j],
                                   constraintLength,
                                   K));
   for (int i = 0;i<HEIGHT;i++)
    for (int j = 1;j<WIDTH;j++)
      springs.push_back(constraint(&currFrame[i][j],
                                   &currFrame[i][j-1],
                                   constraintLength,
                                   K));
}

void writeFrame(frame x)
{
  for (int j = 0;j<HEIGHT;j++)
    for (int i = 0;i<WIDTH;i++)
    {
      fprintf(fp,"%f %f ",x[j][i].x(),x[j][i].y());
    }
  fprintf(fp,"\n");
}

void updatePosition()
{
  for (int j = 1;j<HEIGHT;j++)
    for (int i = 0;i<WIDTH;i++)
      currFrame[j][i].updatePosition(TIMESTEP);
}

void updateAccelerations()
{
  
  // Gravity
  for (int j = 1;j<HEIGHT;j++)
    for (int i = 0;i<WIDTH;i++)
      currFrame[j][i].addForce(vector2D(0,-0.0001));

  for (int i = 0;i<springs.size();i++)
    springs[i].enforce();
  
  for (int j = 0;j<HEIGHT;j++)
    for (int i = 0;i<WIDTH;i++)
      currFrame[j][i].addFriction(FRICTIONAL_CONSTANT);

}

void resolveSphere()
{
  for (int j = 0;j<HEIGHT;j++)
    for (int i = 0;i<WIDTH;i++)
      currFrame[j][i].position = sph.resolve(currFrame[j][i].position);
} 

void updateVelocities()
{
  for (int j = 0;j<HEIGHT;j++)
    for (int i = 0;i<WIDTH;i++)
      currFrame[j][i].updateMomentum(TIMESTEP);
}

int main(int argc, char**argv)
{
  openFile();
  writeHeader();
  initialiseFrame();
  initialiseSprings();
  for (int i = 0;i<FRAME_COUNT;i++)
  {
    writeFrame(currFrame);
    updateAccelerations();
    updatePosition();
    resolveSphere();
    // We do this because the sphere may have thown off some things
    updateVelocities();
    sph.centre = sph.centre + vector2D(0.005,0.001);
  }
  closeFile();
}
