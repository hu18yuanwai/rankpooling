#include "getGMM.h"
int main(int argc, char const *argv[])
{
	char **fullvideoname = getFullVideoName();
	getGMM(fullvideoname,vocabDir,descriptor_path);
	releaseFullVideoName(fullvideoname);
	return 0;
}