//--------------------------------begin--------------------------------
//-----------------------------by Yikun Lin----------------------------
#ifndef SELECTFEATURES_H_
#define SELECTFEATURES_H_


#include <zlib.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <iostream>
#include <fstream>
#include <string.h>

#define Malloc(type,n) (type *)malloc((n)*sizeof(type))

static char* line = NULL;
static int max_line_len;
static const int GR_START = 0;
static const int GR_DI = 96;
static const int OF_START = 96;
static const int OF_DI = 108;
static const int MB_START = 204;
static const int MB_DI = 192;

static const int MINLEN = 20;
static const double ratio = 0.0635;
char* ReadLine(gzFile gzfp);
void SelectLines(bool* isSelected, int nLines, int nSelects);
bool SelectFeatures(int argc, char** argv);

#endif /*SELECTFEATURES_H_*/
//---------------------------------end---------------------------------

