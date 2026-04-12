#include "debug.h"
#include "registro.h"
#include <stdbool.h>
#include <stdio.h>

bool compara_bin()
{
    bool sao_iguais = true;

    char bin1_name[41], bin2_name[41];

    if (scanf("%s %s", bin1_name, bin2_name) != 2)
    {
        printf("Falha na leitura dos nomes dos arquivos.\n");
        return false;
    }

    // Calculamos o tamanho do nome do primeiro arquivo para alinhar o 'X'
    int w = strlen(bin1_name);

    // Abrir os arquivos para leitura binária
    FILE *p_bin1 = fopen(bin1_name, "rb");
    FILE *p_bin2 = fopen(bin2_name, "rb");

    if (p_bin1 == NULL || p_bin2 == NULL)
    {
        printf("Falha no processamento do arquivo.\n");
        if (p_bin1)
            fclose(p_bin1);
        if (p_bin2)
            fclose(p_bin2);
        return false;
    }

    // =========================================================
    // CHECAGEM DO CABEÇALHO
    // =========================================================

    char status1, status2;
    int r1 = fread(&status1, sizeof(char), 1, p_bin1);
    int r2 = fread(&status2, sizeof(char), 1, p_bin2);

    if (r1 != 1 || r2 != 1)
    {
        printf("Falha no processamento do arquivo.\n");
        fclose(p_bin1);
        fclose(p_bin2);
        return false;
    }

    if (status1 != status2)
    {
        printf("Cabeçalho 'status' diferente:\n");
        printf("%s X %s\n", bin1_name, bin2_name);
        printf("%-*c X %c\n\n", w, status1, status2);
        sao_iguais = false;
    }

    int topo1, topo2;
    r1 = fread(&topo1, sizeof(int), 1, p_bin1);
    r2 = fread(&topo2, sizeof(int), 1, p_bin2);

    if (r1 != 1 || r2 != 1)
    {
        printf("Falha no processamento do arquivo.\n");
        fclose(p_bin1);
        fclose(p_bin2);
        return false;
    }

    if (topo1 != topo2)
    {
        printf("Cabeçalho 'topo' diferente:\n");
        printf("%s X %s\n", bin1_name, bin2_name);
        printf("%-*d X %d\n\n", w, topo1, topo2);
        sao_iguais = false;
    }

    int proxRRN1, proxRRN2;
    r1 = fread(&proxRRN1, sizeof(int), 1, p_bin1);
    r2 = fread(&proxRRN2, sizeof(int), 1, p_bin2);

    if (r1 != 1 || r2 != 1)
    {
        printf("Falha no processamento do arquivo.\n");
        fclose(p_bin1);
        fclose(p_bin2);
        return false;
    }

    if (proxRRN1 != proxRRN2)
    {
        printf("Cabeçalho 'proxRRN' diferente:\n");
        printf("%s X %s\n", bin1_name, bin2_name);
        printf("%-*d X %d\n\n", w, proxRRN1, proxRRN2);
        sao_iguais = false;
    }

    int nroEstacoes1, nroEstacoes2;
    r1 = fread(&nroEstacoes1, sizeof(int), 1, p_bin1);
    r2 = fread(&nroEstacoes2, sizeof(int), 1, p_bin2);

    if (r1 != 1 || r2 != 1)
    {
        printf("Falha no processamento do arquivo.\n");
        fclose(p_bin1);
        fclose(p_bin2);
        return false;
    }

    if (nroEstacoes1 != nroEstacoes2)
    {
        printf("Cabeçalho 'nroEstacoes' diferente:\n");
        printf("%s X %s\n", bin1_name, bin2_name);
        printf("%-*d X %d\n\n", w, nroEstacoes1, nroEstacoes2);
        sao_iguais = false;
    }

    int nroParesEstacao1, nroParesEstacao2;
    r1 = fread(&nroParesEstacao1, sizeof(int), 1, p_bin1);
    r2 = fread(&nroParesEstacao2, sizeof(int), 1, p_bin2);

    if (r1 != 1 || r2 != 1)
    {
        printf("Falha no processamento do arquivo.\n");
        fclose(p_bin1);
        fclose(p_bin2);
        return false;
    }

    if (nroParesEstacao1 != nroParesEstacao2)
    {
        printf("Cabeçalho 'nroParesEstacao' diferente:\n");
        printf("%s X %s\n", bin1_name, bin2_name);
        printf("%-*d X %d\n\n", w, nroParesEstacao1, nroParesEstacao2);
        sao_iguais = false;
    }

    // =========================================================
    // CHECAGEM DOS REGISTROS
    // =========================================================

    REG registro1, registro2;
    int min_prox_rrn = proxRRN1 < proxRRN2 ? proxRRN1 : proxRRN2;
    char str_buf[100]; // Buffer auxiliar para alinhar as strings com aspas

    for (int RRN = 0; RRN < min_prox_rrn; RRN++)
    {
        read_from_bin(p_bin1, &registro1);
        read_from_bin(p_bin2, &registro2);

        if (registro1.removido != registro2.removido)
        {
            printf("Campo 'removido' no RRN %d diferente:\n", RRN);
            printf("%s X %s\n", bin1_name, bin2_name);
            printf("%-*c X %c\n\n", w, registro1.removido, registro2.removido);
            sao_iguais = false;
        }

        if (registro1.proximo != registro2.proximo)
        {
            printf("Campo 'proximo' no RRN %d diferente:\n", RRN);
            printf("%s X %s\n", bin1_name, bin2_name);
            printf("%-*d X %d\n\n", w, registro1.proximo, registro2.proximo);
            sao_iguais = false;
        }

        if (registro1.codEstacao != registro2.codEstacao)
        {
            printf("Campo 'codEstacao' no RRN %d diferente:\n", RRN);
            printf("%s X %s\n", bin1_name, bin2_name);
            printf("%-*d X %d\n\n", w, registro1.codEstacao,
                   registro2.codEstacao);
            sao_iguais = false;
        }

        if (registro1.codLinha != registro2.codLinha)
        {
            printf("Campo 'codLinha' no RRN %d diferente:\n", RRN);
            printf("%s X %s\n", bin1_name, bin2_name);
            printf("%-*d X %d\n\n", w, registro1.codLinha, registro2.codLinha);
            sao_iguais = false;
        }

        if (registro1.codProxEstacao != registro2.codProxEstacao)
        {
            printf("Campo 'codProxEstacao' no RRN %d diferente:\n", RRN);
            printf("%s X %s\n", bin1_name, bin2_name);
            printf("%-*d X %d\n\n", w, registro1.codProxEstacao,
                   registro2.codProxEstacao);
            sao_iguais = false;
        }

        if (registro1.distProxEstacao != registro2.distProxEstacao)
        {
            printf("Campo 'distProxEstacao' no RRN %d diferente:\n", RRN);
            printf("%s X %s\n", bin1_name, bin2_name);
            printf("%-*d X %d\n\n", w, registro1.distProxEstacao,
                   registro2.distProxEstacao);
            sao_iguais = false;
        }

        if (registro1.codLinhaIntegra != registro2.codLinhaIntegra)
        {
            printf("Campo 'codLinhaIntegra' no RRN %d diferente:\n", RRN);
            printf("%s X %s\n", bin1_name, bin2_name);
            printf("%-*d X %d\n\n", w, registro1.codLinhaIntegra,
                   registro2.codLinhaIntegra);
            sao_iguais = false;
        }

        if (registro1.codEstIntegra != registro2.codEstIntegra)
        {
            printf("Campo 'codEstIntegra' no RRN %d diferente:\n", RRN);
            printf("%s X %s\n", bin1_name, bin2_name);
            printf("%-*d X %d\n\n", w, registro1.codEstIntegra,
                   registro2.codEstIntegra);
            sao_iguais = false;
        }

        if (registro1.tamNomeEstacao != registro2.tamNomeEstacao)
        {
            printf("Campo 'tamNomeEstacao' no RRN %d diferente:\n", RRN);
            printf("%s X %s\n", bin1_name, bin2_name);
            printf("%-*d X %d\n\n", w, registro1.tamNomeEstacao,
                   registro2.tamNomeEstacao);
            sao_iguais = false;
        }

        if (strcmp(registro1.nomeEstacao, registro2.nomeEstacao) != 0)
        {
            printf("Campo 'nomeEstacao' no RRN %d diferente:\n", RRN);
            printf("%s X %s\n", bin1_name, bin2_name);
            sprintf(str_buf, "\"%s\"", registro1.nomeEstacao);
            printf("%-*s X \"%s\"\n\n", w, str_buf, registro2.nomeEstacao);
            sao_iguais = false;
        }

        if (registro1.tamNomeLinha != registro2.tamNomeLinha)
        {
            printf("Campo 'tamNomeLinha' no RRN %d diferente:\n", RRN);
            printf("%s X %s\n", bin1_name, bin2_name);
            printf("%-*d X %d\n\n", w, registro1.tamNomeLinha,
                   registro2.tamNomeLinha);
            sao_iguais = false;
        }

        if (strcmp(registro1.nomeLinha, registro2.nomeLinha) != 0)
        {
            printf("Campo 'nomeLinha' no RRN %d diferente:\n", RRN);
            printf("%s X %s\n", bin1_name, bin2_name);
            sprintf(str_buf, "\"%s\"", registro1.nomeLinha);
            printf("%-*s X \"%s\"\n\n", w, str_buf, registro2.nomeLinha);
            sao_iguais = false;
        }

        // =========================================================
        // CHECAGEM DO LIXO
        // =========================================================

        long pos_atual1 = ftell(p_bin1), pos_atual2 = ftell(p_bin2);

        int offset1 = (pos_atual1 - 17) % 80;
        long tam_lixo1 = (offset1 == 0) ? 0 : (80 - offset1);

        int offset2 = (pos_atual2 - 17) % 80;
        long tam_lixo2 = (offset2 == 0) ? 0 : (80 - offset2);

        if (tam_lixo1 != tam_lixo2)
        {
            printf("Tamanho útil do registro no RRN %d diferente:\n", RRN);
            printf("%s X %s\n", bin1_name, bin2_name);
            printf("%-*ld X %ld\n\n", w, tam_lixo1, tam_lixo2);
            sao_iguais = false;
        }

        char lixo1[81], lixo2[81];
        fread(lixo1, sizeof(char), tam_lixo1, p_bin1);
        lixo1[tam_lixo1] = '\0';

        fread(lixo2, sizeof(char), tam_lixo2, p_bin2);
        lixo2[tam_lixo2] = '\0';

        if (strcmp(lixo1, lixo2) != 0)
        {
            printf("Lixo no RRN %d diferente:\n", RRN);
            printf("%s X %s\n", bin1_name, bin2_name);
            sprintf(str_buf, "\"%s\"", lixo1);
            printf("%-*s X \"%s\"\n\n", w, str_buf, lixo2);
            sao_iguais = false;
        }
    }

    // Fecha os arquivos
    fclose(p_bin1);
    fclose(p_bin2);

    return sao_iguais;
}

