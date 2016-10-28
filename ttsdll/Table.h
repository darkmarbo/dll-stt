#ifndef TABLE_H_INCLUDED
#define TABLE_H_INCLUDED


int Split(char *str,char **words,int *nWords);

typedef struct{
    char key[30];
    double val;
}TableNode;

typedef struct{
    TableNode *tn;
    int nNodes;
}Table;

Table * ReadTable(char *fname);

double GetTableValue(Table *tab,char * key);


typedef struct{
    char key[300];
    char str[300];
}STableNode;

typedef struct{
    STableNode *tn;
    int nNodes;
}STable;

char * GetSTableValue(STable *tab,char * key);
STable * ReadSTable(char *fname);
void dropReturnTag(char *c);

#endif // TABLE_H_INCLUDED
