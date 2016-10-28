#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"Table.h"
#include"ProsodicAnalysis.h"

#pragma warning(disable: 4996)

int GetWrodPosSegment(char *str,char **words,char **pos,int *nWords){
    int i,j,k,l;
    Split(str,words,nWords);
    for(i=0;i<*nWords;i++){
        l=strlen(words[i]);
        for(j=0;j<l;j++){
            if(words[i][j]=='/'){
                words[i][j]=0;
                for(k=j+1;k<l;k++){
                    pos[i][k-j-1]=words[i][k];
                }
                pos[i][k-j-1]=0;
                break;
            }
        }
    }
    return *nWords;
}

void GetProsodicWordFeat(char **wordseq,char **posseq,int pos,int nWords,char **feats,int *result){
    char temp[20];
    int i,len;
    if(pos==0){
        strcpy(feats[0],"U00:_B-2");
        strcpy(feats[1],"U01:_B-1");
        strcpy(feats[2],"U02:");
        strcat(feats[2],wordseq[pos]);
    }
    else if(pos==1){
        strcpy(feats[0],"U00:_B-1");
        strcpy(feats[1],"U01:");
        strcat(feats[1],wordseq[pos-1]);
        strcpy(feats[2],"U02:");
        strcat(feats[2],wordseq[pos]);
    }
    else{
        strcpy(feats[0],"U00:");
        strcat(feats[0],wordseq[pos-2]);
        strcpy(feats[1],"U01:");
        strcat(feats[1],wordseq[pos-1]);
        strcpy(feats[2],"U02:");
        strcat(feats[2],wordseq[pos]);
    }
    if(pos==nWords-1){
        strcpy(feats[3],"U03:_B+1");
        strcpy(feats[4],"U04:_B+2");
    }
    else if(pos==nWords-2){
        strcpy(feats[3],"U03:");
        strcat(feats[3],wordseq[pos+1]);
        strcpy(feats[4],"U04:_B+1");
    }
    else{
        strcpy(feats[3],"U03:");
        strcat(feats[3],wordseq[pos+1]);
        strcpy(feats[4],"U04:");
        strcat(feats[4],wordseq[pos+2]);
    }

    if(pos==0){
        strcpy(feats[5],"U05:_B-2");
        strcpy(feats[6],"U06:_B-1");
        strcpy(feats[7],"U07:");
        strcat(feats[7],posseq[pos]);
    }
    else if(pos==1){
        strcpy(feats[5],"U05:_B-1");
        strcpy(feats[6],"U06:");
        strcat(feats[6],posseq[pos-1]);
        strcpy(feats[7],"U07:");
        strcat(feats[7],posseq[pos]);
    }
    else{
        strcpy(feats[5],"U05:");
        strcat(feats[5],posseq[pos-2]);
        strcpy(feats[6],"U06:");
        strcat(feats[6],posseq[pos-1]);
        strcpy(feats[7],"U07:");
        strcat(feats[7],posseq[pos]);
    }
    if(pos==nWords-1){
        strcpy(feats[8],"U08:_B+1");
        strcpy(feats[9],"U09:_B+2");
    }
    else if(pos==nWords-2){
        strcpy(feats[8],"U08:");
        strcat(feats[8],posseq[pos+1]);
        strcpy(feats[9],"U09:_B+1");
    }
    else{
        strcpy(feats[8],"U08:");
        strcat(feats[8],posseq[pos+1]);
        strcpy(feats[9],"U09:");
        strcat(feats[9],posseq[pos+2]);
    }

    if(pos==0){
        strcpy(feats[10],"U10:_B-1/");
        strcat(feats[10],posseq[pos]);
    }
    else{
        strcpy(feats[10],"U10:");
        strcat(feats[10],posseq[pos-1]);
        strcat(feats[10],"/");
        strcat(feats[10],posseq[pos]);
    }

    if(pos==nWords-1){
        strcpy(feats[11],"U11:");
        strcat(feats[11],posseq[pos]);
        strcat(feats[11],"/_B+1");

    }
    else{
        strcpy(feats[11],"U11:");
        strcat(feats[11],posseq[pos]);
        strcat(feats[11],"/");
        strcat(feats[11],posseq[pos+1]);
    }

    if(pos==0){
        strcpy(feats[12],"U12:_B-1");
    }
    else{
        strcpy(feats[12],"U12:");
        itoa(strlen(wordseq[pos-1])/2,temp,10);
        strcat(feats[12],temp);
    }
    strcpy(feats[13],"U13:");
    itoa(strlen(wordseq[pos])/2,temp,10);
    strcat(feats[13],temp);
    if(pos==nWords-1){
        strcpy(feats[14],"U14:_B+1");
    }
    else{
        strcpy(feats[14],"U14:");
        itoa(strlen(wordseq[pos+1])/2,temp,10);
        strcat(feats[14],temp);
    }
    if(pos==0){
        itoa(strlen(wordseq[pos])/2,temp,10);
        strcpy(feats[15],"U15:");
        strcat(feats[15],temp);
    }
    else{
        len=strlen(wordseq[pos])/2;
        for(i=pos-1;i>=0;i--){
            if(result[i]==1){
                break;
            }
            len=len+strlen(wordseq[i])/2;
        }
        itoa(len,temp,10);
        strcpy(feats[15],"U15:");
        strcat(feats[15],temp);
    }
}