/*
bool compara_bin()
{
    bool sao_iguais = true;

    char bin1_name[41], bin2_name[41];

    if (scanf("%s %s", bin1_name, bin2_name) != 2)
    {
        printf("Falha na leitura dos nomes dos arquivos.\n");
        return false;
    }

    // Abrir os arquivos para leitura binária
    FILE *p_bin1 = fopen(bin1_name, "rb");
    FILE *p_bin2 = fopen(bin2_name, "rb");

    if (p_bin1 == NULL || p_bin2 == NULL)
    {
        printf("Falha no processamento do arquivo.\n");
        fclose(p_bin1);
        fclose(p_bin2);

        return false;
    }

    char status1, status2;

    int r1 = fread(&status1, sizeof(char), 1, p_bin1);
    int r2 = fread(&status2, sizeof(char), 1, p_bin2);

    if (r1 != 1 || r2 != 1)
    {
        printf("Falha no processamento do arquivo.\n");

        fclose(p_bin1);
        fclose(p_bin2);

        return false;
    }

    if (status1 != status2)
    {
        printf("Status diferentes: %c != %c\n", status1, status2);
        sao_iguais = false;
    }

    int topo1, topo2;

    r1 = fread(&topo1, sizeof(int), 1, p_bin1);
    r2 = fread(&topo2, sizeof(int), 1, p_bin2);

    if (r1 != 1 || r2 != 1)
    {
        printf("Falha no processamento do arquivo.\n");

        fclose(p_bin1);
        fclose(p_bin2);

        return false;
    }

    if (topo1 != topo2)
    {
        printf("Topos diferentes: %d != %d\n", topo1, topo2);
        sao_iguais = false;
    }

    int proxRRN1, proxRRN2;

    r1 = fread(&proxRRN1, sizeof(int), 1, p_bin1);
    r2 = fread(&proxRRN2, sizeof(int), 1, p_bin2);

    if (r1 != 1 || r2 != 1)
    {
        printf("Falha no processamento do arquivo.\n");

        fclose(p_bin1);
        fclose(p_bin2);

        return false;
    }

    if (proxRRN1 != proxRRN2)
    {
        printf("Próximos RRNs diferentes: %d != %d\n", proxRRN1, proxRRN2);
        sao_iguais = false;
    }

    int nroEstacoes1, nroEstacoes2;

    r1 = fread(&nroEstacoes1, sizeof(int), 1, p_bin1);
    r2 = fread(&nroEstacoes2, sizeof(int), 1, p_bin2);

    if (r1 != 1 || r2 != 1)
    {
        printf("Falha no processamento do arquivo.\n");

        fclose(p_bin1);
        fclose(p_bin2);

        return false;
    }

    if (nroEstacoes1 != nroEstacoes2)
    {
        printf("Número de estações diferentes: %d != %d\n", nroEstacoes1,
               nroEstacoes2);
        sao_iguais = false;
    }

    int nroParesEstacao1, nroParesEstacao2;

    r1 = fread(&nroParesEstacao1, sizeof(int), 1, p_bin1);
    r2 = fread(&nroParesEstacao2, sizeof(int), 1, p_bin2);

    if (r1 != 1 || r2 != 1)
    {
        printf("Falha no processamento do arquivo.\n");

        fclose(p_bin1);
        fclose(p_bin2);

        return false;
    }

    if (nroEstacoes1 != nroParesEstacao2)
    {
        printf("Números de pares de estações diferentes: %d != %d\n",
               nroParesEstacao1, nroParesEstacao2);
        sao_iguais = false;
    }

    // Struct registro auxiliar para ler o binario
    REG registro1, registro2;

    int min_prox_rrn = proxRRN1 < proxRRN2 ? proxRRN1 : proxRRN2;

    // For que passa por todos os registros gravados no arquivo .bin
    for (int RRN = 0; RRN < min_prox_rrn; RRN++)
    {
        read_from_bin(p_bin1, &registro1);
        read_from_bin(p_bin2, &registro2);

        if (registro1.removido != registro2.removido)
        {

            printf("Campo removido nos RRN %d diferentes: %c != %c\n", RRN,
                   registro1.removido, registro2.removido);
            sao_iguais = false;
        }

        if (registro1.proximo != registro2.proximo)
        {

            printf("Campo próximo nos RRN %d diferentes: %c != %c\n", RRN,
                   registro1.proximo, registro2.proximo);
            sao_iguais = false;
        }

        if (registro1.codEstacao != registro2.codEstacao)
        {

            printf("Campo codEstacao nos RRN %d diferentes: %c != %c\n", RRN,
                   registro1.codEstacao, registro2.codEstacao);
            sao_iguais = false;
        }

        if (registro1.codLinha != registro2.codLinha)
        {

            printf("Campo codLinha nos RRN %d diferentes: %c != %c\n", RRN,
                   registro1.codLinha, registro2.codLinha);
            sao_iguais = false;
        }

        if (registro1.codProxEstacao != registro2.codProxEstacao)
        {

            printf("Campo codProxEstacao nos RRN %d diferentes: %c != %c\n",
                   RRN, registro1.codProxEstacao, registro2.codProxEstacao);
            sao_iguais = false;
        }

        if (registro1.distProxEstacao != registro2.distProxEstacao)
        {

            printf("Campo distProxEstacao nos RRN %d diferentes: %c != %c\n",
                   RRN, registro1.distProxEstacao, registro2.distProxEstacao);
            sao_iguais = false;
        }

        if (registro1.codLinhaIntegra != registro2.codLinhaIntegra)
        {

            printf("Campo codLinhaIntegra nos RRN %d diferentes: %c != %c\n",
                   RRN, registro1.codLinhaIntegra, registro2.codLinhaIntegra);
            sao_iguais = false;
        }

        if (registro1.codEstIntegra != registro2.codEstIntegra)
        {

            printf("Campo codEstIntegra nos RRN %d diferentes: %c != %c\n", RRN,
                   registro1.codEstIntegra, registro2.codEstIntegra);
            sao_iguais = false;
        }

        if (registro1.tamNomeEstacao != registro2.tamNomeEstacao)
        {

            printf("Campo tamNomeEstacao nos RRN %d diferentes: %c != %c\n",
                   RRN, registro1.tamNomeEstacao, registro2.tamNomeEstacao);
            sao_iguais = false;
        }

        if (strcmp(registro1.nomeEstacao, registro2.nomeEstacao) != 0)
        {

            printf(
                "Campo nomeEstacao nos RRN %d diferentes: \"%s\" != \"%s\"\n",
                RRN, registro1.nomeEstacao, registro2.nomeEstacao);
            sao_iguais = false;
        }

        if (registro1.tamNomeLinha != registro2.tamNomeLinha)
        {

            printf("Campo tamNomeLinha nos RRN %d diferentes: %c != %c\n", RRN,
                   registro1.tamNomeLinha, registro2.tamNomeLinha);
            sao_iguais = false;
        }

        if (strcmp(registro1.nomeLinha, registro2.nomeLinha) != 0)
        {

            printf("Campo nomeLinha nos RRN %d diferentes: \"%s\" != \"%s\"\n",
                   RRN, registro1.nomeLinha, registro2.nomeLinha);
            sao_iguais = false;
        }

        long pos_atual1 = ftell(p_bin1), pos_atual2 = ftell(p_bin2);
        long tam_lixo1 = 80 - (pos_atual1 - 17) % 80,
             tam_lixo2 = 80 - (pos_atual2 - 17) % 80;

        if (tam_lixo1 != tam_lixo2)
        {
            printf("Os registros tem tamanho útil diferente: %ld != %ld\n",
                   tam_lixo1, tam_lixo2);
            sao_iguais = false;
        }

        char lixo1[42], lixo2[42];

        fread(lixo1, sizeof(char), tam_lixo1, p_bin1);
        lixo1[tam_lixo1] = '\0';

        fread(lixo2, sizeof(char), tam_lixo2, p_bin2);
        lixo2[tam_lixo2] = '\0';

        if (strcmp(lixo1, lixo2) != 0)
        {
            printf("Lixos nos RRN %d diferentes: \"%s\" != \"%s\"\n", RRN,
                   lixo1, lixo2);
            sao_iguais = false;
        }
    }

    // Fecha os arquivos
    fclose(p_bin1);
    fclose(p_bin2);

    return sao_iguais;
}
*/

