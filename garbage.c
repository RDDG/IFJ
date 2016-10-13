#include "garbage.h"


struct GC gc;

//alokace paměti
void* myMalloc(unsigned long velikost){
    if(gc.posledni->polozka!=NULL || gc.prvni!=gc.posledni){  //pokud polozka kam chci nahrát pamět je obsazena nebo je v seznamu jen jedna polozka, zajistí místo pro novou
        gc.posledni->dalsi=malloc(sizeof(struct GC_obsah));
        gc.posledni=gc.posledni->dalsi;
    }
    gc.posledni->polozka=malloc(velikost);      //naalokuje potřebnou velikost dle vstupu
    gc.posledni->dalsi=NULL;
    
    return gc.posledni->polozka;                //vrátí příslušný ukazatel
}

void init(){
    gc.prvni=malloc(sizeof(struct GC_obsah));
    gc.posledni=gc.prvni;
    gc.prvni->polozka=NULL;
}

void freeAll(){
    struct GC_obsah *tmp;
    struct GC_obsah *akt;
    
    akt=gc.prvni;
    while(akt!=NULL){
        if(akt->polozka!=NULL){
            free(akt->polozka);  //maže položku
        }
        tmp=akt;
        akt=akt->dalsi;
        free(tmp);      //maže strukturu
    }
    
}

