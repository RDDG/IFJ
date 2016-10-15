#include <stdio.h>
#include <stdlib.h>


struct GC_obsah{
    void* polozka;
    struct GC_obsah* dalsi;
};

struct GC{
    struct GC_obsah* prvni;
    struct GC_obsah *posledni;
};

void* myMalloc(unsigned long velikost);

void freeAll();

void init();
