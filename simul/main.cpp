#include <math.h>
#include <algorithm>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <time.h>
#include <utility>
#include <vector>
#include "vector2d.h"
using namespace std;

#define FRAME_COUNT 1000
#define WIDTH 52
#define HEIGHT 65
#define POINT_MASS 1 
#define TIMESTEP 1
#define K 0.2
#define FRICTIONAL_CONSTANT 0.01

typedef vector<vector<vector2D> > frame;

FILE* fp;
frame currFrame;
frame nextFrame;
frame velocities;
frame accelerations;
float constraintLength;

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
  constraintLength = 0.5/HEIGHT;
  currFrame.clear();
  velocities.clear();
  nextFrame.clear();
  for (int i = 0;i<HEIGHT;i++)
  {
    vector<vector2D> tem;
    vector<vector2D> tem2;
    for (int j=0;j<WIDTH;j++)
    {
      tem.push_back(vector2D(i/float(HEIGHT)*1.6-0.5*1.6,0.9-j/float(HEIGHT*5)));
      tem2.push_back(vector2D(0,0));
    }
    currFrame.push_back(tem);
    nextFrame.push_back(tem);
    velocities.push_back(tem2);
    accelerations.push_back(tem2);
  }
  currFrame[0][HEIGHT-1] = currFrame[0][HEIGHT-1] - vector2D(-0.1,0.1);
}

void writeFrame(frame x)
{
  for (int j = 0;j<HEIGHT;j++)
    for (int i = 0;i<WIDTH;i++)
    {
      fprintf(fp,"%f %f ",x[j][i].x,x[j][i].y);
    }
  fprintf(fp,"\n");
}

void copyBackFrame()
{
  for (int j = 0;j<HEIGHT;j++)
    for (int i = 0;i<WIDTH;i++)
      currFrame[j][i]= nextFrame[j][i];
}

void updatePosition()
{
  for (int j = 0;j<HEIGHT;j++)
    for (int i = 1;i<WIDTH;i++)
      nextFrame[j][i] = currFrame[j][i]+velocities[j][i]*TIMESTEP;
}

void updateAccelerations()
{
  // Gravity
  for (int j = 0;j<HEIGHT;j++)
    for (int i = 1;i<WIDTH;i++)
      accelerations[j][i] = vector2D(0,-0.0001);

  for (int j = 0;j<HEIGHT;j++)
    for (int i = 1;i<WIDTH;i++)
    {
      vector2D diff = currFrame[j][i]-currFrame[j][i-1];
      if (diff.mag()>constraintLength)
      {
        diff = diff - diff*(constraintLength/diff.mag());
        accelerations[j][i] = accelerations[j][i] - diff * K;
        if (i>0)
          accelerations[j][i-1] = accelerations[j][i-1] + diff * K;
      }
    }
  for (int j = 1;j<HEIGHT;j++)
    for (int i = 0;i<WIDTH;i++)
    {
      vector2D diff = currFrame[j][i]-currFrame[j-1][i];
      if (diff.mag()>constraintLength)
      {
        diff = diff - diff*(constraintLength/diff.mag());
        accelerations[j][i] = accelerations[j][i] - diff * K;
        accelerations[j-1][i] = accelerations[j-1][i] + diff * K;
      }
    }
  
  for (int j = 0;j<HEIGHT;j++)
    for (int i = 1;i<WIDTH;i++)
      accelerations[j][i] = accelerations[j][i] - velocities[j][i]*FRICTIONAL_CONSTANT;

}

void updateVelocities()
{
  for (int j = 0;j<HEIGHT;j++)
    for (int i = 1;i<WIDTH;i++)
      velocities[j][i] = velocities[j][i] + accelerations[j][i]*TIMESTEP;
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
    updateVelocities();
    updatePosition();
    copyBackFrame();
  }
  closeFile();
}
