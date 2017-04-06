#include <stdio.h>
#include <stdlib.h>
#include <string>

#include "Vocoder.h"
#include "Table.h"
#include "Char2Pinyin.h"
#include "ProsodicAnalysis.h"
#include "getLabel.h"
#include "str_fun.h"
#include "inter_lib.h"



TTS::TTS()
{
	if (this->engine != NULL)
	{
		delete this->engine;
		this->engine = NULL;
	}

    this->engine = (HTS_Engine *)malloc(sizeof(HTS_Engine));


}

TTS::~TTS()
{
	if (fp_log != NULL)
	{
		fclose(fp_log);
		fp_log = NULL;
	}

	if (engine != NULL)
	{

		free(engine);
		engine = NULL;
	}

	if (wt != NULL)
	{

		delete wt;
		wt = NULL;
	}
	
	if (ct != NULL)
	{
		delete ct;
		ct = NULL;
	}

	if (pw != NULL)
	{
		delete pw;
		pw = NULL;
	}
    
	if (pp != NULL)
	{
		delete pp;
		pp = NULL;
	}
    
	if (ip != NULL)
	{

		delete ip;
		ip = NULL;
	}


}

int TTS::init(const char *model_dir)
{
    fp_log = fopen("yl.log","w");

    //��ѧģ������ļ��Ĵ洢λ��,д���ַ�����
    char *durname = new char[MAX_PATH_SIZE];
    _snprintf(durname, MAX_PATH_SIZE-1, "%s\\model\\dur.pdf", model_dir);
    char *durtreename = new char[MAX_PATH_SIZE];
    _snprintf(durtreename, MAX_PATH_SIZE-1, "%s\\model\\tree-dur.inf", model_dir);
    char *lspname = new char[MAX_PATH_SIZE];
    _snprintf(lspname, MAX_PATH_SIZE-1, "%s\\model\\lsp.pdf", model_dir);
    char *lsptreename = new char[MAX_PATH_SIZE];
    _snprintf(lsptreename, MAX_PATH_SIZE-1, "%s\\model\\tree-lsp.inf", model_dir);
    char *lspwinfn1 = new char[MAX_PATH_SIZE];
    _snprintf(lspwinfn1, MAX_PATH_SIZE-1, "%s\\model\\lsp.win1", model_dir);
    char *lspwinfn2 = new char[MAX_PATH_SIZE];
    _snprintf(lspwinfn2, MAX_PATH_SIZE-1, "%s\\model\\lsp.win2", model_dir);
    char *lspwinfn3 = new char[MAX_PATH_SIZE];
    _snprintf(lspwinfn3, MAX_PATH_SIZE-1, "%s\\model\\lsp.win3", model_dir);

    char **lspwinfn     =   (char**)malloc(3*sizeof(char*));
    lspwinfn[0]         =   lspwinfn1;
    lspwinfn[1]         =   lspwinfn2;
    lspwinfn[2]         =   lspwinfn3;

    char *lf0name = new char[MAX_PATH_SIZE];
    _snprintf(lf0name, MAX_PATH_SIZE-1, "%s\\model\\lf0.pdf", model_dir);
    char *lf0treename = new char[MAX_PATH_SIZE];
    _snprintf(lf0treename, MAX_PATH_SIZE-1, "%s\\model\\tree-lf0.inf", model_dir);
    char *lf0winfn1 = new char[MAX_PATH_SIZE];
    _snprintf(lf0winfn1, MAX_PATH_SIZE-1, "%s\\model\\lf0.win1", model_dir);
    char *lf0winfn2 = new char[MAX_PATH_SIZE];
    _snprintf(lf0winfn2, MAX_PATH_SIZE-1, "%s\\model\\lf0.win2", model_dir);
    char *lf0winfn3 = new char[MAX_PATH_SIZE];
    _snprintf(lf0winfn3, MAX_PATH_SIZE-1, "%s\\model\\lf0.win3", model_dir);

    char **lf0winfn     =   (char**)malloc(3*sizeof(char*));
    lf0winfn[0]         =   lf0winfn1;
    lf0winfn[1]         =   lf0winfn2;
    lf0winfn[2]         =   lf0winfn3;

    HTS_Engine_initialize(engine, 2);
    HTS_Engine_set_sampling_rate(engine, 16000);  //���ò�����
    HTS_Engine_set_log_gain(engine, FALSE);       //�Ƿ���ö�������
    HTS_Engine_set_fperiod(engine, 80);           //֡�Ƴ�ʼ��
    HTS_Engine_set_msd_threshold(engine, 1, 0.5);  //����msd����

    HTS_Engine_load_duration_from_fn(engine, &durname, &durtreename, 1);

    HTS_Engine_load_parameter_from_fn(engine, &lspname, &lsptreename, lspwinfn, 0, FALSE, 3, 1);
    
    HTS_Engine_load_parameter_from_fn(engine, &lf0name, &lf0treename, lf0winfn, 1, TRUE, 3, 1);
    free(lf0winfn);

    //���ɴʡ����ɶ���������ģ��
    char *wm = new char[MAX_PATH_SIZE];
    _snprintf(wm, MAX_PATH_SIZE-1, "%s/resource/ProsodicWordModel.txt", model_dir);
    pw= ReadTable(wm);   //���ɴ�

    char *ppm = new char[MAX_PATH_SIZE];
    _snprintf(ppm, MAX_PATH_SIZE-1, "%s/resource/ProsodicPhraseModel.txt", model_dir);
    pp= ReadTable(ppm);  //���ɶ���

    char *ipm = new char[MAX_PATH_SIZE];
    _snprintf(ipm, MAX_PATH_SIZE-1, "%s/resource/IntPhraseModel.txt", model_dir);
    ip= ReadTable(ipm);       //�������

    char *dict = new char[MAX_PATH_SIZE];
    _snprintf(dict, MAX_PATH_SIZE-1, "%s/resource/dict.txt", model_dir);
    wt = ReadSTable(dict);   //�ֵ�

    char *c2p = new char[MAX_PATH_SIZE];
    _snprintf(c2p, MAX_PATH_SIZE-1, "%s/resource/char2pinyin.txt", model_dir);
    ct = ReadSTable(c2p);  //�������ձ�

    TTS_Label_Init(); //��ʼ��Labelģ��

	
	if (durname != NULL)
	{
		delete durname;
		durname = NULL;
	}
	if (durtreename != NULL)
	{
		delete durtreename;
		durtreename = NULL;
	}
	if (lspname != NULL)
	{
		delete lspname;
		lspname = NULL;
	}
	if (lsptreename != NULL)
	{
		delete lsptreename;
		lsptreename = NULL;
	}
	if (lspwinfn1 != NULL)
	{
		delete lspwinfn1;
		lspwinfn1 = NULL;
	}
	if (lspwinfn2 != NULL)
	{
		delete lspwinfn2;
		lspwinfn2 = NULL;
	}
	if (lspwinfn3 != NULL)
	{
		delete lspwinfn3;
		lspwinfn3 = NULL;
	}
	if (lspwinfn != NULL)
	{
		delete[]lspwinfn;
		lspwinfn = NULL;
	}
	

    return 0;
}

