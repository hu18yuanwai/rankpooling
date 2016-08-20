#include <opencv/cv.h>
#include <opencv/highgui.h>
#include <stdio.h>
#include <stdlib.h>
using namespace cv;
using namespace std;
#define DIMENTIONS 4
#define SAMPLE_NUM 8


float Coordinates[DIMENTIONS*SAMPLE_NUM] = {
    -14.8271317103068,-3.00108550936016,1.52090778549498,3.95534842970601,
    -16.2288612441648,-2.80187433749996,-0.410815700402130,1.47546694457079,
    -15.1242838039605,-2.59871263957451,-0.359965674446737,1.34583763509479,
    -15.7031424565913,-2.53005662064257,0.255003254103276,-0.179334985754377,
    -17.7892158910100,-3.32842422986555,0.255791146332054,1.65118282449042,
    -17.8126324036279,-4.09719527953407,-0.879821957489877,-0.196675865428539,
    -14.9958877514765,-3.90753364293621,-0.418298866141441,-0.278063876667954,
    -15.5246706309866,-2.08905845264568,-1.16425848541704,-1.16976057326753};

int main()
{
    Mat pcaSet(SAMPLE_NUM, DIMENTIONS, CV_32FC1); //原始数据
    for (int i = 0; i < SAMPLE_NUM;i++)
    {
        for (int j = 0; j < DIMENTIONS;j++)
        {
            pcaSet.at<float>(i, j) = Coordinates[i*DIMENTIONS + j];
        }
    }
    cout<<pcaSet<<endl;
    cout<<"=============="<<endl;
    PCA pca(pcaSet,Mat(),CV_PCA_DATA_AS_ROW);
    cout << pca.mean;//均值
    cout << endl;

    cout << pca.eigenvalues << endl;//特征值
    cout << endl;

    cout << pca.eigenvectors << endl;//特征向量

    Mat dst = pca.project(pcaSet);//映射新空间,from this new space , find half of elements !!! 
    cout << endl;
    cout << dst;
    cout << endl;

    Mat src = pca.backProject(dst);//反映射回来
    cout << endl;
    cout << src;

} 