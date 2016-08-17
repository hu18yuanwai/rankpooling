#ifndef GETGMM_H_
#define GETGMM_H_
#include "initialize.h"

using namespace cv;
using namespace std;

void saveDatatoFile(float ** trjAllData, int num,int dimension, char *filepath)
{
	ofstream file(filepath);
	//cout<<"save trjAll Data ***************"<<endl;
	for (size_t  i = 0;  i < num; i ++) {
		for (size_t s = 0; s < dimension; ++s)
		{
			file << trjAllData[i][s]<<" ";
		}
		file<<endl;
	}
	file.close();
	cout<<filepath<<" saved"<<endl;
}

void saveDatatoFile(float* trjData,int size,char *filepath)
{
	ofstream file(filepath);
	//cout<<size<<" is the size"<<endl;
	for (size_t  i = 0;  i < size; i ++) {
		file << trjData[i]<<" ";
	}
	file.close();
	cout<<filepath<<" saved"<<endl;
}
//curvely save the world!!!
void getAndSaveGmmModel(char *fileName, int dimension)
{
	cout<<"save"<<fileName<<endl; //feature
	char *command = new char[200];
	strcpy(command,"./vl_gmm/vlgmm ");
    char *c = new char[20];
    int length = sprintf(c," %d",dimension);
    strcat(command,fileName);
	strcat(command,c);
	cout<<command<<endl;
	system(command);
	delete[] command;
	delete [] c;
}
float* computAndSavePCA(float **data,int DIMENTIONS ,int SAMPLE_NUM, double pcaFactor,int * sizeofResult)
{
	Mat pcaSet(SAMPLE_NUM, DIMENTIONS, CV_32FC1); //原始数据
    for (int i = 0; i < SAMPLE_NUM;i++)
    {
        for (int j = 0; j < DIMENTIONS;j++)
        {
            pcaSet.at<float>(i, j) = data[i][j];
        }
    }
    //cout<<"=============="<<endl;
    PCA pca(pcaSet,Mat(),CV_PCA_DATA_AS_ROW);

    Mat dst = pca.project(pcaSet);//映射新空间,from this new space , find half of elements !!!
    Mat result = dst.colRange(0,DIMENTIONS*pcaFactor);//return dst(:,1:deminsion*factorsize);

	char *filepath = new char [100];
	if(DIMENTIONS == TRJ_DI)
		strcpy(filepath,pcaTrjInfo);
	else if(DIMENTIONS == HOG_DI)
		strcpy(filepath,pcaHogInfo);
	else if(DIMENTIONS == HOF_DI)
		strcpy(filepath,pcaHofInfo);
	else if(DIMENTIONS == MBH_DI)
		strcpy(filepath,pcaMbhInfo);


	Mat eigenvetors_d;
	int index = pcaFactor * DIMENTIONS;
	eigenvetors_d.create(index, DIMENTIONS, CV_32FC1);//eigen values of decreased dimension
	for (int i = 0; i<index; ++i)
	{
		pca.eigenvectors.row(i).copyTo(eigenvetors_d.row(i));
	}
	//cout << "eigenvectors" <<endl << eigenvetors_d << endl;
	FileStorage fs_w(filepath, FileStorage::WRITE);//write mean and eigenvalues into xml file
	fs_w << PCA_MEAN << pca.mean;
	fs_w << PCA_EIGEN_VECTOR << eigenvetors_d;
	fs_w.release();


	//cout<<"done ====================="<<endl;

	float * oneDimResult = new float[int(DIMENTIONS*pcaFactor*SAMPLE_NUM)+1];
	int oneIndex = 0;
	for (int i = 0; i < SAMPLE_NUM;i++) // the reduced dimension  matrix. (pca)
    {
        for (int j = 0; j < DIMENTIONS*pcaFactor;j++)
        {
            oneDimResult[oneIndex++] = result.at<float>(i,j);// index is 0, for interface gmm...getAndSaveGmmModel
        }
    }
	delete[] filepath;
	*sizeofResult = oneIndex;
	return oneDimResult;
}

