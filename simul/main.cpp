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
using namespace std;

#define FRAME_COUNT 1000
#define WIDTH 62
#define HEIGHT 60
#define POINT_MASS 1 
#define TIMESTEP 1
#define K 0.2
#define FRICTIONAL_CONSTANT 0.01
#define constraintLength 0.015

typedef vector<vector<pointMass> > frame;


FILE* fp;
frame currFrame;

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
  fprintf(fp,"%d\n",WIDTH);
  fprintf(fp,"%d\n",HEIGHT);
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
  currFrame[1][1].position = currFrame[1][1].position + vector2D(0.1,0.1);
  currFrame[1][2].position = currFrame[1][2].position + vector2D(0.1,0.1);
  currFrame[1][3].position = currFrame[1][3].position + vector2D(0.1,0.1);
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

  for (int j = 0;j<HEIGHT;j++)
    for (int i = 1;i<WIDTH;i++)
    {
      vector2D diff = currFrame[j][i].position-currFrame[j][i-1].position;
      if (diff.mag()>constraintLength)
      {
        diff = diff - diff*(constraintLength/diff.mag());
        currFrame[j][i].addForce(diff * K * (-1));
        currFrame[j][i-1].addForce(diff * K);
      }
    }
  for (int j = 1;j<HEIGHT;j++)
    for (int i = 0;i<WIDTH;i++)
    {
      vector2D diff = currFrame[j][i].position-currFrame[j-1][i].position;
      if (diff.mag()>constraintLength)
      {
        diff = diff - diff*(constraintLength/diff.mag());
        currFrame[j][i].addForce(diff * K * (-1));
        currFrame[j-1][i].addForce(diff * K);
      }
    }
  
  for (int j = 0;j<HEIGHT;j++)
    for (int i = 0;i<WIDTH;i++)
      currFrame[j][i].addFriction(FRICTIONAL_CONSTANT);

}

int main(int argc, char**argv)
{
  openFile();
  writeHeader();
  initialiseFrame();
  for (int i = 0;i<FRAME_COUNT;i++)
  {
    writeFrame(currFrame);
    updateAccelerations();
    updatePosition();
  }
  closeFile();
}
