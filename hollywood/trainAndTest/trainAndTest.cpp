#include "initialize.h"
#include "svm.h"

#define INF HUGE_VAL
//static int (*info)(const char *fmt,...) = &printf;
//void (*print_func)(const char*) = NULL;	// default printing to stdout
//void print_null(const char *s) {}

struct svm_parameter param;     // set by parse_command_line
struct svm_problem prob;        // set by read_problem
struct svm_model* model;
struct svm_node *x_space;
struct svm_node *x;


using namespace std;

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


void readDarWinfromFile(char * fvFilePath, float **data, int index)
{
    ifstream file(fvFilePath);
    int flag = 0;
    for (int i = 0; i < 2*DIMENSION; ++i)
    {
       file >> data[index][i];
       if(data[index][i] != 0)
       {
        flag = 1 ? data[index][i] > 0 : -1;
        data[index][i] =flag * sqrt(fabs(data[index][i]));
       }
    }
    file.close();
    return ;
}

void darWinNormalizedL2(float ** Data, int frames, int di)
{
    float sum = 0;
    for (int i = 0; i < frames; ++i)
    {
        sum = 0;
        for (int j = 0; j < di; ++j)
        {
            sum += fabs(Data[i][j]) *fabs(Data[i][j]);
        }
        sum = sqrt(sum);
        for (int j = 0; j < di; ++j)
        {
            Data[i][j] /= sum;
        }
    }
    return;
}

void trainAndClassify(float **trainData,int Dimen,int **classlabel, int trainNum, float **testData, int testNum)
{
    double  *accuracy = new double[actionType];
    for (int k = 0; k < actionType ; ++k)
    {
        //read_problem
        prob.l = trainNum;
        size_t elements = trainNum*(Dimen+1);

        int  i,j,s ;
        prob.y = Malloc(double,prob.l);
        prob.x = Malloc(struct svm_node *,prob.l);
        x_space = Malloc(struct svm_node,elements);


        j = 0;
        for(i=0;i<prob.l;i++)
        {
            prob.y[i] = classlabel[i][k];
            prob.x[i] = &x_space[j];
            for (int s = 0; s < Dimen; ++s)
            {
                x_space[j].index = s;
                //cout<<trainData[i][s]<<" ";
                x_space[j++].value = trainData[i][s];
            }
            //cout<<endl;
            x_space[j++].index = -1;
        }
        // default values
        param.svm_type = C_SVC;
        param.kernel_type = PRECOMPUTED;
        param.degree = 3;
        param.gamma = 1.0/(Dimen-1);  // 1/num_features !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
        param.coef0 = 0;
        param.nu = 0.5;
        param.cache_size = 100;
        param.C = 100;
        param.eps = 1e-3;
        param.p = 0.1;
        param.shrinking = 1;
        param.probability = 0;
        param.nr_weight = 0;
        param.weight_label = NULL;
        param.weight = NULL;
        //print_func = &print_null;
        //svm_set_print_string_function(print_func);
        //cout<<" before training "<<endl;
        model = svm_train(&prob,&param);
        //cout<<" after training "<<endl;
        int correct = 0;
        int predict_label;
        int total = testNum;
        x = (struct svm_node *) malloc(Dimen*sizeof(struct svm_node));
        for(i=0;i<testNum;i++)
        {
            for ( s = 0; s < Dimen; ++s)
            {
                x[s].index = s;
                x[s].value = testData[i][s];
            }
            x[s].index = -1;
            predict_label = svm_predict(model,x);
            if(predict_label == classlabel[i+823][k]) //need to change ............===============================
                ++correct;
        }
        svm_free_and_destroy_model(&model);
        svm_destroy_param(&param);
        free(prob.y);
        free(prob.x);
        free(x_space);
        free(x);
        double tempaccuracy = (double)correct/total*100;
        accuracy[k] = tempaccuracy;
        //cout<<accuracy[k]<<" is accuracy for action "<<k<<endl;
    }
    char *accuracyFile = "./result.txt";
    ofstream file(accuracyFile);
    double sum = 0;
    for (int i = 0; i < actionType; ++i)
    {
        sum += accuracy[i];
        file << accuracy[i]<<" ";
    }
    file << endl << " The average accuracy is ";
    file << sum/actionType << endl;
    file.close();
    delete []accuracy;
}

int main(int argc, char const *argv[])
{
    char **fullvideoname = getFullVideoName();

    char *wFilePath = new char[filePathSize];
    int darwinDimension = 2 *DIMENSION;
    float ** all_data_cell = new float*[num_videos];
    for (int i = 0; i < num_videos ; ++i)
    {
        all_data_cell[i] = new float[darwinDimension];
    }
    for (int i = 0; i < num_videos ; ++i)
    {
        strcpy(wFilePath,darwin_feature);
        strcat(wFilePath,basename(fullvideoname[i]));
        strcat(wFilePath,"-w");

        readDarWinfromFile(wFilePath,all_data_cell,i);
    }
    max_iline_len = 1024;
    iline = Malloc(char,max_iline_len);

    int ** classid = readLabelFromFile();
    //saveData(classid,"./classid",datasetSize,actionType);
    darWinNormalizedL2(all_data_cell, num_videos, darwinDimension);

    float ** trainData = new float*[trainNum];
    for (int i = 0; i < trainNum; ++i)
    {
        trainData[i] = new float[darwinDimension];
        for (int j = 0; j < darwinDimension; ++j)
        {
            trainData[i][j] = all_data_cell[i][j];
        }
    }

    float ** testData = new float*[testNum];
    for (int i = 0; i < testNum; ++i)
    {
        testData[i] = new float[darwinDimension];
        for (int j = 0; j < darwinDimension; ++j)
        {
            testData[i][j] = all_data_cell[i+trainNum][j];
        }
    }

    for (int i = 0; i < num_videos; ++i)
    {
        delete [] all_data_cell[i];
    }
    delete [] all_data_cell;

    trainAndClassify(trainData,darwinDimension,classid,trainNum, testData, testNum);

    releaseFullVideoName(fullvideoname);

    for (int i = 0; i < trainNum; ++i)
    {
        delete [] trainData[i];
    }
    delete []trainData;

    for (int i = 0; i < trainNum; ++i)
    {
        delete [] testData[i];
    }
    delete []testData;

    delete []wFilePath;
    return 0;
}
