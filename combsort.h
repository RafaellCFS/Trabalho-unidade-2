#ifndef COMBSORT_H
#define COMBSORT_H

typedef enum {
    TIPO_INTEIRO,
    TIPO_REAL
} TipoDado;

typedef struct {
    TipoDado tipo;
    union {
        int inteiro;
        float real;
    } valor;
} Elemento;

typedef struct {
    Elemento *v;
    int n;
    int gap;
    int i;
    int idxA;
    int idxB;
    int trocou;
    int houveTroca;
    int concluido;
    long comparacoes;
    long trocas;
    long passos;
} CombSort;

double obterChave(const Elemento *e);
int carregarDados(const char *nome, Elemento **v, int *n);
void iniciarCombSort(CombSort *c, Elemento *v, int n);
int passoCombSort(CombSort *c);
void executarCombSort(CombSort *c);

#endif
