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

/*Taulukkoon lisätään fraasi */
void DictAdd(Dict d, char *key);

int DictContainsAndAdd(Dict d, char *key);

//Palauttaa annetun avaimen perusteella viimeisimmän avaimeen liittyvän fraasin.
//Palauttaa 0 jos avainta ei löydy
const char* DictSearch(Dict d, char *key);


//Tuhoaa annetun avaimen perusteella viimeisimmän avaimeen liittyvän fraasin
//jos kyseistä fraasia ei ole, ei tee mitään
void DictDelete(Dict d, const char *key);

struct elt FindLargest(Dict d);

//Etsii useimmin esiintyvän fraasin
void DictFindPhrases(Dict d, const char *key);

//Ei käytetä
int DictFindUniques(Dict d);



#endif // TRAHARKKA_H_INCLUDED
