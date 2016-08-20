#ifndef _GENDESCRIPTORS_H
#define _GENDESCRIPTORS_H
#include "generial.h"
using namespace std;
static const int _MAX_DRIVE = 20;
static const int _MAX_DIR = 100;
static const int _MAX_FNAME = 30;
static const int _MAX_EXT = 20;

void genDescriptors(int st,int send,char **fullvideoname, char *descriptor_path){
    char drive[_MAX_DRIVE];
    char dir[_MAX_DIR];
    char fname[_MAX_FNAME];
    char ext[_MAX_EXT];
    char *descriptorFile = new char[100];
    char *command = new char[200];
    for (int i = st; i < send; ++i)
    {
        strcpy(descriptorFile,descriptor_path);
        strcat(descriptorFile,basename(fullvideoname[i]));
        cout<<descriptorFile<<endl;
        fstream _file;
     	_file.open(descriptorFile,ios::in);
	    if(_file)
	    {
	    	cout<<"exist"<<descriptorFile<<endl; //feature
	    	cout<<descriptorFile<<endl; //feature
	    }
	    else
	    {
	    	cout<<"extract improved features"<<descriptorFile<<endl; //feature
	    	strcpy(command,"./debug/DenseTrackStab ");
	    	strcat(command,fullvideoname[i]);
	    	strcat(command,".avi | gzip > ");
	    	strcat(command,descriptorFile);
			cout<<command<<endl;
	    	system(command);
	    }
	    _file.close();
    }
    delete []descriptorFile;
    delete []command;
}
#endif
