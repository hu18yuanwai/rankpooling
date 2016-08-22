#ifndef TRAINANDTEST_H_
#define TRAINANDTEST_H_
#include "initialize.h"
#include "svm.h"

#define INF HUGE_VAL
struct svm_parameter param;     // set by parse_command_line
struct svm_model* model;
struct svm_problem prob;        // set by read_problem
struct svm_node *x_space;
struct svm_node *x;

static int C[11] = {-5,  -3, -1, 1, 3, 5, 7, 9, 11, 13, 15};
static int cChoice = 11;


void initiateParam();
void readDarWinfromFile(char * fvFilePath, float **data, int index);
void darWinNormalizedL2(float ** Data, int frames, int di);
void trainAndClassify(float **trainData,int Dimen,int **classlabel, int trainNum, float **testData, int testNum);
double CrossValidation(int nFolds);
#endif
