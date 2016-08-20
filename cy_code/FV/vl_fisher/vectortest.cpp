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
#define Malloc(type,n) (type *)malloc((n)*sizeof(type))
extern "C"
{
	#include <vl/generic.h>
	#include <vl/fisher.h>
}
const int TRJ_DI = 30;
const int HOG_DI = 96;
const int HOF_DI = 108;
const int MBH_DI = 192;
const int OBJ_DI = 10;
const int gmmSize = 256;
static char* iiline;
static int max_line_len = 1024;
const float pcaFactor = 0.5f;
using namespace std;
//get config of we need. 
static int st = 1;
static int datasetSize = 1708;
static int send = datasetSize;
static const int actionType = 13;
static const int filePathSize = 100;
void saveObj(std::vector<int> v, char *filename)
{
	ofstream file(filename);
	for (int i = 0; i < v.size(); ++i)
	{
		file << v[i]<<" ";
	}
	file.close();
}
char * ReadLine(gzFile gzfp)
{
	int len;
	if(gzgets(gzfp, iiline, max_line_len) == NULL)
		return NULL;
	while(strrchr(iiline, '\n') == NULL)
	{
		max_line_len *= 2;
		iiline = (char*) realloc(iiline, max_line_len);
		len = (int) strlen(iiline);
		if(gzgets(gzfp, iiline + len, max_line_len - len) == NULL)
			break;
	}
	return iiline;
}
void getDescriptorFromFile(char *descriptorFileName,vector<int>*obj,vector<vector<float> > *trj)
{
	printf("%s\n", "getDescriptorFromFile function to get fisher vector");
	int nLines = 0;
	max_line_len = 1024;
	iiline = Malloc(char, max_line_len);
	gzFile file = gzopen(descriptorFileName,"r");
	float value;
	int value2;
	vector<float> temp;

	while (ReadLine(file) != NULL)
	{
		//printf("%s\n","readline" );
		int j;
		char* feature;
		feature = strtok(iiline," \t");
		value2 = atoi(feature);
		obj->push_back(value2);

		for (; j < OBJ_DI; j++)
		{
			feature = strtok(NULL," \t"); // get rid of obj and trj
		}

		temp.clear();
		for (j = 0; j< TRJ_DI; j++)
		{
			feature = strtok(NULL," \t");
			value = atof(feature);
			temp.push_back(value);
		}
		trj->push_back(temp);
		temp.clear();
	}
	temp.clear();
	printf("%s, and frame-size is ,%d \n","the end of features",(*obj).size());
	gzclose(file);
}
void getFV()
{
	// vector<int>obj;
	// vector<vector<float> > trj;
	// char * descriptorFileName = "../../remote/Data/descriptor/actioncliptrain00001";
	// getDescriptorFromFile(descriptorFileName,&obj,&trj);

	char * descriptorFileName = "../../remote/Data/descriptor/actioncliptrain00001";
	char * feat_trj_fv_file = "../../remote/Data/feats/actioncliptrain00001-trj-fv";
	
	vector<int>obj;
	vector<vector<float> > trj;
	
	obj.clear();
	trj.clear();

	
	getDescriptorFromFile(descriptorFileName,&obj,&trj);

	set<int> uniqueObj(obj.begin(),obj.end());
	
	sort(obj.begin(), obj.end());
	//copy(obj.begin(), obj.end(),ostream_iterator<int>(cout," "));
	
	// int frames = uniqueObj.size();
	// cout<<frames<<" frames in video"<<endl;
	// float **fv_trj = new float* [frames];
	
	// for (size_t i = 0; i < frames; i++) {
	// 	fv_trj[i] = new float[(int)(2*pcaFactor*TRJ_DI*gmmSize)+1];
		
	// }

	// set<int>::iterator it;
	// int value = 0,indexLineofFisher = 0;
	// vector<int>::iterator itv = obj.begin();
	// int startindex = 0;
	// int tempa,tempb,numDataToEncode;
	// for (it = uniqueObj.begin();it != uniqueObj.end(); it++)
	// {
	// 	tempa = startindex;
	// 	while(*itv == *it && itv!= obj.end())
	// 	{
	// 		obj.erase(itv);
	// 		startindex++;
	// 	}
	// 	tempb = startindex-1;
	// 	numDataToEncode = tempb-tempa+1;
	// 	//cout<<tempa<<" is tempa "<< tempb <<" is tempb"<<endl;
	// }
	saveObj(obj,"./obj");
}

void readGmmFromFile(float *data, char *fileName)
{
	cout<<"read Gmm from "<<fileName<<endl;
	ifstream _file(fileName);
	if(_file)
	{
		int index = 0;
		while(!_file.eof())
		{
			_file >> data[index++];
		}
		_file.close();
	}
	else{
		cout<<fileName<<" do not exist"<<endl;
		return ;
	}
}


int main(int argc, char const *argv[])
{
	int gmmSize = 256;
	int TRJ_DI = 30;

	char *gmmMeansTrjFileName = new char[50];
	strcpy(gmmMeansTrjFileName, "../../remote/Data/Vocab/trj.gmmmeans");
	char *gmmCovariancesTrjFileName = new char[50];
	strcpy(gmmCovariancesTrjFileName, "../../remote/Data/Vocab/trj.gmmcovariances");
	char *gmmPriorsTrjFileName = new char[50];
	strcpy(gmmPriorsTrjFileName, "../../remote/Data/Vocab/trj.gmmpriors");
	float * Trjmeans = new float[gmmSize*TRJ_DI];
	float * Trjcovariances = new float[gmmSize*TRJ_DI];
	float * Trjpriors = new float[gmmSize];
	readGmmFromFile(Trjmeans,gmmMeansTrjFileName);
	readGmmFromFile(Trjcovariances,gmmCovariancesTrjFileName);
	readGmmFromFile(Trjpriors,gmmPriorsTrjFileName);
	getFV();
	vector<int>obj;
	vector<vector<float> > trj;
	char * descriptorFileName = "../../remote/Data/descriptor/actioncliptrain00001";
	getDescriptorFromFile(descriptorFileName,&obj,&trj);
	saveObj(obj,"./obj");

	//test();
	return 0;
}