int TTS::line2short_array(const char *line, short *out, int out_size)
{

    if(line == NULL || out == NULL || out_size < 1)
    {
        printf("line==NULL || out == NULL || out_size < 1\n");
        return -1;
    }
	int ret = 0;
	const int MAX_LINE_SIZE = 10000;
    char tline[MAX_LINE_SIZE]={0};
    _snprintf(tline, MAX_LINE_SIZE, "%s", line);
    dropReturnTag(tline);
	fprintf(fp_log, "tline=%s\n",tline);
	fflush(fp_log);
	if (strlen(tline) == 0)
	{
		return 0;
	}

    int len, i, msd_frame, nWord, nChar;
    short temp;
    double *gen, *lf0;

    lf0 = (double*)malloc(sizeof(double) * 20000);
    TtsLabelCharInfo *cif   =   (TtsLabelCharInfo *)malloc(sizeof(TtsLabelCharInfo)*300);


    int *pwr,*ppr;
    short *ptag;
    char *teof;
    pwr =   (int *)malloc(sizeof(int)*60);
    ppr =   (int *)malloc(sizeof(int)*60);
    ptag=   (short *)malloc(sizeof(short)*60);

    char **wordseq, **posseq, **pinyinseq;
    wordseq     =   (char**)malloc(sizeof(char *)*150);
    posseq      =   (char**)malloc(sizeof(char *)*150);
    pinyinseq   =   (char**)malloc(sizeof(char *)*150);
    for(i=0; i<150; i++)
    {
        wordseq[i]  =   (char *)malloc(sizeof(char)*300);  //�������У�ÿһ��wordseq[i]�洢һ������
        posseq[i]   =   (char *)malloc(sizeof(char)*300);   //��������
        pinyinseq[i]=   (char *)malloc(sizeof(char)*300); //����ת����õ���ƴ������
    }


    TTS_Label_Init(); //��ʼ��Labelģ��
	fprintf(fp_log, "TTS_Label_Init ok!\n");
	fflush(fp_log);

    nWord = GetWordSegmentAndPosTagger(tline,wordseq,posseq);
	fprintf(fp_log, "GetWordSegmentAndPosTagger ok!\n");
	fprintf(fp_log, "\nnWord=%d\n", nWord);
	for (i = 0; i<nWord; i++)
	{
		fprintf(fp_log, "%s/%s ", wordseq[i], posseq[i]);
	}
	fflush(fp_log);

    ProsodicWordAnalysis(wordseq, posseq, nWord, pwr, pw);  //���ɴʷ���    �õ�pwr
    ProsodicPhraseAnalysis(wordseq, posseq, nWord, pwr, ppr, pp, ip); //һ�����������ɶ���   �õ�ppr

    GetProsodicTag(wordseq, nWord, pwr, ppr, ptag);     // ͨ�� pwr��ppr �õ�ÿ��pinyin��Ӧ��ptagֵ
    //ͳһת����ʽ������ptag��ptag����1��2��3 �ֱ��ʾ���ɴ�β�������϶�β��һ���϶�β 0��ʾ�����ɴ�β
	fprintf(fp_log, "GetProsodicTag ok!\n");
	fflush(fp_log);

    //����ת��
    Char2Pinyin(wordseq, pinyinseq, nWord, &nChar, wt, ct);
	fprintf(fp_log, "Char2Pinyin ok!\n");
	fprintf(fp_log, "\nnChar=%d\n", nChar);
	for (i = 0; i<nChar; i++)
	{
		fprintf(fp_log, "pinyinseq[%d]:%s\t", i, pinyinseq[i]);
		fprintf(fp_log, "ptag[%d]     :%d\n", i, ptag[i]);

	}
	fflush(fp_log);

    //��������ת����Ϣ��������Ϣ������ÿ���ֵ�������Ϣ����д��cif
	/*
	fprintf(fp_log, "\nwt_Nodes=%d\n", wt->nNodes);
	for (i = 0; i<wt->nNodes; i++)
	{
		fprintf(fp_log, "%s/\t%s\n", wt->tn[i].key, wt->tn[i].str);
	}
	fprintf(fp_log, "\nct_Nodes=%d\n", ct->nNodes);
	for (i = 0; i<ct->nNodes; i++)
	{
		fprintf(fp_log, "%s/\t%s\n", ct->tn[i].key, ct->tn[i].str);
	}
	*/

	char word_seq_temp[1000] = { 0 };
	for (i = 0; i < nWord; i++)
	{
		strcat(word_seq_temp, wordseq[i]);
	}

	ret = py_bd(word_seq_temp, pinyinseq, ptag, nChar);
	if (ret < 0)
	{	
		fprintf(fp_log, "py_bd error!!!!!!! ret %d\n",ret);
		fflush(fp_log);
	}

	fprintf(fp_log, "py_bd is over !\n");
	fprintf(fp_log, "\nnChar=%d\n", nChar);
	for (i = 0; i<nChar; i++)
	{
		fprintf(fp_log, "pinyinseq[%d]:%s\t", i, pinyinseq[i]);
		fprintf(fp_log, "ptag[%d]     :%d\n", i, ptag[i]);	
		
	}
	fflush(fp_log);

    TtsLabel_ObtainLabelCharSeq(cif, pinyinseq, nChar, ptag);
	fprintf(fp_log, "TtsLabel_ObtainLabelCharSeq ok!\n");
	fflush(fp_log);

    //��ӡ����׼HTS��ʽlabel�ļ�����д��label.txt
    PrintLabel(cif, nChar, "./label.txt");
	fprintf(fp_log, "PrintLabel ok!\n");
	fflush(fp_log);

    //�������������Ϣ����������Ա����
    for(i=0;i<nWord;i++)
    {
        fprintf(fp_log, "%s", wordseq[i]);
        if(ppr[i]==1)
        {
            fprintf(fp_log, "|");
        }
        if(ppr[i]==2)
        {
            fprintf(fp_log,"$");
        }
            else if(pwr[i]==1){
                fprintf(fp_log, " ");
        }
        fflush(fp_log);
    }
    fprintf(fp_log, "\n\n");
	fflush(fp_log);


   //����HTS����״̬
    HTS_Engine_refresh(engine);

    //���HTS����label�ļ���
    HTS_Engine_load_label_from_fn(engine, "./label.txt");

    //�����滮����
    HTS_Engine_create_sstream(engine);
    HTS_Engine_create_pstream(engine);

    for(i=0,msd_frame=0; i<engine->pss.total_frame; i++)
    {
        if ( engine->pss.pstream[1].msd_flag[i] )
        {
            lf0[i] = engine->pss.pstream[1].par[msd_frame][0];
            msd_frame++;
        }
        else
        {
            lf0[i]=0;
        }
    }

    //�ϳɹ���
    gen = LPCSynth(engine->pss.pstream[0].par+5, lf0+5,
        engine->pss.pstream[0].static_length-1, engine->pss.total_frame-5, &len);
	fprintf(fp_log, "LPCSynth ok!\n");
	fflush(fp_log);

	// �� gen������456�������� ���� 
    short short0 = 0;
    for(i=0; i<len-456; i++)
    {
        temp = (short)(gen[i]*32700);
        if(i < out_size)
        {
            out[i] = temp;
        }
        else
        {
            printf("out size too small!\n");
            return -1;
        }
    }

	// out���� LEN_SIL=300�������� ���Ͼ��� 
	for (i = 0; i<LEN_SIL; i++)
    {
        if(i+len-456 < out_size)
        {
            out[i+len-456] = short0;
        }
        else
        {
            printf("out size too small!\n");
            return -1;
        }

    }
	/*
    free(gen);
	if (gen != NULL)
	{
		free(gen);
		gen = NULL;
	}
	if (lf0 != NULL)
	{
		free(lf0);
		lf0 = NULL;
	}
	if (cif != NULL)
	{
		free(cif);
		cif = NULL;
	}

	if (pwr != NULL)
	{
		free(pwr);
		pwr = NULL;
	}
	if (ppr != NULL)
	{
		free(ppr);
		ppr = NULL;
	}
	if (ptag != NULL)
	{
		free(ptag);
		ptag = NULL;
	}
	for (i = 0; i<150; i++)
	{
		free(wordseq[i]); 
		free(posseq[i]);
		free(pinyinseq[i]);
	}
	free (wordseq);
	free(posseq);
	free(pinyinseq);
	*/

	return len - 456 + LEN_SIL;

}

