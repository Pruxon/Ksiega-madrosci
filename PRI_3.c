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


int sprawdz_czy_pusta ()
{
    int k=0;
    int i=0;
    do
    {
        if (poczatek[i]!=NULL)
            k++;
        i++;
    }
    while (i<MAX_KATE);
    return k;
}

void zapisz()
{
    int k=0;
    int i=0;
    FILE *zapisz=NULL;
    el *wsk;
    char nazwa_pliku[]="ksiega_madrosci";
    if (sprawdz_czy_pusta()==0)
        {
            printf("Nie ma plikow do zapisania\n");
        }
        if (sprawdz_czy_pusta()!=0)
        {
            zapisz=fopen(nazwa_pliku, "w");
            if (zapisz!=NULL)
            {
                do
                {
                 wsk=poczatek[i];
                while (wsk!=NULL)
                {
                    fprintf(zapisz, "%s\n", wsk->kategoria);
                    fprintf(zapisz, "%s\n", wsk->madrosc);
                    fprintf(zapisz, "%d\n", wsk->numer);
                    wsk=wsk->nast;
                }
                i++;
            }
            while (i<MAX_KATE);
            fclose(zapisz);
        }

    }
}

void odczytaj()
{
    FILE *wczytaj=NULL;
    char nazwa_pliku[]="ksiega_madrosci";
    char bufor [MAX_M+1];
    char buforek [MAX_K+1];
    el *tmp, *pom;
    head=NULL;
    int i;
    wczytaj=fopen(nazwa_pliku, "r");
    if (wczytaj==NULL)
        printf("Blad otwarcia pliku\n");
    else
    {
        while (fscanf(wczytaj, "%s", &buforek)!=EOF)
        {
            tmp=malloc(sizeof(el));
            tmp->nast=NULL;
            strcpy(tmp->kategoria, buforek);
            fscanf(wczytaj, "%s", &bufor);
            strcpy(tmp->madrosc, bufor);
            fscanf(wczytaj, "%d", &i);
            tmp->numer=i;

            if (head==NULL)
                head=tmp;
            else
            {
                pom=head;
                while (pom->nast!=NULL)
                    pom=pom->nast;
                pom->nast=tmp;
            }
        }
    }
fclose(wczytaj);
}


void rozdziel()
{
    el *next, *teraz;
    int pom=0;
    if (head==NULL)
    {
        return;
    }
    else
    {
        while (head!=NULL)
        {
            poczatek [pom]=head;
            teraz=head;
            next=head->nast;
            if (next==NULL)
                break;
            while (strcmp(next->kategoria, poczatek[pom]->kategoria)==0)
            {
                teraz=next;
                next=next->nast;
                if(next==NULL)
                    break;
            }
            head=next;
            teraz->nast=NULL;
            pom++;
            if (pom==MAX_KATE)
                return;
        }
    }
    return;
}