void ProsodicWordAnalysis(char **wordseq,char **posseq,int nWords,int *result,Table *pwModel){
    int i,j;
    double cost;
    static char **feats=NULL;
    if(feats==NULL){
        feats=(char **)malloc(sizeof(char *)*16);
        for(i=0;i<16;i++){
            feats[i]=(char *)malloc(sizeof(char)*40);
        }
    }
    for(i=0;i<nWords;i++){
        GetProsodicWordFeat(wordseq,posseq,i,nWords,feats,result);
        cost=0;
        for(j=0;j<16;j++){
            cost+=GetTableValue(pwModel,feats[j]);
        }
        if(cost<=0){
            result[i]=1;
        }
        else{
            result[i]=0;
        }
    }
}





void GetProsodicPhraseFeat(char **wordseq,char **posseq,int pos,int nWords,char **feats,int *result){
    char temp[20];
    int i,len;
    if(pos==0){
        strcpy(feats[0],"U00:_B-2");
        strcpy(feats[1],"U01:_B-1");
        strcpy(feats[2],"U02:");
        strcat(feats[2],wordseq[pos]);
    }
    else if(pos==1){
        strcpy(feats[0],"U00:_B-1");
        strcpy(feats[1],"U01:");
        strcat(feats[1],wordseq[pos-1]);
        strcpy(feats[2],"U02:");
        strcat(feats[2],wordseq[pos]);
    }
    else{
        strcpy(feats[0],"U00:");
        strcat(feats[0],wordseq[pos-2]);
        strcpy(feats[1],"U01:");
        strcat(feats[1],wordseq[pos-1]);
        strcpy(feats[2],"U02:");
        strcat(feats[2],wordseq[pos]);
    }
    if(pos==nWords-1){
        strcpy(feats[3],"U03:_B+1");
        strcpy(feats[4],"U04:_B+2");
    }
    else if(pos==nWords-2){
        strcpy(feats[3],"U03:");
        strcat(feats[3],wordseq[pos+1]);
        strcpy(feats[4],"U04:_B+1");
    }
    else{
        strcpy(feats[3],"U03:");
        strcat(feats[3],wordseq[pos+1]);
        strcpy(feats[4],"U04:");
        strcat(feats[4],wordseq[pos+2]);
    }

    if(pos==0){
        strcpy(feats[5],"U05:_B-2");
        strcpy(feats[6],"U06:_B-1");
        strcpy(feats[7],"U07:");
        strcat(feats[7],posseq[pos]);
    }
    else if(pos==1){
        strcpy(feats[5],"U05:_B-1");
        strcpy(feats[6],"U06:");
        strcat(feats[6],posseq[pos-1]);
        strcpy(feats[7],"U07:");
        strcat(feats[7],posseq[pos]);
    }
    else{
        strcpy(feats[5],"U05:");
        strcat(feats[5],posseq[pos-2]);
        strcpy(feats[6],"U06:");
        strcat(feats[6],posseq[pos-1]);
        strcpy(feats[7],"U07:");
        strcat(feats[7],posseq[pos]);
    }
    if(pos==nWords-1){
        strcpy(feats[8],"U08:_B+1");
        strcpy(feats[9],"U09:_B+2");
    }
    else if(pos==nWords-2){
        strcpy(feats[8],"U08:");
        strcat(feats[8],posseq[pos+1]);
        strcpy(feats[9],"U09:_B+1");
    }
    else{
        strcpy(feats[8],"U08:");
        strcat(feats[8],posseq[pos+1]);
        strcpy(feats[9],"U09:");
        strcat(feats[9],posseq[pos+2]);
    }

    if(pos==0){
        strcpy(feats[10],"U10:_B-1/");
        strcat(feats[10],posseq[pos]);
    }
    else{
        strcpy(feats[10],"U10:");
        strcat(feats[10],posseq[pos-1]);
        strcat(feats[10],"/");
        strcat(feats[10],posseq[pos]);
    }

    if(pos==nWords-1){
        strcpy(feats[11],"U11:");
        strcat(feats[11],posseq[pos]);
        strcat(feats[11],"/_B+1");

    }
    else{
        strcpy(feats[11],"U11:");
        strcat(feats[11],posseq[pos]);
        strcat(feats[11],"/");
        strcat(feats[11],posseq[pos+1]);
    }

    if(pos==0){
        strcpy(feats[12],"U12:_B-1");
    }
    else{
        strcpy(feats[12],"U12:");
        itoa(strlen(wordseq[pos-1])/2,temp,10);
        strcat(feats[12],temp);
    }
    strcpy(feats[13],"U13:");
    itoa(strlen(wordseq[pos])/2,temp,10);
    strcat(feats[13],temp);
    if(pos==nWords-1){
        strcpy(feats[14],"U14:_B+1");
    }
    else{
        strcpy(feats[14],"U14:");
        itoa(strlen(wordseq[pos+1])/2,temp,10);
        strcat(feats[14],temp);
    }
    strcpy(feats[15],"U15:1");
    if(pos==0){
        itoa(strlen(wordseq[pos])/2,temp,10);
        strcpy(feats[16],"U16:");
        strcat(feats[16],temp);
    }
    else{
        len=strlen(wordseq[pos])/2;
        for(i=pos-1;i>=0;i--){
            if(result[i]==1){
                break;
            }
            len=len+strlen(wordseq[i])/2;
        }
        itoa(len,temp,10);
        strcpy(feats[16],"U16:");
        strcat(feats[16],temp);
    }
}