int TTS::lines2short_array(const char *lines, short *out, int out_size)
{


    int pos = 0;
    int size_wav = 0;
    int size_tmp = 0;
    short *p_out = out;

    printf("###lines:%s###",lines);
    std::string str_lines(lines);
    std::string line;


    pos = str_lines.find_first_of("\n\r");
    while(pos >= 0)
    {
        line = str_lines.substr(0,pos);
        printf("inline:%s:::",line.c_str());

        size_tmp = line2short_array(line.c_str(), p_out, MAX_WAV_SIZE-size_wav);
        if(size_tmp < 0)
        {
            printf("line2short_array error!\n");\
            return -1;
        }
        size_wav += size_tmp;
        p_out += size_tmp;

        str_lines = str_lines.substr(pos+1);
        pos = str_lines.find_first_of("\n\r");
    }

    line =  str_lines;
    if(line.length() >= 2)
    {
        printf("lastline:%s:::", line.c_str());

        size_tmp = line2short_array(line.c_str(), p_out, MAX_WAV_SIZE-size_wav);
        if(size_tmp <= 0)
        {
            printf("line2short_array error!\n");
            return -1;
        }
        size_wav += size_tmp;
        p_out += size_tmp;
    }

    return size_wav;
}

int TTS::lines2wav(const char *line, const char *wav_name)
{


    int size_wav;
    short *out = new short[MAX_WAV_SIZE];
    FILE * fp_wav = fopen(wav_name,"wb"); //������д�룬���ڴ洢�ϳɵ�����

    size_wav = lines2short_array(line, out, MAX_WAV_SIZE);
    if(size_wav <= 0)
    {
        printf("lines2short_array error!\n");
        return -1;
    }

    //printf("wav_size = %d\n",size_wav);

    for(int i=0; i<size_wav; i++)
    {

        fwrite(&out[i], sizeof(short), 1, fp_wav);
    }

    fclose(fp_wav);
    delete out;

    return 0;

}

