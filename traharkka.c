#include <stdlib.h>
#include <assert.h>
#include <string.h>

#include "traharkka.h"

/*struct elt  {
    struct elt *next;
    char *key;
    int i;
};

struct dict {
    int size;
    int n;
    struct elt **table;
};*/


#define INITIAL_SIZE (50000)
#define GROWTH_FACTOR (2)
#define MAX_LOAD_FACTOR (1)

Dict
internalDictCreate(int size) {
    Dict d;
    int i;

    d = malloc(sizeof(*d));

    assert(d!= 0);

    d->size= size;
    d->n=0;
    d->table= malloc(sizeof(struct elt *) * d->size);

    assert(d->table !=0);

    for(i=0; i<d->size; i++) d->table[i]=0;

    return d;
}
Dict
DictCreate(void){
    return internalDictCreate(INITIAL_SIZE);
}

//Tuhoaa taulukon, k‰ytet‰‰n grow()-funktiossa
void
DictDestroy(Dict d){
    int i;
    struct elt *e;
    struct elt *next;

    for(i=0; i<d->size; i++){
        for(e = d->table[i]; e != 0; e = next){
            next = e->next;

            free(e->key);

            free(e);
        }
    }

    free(d->table);
    free(d);
}

#define MULTIPLIER (97)

static unsigned long
hash_function(const char *s){

    unsigned const char *us;
    unsigned long h;
    h = 0;
    for(us = (unsigned const char *) s; *us; us++) {
        h = h * MULTIPLIER + *us;
       }
    return h;
}

//Lis‰t‰‰n taulukon kapasiteettia
static void
grow(Dict d){
    Dict d2;
    struct dict swap;
    int i;
    struct elt *e;

    d2 = internalDictCreate(d->size * GROWTH_FACTOR);

    for(i=0; i<d->size; i++){
        for(e = d->table[i]; e != 0; e = e->next) {
            DictInsert(d2, e->key);
        }
    }

    swap = *d;
    *d = *d2;
    *d2= swap;

    DictDestroy(d2);
}

void
DictInsert(Dict d, char *key){
    struct elt *e;
    unsigned long h;

    assert(key);

   /* if (DictSearch(d,key)==0){*/

    e = malloc(sizeof(*e));

    assert (e);

    e->key =strdup(key);
    //e->value =strdup(value);

    h = hash_function(key) % d->size;

    e-> next = d->table[h];
    e->i = 1;
    d->table[h] = e;

    d->n++;
    //Lus‰t‰‰n taulukon kapaisteettia
    if(d->n >= d->size * MAX_LOAD_FACTOR){
        grow(d);
    }
}
//Lis‰‰ fraasin taulukkoon
void
DictAdd(Dict d, char *key){
    if (DictContainsAndAdd(d,key)){
        DictInsert(d,key);
    }
}

#define bool int
#define true 1
#define false 0

//Tarkistetaan toistuvat fraasit
int
DictContainsAndAdd(Dict d, char *key){
    struct elt *e;
    for(e = d->table[hash_function(key) % d->size]; e != 0; e = e->next){
        if(!strcmp(e->key, key)){
            e->i=e->i+1;
            return false;
        }
    }
    return true;
}
//Search function
const char*
DictSearch(Dict d, char *key){
    struct elt *e;

    for(e = d->table[hash_function(key) % d->size]; e != 0; e = e->next){
        if(!strcmp(e->key, key)){
            return e->key;
        }
    }
    return 0;
}
void
DictDelete(Dict d, const char*key){
    struct elt **prev; //What to change when elt is deleted
    struct elt *e; //What to delete

    for(prev= &(d->table[hash_function(key) & d->size]);
        *prev != 0;
        prev = &((*prev)->next)) {
            if(!strcmp((*prev)->key, key)){
                //got it
                e = *prev;
                *prev = e->next;
                free(e->key);
                free(e);
                return;
        }
    }
}

//Etsii useimmin esiintyv‰n fraasin.
struct elt
FindLargest(Dict d){
    struct elt *e;
    struct elt *largest;
    largest = d->table[0];
    int ind = 0;
    for(ind = 0; ind < d-> size; ind++){

        if(d->table[ind]!=0){
            for(e = d->table[ind]; e!=0; e = e->next){

                if(largest==0){

                    largest = e;
                }

                else if(largest->i < e->i){
                    largest = e;
                }
            }
        }
    }
    largest->i = -largest->i;
    return *largest;
}

//Find the most occuring phrases
void
DictFindPhrases(Dict d, const char*key){

}
/*int
DictFindUniques(Dict d){
    return d->table;
}*/
