#include "genDescriptors.h"

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
