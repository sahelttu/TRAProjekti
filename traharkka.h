#ifndef TRAHARKKA_H_INCLUDED
#define TRAHARKKA_H_INCLUDED

struct elt  {
    struct elt *next;
    char *key;
    int i;
};

struct dict {
    int size;
    int n;
    struct elt **table;
};

typedef struct dict *Dict;
//luo uuden taulukon
Dict DictCreate(void);

//tuhoaa taulukon
void DictDestroy(Dict);
void DictInsert(Dict, char *key);

/*Taulukkoon lis�t��n fraasi */
void DictAdd(Dict d, char *key);

int DictContainsAndAdd(Dict d, char *key);

//Palauttaa annetun avaimen perusteella viimeisimm�n avaimeen liittyv�n fraasin.
//Palauttaa 0 jos avainta ei l�ydy
const char* DictSearch(Dict d, char *key);


//Tuhoaa annetun avaimen perusteella viimeisimm�n avaimeen liittyv�n fraasin
//jos kyseist� fraasia ei ole, ei tee mit��n
void DictDelete(Dict d, const char *key);

struct elt FindLargest(Dict d);

//Etsii useimmin esiintyv�n fraasin
void DictFindPhrases(Dict d, const char *key);

//Ei k�ytet�
int DictFindUniques(Dict d);



#endif // TRAHARKKA_H_INCLUDED