int TTS::line2wav(const char *line, const char *wav_name)
{


    int size_wav;
    short *out = new short[MAX_WAV_SIZE];
    FILE * fp_wav = fopen(wav_name,"wb"); //������д�룬���ڴ洢�ϳɵ�����

    size_wav = line2short_array(line, out, MAX_WAV_SIZE);
    if(size_wav <= 0)
    {
        printf("line2short_array error!\n");
        return -1;
    }

    //printf("wav_size = %d\n",size_wav);

    for(int i=0; i<size_wav; i++)
    {

        fwrite(&out[i], sizeof(short), 1, fp_wav);
    }

    fclose(fp_wav);

    delete out;

    return 0;

}


int TTS::line2wav_old(const char *line, const char *wav_name)
{

    FILE * fp_wav = fopen(wav_name,"wb"); //������д�룬���ڴ洢�ϳɵ�����

    char tline[1024]={0};
    _snprintf(tline, 1023, "%s", line);
    dropReturnTag(tline);

    int len, i, msd_frame, nWord, nChar;
    short temp;
    double *gen,*lf0;

    lf0 = (double*)malloc(sizeof(double) * 20000);
    TtsLabelCharInfo *cif   =   (TtsLabelCharInfo *)malloc(sizeof(TtsLabelCharInfo)*300);


    int *pwr,*ppr;
    short *ptag;
    char *teof;
    pwr =   (int *)malloc(sizeof(int)*60);
    ppr =   (int *)malloc(sizeof(int)*60);
    ptag=   (short *)malloc(sizeof(short)*60);

    char **wordseq, **posseq, **pinyinseq;
    wordseq     =   (char**)malloc(sizeof(char *)*150);
    posseq      =   (char**)malloc(sizeof(char *)*150);
    pinyinseq   =   (char**)malloc(sizeof(char *)*150);
    for(i=0; i<150; i++)
    {
        wordseq[i]  =   (char *)malloc(sizeof(char)*30);  //�������У�ÿһ��wordseq[i]�洢һ������
        posseq[i]   =   (char *)malloc(sizeof(char)*30);   //��������
        pinyinseq[i]=   (char *)malloc(sizeof(char)*30); //����ת����õ���ƴ������
    }


    TTS_Label_Init(); //��ʼ��Labelģ��

    nWord = GetWordSegmentAndPosTagger(tline,wordseq,posseq);

    ProsodicWordAnalysis(wordseq, posseq, nWord, pwr, pw);  //���ɴʷ���
    ProsodicPhraseAnalysis(wordseq, posseq, nWord, pwr, ppr, pp, ip); //һ�����������ɶ���

    GetProsodicTag(wordseq, nWord, pwr, ppr, ptag);
    //ͳһת����ʽ������ptag��ptag����1��2��3 �ֱ��ʾ���ɴ�β�������϶�β��һ���϶�β
    //0��ʾ�����ɴ�β


    //����ת��
    Char2Pinyin(wordseq, pinyinseq, nWord, &nChar, wt, ct);

    //��������ת����Ϣ��������Ϣ������ÿ���ֵ�������Ϣ����д��cif
    TtsLabel_ObtainLabelCharSeq(cif, pinyinseq, nChar, ptag);

    //��ӡ����׼HTS��ʽlabel�ļ�����д��label.txt
    PrintLabel(cif, nChar, "./label.txt");

   //����HTS����״̬
    HTS_Engine_refresh(engine);

    //���HTS����label�ļ���
    HTS_Engine_load_label_from_fn(engine, "./label.txt");

    //�����滮����
    HTS_Engine_create_sstream(engine);
    HTS_Engine_create_pstream(engine);

    for(i=0,msd_frame=0; i<engine->pss.total_frame; i++)
    {
        if ( engine->pss.pstream[1].msd_flag[i] )
        {
            lf0[i] = engine->pss.pstream[1].par[msd_frame][0];
            msd_frame++;
        }
        else
        {
            lf0[i]=0;
        }
    }

    //�ϳɹ���
    gen = LPCSynth(engine->pss.pstream[0].par+5, lf0+5,
        engine->pss.pstream[0].static_length-1, engine->pss.total_frame-5, &len);

    for(i=0; i<len-456; i++)
    {
        temp = (short)(gen[i]*32700);
        fwrite(&temp,sizeof(short),1,fp_wav);
    }

	for (i = 0; i<LEN_SIL; i++)
    {
        fwrite((short)0, sizeof(short), 1, fp_wav);
    }

    fclose(fp_wav);
    free(gen);
    free(lf0);

    return 0;

}

