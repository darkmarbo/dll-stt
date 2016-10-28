#ifndef CHAR2PINYIN_H_INCLUDED
#define CHAR2PINYIN_H_INCLUDED

#include <vector>
#include <string>


void Char2Pinyin(char **wordseq,char **pinyinseq,int nword,int *npinyin,STable *wt,STable *ct);

int biandiao(const char *input, char *output, int out_size);
int yibu_biandiao(const char *input_word, const char *input_py, char *output, int out_size);

int py_bd(const char *word_seq, char **py_sq, short *ptag, int nChar);
int get_word(const char *word_seq, std::vector<std::string> &vec_word);
/*
input_py: wen4 chuan1 da4 di4 zhen4
*/
int get_py_vec(const char *input_py, std::vector<std::string> &vec_py);

#endif // CHAR2PINYIN_H_INCLUDED
