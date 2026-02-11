#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <locale.h>

void imprimirLinhaSeparadora(int colunas, int larguraCelula) {
    for (int i = 0; i < colunas; i++) {
        printf("+");
        for (int j = 0; j < larguraCelula; j++) {
            printf("-");
        }
    }
    printf("+\n");
}

void imprimirMatriz(int **matriz, int linhas, int colunas, char nomeDaMatriz) {
    const int LARGURA_CELULA = 4;
    printf("\n\nMatriz %c:\n", nomeDaMatriz);
    imprimirLinhaSeparadora(colunas, LARGURA_CELULA);

    for (int i = 0; i < linhas; i++) {
        printf("|");
        for (int j = 0; j < colunas; j++) {
            printf("%*d|", LARGURA_CELULA, matriz[i][j]);
        }
        printf("\n");
        imprimirLinhaSeparadora(colunas, LARGURA_CELULA);
    }
}

int **alocarMatriz(int linhas, int colunas) {
    int **matriz = (int **) malloc(linhas * sizeof(int *));
    for (int i = 0; i < linhas; i++) {
        matriz[i] = (int *) malloc(colunas * sizeof(int));
    }
    return matriz;
}

void desalocarMatriz(int **matriz, int linhas) {
    if (matriz == NULL) return;
    for (int i = 0; i < linhas; i++) {
        free(matriz[i]);
    }
    free(matriz);
}

void preencherMatrizAleatoriamente(int **matriz, int linhas, int colunas) {
    for (int i = 0; i < linhas; i++) {
        for (int j = 0; j < colunas; j++) {
            matriz[i][j] = rand() % 10;
        }
    }
}

void preencherMatrizManualmente(int **matriz, int linhas, int colunas, char nomeMatriz) {
    for (int i = 0; i < linhas; i++) {
        for (int j = 0; j < colunas; j++) {
            printf("Digite o valor para %c[%d][%d]: ", nomeMatriz, i, j);
            scanf("%d", &matriz[i][j]);
        }
    }
}

int calcularCelulaRecursivo(int **matrizA, int **matrizB, int i, int j, int k, int colunasA) {
    if (k >= colunasA) return 0;
    return matrizA[i][k] * matrizB[k][j] + calcularCelulaRecursivo(matrizA, matrizB, i, j, k + 1, colunasA);
}

void multiplicarProdutoRecursivo(int **matrizA, int **matrizB, int **matrizC, int linhasA, int colunasA, int colunasB, int i, int j) {
    if (i >= linhasA) return;
    matrizC[i][j] = calcularCelulaRecursivo(matrizA, matrizB, i, j, 0, colunasA);

    if (j + 1 < colunasB)
        multiplicarProdutoRecursivo(matrizA, matrizB, matrizC, linhasA, colunasA, colunasB, i, j + 1);
    else
        multiplicarProdutoRecursivo(matrizA, matrizB, matrizC, linhasA, colunasA, colunasB, i + 1, 0);
}

void exibirMenu() {
    printf("\n\n\n.-------------------------------.\n");
    printf("| MULTIPLICAÇÃO DE MATRIZES    |\n");
    printf("|------------------------------|\n");
    printf("| 1 - Preencher Manualmente    |\n");
    printf("| 2 - Preencher Automaticamente|\n");
    printf("| 3 - Preencher Semiautomático |\n");
    printf("| 4 - Alterar dimensões        |\n");
    printf("| 5 - Sair                     |\n");
    printf("'-----------------------------'\n");
    printf("Escolha uma opção: ");

}

void exibirIntroducao() {
    printf("\n\n+-------------------------------------+\n");
    printf("|      MULTIPLICACAO DE MATRIZES      |\n");
    printf("+-------------------------------------+\n");
    printf("| Informe o numero de linhas/colunas  |\n");
    printf("|        das matrizes A e B:          |\n");
    printf("+-------------------------------------+\n");
}


int main() {
    setlocale(LC_ALL, "Portuguese");
    srand(time(NULL));

    int linhasA, colunasA, colunasB, linhasB;
    int **matrizA = NULL, **matrizB = NULL, **matrizC = NULL;
    int opcao;

    exibirIntroducao();

    do {
        do {
            printf("\nQual serão as dimensões da primeira matriz? (ixj)\n");
            scanf("%dx%d", &linhasA, &colunasA);
            printf("\nQual serão as dimensões da segunda matriz? (ixj)\n");
            scanf("%dx%d", &linhasB, &colunasB);

            if (linhasA <= 0 || colunasA <= 0 || linhasB <= 0 || colunasB <= 0) {
                printf("\n\nATENÇÃO!!!\nAs dimensões das matrizes devem ser números maiores que zero.\n");
                printf("Tente novamente.\n");
            }
            else if (linhasB!=colunasA){
                printf("\n\nATENÇÃO!!!\nO número de colunas da primeira matriz deve ser igual ao número de linhas da segunda ex: 2x3 e 3x3\n\n");
                printf("Dimensões inválidas! Tente novamente.\n");
            }

        } while (linhasA <= 0 || colunasA <= 0 || linhasB <= 0 || colunasB <= 0 || colunasA != linhasB);

        matrizA = alocarMatriz(linhasA, colunasA);
        matrizB = alocarMatriz(colunasA, colunasB);
        matrizC = alocarMatriz(linhasA, colunasB);

        do {
            exibirMenu();
            scanf("%d", &opcao);

            switch (opcao) {
                case 1:
                    preencherMatrizManualmente(matrizA, linhasA, colunasA, 'A');
                    preencherMatrizManualmente(matrizB, colunasA, colunasB, 'B');
                    break;
                case 2:
                    preencherMatrizAleatoriamente(matrizA, linhasA, colunasA);
                    preencherMatrizAleatoriamente(matrizB, colunasA, colunasB);
                    break;
                case 3:
                    preencherMatrizManualmente(matrizA, linhasA, colunasA, 'A');
                    preencherMatrizAleatoriamente(matrizB, colunasA, colunasB);
                    break;
                case 4:
                    desalocarMatriz(matrizA, linhasA);
                    desalocarMatriz(matrizB, colunasA);
                    desalocarMatriz(matrizC, linhasA);
                    matrizA = matrizB = matrizC = NULL;
                      exibirIntroducao();
                    break;
                case 5:
                    printf("Até logo!\n");
                    break;
                default:
                    printf("Opção inválida. Tente novamente.\n");
            }

            if (opcao >= 1 && opcao <= 3) {
                imprimirMatriz(matrizA, linhasA, colunasA, 'A');
                imprimirMatriz(matrizB, colunasA, colunasB, 'B');

                multiplicarProdutoRecursivo(matrizA, matrizB, matrizC, linhasA, colunasA, colunasB, 0, 0);
                imprimirMatriz(matrizC, linhasA, colunasB, 'C');
            }

        } while (opcao != 4 && opcao != 5);

        if (opcao != 4) {
            desalocarMatriz(matrizA, linhasA);
            desalocarMatriz(matrizB, colunasA);
            desalocarMatriz(matrizC, linhasA);
        }

    } while (opcao != 5);

    return 0;
}
