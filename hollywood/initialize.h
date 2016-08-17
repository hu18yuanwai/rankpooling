#ifndef INITIALIZE_H
#define  INITIALIZE_H
#include <stdlib.h>
#include <stdio.h>
#include <fstream>

#include <iostream>
#include <string.h>

#include <vector>
#include <math.h>
#include <zlib.h>
#include <opencv/cv.h>
#include <opencv/highgui.h>

#include <set>
#include <iterator>
#include <algorithm>

using namespace std;

#define Malloc(type,n) (type *)malloc((n)*sizeof(type))
#define PCA_MEAN	"mean"
#define PCA_EIGEN_VECTOR	"eigen_vector"
//读入gzip的参数
static char* iline;
static int max_iline_len = 1024;

//数据集参数
static int datasetSize = 1707;
static const int actionType = 12;
static const int filePathSize = 100;//文件名长度

//各种描述符的维度
const int TRJ_DI = 30;
const int HOG_DI = 96;
const int HOF_DI = 108;
const int MBH_DI = 192;
const int OBJ_DI = 10;

//高斯模型参数
const int gmmSize = 256;
static char* iiline;
static int max_line_len = 1024;
const float pcaFactor = 0.5f;
//
static char *feature_out = "../../../remote/Data/feats/hof/";
const int DIMENSION = HOF_DI*gmmSize;
static int samples = 1000000;
static int trainNum = 823;
static int testNum = 884;
static int num_videos = 1707;

//初始化目录
static char *vocabDir = "../../../remote/Data/Vocab/";
static char *featDir = "../../../remote/Data/feats/";
static char *descriptor_path = "../../../remote/Data/descriptor/";

static char * pcaTrjInfo = "../../../remote/Data/Vocab/pcaTrjInfo.xml";
static char * pcaHogInfo = "../../../remote/Data/Vocab/pcaHogInfo.xml";
static char * pcaHofInfo = "../../../remote/Data/Vocab/pcaHofInfo.xml";
static char * pcaMbhInfo = "../../../remote/Data/Vocab/pcaMbhInfo.xml";

static char *reducedPCADataoftrjALL =  "../../../remote/Data/Vocab/trj";
static char *reducedPCADataofhogALL =  "../../../remote/Data/Vocab/hog";
static char *reducedPCADataofhofALL =  "../../../remote/Data/Vocab/hof";
static char *reducedPCADataofmbhALL =  "../../../remote/Data/Vocab/mbh";

static char *gmmMeansTrj =  "../../../remote/Data/Vocab/trj.gmmmeans";
static char *gmmCovariancesTrj =  "../../../remote/Data/Vocab/trj.gmmcovariances";
static char *gmmPriorsTrj =  "../../../remote/Data/Vocab/trj.gmmpriors";

static char *gmmMeansHog =  "../../../remote/Data/Vocab/hog.gmmmeans";
static char *gmmCovariancesHog =  "../../../remote/Data/Vocab/hog.gmmcovariances";
static char *gmmPriorsHog =  "../../../remote/Data/Vocab/hog.gmmpriors";

static char *gmmMeansHof =  "../../../remote/Data/Vocab/hof.gmmmeans";
static char *gmmCovariancesHof =  "../../../remote/Data/Vocab/hof.gmmcovariances";
static char *gmmPriorsHof =  "../../../remote/Data/Vocab/hof.gmmpriors";

static char *gmmMeansMbh =  "../../../remote/Data/Vocab/mbh.gmmmeans";
static char *gmmCovariancesMbh =  "../../../remote/Data/Vocab/mbh.gmmcovariances";
static char *gmmPriorsMbh =  "../../../remote/Data/Vocab/mbh.gmmpriors";

static char *sampledtrjFeatureAllData = "../../../remote/Data/Vocab/trjAll";
static char *sampledhogFeatureAllData = "../../../remote/Data/Vocab/hogAll";
static char *sampledhofFeatureAllData = "../../../remote/Data/Vocab/hofAll";
static char *sampledmbhFeatureAllData = "../../../remote/Data/Vocab/mbhAll";

