#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <fstream>
#include <vector>
#include <string.h>
#include <set>
#include <iterator>
#include <algorithm>
#include <math.h>
#include "generial.h"
#include "linear.h"

#define INF HUGE_VAL
#define Malloc(type,n) (type *)malloc((n)*sizeof(type))

struct feature_node *x_space;
struct parameter param;
struct problem prob;
struct model* model_;

using namespace std;

float **getNonLinearity(float ** Data , int frames)
{
    int sign = 1;
     for (int i = 0; i < frames; ++i)
    {
        for (int j = 0; j < DIMENSION; ++j)
        {
            if(Data[i][j] != 0 )
            {
               sign = Data[i][j] > 0 ? 1:-1;
               Data[i][j] = sign * sqrt(fabs(Data[i][j]));
            }
        }
    }
    return Data;
}
void printData(float **Data,int frames)
{
    for (int i = 0; i < frames; ++i)
    {
        for (int j = 0; j < DIMENSION; ++j)
        {
            if(Data[i][j] != 0 )
            {
               cout<<Data[i][j]<<" ";
            }
        }
        cout<<endl;
    }
}
float **normalizedL2(float ** Data, int frames)
{
    float sum = 0;
    for (int i = 0; i < frames; ++i)
    {
        sum = 0;
        for (int j = 0; j < DIMENSION; ++j)
        {
            sum += fabs(Data[i][j]) *fabs(Data[i][j]);
        }
        sum = sqrt(sum);
        for (int j = 0; j < DIMENSION; ++j)
        {
            Data[i][j] /= sum;
        }
    }
    return Data;
}


void saveData(int ** Data,char *filename,int frames, const int dim)
{
    ofstream file(filename);

    for (int i = 0; i < frames; ++i)
    {
        for (int j = 0; j < dim; ++j)
        {
            file<<Data[i][j]<<" ";
        }
        file<<endl;
    }
    file.close();
}
void saveData(float ** Data,int frames)
{
    ofstream file("./data");
     for (int i = 0; i < frames; ++i)
    {
        for (int j = 0; j < DIMENSION; ++j)
        {
            if(Data[i][j] != 0 )
            {
               file<<Data[i][j]<<" ";
            }
        }
        file<<endl;
    }
    file.close();
}
void saveResult(float * w_fow,float *w_ref,char *filename)
{
    //cout<<filename<<endl;
    ofstream file(filename);
    for (int j = 0; j < DIMENSION; ++j)
    {
           file<<w_fow[j]<<" ";
    }
    for (int j = 0; j < DIMENSION; ++j)
    {
           file<<w_ref[j]<<" ";
    }
    file<<endl;
    file.close();
}
float * liblineaqrsvr(float ** Data,int frames)
{
    Data = normalizedL2(Data,frames);
    //printData(Data,frames);
    float *result = new float[DIMENSION];
    for (int i = 0; i < DIMENSION; ++i)
    {
        result[i] = 0;
    }
    double *label = new double[frames];
    for (int i = 0; i < frames; ++i)
    {
        label[i] = i+1;
    }
    int max_index, inst_max_index, i;
    size_t  j;

    prob.l = frames;
    size_t elements = frames*(DIMENSION+1);
    prob.y = Malloc(double,prob.l);
    prob.x = Malloc(struct feature_node *,prob.l);
    x_space = Malloc(struct feature_node,elements+prob.l);
    //saveData(Data,frames);

    max_index = 0;
    j=0;
    for(i=0;i<frames;i++)
    {
        inst_max_index = 0; // strtol gives 0 if wrong format
        prob.y[i] = label[i];
        prob.x[i] = &x_space[j];
        for (int s = 0; s < DIMENSION; ++s)
        {
            x_space[j].index = s+1;
            x_space[j++].value = Data[i][s];
        }
        //cout<<" j is "<<j<<endl;
        x_space[j++].index = -1;
    }
    prob.n=DIMENSION;


    // default values
    param.solver_type = L2R_L2LOSS_SVC_DUAL;
    param.C = 1;
    param.eps = INF; // see setting below
    param.p = 0.1;
    param.nr_weight = 0;
    param.weight_label = NULL;
    param.weight = NULL;
    param.init_sol = NULL;
    param.solver_type = L2R_L2LOSS_SVR;
    param.C = 1.0f;
    param.eps = 0.001;
    print_func = &print_null;
    set_print_string_function(print_func);
    model_=train(&prob, &param);
    for(int i=0; i<DIMENSION; i++)
    {
        result[i] =  model_->w[i];
    }
    destroy_param(&param);
    free_and_destroy_model(&model_);
    free(prob.y);
    free(prob.x);
    free(x_space);
    return result;
}


void getDarwin(char * wFilePath,float **data, int frames)
{
    float **Data  = new float*[frames];
    float *columnSum  = new float[DIMENSION];
    for (int i = 0; i < DIMENSION; ++i)
    {
        columnSum[i] = 0;
    }
    for (int i = 0; i < frames; ++i)
    {
        Data[i] = new float[DIMENSION];
        for (int j = 0; j < DIMENSION; ++j)
        {
            columnSum[j] += data[i][j];
            Data[i][j] = columnSum[j]/(i+1);
        }
    }
    float *w_fow = liblineaqrsvr(getNonLinearity(Data,frames),frames);
    for (int i = 0; i < DIMENSION; ++i)
    {
        columnSum[i] = 0;
    }
    for (int i = 0; i < frames; ++i)
    {
        for (int j = 0; j < DIMENSION; ++j)
        {
            columnSum[j] += data[frames-i-1][j];
            Data[i][j] = columnSum[j]/(i+1);
        }
    }
    float *w_ref = liblineaqrsvr(getNonLinearity(Data,frames),frames);
    saveResult(w_fow,w_ref,wFilePath);
    delete columnSum;
    for (int i = 0; i < frames; ++i)
    {
        delete [] Data[i];
    }
    delete []Data;
    delete w_fow;
    delete w_ref;
}
void readFVfromFile(char * fvFilePath, float **data, int SAMPLENUM)
{
    ifstream file(fvFilePath);
    for (int i = 0; i < SAMPLENUM; ++i)
    {
        for (int j = 0; j < DIMENSION; ++j)
        {
            file >> data[i][j];
        }
    }
    file.close();
    return ;
}

int main(int argc, char const *argv[])
{
    char **fullvideoname = getFullVideoName();

    char *wFilePath = new char[100]; 
   
    char *fvFilePath = new char[100];

    int i;
    for ( i = st; i < send ; ++i)
    {
        // read fv file to get Origin Data
        strcpy(fvFilePath,feature_out);
        strcat(fvFilePath,basename(fullvideoname[i]));
        strcat(fvFilePath,"-fv");

        strcpy(wFilePath,darwin_feature);
        strcat(wFilePath,basename(fullvideoname[i]));
        strcat(wFilePath,"-w");

        cout<<fvFilePath<<endl;
        int frames = readLineFromFile(fvFilePath);
        float ** data = new float*[frames];
        //cout<<frames<<" is its lines"<<endl;
        for (int s = 0; s < frames; ++s)
        {
            data[s] = new float[DIMENSION];
        }
        readFVfromFile(fvFilePath,data,frames);
        // use getDarwin() funciton to get w Data
        getDarwin(wFilePath,data,frames);
        // save w Data;
        for (int s = 0; s < frames; ++s)
        {
            delete [] data[s] ;
        }
        delete []data;
    }
    delete []fvFilePath;
    delete []wFilePath;
    releaseFullVideoName(fullvideoname);
    return 0;
}