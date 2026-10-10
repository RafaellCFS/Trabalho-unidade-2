#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "combsort.h"

int main(void) {
    const char *tipos[] = {"aleatorio", "ordenado", "inverso", "repetido"};
    int tamanhos[] = {10, 100, 500, 1000, 5000, 10000};
    printf("tipo,n,comparacoes,trocas,tempo_ms\n");
    for (int t = 0; t < 4; t++) {
        for (int s = 0; s < 6; s++) {
            char nome[64];
            snprintf(nome, sizeof(nome), "dados/%s_%d.txt", tipos[t], tamanhos[s]);
            Elemento *v = NULL;
            int n = 0;
            if (!carregarDados(nome, &v, &n)) {
                printf("erro ao abrir %s\n", nome);
                return 1;
            }
            CombSort c;
            iniciarCombSort(&c, v, n);
            clock_t ini = clock();
            executarCombSort(&c);
            clock_t fim = clock();
            double ms = 1000.0 * (double)(fim - ini) / CLOCKS_PER_SEC;
            for (int k = 1; k < n; k++) {
                if (obterChave(&v[k - 1]) > obterChave(&v[k])) {
                    printf("ERRO: nao ordenado\n");
                    return 1;
                }
            }
            printf("%s,%d,%ld,%ld,%.3f\n", tipos[t], n, c.comparacoes, c.trocas, ms);
            free(v);
        }
    }
    return 0;
}
