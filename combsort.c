#include <stdio.h>
#include <stdlib.h>
#include "combsort.h"

double obterChave(const Elemento *e) {
    if (e->tipo == TIPO_REAL) {
        return (double)e->valor.real;
    }
    return (double)e->valor.inteiro;
}

int carregarDados(const char *nome, Elemento **v, int *n) {
    FILE *f = fopen(nome, "r");
    if (f == NULL) {
        return 0;
    }
    int qtd;
    if (fscanf(f, "%d", &qtd) != 1 || qtd <= 0) {
        fclose(f);
        return 0;
    }
    Elemento *dados = malloc(qtd * sizeof(Elemento));
    if (dados == NULL) {
        fclose(f);
        return 0;
    }
    for (int k = 0; k < qtd; k++) {
        char t;
        int ok;
        if (fscanf(f, " %c", &t) != 1) {
            ok = 0;
        } else if (t == 'f') {
            dados[k].tipo = TIPO_REAL;
            ok = fscanf(f, "%f", &dados[k].valor.real) == 1;
        } else {
            dados[k].tipo = TIPO_INTEIRO;
            ok = fscanf(f, "%d", &dados[k].valor.inteiro) == 1;
        }
        if (!ok) {
            free(dados);
            fclose(f);
            return 0;
        }
    }
    fclose(f);
    *v = dados;
    *n = qtd;
    return 1;
}

static int proximoGap(int gap) {
    gap = (gap * 10) / 13;
    if (gap < 1) {
        gap = 1;
    }
    return gap;
}

static void trocar(Elemento *a, Elemento *b) {
    Elemento temp = *a;
    *a = *b;
    *b = temp;
}

void iniciarCombSort(CombSort *c, Elemento *v, int n) {
    c->v = v;
    c->n = n;
    c->gap = n;
    c->i = 0;
    c->idxA = -1;
    c->idxB = -1;
    c->trocou = 0;
    c->houveTroca = 0;
    c->concluido = (n < 2);
    c->comparacoes = 0;
    c->trocas = 0;
    c->passos = 0;
}

int passoCombSort(CombSort *c) {
    if (c->concluido) {
        return 0;
    }
    if (c->i == 0) {
        c->gap = proximoGap(c->gap);
        c->trocou = 0;
    }
    int a = c->i;
    int b = c->i + c->gap;
    Elemento *pa = &c->v[a];
    Elemento *pb = &c->v[b];
    c->idxA = a;
    c->idxB = b;
    c->houveTroca = 0;
    c->comparacoes++;
    c->passos++;
    if (obterChave(pa) > obterChave(pb)) {
        trocar(pa, pb);
        c->trocas++;
        c->passos++;
        c->trocou = 1;
        c->houveTroca = 1;
    }
    c->i++;
    if (c->i + c->gap >= c->n) {
        if (c->gap == 1 && !c->trocou) {
            c->concluido = 1;
        }
        c->i = 0;
    }
    return 1;
}

void executarCombSort(CombSort *c) {
    while (passoCombSort(c)) {
    }
}
