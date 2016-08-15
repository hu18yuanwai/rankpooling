//--------------------------------begin--------------------------------
//-----------------------------by Yikun Lin----------------------------
#include "SelectFeatures.h"
char* ReadLine(gzFile gzfp)
{
	int len;
	if(gzgets(gzfp, line, max_line_len) == NULL)
		return NULL;
	while(strrchr(line, '\n') == NULL)
	{

		max_line_len *= 2;
		line = (char*) realloc(line, max_line_len);
		len = (int) strlen(line);
		if(gzgets(gzfp, line + len, max_line_len - len) == NULL)
			break;
	}
	return line;
}

// randomly select lines in a file
// 选中的设置为true
void SelectLines(bool* isSelected, int nLines, int nSelects)
{

	srand((unsigned)time(NULL));
	for (int index = 0; index < nLines; index++)
	{
		isSelected[index] = false;
	}
	int value;
	for (int index = 0; index < nSelects; index++)
	{
		do {
			value = (rand() % nLines);
		} while (isSelected[value]);
		isSelected[value] = true;
	}	
}


bool SelectFeatures(int argc, char** argv)
{
	char* gzName = argv[1];
	char* grFile = argv[2];
	char* ofFile = argv[3];
	char* mbFile = argv[4];
	//open .gz file
	gzFile gzfp = gzopen(gzName, "r");
	std::ofstream grOut(grFile, std::ios::app);
	std::ofstream ofOut(ofFile, std::ios::app);
	std::ofstream mbOut(mbFile, std::ios::app);
	if (!gzfp)
	{
		return false;
	}
	max_line_len = 1024;
	line = Malloc(char, max_line_len);
	int nLines = 0;

	// quantity of trajectories selected to perform k-means
	int nSelects = 0;
	while (ReadLine(gzfp) != NULL)
	{
		nLines++;
	}
	gzrewind(gzfp);

	// decide the quantity of trajectories to choose
	if (nLines <= MINLEN)
	{
		nSelects = nLines;
	}
	else
	{
		nSelects = (int) (MINLEN + (nLines - MINLEN) * ratio);
	}
	bool* isSelected = new bool[nLines];

	SelectLines(isSelected, nLines, nSelects); //随机标记需要取出的那一行Line

	int index = 0;
	int iSelect = 0;
	while (ReadLine(gzfp) != NULL)
	{
		// write selected features to corresponding files
		if (isSelected[index])
		{
			int iToken;
			char* feature;
			/*strtok(line," \t");
			for (iToken = 2; iToken < GR_START; iToken++)
			{
				strtok(NULL," \t");
			}*/
			feature = strtok(line, " \t");
			grOut << feature << "\t";
			for (iToken = GR_START + 1; iToken < GR_START + GR_DI; iToken++)
			{
				feature = strtok(NULL," \t");
				grOut << feature << "\t";
			}
			grOut << std::endl;
			for (iToken = OF_START; iToken < OF_START + OF_DI; iToken++)
			{
				feature = strtok(NULL," \t");
				ofOut << feature << "\t";
			}
			ofOut << std::endl;
			for (iToken = MB_START; iToken < MB_START + MB_DI; iToken++)
			{
				feature = strtok(NULL," \t");
				mbOut << feature << "\t";
			}
			mbOut << std::endl;
			++iSelect;
			if (iSelect >= nSelects)
			{
				break;
			}
		}
		index++;
	}


	delete []isSelected;
	free(line);
	mbOut.close();
	ofOut.close();
	grOut.close();
	//close .gz file
	gzclose(gzfp);
	return true;
}
//---------------------------------end---------------------------------