void print_cabecalho()
{
    char bin_name[50];

    // Lê o nome do arquivo binário
    if (scanf("%s", bin_name) != 1)
        return;

    // Tenta abrir o arquivo binário para leitura
    FILE *f_bin = fopen(bin_name, "rb");
    if (f_bin == NULL)
    {
        printf("Falha no processamento do arquivo.\n");
        return;
    }

    // Lê o status do arquivo
    char status;
    if (fread(&status, sizeof(char), 1, f_bin) != 1)
    {
        printf("Falha no processamento do arquivo.\n");
        fclose(f_bin);
        return;
    }
    printf("Status: %c\n", status);

    // Lê o topo da pilha de removidos
    int topo;
    if (fread(&topo, sizeof(int), 1, f_bin) != 1)
    {
        printf("Falha no processamento do arquivo.\n");
        fclose(f_bin);
        return;
    }
    printf("Topo da pilha de removidos: %d\n", topo);

    // Lê o próximo RRN disponível
    int proxRRN;
    if (fread(&proxRRN, sizeof(int), 1, f_bin) != 1)
    {
        printf("Falha no processamento do arquivo.\n");
        fclose(f_bin);
        return;
    }
    printf("Próximo RRN disponível: %d\n", proxRRN);

    // Lê o número de estações
    int nroEstacoes;
    if (fread(&nroEstacoes, sizeof(int), 1, f_bin) != 1)
    {
        printf("Falha no processamento do arquivo.\n");
        fclose(f_bin);
        return;
    }
    printf("Número de estações: %d\n", nroEstacoes);

    // Lê o número de pares de estações
    int nroParesEstacao;
    if (fread(&nroParesEstacao, sizeof(int), 1, f_bin) != 1)
    {
        printf("Falha no processamento do arquivo.\n");
        fclose(f_bin);
        return;
    }
    printf("Número de pares de estações: %d\n", nroParesEstacao);

    // Fecha o arquivo
    fclose(f_bin);
}
