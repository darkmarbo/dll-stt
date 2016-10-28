
#ifndef  __INTER_LIB_H_
#define  __INTER_LIB_H_

#include "HTS_engine.h"
#include <stdio.h>

#ifdef  MYLIBDLL
#define MYLIBDLL extern "C" _declspec(dllimport)
#else
#define MYLIBDLL extern "C" _declspec(dllexport)
#endif

const int MAX_WAV_SIZE = 100000000;
const int MAX_PATH_SIZE = 1000;
const int LEN_SIL = 300;


class __declspec(dllexport) TTS
{
public:
    TTS();
    ~TTS();

    int init(const char *model_dir);



    int line2short_array(const char *line, short *out, int out_size);
    int lines2short_array(const char *lines, short *out, int out_size);

    int line2wav(const char *line, const char *wav_name);
    int lines2wav(const char *line, const char *wav_name);
    int line2wav_old(const char *line, const char *wav_name);


private:
    HTS_Engine *engine;
    STable *wt, *ct;
    Table *pw, *pp, *ip;

    FILE *fp_log ;

};





#endif  // __INTER_LIB_H_
