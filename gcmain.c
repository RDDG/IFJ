#include "garbage.h"


int main (int argc, char *argv[]){
    init();
    
    int *i, *c, *d;
    float *g;
    i=(int*) myMalloc(sizeof(int));
    d=(int*) myMalloc(sizeof(int));
    c=(int*) myMalloc(sizeof(int));
    g=(float*) myMalloc(sizeof(float));
    *i=3;
    *c=5;
    *d=42;
    *g=5.5;
    printf("%d\n", *i);
    printf("%d\n", *c);
    printf("%d\n", *d);
    printf("%f\n", *g);
    freeAll();
    
    
    return 0;
}