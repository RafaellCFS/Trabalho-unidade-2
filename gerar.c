#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv) {
    if (argc < 4) {
        printf("uso: %s tipo n arquivo\n", argv[0]);
        return 1;
    }
    int n = atoi(argv[2]);
    FILE *f = fopen(argv[3], "w");
    if (f == NULL || n <= 0) {
        return 1;
    }
    srand(42);
    fprintf(f, "%d\n", n);
    for (int k = 0; k < n; k++) {
        int valor;
        if (strcmp(argv[1], "ordenado") == 0) {
            valor = k;
        } else if (strcmp(argv[1], "inverso") == 0) {
            valor = n - k;
        } else if (strcmp(argv[1], "repetido") == 0) {
            valor = rand() % 10;
        } else {
            valor = rand() % 100000;
        }
        fprintf(f, "i %d\n", valor);
    }
    fclose(f);
    return 0;
}
