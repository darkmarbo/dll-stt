
#ifndef _VOCODER_SYN_HTS_
#define _VOCODER_SYN_HTS_


void copyData(double *a, double *b, int len);

double maxVal(double *y,int len);

double * LPCSynth(double **lsp, double *lf0, int order, int frameNum,int *len);


#endif
