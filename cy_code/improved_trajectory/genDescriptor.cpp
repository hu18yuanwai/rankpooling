#include "genDescriptors.h"
int main(int argc, char const *argv[])
{
	char **fullvideoname = getFullVideoName();
	genDescriptors(st,send,fullvideoname,descriptor_path);
	releaseFullVideoName(fullvideoname);
	return 0;
}