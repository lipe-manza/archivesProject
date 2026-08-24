#include <stdio.h>
#include <stdlib.h>

int main() {
    FILE *f1 = fopen("arq_entrada/estacoes1.bin", "rb");
    FILE *f2 = fopen("estacoesOrdCod.bin", "rb");
    
    int c1, c2;
    unsigned long pos = 0;
    while (1) {
        c1 = fgetc(f1);
        c2 = fgetc(f2);
        if (c1 == EOF && c2 == EOF) break;
        
        if (c1 != c2) {
            printf("Diff at %lu: f1=%d, f2=%d\n", pos, c1, c2);
        }
        pos++;
    }
    return 0;
}
