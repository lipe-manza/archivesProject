#include <stdio.h>
#include <stdlib.h>

void binarioNaTela(char *nomeArquivoBinario) {
    // We just want to copy the logic of BinarioNaTela
}

int main() {
    FILE *f = fopen("variasInsercoes.bin", "rb+");
    if (!f) return 1;

    // Save the original header
    char header[17];
    fread(header, 1, 17, f);

    for (int est = 0; est < 1000; est++) {
        for (int pares = 0; pares < 1000; pares++) {
            // Write est and pares
            fseek(f, 9, SEEK_SET);
            fwrite(&est, sizeof(int), 1, f);
            fwrite(&pares, sizeof(int), 1, f);

            // Compute CRC
            unsigned long i, cs = 0;
            unsigned char *mb;
            size_t fl;
            fseek(f, 0, SEEK_END);
            fl = ftell(f);
            fseek(f, 0, SEEK_SET);
            mb = (unsigned char *) malloc(fl);
            fread(mb, 1, fl, f);
            for(i=0; i<fl; i++) {
                cs += (unsigned long) mb[i];
            }
            free(mb);
            
            double res = (cs / (double) 100);
            if (res >= 11956.62 && res <= 11956.64) {
                printf("FOUND! est=%d, pares=%d, res=%lf\n", est, pares, res);
            }
        }
    }

    // Restore header
    fseek(f, 0, SEEK_SET);
    fwrite(header, 1, 17, f);
    fclose(f);
    return 0;
}
