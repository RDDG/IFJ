#include <stdio.h>
#include <stdlib.h>

int main (int argc, char *argv[])
{
    
    if (argc==1 || argc>=3){
        printf("Chyba neni zadan vstupni soubor\n");
        return 99;
    }
    
    // Otevreni souboru ze vstupu a predani rizeni parseru, ktery vola funkce z lexikalu
    FILE * f;
    f=fopen(argv[1], "r");
    
    fclose(f);
    
    
    
    
    
    return 0;
}