#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<vector>

#include"Table.h"
#include "Char2Pinyin.h"

const int MAX_PY_LEN = 600;



void Word2Pinyin(char *word, char *buf, STable *ct)
{
    int len;
    int i = 0;
    char ch[3];
    char *temp;

    len = strlen(word);
    buf[0]=0;


    while(i<len) // ÿһ���ֽ�
    {
        if(*(word+i) & 0x80 && i+1<len) // ˫�ֽ�
        {
            ch[0] = word[i];
            ch[1] = word[i+1];
            ch[2]=0;
            temp = GetSTableValue(ct,ch);
            if(temp != NULL)
            {
                strcat(buf,temp);
                strcat(buf," ");
            }
            else
            {
                // δ֪������
                strcat(buf,"e5 ");
            }
            i += 2;
        }
        else
        {
            ch[0] = word[i];
            ch[1] = 0;

            temp = GetSTableValue(ct, ch);
            if(temp != NULL)
            {
                strcat(buf,temp);
                strcat(buf," ");
            }
            else
            {
                // δ֪������
                //strcat(buf,"e5 ");
            }

            i++;
        }
    }
}

/*
void Word2Pinyin(char *word, char *buf, STable *ct)
{
    int len;
    int i;
    char ch[3];
    char *temp;
    len=strlen(word)/2;
    buf[0]=0;
    ch[2]=0;

    for(i=0;i<len;i++)
    {
        ch[0]=word[i*2];
        ch[1]=word[i*2+1];
        temp=GetSTableValue(ct,ch);
        if(temp!=NULL){
            strcat(buf,temp);
            strcat(buf," ");
        }
        // δ֪������
        else{
            strcat(buf,"e5 ");
        }
    }
}
*/

void Char2Pinyin(char **wordseq, char **pinyinseq, int nword, int *npinyin, STable *wt, STable *ct)
{
	int ret = 0;
	char *temp, temp2[MAX_PY_LEN];
    static char *buf=NULL;
    if(buf==NULL)
    {
        buf=(char *)malloc(sizeof(char)*MAX_PY_LEN);
    }
    buf[0]=0;
    int i;

    for(i=0;i<nword;i++)
    {
        // ÿһ����
        temp = GetSTableValue(wt, wordseq[i]);
        if(temp != NULL) // �ҵ�������
        {
			char biandiao_33[MAX_PY_LEN];
			memset(biandiao_33, MAX_PY_LEN, 0);
			char biandiao_yibu[MAX_PY_LEN];
			memset(biandiao_yibu, MAX_PY_LEN, 0);
			
			//strcat(buf, temp);

			biandiao(temp, biandiao_33, MAX_PY_LEN);

			//strcat(buf, biandiao_33);
			
			ret = yibu_biandiao(wordseq[i], biandiao_33, biandiao_yibu, MAX_PY_LEN);
			/*
			if (ret < 0)
			{
				if (ret == -1)strcat(buf, "cuo1 ");
				if (ret == -2)strcat(buf, "cuo2 ");
				if (ret == -3)strcat(buf, "cuo3 ");
				if (ret == -4)strcat(buf, "cuo3 ");
			} */
			strcat(buf, biandiao_yibu);

            strcat(buf, " ");
            continue;
        }

        // û���ҵ������
        Word2Pinyin(wordseq[i], temp2, ct);

		char biandiao_33[MAX_PY_LEN];
		memset(biandiao_33, MAX_PY_LEN, 0);
		char biandiao_yibu[MAX_PY_LEN];
		memset(biandiao_yibu, MAX_PY_LEN, 0);
        
		//strcat(buf, temp2);

		biandiao(temp2, biandiao_33, MAX_PY_LEN);
		
		//strcat(buf, biandiao_33);

		yibu_biandiao(wordseq[i], biandiao_33, biandiao_yibu, MAX_PY_LEN);
		strcat(buf, biandiao_yibu);
    }

    Split(buf, pinyinseq, npinyin);
}

int get_word(const char *word_seq, std::vector<std::string> &vec_word)
{
	char word_temp[MAX_PY_LEN] = { 0 };
	int len_word = 0;
	int ii = 0;
	
	vec_word.clear();

	if (word_seq == NULL || strlen(word_seq)== 0 )
	{
		return -1;
	}
	

	// ��ȡÿһ���֣�
	_snprintf(word_temp, MAX_PY_LEN, "%s", word_seq);
	len_word = strlen(word_temp);
	while (ii < len_word)
	{
		if (word_temp[ii] & 0x80) // ����
		{
			char word[3];
			_snprintf(word, 3, "%s", word_temp + ii);
			word[2] = '\0';
			vec_word.push_back(word);
			ii += 2;
		}
		else // abc
		{
			char word[2];
			_snprintf(word, 2, "%s", word_temp + ii);
			word[1] = '\0';
			vec_word.push_back(word);
			ii++;
		}
	}
	return 0;
}