int main()
{
    char kate[MAX_K];
    char napi[MAX_M];
    int nume;
    char akcja[20];
    printf("KSIEGA PRZEMADRYCH MADROSCI\n");
    inicjuj();
    odczytaj();
    rozdziel();
    do
    {
        printf("Jesli chcesz dodac madrosc wpisz: dodaj\n");
        printf("Jesli chcesz wyswietlic wpisz: wyswietl\n");
        printf("Jesli chcesz usunac wpisz: usun\n");
        printf("Jesli chcesz policzyc madrosci wpisz: policz\n");
        printf("Jesli chcesz zapisac wpisz: zapisz\n");
        printf("Aby zakonczyc dzialanie programu wpisz: koniec\n");
        printf("Co chcesz zrobic?\n");
        scanf("%s", &akcja);
            if (strcmp(akcja, "dodaj")==0) //dodawanie
                {
                    printf("Podaj kategorie:\n");
                    scanf("%s", &kate);
                    printf("Podaj madrosc:\n");
                    scanf("%s",&napi);
                    int pom=0;
                    int czy_udalo=0;
                    int pomoc=0;
                    do
                    {
                        if (poczatek[pom]!=NULL)
                        {
                            if (strcmp(poczatek[pom]->kategoria,kate)==0)
                            {
                                int katel;
                                katel=policz(pom);
                                printf("W tej kategorii jest %d madrosci\n", katel);
                                printf("Podaj numer madrosci:\n");
                                scanf("%d", &nume);
                                dodaj(kate, napi, nume, pom);
                                czy_udalo=1;
                                break;
                            }
                        }
                        pom++;
                    }
                    while (pom<MAX_KATE);
                    do
                    {
                    if (czy_udalo==0)
                    {
                        if (poczatek[pomoc]==NULL)
                        {
                                int katel;
                                katel=policz(pomoc);
                                printf("W tej kategorii jest %d madrosci\n", katel);
                                printf("Podaj numer madrosci:\n");
                                scanf("%d", &nume);
                                dodaj(kate, napi, nume, pomoc);
                                czy_udalo=1;
                                break;
                        }
                    }
                    pomoc++;
                    }
                    while (pomoc<MAX_KATE);
                    if (czy_udalo==0)
                        printf("Nie ma miejsca na nowa kategorie :(\n");
                    }


                if (strcmp(akcja,"wyswietl")==0) //wyswietlanie
                    {
                    printf("Jesli chcesz wyswietlic jedna kategorie wpisz 1\nJesli cala ksiege wpisz 2\n");
                    int co;
                    scanf("%d", &co);
                    if (co==1)
                        {
                        printf ("Ktora kategorie chcesz wyswietlic? Dostepne kategorie:\n");
                        wyswietl_kategorie();
                        int de;
                        scanf("%d", &de);
                        wypisz_liste(de);
                        }
                    if (co==2)
                    {
                        printf("\n");
                        int e=0;
                        while (poczatek[e]!=NULL&&e<(MAX_KATE+1))
                        {
                            wypisz_liste(e);
                            e++;
                        }
                    }

                    }
                if (strcmp(akcja,"usun")==0) //usuwanie
                {
                    printf("Jesli chcesz usunac jedna madrosc wpisz 1\nJesli cala kategorie wpisz 2\nJesli cala ksiege wpisz 3\n");
                    int co;
                    scanf("%d", &co);

                    if (co==1)
                    {
                        printf("Do ktorej kategorii nalezy to co chcesz usunac?\n");
                        wyswietl_kategorie();
                        int d;
                        scanf("%d",&d);
                        printf("Jaki numer ma madrosc ktora chcesz usunac?\n");
                        int nr;
                        scanf("%d", &nr);
                        usun(d, nr);
                    }

                    if (co==2)
                    {
                        printf("Ktora kategorie chcesz usunac?\n");
                        wyswietl_kategorie();
                        int a;
                        scanf("%d", &a);
                        usun_kategorie(a);
                    }

                    if (co==3)
                    {
                        int k=1;
                        do
                        {
                            usun_kategorie(k-1);
                            k++;
                        }
                        while (k<MAX_KATE);
                    }
                }

                if (strcmp(akcja,"policz")==0) //liczenie
                {
                    printf("Jesli chcesz policzyc madrosci z jednej kategorii wpisz 1\nJesli z calej ksiegi wpisz 2\n");
                    int m;
                    scanf("%d", &m);
                    if (m==1)
                    {
                        wyswietl_kategorie();
                        int sa;
                        scanf("%d", &sa);
                        int c;
                        c=policz(sa);
                        printf("%c\n", c);
                    }
                    if (m==2)
                    {
                        int ka;
                        ka=policz_wszystko();
                        printf("%d\n", ka);
                    }

                }

                if (strcmp(akcja,"zapisz")==0)
                {
                    zapisz();
                }


            printf("\n\n");
        }
    while (strcmp(akcja, "koniec")!=0);
    return 0;
}



