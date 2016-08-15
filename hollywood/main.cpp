#include "genDescriptors.h"
#include "getBOWHistograms.h"
#include "getVideoDarwin.h"

#include <ctype.h>
#include <unistd.h>
#include <algorithm>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <fstream>
#include <iostream>
#include <vector>
#include <list>
#include <string>

char *vocabDir = "~/remote/Data/Vocab";
char *featDir = "~/remote/Data/feats";
char *descriptor_path = "~/remote/Data/descriptor/";

void getConfig(){
}

int main(){
    getConfig();
    genDescriptors(st,send,fullvideoname,descriptor_path);
    getBOWHistograms(fullvideoname,gmm,vocab,st,send,featDir,descriptor_path);
    getVideoDarwin(feats{f},featDir,videoname,0,st,send);
    return 0;
}
