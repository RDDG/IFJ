#include "garbade.h"


struct GC gc;

void* myMalloc(unsigned long velikost){
    if(gc.posledni->obsah!=NULL){
        gc.posledni->dalsi=malloc(sizeof(struct GC_obsah);
        gc.posledn=gc.posledn->dalsi;
    }
    gc.posledni->polozka=malloc(velikost);
    gc.posledni->dalsi=NULL;
    
    return gc.posledni->obsah;
}

void init(){
    gc.prvni=malloc(sizeof(struct GC_obsah));
    gc.posledni=gc.prvni;
    gc.prvni->dalsi=NULL;
}

void freeAll(){
    struct GC_obsah *tmp;
  
    while(gc.prvni!=NULL){
        tmp=gc.prvni;
        gc.prvni=gc.prvni->dalsi;
        free(tmp);
        
      
    }
    free(gc.prvni);
}

