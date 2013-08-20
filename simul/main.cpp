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

int currFrame;
int width,height;
vector<vector<pff> > positions;
FILE* fp;

void openFile()
{
  fp = fopen("output.inp","w");
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

int main(int argc, char**argv)
{
  openFile();
  writeHeader();
  for (int i = 0;i<FRAME_COUNT;i++)
  {
  }
  closeFile();
}
