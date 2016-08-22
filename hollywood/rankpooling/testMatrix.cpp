#include <iostream>
using namespace std;

int i,j;
float ** getREV(float ** data, int sampleNum, int dimension)
{
  
  float ** rev = new float*[dimension];
  for ( i = 0; i < dimension; ++i)
  {
      rev[i] = new float[sampleNum];
  }
  for ( i = 0; i < sampleNum; ++i)
  {
      for ( j = 0; j < dimension; ++j)
      {
          rev[j][i] = data[i][j];
      }
  }
  return rev;
}
float ** getResult(float ** a ,float **arev, int sampleNum, int dimension)
{
  float **result = new float*[sampleNum];
  for ( i = 0; i < sampleNum; ++i)
  {
      result[i] = new float[sampleNum];
  }
  int i,j,k;
  
  for ( i = 0; i < sampleNum ; ++i)
  {
    for (j = 0; j < sampleNum ; ++j)
    {
      for (k = 0; k < dimension; ++k)
      {
        result[i][j] += a[i][k]*arev[k][j];
      }
    }
  }
  cout<<"the reverse matrixt"<<endl;
  for ( i = 0; i < dimension; ++i)
  {
    for ( j = 0; j < sampleNum; ++j)
    {
        cout<< arev[i][j]<<" ";
    }
    cout<<endl;
  }
 cout<<"the result"<<endl;
  for ( i = 0; i < sampleNum; ++i)
  {
    for ( j = 0; j < sampleNum; ++j)
    {
        cout<< result[i][j]<<" ";
    }
    cout<<endl;
  }
  return result;
}
int main(int argc, char const *argv[])
{
   int dimension = 3;
   int sampleNum = 2;

  float **a = new float*[sampleNum];
  for ( i = 0; i < sampleNum; ++i)
  {
      a[i] = new float[dimension];
  }
  for ( i = 0; i < sampleNum; ++i)
  {
      for ( j = 0; j < dimension; ++j)
      {
          a[i][j] = i+j;
      }
  }
  float ** arev =getREV(a,sampleNum,dimension);
  float ** result = getResult(a,arev,sampleNum,dimension);
  
  return 0;
}
