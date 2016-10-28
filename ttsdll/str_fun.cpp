#include <stdio.h>
#include <stdlib.h>
#include "Table.h"



void trimWordTailTagger(char **wordseq, const int nWords)
{
    int i = 0;
    for(i = 0; i<nWords; i++)
    {
        int j=0;
        while(1)
        {
            if(wordseq[i][j]=='/')
            {
                wordseq[i][j] = 0;
                j = 0;
                break;
            }
            j++;
        }
    }
}


void getPosTagger(const char *line, int nWords, char **tagseq)
{
    int i=0, j=0;
    const char* tmp = line;

    for(; *tmp!=0; tmp++)
    {
        if( *tmp != '/')
        {
            continue;
        }
        tmp++;//skip '/'
        do{
            tagseq[i][j++] = *tmp;
            tmp++;
        }while(*tmp!=' ');

        tagseq[i][j] = 0;
        i++;
        j=0;
    }
}

int GetWordSegmentAndPosTagger(char *tline, char **wordseq, char **posseq){
    int nWords;
    Split(tline,wordseq,&nWords);
    getPosTagger(tline, nWords, posseq);
    trimWordTailTagger(wordseq, nWords);
    return nWords;
}
