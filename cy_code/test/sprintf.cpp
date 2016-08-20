#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <fstream>
using namespace std;

int main(int argc, char const *argv[])
{
	int aa = 30;
    char c[2]; 
    int length = sprintf(c,"%d",aa); 
    cout<<c<<endl; // 0001E
	return 0;
}