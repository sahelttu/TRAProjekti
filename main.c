#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "traharkka.h"

int main()
{
    Dict words;
    words=DictCreate();
    FILE *fp;
    char fileName;
    int wordCount=0;
    int i;

    char line[60];
    //Ohjelma kysyy syötettä, minkä perusteella se avaa tietyn kansion

    printf("Available files:\n1: small.txt\n2: medium.txt\n3: big.txt\n\nChoose a file by entering the correct number: ");
    scanf("%c",&fileName);

    //Seuraavaksi ohjelma lukee halutun tiedoston ja tallentaa fraasit words-taulukkoon

    switch(fileName)
    {
    case '1':
        fp = fopen("small.txt","r");
        printf("small.txt opened\n");
        while (fgets(line,60/*len*/,fp)!=NULL){
            char *word1= strtok(line,":");
            wordCount++;
//            char *word2= strtok(NULL,":");

            DictAdd(words,word1);

           // DictAdd(words,word2);
        }
        break;

    case '2':
        fp = fopen("medium.txt","r");
        printf("medium.txt opened\n");
        while (fgets(line,60/*len*/,fp)!=NULL){
            char *word1= strtok(line,":");
            wordCount++;
           // char *word2= strtok(NULL,":");

            DictAdd(words,word1);
          //  DictInsert(words,word2);
        }
        break;

    case '3':
        fp = fopen("big.txt", "r");
        printf("big.txt opened\n");
        while (fgets(line,60/*len*/,fp)!=NULL){
            char *word1= strtok(line,":");
            wordCount++;
           // char *word2= strtok(NULL,":");

            DictAdd(words,word1);
            //DictInsert(words,word2);
        }
        break;

    default:
        printf("ERROR -  INVALID INPUT.");
        break;
    }
    printf("Phrases counted.\n");
    printf("The most occurring words found.\n");
    printf("Total number of phrases: %d\n", wordCount);
    printf("The 100 most occurring words:\n");
    //FindLargest()-funktion käyttöönotto, toistetaan 100 kertaa
    for(i=1; i <= 100; i++)
        {
            struct elt largest = FindLargest(words);
            printf("%i. ", i);
            printf("%s - %d\n", largest.key, -largest.i);
        }
    //printf("%s", FindLargest);

  /*  printf("Total number of different phrases: %d\n", DictFindUniques (words));*/
    return 0;
}