/*
input_py: wen4 chuan1 da4 di4 zhen4 
*/
int get_py_vec(const char *input_py, std::vector<std::string> &vec_py)
{
	char input_py_temp[MAX_PY_LEN] = { 0 };
	char *temp = NULL;
	vec_py.clear();
	
	if (input_py == NULL || strlen(input_py) == 0)
	{
		return -1;
	}

	// ��ȡÿһ��ƴ�� 
	_snprintf(input_py_temp, MAX_PY_LEN, "%s", input_py);
	temp = strtok(input_py_temp, " ");
	while (temp != NULL )
	{
		if (strlen(temp) != 0 )
		{
			vec_py.push_back(temp);
		}
		temp = strtok(NULL, " ");
	}
	return 0;
}
/*
// nChar ��pinyin��ptag    150����300
//word_seq: �봨����δ������һ��ǳԴ����
// pinyin: wen4 chuan1 de1 zhe4 ci4 da4 di4 zhen4  shi4 yi1 ci4 qian3 yuan2 di4 zhen4 
// ptag:   0      0     2   0    2   0   0    2      1   0   2    0     1     0    4
*/
int py_bd(const char *word_seq, char **py_sq, short *ptag, int nChar)
{
	int ii = 0;
	int ret = 0;
	int flag_0 = 0;  // ǰ���Ƿ���� 0 
	int left_ii = -1; // ��ʾ���û�� 0 ��λ��
	char py_temp[MAX_PY_LEN] = {0};
	std::vector<std::string> vec_word;
	char word_temp[MAX_PY_LEN] = { 0 };
	

	// ��ȡÿһ���֣�
	ret = get_word(word_seq, vec_word);
	if (vec_word.size() != nChar || ret < 0)
	{
		return -1;
	}
	
	//ÿһ�����ɱ�ע��� ptag ��ÿһ������ pinyin 
	for (ii = 0; ii < nChar; ii++)
	{
		if (ptag[ii] == 0 && flag_0 == 1) // ��ǰ��0  ǰ���Ѿ��� 0
		{
			continue;
		}
		if (ptag[ii] == 0 && flag_0 == 0) // ��ǰ��һ�� 0
		{
			left_ii = ii;
			flag_0 = 1;
			continue;
		}

		if (ptag[ii] != 0)   //  ��ǰ���� 0 
		{
			if (flag_0 == 0) // ǰ��û�оۼ�0����ȻΪ��һ���ַ�
			{
				left_ii = ii;
			}

			for (int jj = left_ii; jj <= ii; jj++)
			{
				strcat(py_temp, py_sq[jj]);
				strcat(py_temp, " ");

				strcat(word_temp, vec_word[jj].c_str());			
			}

			// word_temp: �봨�����
			// py_temp:   wen4 chuan1 da4 di4 zhen4
			char biandiao_33[MAX_PY_LEN];
			memset(biandiao_33, MAX_PY_LEN, 0);
			char biandiao_yibu[MAX_PY_LEN];
			memset(biandiao_yibu, MAX_PY_LEN, 0);

			biandiao(py_temp, biandiao_33, MAX_PY_LEN);// 33���

			ret = yibu_biandiao(word_temp, biandiao_33, biandiao_yibu, MAX_PY_LEN); // һ�����
			/*
			if (ret < 0)
			{
				if (ret == -1)strcat(biandiao_yibu, "cuo1 ");
				if (ret == -2)strcat(biandiao_yibu, "cuo2 ");
				if (ret == -3)strcat(biandiao_yibu, "cuo3 ");
				if (ret == -4)strcat(biandiao_yibu, "cuo4 ");
			} */

			std::vector<std::string> yb_bd_vec;
			get_py_vec(biandiao_yibu, yb_bd_vec);
			for (int jj = left_ii; jj <= ii; jj++)
			{
				_snprintf(py_sq[jj], MAX_PY_LEN, "%s", yb_bd_vec[jj - left_ii].c_str());

			}

			flag_0 = 0;
			left_ii = -1;
			memset(py_temp, 0, MAX_PY_LEN);
			memset(word_temp, 0, MAX_PY_LEN);

		}
	}

	return 0;
}


