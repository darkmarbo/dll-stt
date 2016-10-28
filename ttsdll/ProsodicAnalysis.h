#ifndef PROSODICANALYSIS_H_INCLUDED
#define PROSODICANALYSIS_H_INCLUDED


int GetWrodPosSegment(char *str,char **words,char **pos,int *nWords);
void ProsodicWordAnalysis(char **wordseq,char **posseq,int nWords,int *result,Table *pwModel);
void ProsodicPhraseAnalysis(char **wordseq,char **posseq,int nWords,int *pwresult,int *result,Table *ppModel,Table *ipModel);
void GetProsodicTag(char **wordseq,int nWords,int *pwresult,int *ppresult,short *tag);

#endif // PROSODICANALYSIS_H_INCLUDED
