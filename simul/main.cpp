#include <math.h>
#include <algorithm>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <time.h>
#include <utility>
#include <vector>
using namespace std;

#define FRAME_COUNT 100
#define WIDTH 10
#define HEIGHT 15

typedef pair<float,float> pff;
typedef vector<vector<pff> > frame;

FILE* fp;
frame currFrame;
frame nextFrame;
frame momenta;

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
  momenta.clear();
  nextFrame.clear();
  for (int i = 0;i<HEIGHT;i++)
  {
    vector<pff> tem;
    vector<pff> tem2;
    for (int j=0;j<WIDTH;j++)
    {
      pff t = make_pair(i/float(HEIGHT)-0.5,-j/float(WIDTH));
      tem.push_back(t);
      tem2.push_back(make_pair(0,-0.001));
    }
    currFrame.push_back(tem);
    nextFrame.push_back(tem);
    momenta.push_back(tem2);
  }
}

void writeFrame(frame x)
{
  for (int j = 0;j<HEIGHT;j++)
    for (int i = 0;i<WIDTH;i++)
    {
      fprintf(fp,"%f %f ",x[j][i].first,x[j][i].second);
    }
  fprintf(fp,"\n");
}

void copyBackFrame()
{
  for (int j = 0;j<HEIGHT;j++)
    for (int i = 0;i<WIDTH;i++)
      currFrame[j][i]= nextFrame[j][i];
}

pff add(pff a,pff b)
{
  return make_pair(a.first+b.first,a.second+b.second);
}

void updatePosition()
{
  for (int j = 0;j<HEIGHT;j++)
    for (int i = 1;i<WIDTH;i++)
      nextFrame[j][i] = add(currFrame[j][i],momenta[j][i]);
}

int main(int argc, char**argv)
{
  openFile();
  writeHeader();
  initialiseFrame();
  for (int i = 0;i<FRAME_COUNT;i++)
  {
    writeFrame(currFrame);
    updatePosition();
    copyBackFrame();
  }
  closeFile();
}
