#include "garbage.h"


struct GC gc;

void* myMalloc(unsigned long velikost){
    if(gc.posledni->polozka!=NULL){
        gc.posledni->dalsi=malloc(sizeof(struct GC_obsah));
        gc.posledni=gc.posledni->dalsi;
    }
    gc.posledni->polozka=malloc(velikost);
    gc.posledni->dalsi=NULL;
    
    return gc.posledni->polozka;
}

void init(){
    gc.prvni=malloc(sizeof(struct GC_obsah));
    gc.posledni=gc.prvni;
    gc.prvni->dalsi=NULL;
}

void freeAll(){
    struct GC_obsah *tmp;
    struct GC_obsah *akt;
    
    akt=gc.prvni;
    while(akt!=NULL){
        if(akt->polozka!=NULL){
            free(akt->polozka);
        }
        tmp=akt;
        akt=akt->dalsi;
        free(tmp);
    }
    gc.prvni=NULL;
    
}

