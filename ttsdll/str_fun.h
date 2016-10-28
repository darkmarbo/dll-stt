
#include <stdio.h>
#include <stdlib.h>
#include "Table.h"


void trimWordTailTagger(char **wordseq, const int nWords);
void getPosTagger(const char *line, int nWords, char **tagseq);
int GetWordSegmentAndPosTagger(char *tline, char **wordseq, char **posseq);