void selectAllDescriptor(int st,int send,bool *isSelected,float ** trjAll,float ** hogAll,float ** hofAll,float **mbhAll,
	vector<vector<float> > *trj,vector<vector<float> > *hog,vector<vector<float> > *hof,vector<vector<float> > *mbh)
{
	int selectItindex = 0;
	for (size_t j = st; j < send; j++) {
			while(!isSelected[selectItindex])
			{
				selectItindex++;
			}
			for (size_t ti = 0; ti < TRJ_DI; ti++) {
				trjAll[j][ti] = (*trj)[selectItindex][ti];
			}
			for (size_t ti = 0; ti < HOG_DI; ti++) {
				hogAll[j][ti] = (*hog)[selectItindex][ti];
			}
			for (size_t ti = 0; ti < HOF_DI; ti++) {
				hofAll[j][ti] = (*hof)[selectItindex][ti];
			}
			for (size_t ti = 0; ti < MBH_DI; ti++) {
				mbhAll[j][ti] = (*mbh)[selectItindex][ti];
			}
			selectItindex++;
	}
	return;
}

// randomly select lines
void SelectLines(bool* isSelected, int nLines, int nSelects)
{
	srand((unsigned)time(NULL));
	for (int index = 0; index < nLines; index++)
	{
		isSelected[index] = false;
	}
	int value;
	for (int index = 0; index < nSelects; index++)
	{
		do {
			value = (rand() % nLines);
		} while (isSelected[value]);
		isSelected[value] = true;
	}
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

//find interface of gmm for next process.
void getDescriptorFromFile(char *descriptorFileName,vector<vector<float> > *trj,vector<vector<float> > *hog,vector<vector<float> > *hof,vector<vector<float> > *mbh)
{

	printf("%s,%s\n", descriptorFileName,"select function works");
	int nLines = 0;
	max_line_len = 1024;
	iiline = Malloc(char, max_line_len);
	gzFile file = gzopen(descriptorFileName,"r");
	float value;
	vector<float> temp;

	while (ReadLine(file) != NULL)
	{
		//printf("%s\n","readline" );
		int iToken,j;
		char* feature;
		feature = strtok(iiline," \t");
		iToken = 0;
		while(iToken < OBJ_DI-1)
		{
			feature = strtok(NULL," \t"); // get rid of obj and trj
			iToken++;
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
		for (j = 0; j< HOG_DI; j++)
		{
			feature = strtok(NULL," \t");
			value = atof(feature);
			value = sqrt(value);
			temp.push_back(value);
		}
		hog->push_back(temp);
		temp.clear();
		for (j = 0; j < HOF_DI; j++)
		{
			feature = strtok(NULL," \t");
			value = atof(feature);
			value = sqrt(value);
			temp.push_back(value);
		}
		hof->push_back(temp);
		temp.clear();

		for (j = 0; j < MBH_DI; j++)
		{
			feature = strtok(NULL," \t");
			value = atof(feature);
			value = sqrt(value);
			temp.push_back(value);
		}
		mbh->push_back(temp);
	}
	//printf("%s, %d and dimension is ,%d \n","the end of features",(*mbh).size(),(*mbh)[0].size() );
	free(iiline);
	gzclose(file);
}

void saveTrj(vector<vector <float > > *trj,char *fileName)
{
	int size = (*trj).size();
	int dimension = (*trj)[0].size();
	ofstream out(fileName);
	for (int i = 0; i < size; ++i)
	{
		for (int s = 0; s < dimension; ++s)
		{
			out<< (*trj)[i][s]<<" ";
		}
		out<<endl;
	}
	out.close();
	return ;
}

void getGMM(char **fullvideoname,char * vocabsDir, char * descriptor_path)
{

			float **trjAll = new float *[samples];
			float **hogAll = new float *[samples];
			float **hofAll = new float *[samples];
			float **mbhAll = new float *[samples];
			for (int i = 0; i < samples; ++i)
			{
				trjAll[i] = new float[TRJ_DI+1];
				hogAll[i] = new float[HOG_DI+1];
				hofAll[i] = new float[HOF_DI+1];
				mbhAll[i] = new float[MBH_DI+1];
			}

			int st = 0,send=0; //startindex, endindex.
			int num_samples_per_vid = round(samples / num_videos);
			vector<vector<float> > trj;
			vector<vector<float> > hog;
			vector<vector<float> > hof;
			vector<vector<float> > mbh;
			for (int i = 0; i < num_videos; ++i)
			{
				hog.clear();
				hof.clear();
				mbh.clear();
				trj.clear();
				char *descriptorFile = new char[filePathSize];
				strcpy(descriptorFile,descriptor_path);
				strcat(descriptorFile,basename(fullvideoname[i]));
				getDescriptorFromFile(descriptorFile,&trj,&hog,&hof,&mbh);
				int selectSize = trj.size(); //样本总数
				bool *isSelected = new bool[selectSize];
				if(selectSize > num_samples_per_vid)//样本总数大于采样总数
				{
					SelectLines(isSelected,selectSize,num_samples_per_vid);
					send = st + num_samples_per_vid;
				}
				else
				{
					for (int i = 0; i < selectSize; i++) {
						isSelected[i] = 1;
					}
					send = st + selectSize;
				}
				selectAllDescriptor(st,send,isSelected,trjAll,hogAll,hofAll,mbhAll,&trj,&hog,&hof,&mbh);
				st = send;
				delete []isSelected;
				delete []descriptorFile;
			}
			// saveTrj(&trj,"./trj");
			// saveTrj(&mbh,"./mbh");
			//cout<<send<<" is the end of trjAll "<<samples<<" this is samples"<<endl;
			//save the sample feat file. in four indiviual files.
			printf("%s\n", "start computing pca");
			int trjSize = 0;
			int hogSize = 0;
			int hofSize = 0;
			int mbhSize = 0;

			//trjData is reduced trjAll Data.
			float *trjData = computAndSavePCA(trjAll,TRJ_DI,send,pcaFactor,&trjSize);
			float *hogData = computAndSavePCA(hogAll,HOG_DI,send,pcaFactor,&hogSize);
			float *hofData = computAndSavePCA(hofAll,HOF_DI,send,pcaFactor,&hofSize);
			float *mbhData = computAndSavePCA(mbhAll,MBH_DI,send,pcaFactor,&mbhSize);
			// cout<<"trj size is "<<trjSize<<" trjSize/dimension is "<<trjSize/(TRJ_DI*pcaFactor)<<endl;
			// cout<<"hog size is "<<hogSize<<" hogSIze/dimension is "<<hogSize/(HOG_DI*pcaFactor)<<endl;
			// cout<<"hof size is "<<hofSize<<" hofSIze/dimension is "<<hofSize/(HOF_DI*pcaFactor)<<endl;
			// cout<<"mbh size is "<<mbhSize<<" mbhSIze/dimension is "<<mbhSize/(MBH_DI*pcaFactor)<<endl;
            //存储降维后的数据
			saveDatatoFile(trjData,trjSize,reducedPCADataoftrjALL);
			saveDatatoFile(hogData,hogSize,reducedPCADataofhogALL);
			saveDatatoFile(hofData,hofSize,reducedPCADataofhofALL);
			saveDatatoFile(mbhData,mbhSize,reducedPCADataofmbhALL);

            //存储没有降维前的1000000条数据
			saveDatatoFile(trjAll,send,TRJ_DI,sampledtrjFeatureAllData);
			saveDatatoFile(hogAll,send,HOG_DI,sampledhogFeatureAllData);
			saveDatatoFile(hofAll,send,HOF_DI,sampledhofFeatureAllData);
			saveDatatoFile(mbhAll,send,MBH_DI,sampledmbhFeatureAllData);


			delete []trjData;
			delete []hogData;
			delete []hofData;
			delete []mbhData;
			for (int i = 0; i < send; ++i)
			{
				delete [] trjAll[i];
				delete [] hogAll[i];
				delete [] hofAll[i];
				delete [] mbhAll[i];
			}
			delete []trjAll;
			delete []hogAll;
			delete []hofAll;
			delete []mbhAll;

			getAndSaveGmmModel(reducedPCADataoftrjALL,(int)(TRJ_DI*pcaFactor));
			getAndSaveGmmModel(reducedPCADataofhogALL,(int)(HOG_DI*pcaFactor));
			getAndSaveGmmModel(reducedPCADataofhofALL,(int)(HOF_DI*pcaFactor));
			getAndSaveGmmModel(reducedPCADataofmbhALL,(int)(MBH_DI*pcaFactor));

}
#endif
