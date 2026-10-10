#include <stdlib.h>
#include <string.h>
#include "raylib.h"
#include "combsort.h"

#define LARGURA 1000
#define ALTURA 700
#define ALTURA_MAX_BARRA 480
#define BASE_Y 690

typedef enum {
    ESTADO_PARADO,
    ESTADO_EXECUTANDO,
    ESTADO_PAUSADO,
    ESTADO_FINALIZADO
} Estado;

static const char *nomeEstado(Estado e) {
    switch (e) {
        case ESTADO_PARADO: return "Parado";
        case ESTADO_EXECUTANDO: return "Executando";
        case ESTADO_PAUSADO: return "Pausado";
        default: return "Finalizado";
    }
}

static void calcularLimites(const Elemento *v, int n, double *min, double *max) {
    *min = obterChave(&v[0]);
    *max = *min;
    for (int k = 1; k < n; k++) {
        double chave = obterChave(&v[k]);
        if (chave < *min) {
            *min = chave;
        }
        if (chave > *max) {
            *max = chave;
        }
    }
}

static void desenharBarras(const CombSort *c, Estado estado, double min, double max) {
    float largura = (float)LARGURA / (float)c->n;
    int larguraBarra = (int)largura > 1 ? (int)largura - 1 : 1;
    for (int k = 0; k < c->n; k++) {
        float altura = ALTURA_MAX_BARRA / 2.0f;
        if (max > min) {
            double chave = obterChave(&c->v[k]);
            altura = 10.0f + (float)((chave - min) / (max - min)) * (ALTURA_MAX_BARRA - 10.0f);
        }
        Color cor = SKYBLUE;
        if (estado == ESTADO_FINALIZADO) {
            cor = GREEN;
        } else if (k == c->idxA || k == c->idxB) {
            cor = c->houveTroca ? RED : YELLOW;
        }
        DrawRectangle((int)(k * largura), BASE_Y - (int)altura, larguraBarra, (int)altura, cor);
    }
}

int main(int argc, char **argv) {
    const char *arquivo = "dados/aleatorio_100.txt";
    if (argc > 1) {
        arquivo = argv[1];
    }
    Elemento *v = NULL;
    int n = 0;
    if (!carregarDados(arquivo, &v, &n)) {
        TraceLog(LOG_ERROR, "Nao foi possivel ler %s", arquivo);
        return 1;
    }
    Elemento *original = malloc(n * sizeof(Elemento));
    if (original == NULL) {
        free(v);
        return 1;
    }
    memcpy(original, v, n * sizeof(Elemento));

    double min, max;
    calcularLimites(v, n, &min, &max);

    CombSort c;
    iniciarCombSort(&c, v, n);
    Estado estado = ESTADO_PARADO;
    int velocidade = 1;

    InitWindow(LARGURA, ALTURA, "Comb Sort - UFERSA");
    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        if (IsKeyPressed(KEY_ENTER) && estado == ESTADO_PARADO) {
            estado = ESTADO_EXECUTANDO;
        }
        if (IsKeyPressed(KEY_P) && estado == ESTADO_EXECUTANDO) {
            estado = ESTADO_PAUSADO;
        }
        if (IsKeyPressed(KEY_C) && estado == ESTADO_PAUSADO) {
            estado = ESTADO_EXECUTANDO;
        }
        if (IsKeyPressed(KEY_R)) {
            memcpy(v, original, n * sizeof(Elemento));
            iniciarCombSort(&c, v, n);
            estado = ESTADO_PARADO;
        }
        if (IsKeyPressed(KEY_UP) && velocidade < 1024) {
            velocidade *= 2;
        }
        if (IsKeyPressed(KEY_DOWN) && velocidade > 1) {
            velocidade /= 2;
        }
        if (IsKeyPressed(KEY_S) && (estado == ESTADO_PARADO || estado == ESTADO_PAUSADO)) {
            passoCombSort(&c);
            estado = ESTADO_PAUSADO;
        }
        if (estado == ESTADO_EXECUTANDO) {
            for (int k = 0; k < velocidade; k++) {
                passoCombSort(&c);
            }
        }
        if (c.concluido && estado != ESTADO_PARADO) {
            estado = ESTADO_FINALIZADO;
        }

        BeginDrawing();
        ClearBackground(BLACK);
        DrawText("Algoritmo: Comb Sort", 10, 10, 20, RAYWHITE);
        DrawText(TextFormat("Elementos: %d", n), 10, 35, 20, RAYWHITE);
        DrawText(TextFormat("Comparacoes: %ld", c.comparacoes), 10, 60, 20, RAYWHITE);
        DrawText(TextFormat("Trocas: %ld", c.trocas), 10, 85, 20, RAYWHITE);
        DrawText(TextFormat("Passo: %ld", c.passos), 10, 110, 20, RAYWHITE);
        DrawText(TextFormat("Gap: %d", c.gap), 10, 135, 20, RAYWHITE);
        DrawText(TextFormat("Estado: %s  Velocidade: %dx", nomeEstado(estado), velocidade), 10, 160, 20, RAYWHITE);
        DrawText("ENTER iniciar | P pausar | C continuar | R reiniciar | S proximo passo | CIMA/BAIXO velocidade", 330, 10, 14, LIGHTGRAY);
        desenharBarras(&c, estado, min, max);
        EndDrawing();
    }

    CloseWindow();
    free(v);
    free(original);
    return 0;
}