// ��һ�� yi4 qi3   ��Ҫ bu2 yao4
int yibu_biandiao(const char *input_word, const char *input_py, char *output, int out_size)
{
	if (input_word == NULL || input_py == NULL || strlen(input_word) == 0 || strlen(input_py) == 0)
	{
		_snprintf(output, out_size, "%s", input_py);
		return -1;
	}

	if (std::string(input_word).find("һ") == std::string::npos && std::string(input_word).find("��") == std::string::npos )
	{
		_snprintf(output, out_size, "%s", input_py);
		return -2;
	}

	int ii = 0;
	int vec_len;	
	char *temp = NULL;
	char input_py_temp[MAX_PY_LEN] = { 0 };
	char input_word_temp[MAX_PY_LEN] = { 0 };
	
	char *output_temp = output;
	int copy_size = 0;
	std::vector<std::string> vec_py; // yi1 ge4
	std::vector<std::string> vec_word; // һ��
	int word_num = 0;

	// ��ȡÿһ��ƴ�� 
	get_py_vec(input_py, vec_py);


	// ��ȡÿһ���֣�
	get_word(input_word, vec_word);


	// �ֺ�����ͬ���� 
	if (vec_word.size() != vec_py.size())
	{
		_snprintf(output, out_size, "%s", input_py);
		return -3;
	}

	for (ii = 0; ii < vec_word.size(); ii++)
	{
		// "һ"��"��" 
		if ((vec_word[ii].compare("һ") == 0 || vec_word[ii].compare("��") == 0) && ii + 1 < vec_word.size() )
		{
			// ������ 4 �� �� �磺 һ�� ����Ҫ
			if (vec_py[ii + 1][vec_py[ii+1].size()-1] == '4')
			{
				vec_py[ii].replace(vec_py[ii].size() - 1, 1, "2");
				//vec_py[ii] = "cuo444";
			}
			else 
			{
				vec_py[ii].replace(vec_py[ii].size() - 1, 1, "4");
				//vec_py[ii] = "cuo44444";
			}
			
		}
	}

	for (ii = 0; ii < vec_py.size(); ii++)
	{
		if (out_size - copy_size < vec_py[ii].size() + 1)
		{
			return -4;
		}
		_snprintf(output_temp, out_size - copy_size, "%s ", vec_py[ii].c_str());
		copy_size += vec_py[ii].size() + 1;
		output_temp += vec_py[ii].size() + 1;
	}

	*output_temp = '\0';
	return 0;
}

int biandiao(const char *input, char *output, int out_size)
{
	int ii = 0;
	int vec_len;
	char *temp = NULL;
	char input_temp[MAX_PY_LEN] = {0};
	char *output_temp = output;
	int copy_size = 0;
	std::vector<std::string> vec_str;

	if (input == NULL || strlen(input) == 0)
	{
		output[0] = 0;
		return -1;
	}

	_snprintf(input_temp, MAX_PY_LEN, "%s", input); 
	temp = strtok(input_temp, " ");
	while (temp != NULL)
	{
		
		vec_str.push_back(temp);
		temp = strtok(NULL, " ");
	}
	// �������
	vec_len = vec_str.size();
	ii = 0;
	while (ii < vec_len)
	{
		// mi3 lao3 hu3
		if (vec_str[ii][vec_str[ii].size() - 1] == '3' && ii + 1<vec_len && vec_str[ii + 1][vec_str[ii + 1].size() - 1] == '3' && ii + 2<vec_len && vec_str[ii + 2][vec_str[ii + 2].size() - 1] == '3')
		{
			vec_str[ii].replace(vec_str[ii].size() - 1, 1, "2");
			vec_str[ii+1].replace(vec_str[ii+1].size() - 1, 1, "2");
			ii += 3;
		} // lao3 shu3
		else if (vec_str[ii][vec_str[ii].size() - 1] == '3' && ii + 1<vec_len && vec_str[ii+1][vec_str[ii+1].size() - 1] == '3')
		{
			vec_str[ii].replace(vec_str[ii].size() - 1, 1, "2");
			ii += 2;
		}
		else
		{
			ii++;
		}
	}

	for (ii = 0; ii < vec_str.size(); ii++)
	{
		if (out_size - copy_size < vec_str[ii].size() + 1)
		{
			return -1;
		}
		_snprintf(output_temp, out_size - copy_size, "%s ", vec_str[ii].c_str());
		copy_size += vec_str[ii].size() + 1;
		output_temp += vec_str[ii].size() + 1;
	}

	*output_temp = '\0';
	return 0;
}