void RefreshFeatForIP(char **wordseq,char **posseq,int pos,int nWords,char **feats,int *result){
    int i,len;
    char temp[20];
    if(pos==0){
        itoa(strlen(wordseq[pos])/2,temp,10);
        strcpy(feats[16],"U16:");
        strcat(feats[16],temp);
    }
    else{
        len=strlen(wordseq[pos])/2;
        for(i=pos-1;i>=0;i--){
            if(result[i]==2){
                break;
            }
            len=len+strlen(wordseq[i])/2;
        }
        itoa(len,temp,10);
        strcpy(feats[16],"U16:");
        strcat(feats[16],temp);
    }
}



void ProsodicPhraseAnalysis(char **wordseq,char **posseq,int nWords,int *pwresult,int *result,Table *ppModel,Table *ipModel){
    int i,j;
    double cost,cost2;
    static char **ppfeats=NULL;
    if(ppfeats==NULL){
        ppfeats=(char **)malloc(sizeof(char *)*17);
        for(i=0;i<17;i++){
            ppfeats[i]=(char *)malloc(sizeof(char)*40);
        }
    }
    for(i=0;i<nWords;i++){
        if(pwresult[i]==0){
            result[i]=0;
            continue;
        }
        GetProsodicPhraseFeat(wordseq,posseq,i,nWords,ppfeats,result);
        cost=0;
        for(j=0;j<17;j++){
            cost+=GetTableValue(ppModel,ppfeats[j]);
        }
        if(cost<=0){
            result[i]=1;
            cost2=0;
            RefreshFeatForIP(wordseq,posseq,i,nWords,ppfeats,result);
            for(j=0;j<17;j++){
                    cost2+=GetTableValue(ipModel,ppfeats[j]);
            }
            if(cost2<=0){
                result[i]=2;
            }
        }
        else{
            result[i]=0;
        }
    }
}

void GetProsodicTag(char **wordseq,int nWords,int *pwresult,int *ppresult,short *tag){
    int i,j,k,l;
    k=0;
    for(i=0;i<nWords;i++){
        l=strlen(wordseq[i])/2;
        for(j=0;j<l-1;j++){
            tag[k]=0;
            k++;
        }
        tag[k]=pwresult[i]+ppresult[i];
        k++;
    }
    tag[k-1]=4;
}
