#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <fstream>
#include <zlib.h>
#include <vector>
#include <string.h>
#include <set>
#include <iterator>
#include <algorithm>
#include <math.h>
#include <opencv/cv.h>
#include <opencv/highgui.h>
using namespace std;
#define Malloc(type,n) (type *)malloc((n)*sizeof(type))
extern "C"
{
	#include <vl/generic.h>
	#include <vl/fisher.h>
}
int main(int argc, char const *argv[])
{

	float **fv_trj = new float*[5];
	for (int i = 0; i < 5; ++i)
	{
		fv_trj[i] = new float[2];
	}
	void * encTrj = vl_malloc(sizeof(float) * 10);
	for (int i = 0; i < 10; ++i)
	{
		((float * )encTrj)[i] = 10; 
	}
	

	for (int j = 0; j < 2; ++j)
	{
		fv_trj[0][j] = ((float *)encTrj)[j];	
	}
	delete []encTrj;
	cout<<fv_trj[0][0]<<endl;

	return 0;
}