static char tempStyeStart[filePathSize] = "../../../remote/Hollywood2/AVIClips/actioncliptrain";
static char tempStyeStart2[filePathSize] = "../../../remote/Hollywood2/AVIClips/actioncliptest";


static char *darwin_feature = "../../../remote/Data/feats/w/";

//常用的函数
//从文件中读入一行数据
char* Readiline(FILE* input)
{
	int len;

	if(fgets(iline, max_iline_len, input) == NULL)
		return NULL;
	while(strrchr(iline, '\n') == NULL)
	{
		max_iline_len *= 2;
		iline = (char *) realloc(iline, max_iline_len);
		len = (int) strlen(iline);
		if(fgets(iline + len, max_iline_len - len, input) == NULL)
			break;
	}
	return iline;
}

int readLineFromFile(char * fileName)
{
	FILE *fp = fopen(fileName,"r");
	max_iline_len = 1024;
	iline = Malloc(char,max_iline_len);
	int len = 0;
	while(Readiline(fp)!=NULL)
	{
		len++;
	}
	fclose(fp);
	return len;
}


//读入类别标签
int ** readLabelFromFile()
{
	int **label = new int*[datasetSize];
	for (int i = 0; i < datasetSize; ++i)
	{
		label[i] = new int[actionType];
		for (int j = 0; j < actionType; ++j)
		{
			label[i][j] = -1;
		}
	}
	FILE *labelfile = fopen("./initialize_data/classLabel.txt","r");
	int iiline = 0;
	int index= 0;
	int tempvalue = 0;
	while (Readiline(labelfile))
	{
		index =0;
		char * feature = strtok(iline, " \t"); // label
		tempvalue = atoi(feature);
		if (tempvalue == 1 )
		{
			label[iiline][index] = 1;
			iiline++;
			continue;
		}
		index++;
		while (1)
		{
			feature = strtok(NULL, " \t");
			tempvalue = atoi(feature);
			if (tempvalue == 1 )
			{
				label[iiline][index] = 1;
				break;
			}
			index++;
		}
		iiline++;
	}
	fclose(labelfile);
	return label;
}


char * getStyle(char *result,int a,int index)
{

	for (int i = 0; i < 5; ++i)
	{
		result[index++] = '0';
	}
	int j = index;
	index --;
	while(a >= 1)
	{
		int rem = a % 10;
		result[index--] = rem+'0';
		a-=rem;
		a/=10;
	}
	return result;
}

char ** getFullVideoName()
{
	char *resultStart = new char[filePathSize];
	char *resultStart2 = new char[filePathSize];
	char tempStyeStart[filePathSize] = "../../remote/Hollywood2/AVIClips/actioncliptrain";
	char tempStyeStart2[filePathSize] = "../../remote/Hollywood2/AVIClips/actioncliptest";
	strcpy(resultStart,tempStyeStart);
	strcpy(resultStart2,tempStyeStart2);

	char **fullvideoname = new char*[datasetSize];
	for (int i = 0; i < datasetSize; ++i)
	{
		fullvideoname[i] = new char[filePathSize];
		if(i < 823)
		{
			strcpy(fullvideoname[i],getStyle(resultStart,i+1,strlen(tempStyeStart)));
		}
		else
		{
			strcpy(fullvideoname[i],getStyle(resultStart2,i-822,strlen(tempStyeStart2)));
		}
		cout<<fullvideoname[i]<<endl;
	}
	delete [] resultStart;
	delete [] resultStart2;
	return fullvideoname;
}

void  releaseFullVideoName(char ** fullvideoname)
{
	for (int i = 0; i < datasetSize; ++i)
	{
		delete [] fullvideoname[i];
	}
	delete fullvideoname;
}

#endif
