#include <opencv/cv.h>
#include <opencv/highgui.h>
#include <stdio.h>
#include <stdlib.h>

using namespace cv;
using namespace std;

#define DIMENTIONS	7
#define SAMPLE_NUM	31

float Coordinates_test[DIMENTIONS]={
	104.3,98.7,100.2,116.1,105.2,101.6,102.6
};

#define PCA_MEAN	"mean"
#define PCA_EIGEN_VECTOR	"eigen_vector"
int main()
{

	Mat input(1,DIMENTIONS, CV_32FC1);//Test input
	for (int j=0; j<DIMENTIONS; ++j)
	{
		input.at<float>(0, j) = Coordinates_test[j];
	}
//Encoding
	
	PCA *pca_encoding = new PCA();
	FileStorage fs_r("config.xml", FileStorage::READ);
	fs_r[PCA_MEAN] >> pca_encoding->mean;
	fs_r[PCA_EIGEN_VECTOR] >> pca_encoding->eigenvectors;
	fs_r.release();
	Mat output_encode(1, pca_encoding->eigenvectors.rows, CV_32FC1);
	pca_encoding->project(input, output_encode);
	cout << endl << "pca_encode:" << endl << output_encode;

	delete pca_encoding;
	return 0;
}