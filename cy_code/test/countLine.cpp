#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <fstream>
#include <string.h>

#define Malloc(type,n) (type *)malloc((n)*sizeof(type))

static char* line = NULL;
static int max_line_len;
using namespace std;
char* readline(FILE *input)
{
	int len;
	
	if(fgets(line,max_line_len,input) == NULL)
		return NULL;

	while(strrchr(line,'\n') == NULL)
	{
		max_line_len *= 2;
		line = (char *) realloc(line,max_line_len);
		len = (int) strlen(line);
		if(fgets(line+len,max_line_len-len,input) == NULL)
			break;
	}
	return line;
}

void  countLine(const char* fileName )
{
	FILE *fp = fopen(fileName,"r");
	if(fp == NULL)
	{
		fprintf(stderr,"can't open input file %s\n",fileName);
		exit(1);
	}
	max_line_len = 1024;
	line = Malloc(char,max_line_len);
	int len = 0;
	while(readline(fp)!=NULL)
	{
		len++;
	}
	std::cout << len << std::endl;
	fclose(fp);

}
int main(int argc, char const *argv[])
{
	countLine(argv[1]);
	return 0;
}