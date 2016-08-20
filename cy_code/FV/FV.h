#ifndef _GETFV_
#define _GETFV_
#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <fstream>
#include <vector>
#include <math.h>
#include "generial.h"
using namespace std;
void getFV(char * featDir)
{
	char *fvFilePath = new char[filePathSize];
	char *command = new char[filePathSize];
	// strcpy(command,"mkdir ");
	// strcpy(fvFilePath,featDir);
	// strcat(fvFilePath,"trj");
	// strcat(command,fvFilePath);
	// //cout<<command<<endl;
	// system(command);
	// strcpy(command,"mkdir ");
	// strcpy(fvFilePath,featDir);
	// strcat(fvFilePath,"hog");
	// strcat(command,fvFilePath);
	// //cout<<command<<endl;
	// system(command);
	// strcpy(command,"mkdir ");
	// strcpy(fvFilePath,featDir);
	// strcat(fvFilePath,"hof");
	// strcat(command,fvFilePath);
	// //cout<<command<<endl;
	//system(command);
	strcpy(command,"mkdir ");
	strcpy(fvFilePath,featDir);
	strcat(fvFilePath,"mbh");
	strcat(command,fvFilePath);
	//cout<<command<<endl;
	system(command);
	
	strcpy(command,"mkdir ");
	strcpy(fvFilePath,featDir);
	strcat(fvFilePath,"w");
	strcat(command,fvFilePath);
	//cout<<command<<endl;
	system(command);
	
	strcpy(command,"mkdir ");
	strcpy(fvFilePath,featDir);
	strcat(fvFilePath,"matrix");
	strcat(command,fvFilePath);
	//cout<<command<<endl;
	system(command);

	strcpy(command,"./vl_fisher/vlfisher ");
	cout<<command<<endl;
	system(command);
	delete []fvFilePath;
	delete []command;
}
#endif
