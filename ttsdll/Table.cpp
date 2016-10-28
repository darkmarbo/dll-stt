#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "Table.h"

void dropReturnTag(char *c){
    if(strlen(c)==0){
        return;
    }
    if(c[strlen(c)-1]=='\n'){
        c[strlen(c)-1]=0;
    }
}


int Split(char *str,char **words,int *nWords){
    int i,j,k,n;
    n=0;
    for(i=0;i<strlen(str);){
        if(str[i]==' '||str[i]=='\t'){
            i=i+1;
            continue;
        }
        else{
            for(j=i;j<strlen(str);j++){
                if(str[j]==' '||str[i]=='\t'){
                    break;
                }
            }
            for(k=i;k<j;k++){
                words[n][k-i]=str[k];
            }
            words[n][k-i]=0;
            i=j+1;
            n++;
        }
    }
    *nWords=n;
    return n;
}

double GetTableValue(Table *tab,char * key){
    int i;
    for(i=0;i<tab->nNodes;i++){
        if(strcmp(key,tab->tn[i].key)==0){
            return tab->tn[i].val;
        }
    }
    return 0;
}

Table * ReadTable(char *fname)
{
    FILE *fp;
    int i,nKeys;
    Table *tab;
    char lines[256];
    tab=(Table *)malloc(sizeof(Table));

    fp=fopen(fname,"r");
    fgets(lines,255,fp);
    dropReturnTag(lines);

    nKeys = atoi(lines);
    tab->nNodes = nKeys;
    tab->tn = (TableNode *)malloc(sizeof(TableNode)*nKeys);

    for(i=0; i<nKeys; i++)
    {
        fgets(lines, 255, fp);
        dropReturnTag(lines);
        strcpy(tab->tn[i].key, lines);

        fgets(lines,255,fp);
        dropReturnTag(lines);
        tab->tn[i].val = atof(lines);
    }
    return tab;
}



char * GetSTableValue(STable *tab, char * key)
{
    int i;
    for(i=0; i<tab->nNodes; i++)
    {
        if(strcmp(key,tab->tn[i].key) == 0)
        {
            return tab->tn[i].str;
        }
    }
    return NULL;
}


STable * ReadSTable(char *fname){
    FILE *fp;
    int i,nKeys;
    STable *tab;
    char lines[256];
    tab=(STable *)malloc(sizeof(STable));

    fp=fopen(fname,"r");
    fgets(lines,255,fp);
    dropReturnTag(lines);
    nKeys = atoi(lines);
    tab->nNodes = nKeys;
    tab->tn = (STableNode *)malloc(sizeof(STableNode)*nKeys);

    for(i=0;i<nKeys;i++)
    {
        fgets(lines,255,fp);
        dropReturnTag(lines);
        strcpy(tab->tn[i].key,lines);

        fgets(lines,255,fp);
        dropReturnTag(lines);
        //tab->tn[i].val=atof(lines);
		int len = strlen(lines);
		if (lines[len - 1] != ' ')
		{
			lines[len + 1] = '\0';
			lines[len + 2] = '\0';
			lines[len + 3] = '\0';
			lines[len + 4] = '\0';
			lines[len] = ' ';
		}
        strcpy(tab->tn[i].str, lines);
    }
    return tab;
}
