# Comb Sort com visualização em Raylib

Trabalho Prático da Unidade II – Algoritmos de Busca e Ordenação

**Universidade Federal Rural do Semi-Árido (UFERSA)**
**Disciplina:** Algoritmos e Estrutura de Dados I – **Semestre:** 2026.2
**Professora:** Rosana Rego
**Discentes:** Gabriel Duarte Martins e Rafael Caetano Fernandes da Silva

## Sobre o projeto

Implementação do algoritmo **Comb Sort** em linguagem C, sem funções prontas de ordenação como `qsort()`, com visualização gráfica feita na biblioteca **Raylib**. Os dados são lidos de arquivos de texto, e as estatísticas (comparações, trocas e passos) são contadas durante a execução real do algoritmo.

Recursos da linguagem utilizados: `struct`, ponteiros, `enum`, `union` e arquivos. A justificativa de cada um está no relatório em PDF.

## Estrutura do repositório

```
.
├── combsort.h        # structs, enums, union e protótipos
├── combsort.c        # leitura de arquivo e algoritmo Comb Sort (passo a passo)
├── main.c            # visualização com Raylib
├── gerar.c           # gerador dos arquivos de entrada
├── experimentos.c    # coleta de comparações, trocas e tempo
├── dados/            # arquivos de entrada (gerados por gerar.c)
├── README.md
└── relatorio.pdf
```

## Dependências

- Compilador **GCC** (Linux, macOS ou MinGW no Windows)
- Biblioteca **Raylib** 4.x ou superior (necessária apenas para a visualização, `main.c`)

Instalação da Raylib:

- **macOS:** `brew install raylib`
- **Linux:** instale pelo gerenciador de pacotes da distribuição, se disponível, ou compile a partir do código-fonte seguindo as instruções em https://github.com/raysan5/raylib
- **Windows:** use o instalador oficial da Raylib, que já inclui o MinGW (https://www.raylib.com)

## Formato dos arquivos de entrada

A primeira linha contém a quantidade de elementos `n`. Cada uma das `n` linhas seguintes contém o tipo do dado e o valor: `i` para inteiro ou `f` para real.

```
5
i 42
i 7
f 3.14
i 19
i 7
```

## Gerando os arquivos de entrada

O programa `gerar` recebe o perfil dos dados, a quantidade de elementos e o arquivo de saída. Os perfis disponíveis são `aleatorio`, `ordenado`, `inverso` e `repetido`. A semente aleatória é fixa (42), então os arquivos gerados são sempre os mesmos.

```
gcc gerar.c -o gerar
mkdir -p dados
./gerar aleatorio 100 dados/aleatorio_100.txt
```

Para gerar todos os arquivos usados nos experimentos (Linux, macOS ou Git Bash no Windows):

```
for t in aleatorio ordenado inverso repetido; do
  for n in 10 100 500 1000 5000 10000; do
    ./gerar $t $n dados/${t}_$n.txt
  done
done
```

## Compilação e execução da visualização

**Linux:**

```
gcc main.c combsort.c -o combsort -lraylib -lGL -lm -lpthread -ldl -lrt -lX11
./combsort dados/aleatorio_100.txt
```

**macOS:**

```
gcc main.c combsort.c -o combsort $(pkg-config --cflags --libs raylib) -lm
./combsort dados/aleatorio_100.txt
```

**Windows (MinGW):**

```
gcc main.c combsort.c -o combsort.exe -lraylib -lopengl32 -lgdi32 -lwinmm
combsort.exe dados\aleatorio_100.txt
```

Se nenhum arquivo for informado, o programa usa `dados/aleatorio_100.txt`.

### Controles

| Tecla | Função |
|---|---|
| ENTER | Iniciar |
| P | Pausar |
| C | Continuar |
| R | Reiniciar (restaura o vetor original lido do arquivo) |
| S | Executar o próximo passo |
| Seta para cima / baixo | Aumentar / diminuir a velocidade (passos por quadro) |

### Cores das barras

- **Azul:** elementos não envolvidos no passo atual
- **Amarelo:** par comparado (`i` e `i + gap`) sem troca
- **Vermelho:** par que acabou de ser trocado
- **Verde:** vetor ordenado

O painel no canto da tela mostra o algoritmo, o número de elementos, as comparações, as trocas, o passo, o gap atual, o estado e a velocidade.

## Experimentos

O programa `experimentos` lê os arquivos de `dados/` (4 perfis × 6 tamanhos: 10, 100, 500, 1000, 5000 e 10000), executa o Comb Sort, confere se o vetor ficou ordenado e imprime em CSV o número de comparações, trocas e o tempo em milissegundos.

```
gcc experimentos.c combsort.c -o experimentos
./experimentos > resultados.csv
```

O tempo depende da máquina e das opções de compilação. Comparações e trocas são sempre iguais para os mesmos arquivos.

## Complexidade do Comb Sort

| Caso | Tempo | Espaço auxiliar |
|---|---|---|
| Melhor caso | Θ(n log n) | O(1) |
| Caso médio | próximo de n log n (observado nos experimentos) | O(1) |
| Pior caso | O(n²) | O(1) |

A análise completa, os resultados e a comparação com a teoria estão no relatório (`relatorio.pdf`).
