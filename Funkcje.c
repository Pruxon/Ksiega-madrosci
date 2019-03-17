#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_K 25
#define MAX_M 200
#define MAX_KATE 6
#include "Funkcje.h"

typedef struct madrosc {
    char kategoria[MAX_K];
    char madrosc[MAX_M];
    int numer;
    struct madrosc *nast;
}el;

el *poczatek[MAX_KATE];
el *head;

int dodaj (char kat[MAX_K], char napis[MAX_M], int numer, int gdzie)
{
    el *nowy;
    if (poczatek[gdzie]==NULL){
        nowy = malloc(sizeof(el));
        strcpy(nowy->kategoria,kat);
        strcpy(nowy->madrosc,napis);
        nowy->numer=numer;
        nowy->nast=NULL;
        poczatek[gdzie]=nowy;
    }
    else
    {
        nowy = malloc(sizeof(el));
        el *temp;
        temp = poczatek[gdzie];
        while (temp->nast)
        {
            temp=temp->nast;
        }
        temp->nast=nowy;
        strcpy(nowy->kategoria,kat);
        strcpy(nowy->madrosc,napis);
        nowy->numer=numer;
        nowy->nast=NULL;
    }
return 1;

};

void inicjuj ()
{
    int i=0;
    do
    {
        poczatek[i]=NULL;
        i++;
    }
    while (i<MAX_KATE);
}

void wypisz_liste (int jaka)
{
    el *wsk;
    wsk=poczatek[jaka];
    if (poczatek[jaka]==NULL)
        printf("LISTA JEST PUSTA!\n");
    else
    while (wsk !=NULL)
    {
        printf("%s %s %d\n", wsk->kategoria, wsk->madrosc, wsk->numer);
        wsk=wsk->nast;
    }
    free (wsk);
};

int policz(gdzie)
{
    int i=0;
    el *wsk;
    wsk=poczatek[gdzie];
    while (wsk!=NULL)
    {
        wsk=wsk->nast;
        i++;
    }
    return i;
};
int policz_wszystko()
{
    int i=0;
    int ile=0;
    do
    {
       ile=ile+policz(i);
       i++;
    }
    while (i<MAX_KATE);
    return ile;
}

void wyswietl_kategorie()
{
    int i=0;
    do
    {
        if (poczatek[i]!=NULL)
        {
            printf("%d:%s\t",i, poczatek[i]->kategoria);
        }
        i++;
    }
    while (i<MAX_KATE);
    printf("\n");
}

void usun (int skad, int numer)
{
    el *poprzedni, *wsk;
    poprzedni=NULL;
    wsk=poczatek[skad];
    while (numer!=wsk->numer)
    {
        poprzedni=wsk;
        wsk=wsk->nast;
        if (wsk==NULL)
            break;
    }
    if(poprzedni==NULL)
    {
        wsk=wsk->nast;
        free (poczatek[skad]);
        poczatek [skad]=wsk;
    }
    else
        {
            poprzedni->nast=wsk->nast;
            free(wsk);
        }
}

void usun_kategorie (int jaka)
{
   el *wsk;
   wsk=poczatek[jaka];
   while (poczatek[jaka]!=NULL)
   {
        wsk=wsk->nast;
        free (poczatek[jaka]);
        poczatek [jaka]=wsk;
   }
}


