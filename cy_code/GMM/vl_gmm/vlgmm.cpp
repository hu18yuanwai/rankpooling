extern "C"
{
	#include <vl/generic.h>
	#include <vl/gmm.h>
}
#include <fstream>
#include <iostream>
#include <vector>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
using namespace std;
void saveTofile(const void *data,int size,char *filename)
{
    ofstream file(filename);
		for (size_t  i = 0;  i < size; i ++) {
		file << ((float *)data)[i]<<" ";
	}
	file.close();
	cout<<filename<<"saved!"<<endl;
	return ;
}
int main(int argc, char const *argv[])
{
	const char *filename = argv[1];
	const char *dimensionC = argv[2];
	int dimension = atoi(dimensionC);
	
	//remember the dimension of feature is half of originfeature!!!!!!!!!!!!!
	//cout<<dimension<<" is the dimension of "<<filename<<endl;
	vector<float> tempData;
	float tempValue;
	ifstream file(filename);
	if(!file)
	{
		VL_PRINT("file not exist");
	}
	else
	{
		while(!file.eof())
		{
			file >> tempValue;
			tempData.push_back(tempValue);
		}
		file.close();
	}
	//cout<<"=================after read"<<endl;
	float *data = new float[tempData.size()+1];
	for (int i = 0; i < tempData.size(); ++i)
	{
		data[i] = tempData[i];
	}

	int numClusters = 256;
	int numData = tempData.size()/dimension;
	// create a new instance of a GMM object for float data
	//cout<<tempData.size()<<" is tempData's size"<<numData<<" is number of Data =================before gmm"<<endl;
	
	VlGMM *gmm = vl_gmm_new (VL_TYPE_FLOAT, dimension, numClusters) ;
	// set the maximum number of EM iterations to 100
	cout<<"==================generate gmm================="<<endl;
	
	vl_gmm_set_max_num_iterations (gmm, 100) ;
	// set the initialization to random selection
	vl_gmm_set_initialization (gmm,VlGMMRand);
	// cluster the data, i.e. learn the GMM
	//cout<<"=================set iteration and initialization "<<endl;
	
	vl_gmm_cluster (gmm, data, numData);
	// get the means, covariances, and priors of the GMM
	//do not knowing the size of means.
	//cout<<"=================cluster "<<endl;
	
	const void *means = vl_gmm_get_means(gmm);
	const void *covariances = vl_gmm_get_covariances(gmm);
	const void *priors = vl_gmm_get_priors(gmm);
	//cout<<"=================get means"<<endl;
	
	
	char *temp = new char [strlen(filename)+50];// !!!!!!!!!!!!!!!!!!!!MEMORY COURPOTION....
	strcpy(temp,filename);
	saveTofile(means,dimension*numClusters,strcat(temp,".gmmmeans"));
	
	strcpy(temp,filename);
	saveTofile(covariances,dimension*numClusters,strcat(temp,".gmmcovariances"));
	
	strcpy(temp,filename);
	saveTofile(priors,numClusters,strcat(temp,".gmmpriors"));
	
	vl_free(gmm);
	delete [] data;
	delete []temp;
	return 0;
}