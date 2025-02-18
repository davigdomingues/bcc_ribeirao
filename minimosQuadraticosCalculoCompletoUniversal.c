#include <stdio.h>
#include <stdlib.h>

// Função para multiplicar duas matrizes
void multiplicarMatrizes(float **A, float **B, float **resultado, int linhaA, int colunaA, int linhaB, int colunaB) {
    for (int i = 0; i < linhaA; i++) {
        for (int j = 0; j < colunaB; j++) {
            resultado[i][j] = 0;
            for (int k = 0; k < colunaA; k++) {
                resultado[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}

// Função para calcular a transposta de uma matriz
void transpostaMatriz(float **matriz, float **transposta, int linha, int coluna) {
    for (int i = 0; i < linha; i++) {
        for (int j = 0; j < coluna; j++) {
            transposta[j][i] = matriz[i][j];
        }
    }
}

// Função para calcular a inversa de uma matriz nxn (método de Gauss-Jordan)
int inversaMatriz(float **matriz, float **inversa, int n) {
    // Inicializando a matriz identidade
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i == j)
                inversa[i][j] = 1;
            else
                inversa[i][j] = 0;
        }
    }

    // Cria uma cópia da matriz original
    float **matrizCopia = (float **)malloc(n * sizeof(float *));
    for (int i = 0; i < n; i++) {
        matrizCopia[i] = (float *)malloc(n * sizeof(float));
        for (int j = 0; j < n; j++) {
            matrizCopia[i][j] = matriz[i][j];
        }
    }

    // Método de Gauss-Jordan para inversão de matriz
    for (int i = 0; i < n; i++) {
        // Se o elemento pivô é zero, troca de linha
        if (matrizCopia[i][i] == 0) {
            int j = i + 1;
            while (j < n && matrizCopia[j][i] == 0) {
                j++;
            }
            if (j < n) {
                // Troca as linhas
                for (int k = 0; k < n; k++) {
                    float temp = matrizCopia[i][k];
                    matrizCopia[i][k] = matrizCopia[j][k];
                    matrizCopia[j][k] = temp;

                    temp = inversa[i][k];
                    inversa[i][k] = inversa[j][k];
                    inversa[j][k] = temp;
                }
            } else {
                printf("A matriz não é invertível.\n");
                return 0;
            }
        }

        // Normaliza a linha i
        float pivo = matrizCopia[i][i];
        for (int j = 0; j < n; j++) {
            matrizCopia[i][j] /= pivo;
            inversa[i][j] /= pivo;
        }

        // Elimina os elementos acima e abaixo do pivô
        for (int j = 0; j < n; j++) {
            if (j != i) {
                float fator = matrizCopia[j][i];
                for (int k = 0; k < n; k++) {
                    matrizCopia[j][k] -= matrizCopia[i][k] * fator;
                    inversa[j][k] -= inversa[i][k] * fator;
                }
            }
        }
    }

    // Libera a memória da matriz copiada
    for (int i = 0; i < n; i++) {
        free(matrizCopia[i]);
    }
    free(matrizCopia);

    return 1;
}

// Função para imprimir uma matriz
void imprimirMatriz(float **matriz, int linha, int coluna) {
    for (int i = 0; i < linha; i++) {
        for (int j = 0; j < coluna; j++) {
            printf("%.2f ", matriz[i][j]);
        }
        printf("\n");
    }
}

int main() {
    int m, n;

    // Entrada para a matriz A
    printf("Informe o número de linhas da matriz A (M): ");
    scanf("%d", &m);
    printf("Informe o número de colunas da matriz A (N): ");
    scanf("%d", &n);

    // Alocação da matriz A (MxN)
    float **A = (float **)malloc(m * sizeof(float *));
    for (int i = 0; i < m; i++) {
        A[i] = (float *)malloc(n * sizeof(float));
    }

    printf("Digite os elementos da matriz A (%d linhas e %d colunas):\n", m, n);
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            printf("Elemento A[%d][%d]: ", i + 1, j + 1);
            scanf("%f", &A[i][j]);
        }
    }

    // Alocação da matriz C (Mx1)
    float **C = (float **)malloc(m * sizeof(float *));
    for (int i = 0; i < m; i++) {
        C[i] = (float *)malloc(sizeof(float));
    }

    printf("Digite os elementos da matriz C (%d linhas e 1 coluna):\n", m);
    for (int i = 0; i < m; i++) {
        printf("Elemento C[%d]: ", i + 1);
        scanf("%f", &C[i][0]);
    }

    // Alocação da matriz transposta A^T (NxM)
    float **A_T = (float **)malloc(n * sizeof(float *));
    for (int i = 0; i < n; i++) {
        A_T[i] = (float *)malloc(m * sizeof(float));
    }

    // Calculando a transposta de A
    transpostaMatriz(A, A_T, m, n);

    // Alocação da matriz A^T * A (NxN)
    float **A_T_A = (float **)malloc(n * sizeof(float *));
    for (int i = 0; i < n; i++) {
        A_T_A[i] = (float *)malloc(n * sizeof(float));
    }

    // Calculando A^T * A
    multiplicarMatrizes(A_T, A, A_T_A, n, m, m, n);

    // Alocação da matriz inversa de A^T * A
    float **A_T_A_inv = (float **)malloc(n * sizeof(float *));
    for (int i = 0; i < n; i++) {
        A_T_A_inv[i] = (float *)malloc(n * sizeof(float));
    }

    // Calculando a inversa de A^T * A
    if (!inversaMatriz(A_T_A, A_T_A_inv, n)) {
        printf("Erro ao calcular a inversa.\n");
        return 1;
    }

    // Alocação da matriz (A^T * A)^-1 * A^T (NxM)
    float **A_T_A_inv_A_T = (float **)malloc(n * sizeof(float *));
    for (int i = 0; i < n; i++) {
        A_T_A_inv_A_T[i] = (float *)malloc(m * sizeof(float));
    }

    // Calculando (A^T * A)^-1 * A^T
    multiplicarMatrizes(A_T_A_inv, A_T, A_T_A_inv_A_T, n, n, n, m);

    // Alocação da matriz resultado final X (Nx1)
    float **X = (float **)malloc(n * sizeof(float *));
    for (int i = 0; i < n; i++) {
        X[i] = (float *)malloc(sizeof(float));
    }

    // Calculando X = (A^T * A)^-1 * A^T * C
    multiplicarMatrizes(A_T_A_inv_A_T, C, X, n, m, m, 1);

    // Imprimindo o resultado
    printf("Resultado X = (A^T * A)^-1 * A^T * C:\n");
    for (int i = 0; i < n; i++) {
        printf("X[%d]: %.2f\n", i + 1, X[i][0]);
    }

    // Liberando a memória alocada
    for (int i = 0; i < m; i++) free(A[i]);
    for (int i = 0; i < m; i++) free(C[i]);
    for (int i = 0; i < n; i++) free(A_T[i]);
    for (int i = 0; i < n; i++) free(A_T_A[i]);
    for (int i = 0; i < n; i++) free(A_T_A_inv[i]);
    for (int i = 0; i < n; i++) free(A_T_A_inv_A_T[i]);
    for (int i = 0; i < n; i++) free(X[i]);

    free(A);
    free(C);
    free(A_T);
    free(A_T_A);
    free(A_T_A_inv);
    free(A_T_A_inv_A_T);
    free(X);

    return 0;
}
