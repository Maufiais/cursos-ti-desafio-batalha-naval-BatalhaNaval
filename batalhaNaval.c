#include <stdio.h>

#define TAMANHO 10

// Função para inicializar o tabuleiro com navios pré-definidos
void inicializarTabuleiro(int tabuleiro[TAMANHO][TAMANHO]) {
    for (int i = 0; i < TAMANHO; i++) {
        for (int j = 0; j < TAMANHO; j++) {
            tabuleiro[i][j] = 0;
        }
    }

    // Adicionando navios (3 blocos cada)
    for (int i = 0; i < 3; i++) {
        tabuleiro[3][1 + i] = 1;  // Navio horizontal
        tabuleiro[6][3 + i] = 1;  // Navio horizontal
        tabuleiro[4 + i][5 + i] = 1;  // Navio diagonal
        tabuleiro[7 + i][8 + i] = 1;  // Navio diagonal
    }
}

// Função para exibir o tabuleiro com limitadores e identificadores
void exibirTabuleiro(int tabuleiro[TAMANHO][TAMANHO]) {
    printf("\n   ");
    for (int i = 0; i < TAMANHO; i++) {
        printf("%2d ", i);  // Cabeçalho das colunas
    }
    printf("\n");

    printf("  +");
    for (int i = 0; i < TAMANHO; i++) {
        printf("---");
    }
    printf("+\n");

    for (int i = 0; i < TAMANHO; i++) {
        printf("%2d|", i);  // Indicador de linha
        for (int j = 0; j < TAMANHO; j++) {
            printf(" %d ", tabuleiro[i][j]);
        }
        printf("|\n");
    }

    printf("  +");
    for (int i = 0; i < TAMANHO; i++) {
        printf("---");
    }
    printf("+\n");
}

// Função para aplicar uma habilidade no tabuleiro
void aplicarHabilidade(int tabuleiro[TAMANHO][TAMANHO], int habilidade, int origemX, int origemY) {
    switch (habilidade) {
        case 4: // Cone (4x4)
            for (int i = 0; i < 4; i++) {
                for (int j = -i; j <= i; j++) {
                    if (origemX + i < TAMANHO && origemY + j >= 0 && origemY + j < TAMANHO) {
                        tabuleiro[origemX + i][origemY + j] = 4;
                    }
                }
            }
            break;
        case 5: // Cruz (5x5)
            for (int i = -2; i <= 2; i++) {
                for (int j = -2; j <= 2; j++) {
                    if ((i == 0 || j == 0) && origemX + i >= 0 && origemX + i < TAMANHO &&
                        origemY + j >= 0 && origemY + j < TAMANHO) {
                        tabuleiro[origemX + i][origemY + j] = 5;
                    }
                }
            }
            break;
        case 6: // Octaedro (3x3)
            for (int i = -1; i <= 1; i++) {
                for (int j = -1; j <= 1; j++) {
                    if (abs(i) + abs(j) <= 1 && origemX + i >= 0 && origemX + i < TAMANHO &&
                        origemY + j >= 0 && origemY + j < TAMANHO) {
                        tabuleiro[origemX + i][origemY + j] = 6;
                    }
                }
            }
            break;
        default:
            printf("Habilidade inválida!\n");
    }
}

// Função para validar entrada de posição
int obterPosicaoValida(int *linha, int *coluna) {
    printf("Informe a posição de origem (linha,coluna no formato i,j): ");
    if (scanf("%d,%d", linha, coluna) != 2) {
        printf("Formato inválido! Use i,j (exemplo: 2,3).\n");
        return 0;
    }
    if (*linha < 0 || *linha >= TAMANHO || *coluna < 0 || *coluna >= TAMANHO) {
        printf("Posição fora dos limites! Informe valores entre 0 e %d.\n", TAMANHO - 1);
        return 0;
    }
    return 1;
}

int main() {
    int tabuleiro[TAMANHO][TAMANHO];
    int escolha, habilidade, x, y;

    inicializarTabuleiro(tabuleiro);

    while (1) {
        printf("\nMenu:\n");
        printf("1. Mostrar tabuleiro\n");
        printf("2. Lançar habilidade\n");
        printf("3. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &escolha);

        if (escolha == 1) {
            exibirTabuleiro(tabuleiro);
        } else if (escolha == 2) {
            printf("Escolha uma habilidade (4: Cone, 5: Cruz, 6: Octaedro): ");
            scanf("%d", &habilidade);

            if (obterPosicaoValida(&x, &y)) {
                aplicarHabilidade(tabuleiro, habilidade, x, y);
            }
        } else if (escolha == 3) {
            break;
        } else {
            printf("Opção inválida!\n");
        }
    }

    return 0;
}