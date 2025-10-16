#include <stdio.h>

int main() {
    int tabuleiro[10][10]; // Matriz que representa o tabuleiro
    int i, j;

    // 1. Inicializar o tabuleiro com água (0)
    for (i = 0; i < 10; i++) {
        for (j = 0; j < 10; j++) {
            tabuleiro[i][j] = 0; // 0 representa água
        }
    }

    // === COORDENADAS INICIAIS DOS NAVIOS ===
    // Navio 1: Horizontal (→)
    int linhaNavio1 = 2;
    int colunaNavio1 = 4;

    // Navio 2: Vertical (↓)
    int linhaNavio2 = 6;
    int colunaNavio2 = 1;

    // Navio 3: Diagonal principal ↘ (linha e coluna aumentam)
    int linhaNavio3 = 0;
    int colunaNavio3 = 0;

    // Navio 4: Diagonal secundária ↙ (linha aumenta, coluna diminui)
    int linhaNavio4 = 0;
    int colunaNavio4 = 9;

    // === VERIFICAÇÃO DE LIMITES ===
    if (colunaNavio1 + 3 > 10) {
        printf("Erro: o navio horizontal ultrapassa o limite do tabuleiro!\n");
        return 1;
    }
    if (linhaNavio2 + 3 > 10) {
        printf("Erro: o navio vertical ultrapassa o limite do tabuleiro!\n");
        return 1;
    }
    if (linhaNavio3 + 3 > 10 || colunaNavio3 + 3 > 10) {
        printf("Erro: o navio diagonal ↘ ultrapassa o limite do tabuleiro!\n");
        return 1;
    }
    if (linhaNavio4 + 3 > 10 || colunaNavio4 - 2 < 0) {
        printf("Erro: o navio diagonal ↙ ultrapassa o limite do tabuleiro!\n");
        return 1;
    }

    // === POSICIONAMENTO DOS NAVIOS ===
    // 1. Horizontal
    for (j = 0; j < 3; j++) {
        tabuleiro[linhaNavio1][colunaNavio1 + j] = 3;
    }

    // 2. Vertical (verifica sobreposição)
    for (i = 0; i < 3; i++) {
        if (tabuleiro[linhaNavio2 + i][colunaNavio2] == 3) {
            printf("Erro: sobreposição entre navios!\n");
            return 1;
        }
        tabuleiro[linhaNavio2 + i][colunaNavio2] = 3;
    }

    // 3. Diagonal principal ↘
    for (i = 0; i < 3; i++) {
        if (tabuleiro[linhaNavio3 + i][colunaNavio3 + i] == 3) {
            printf("Erro: sobreposição entre navios!\n");
            return 1;
        }
        tabuleiro[linhaNavio3 + i][colunaNavio3 + i] = 3;
    }

    // 4. Diagonal secundária ↙
    for (i = 0; i < 3; i++) {
        if (tabuleiro[linhaNavio4 + i][colunaNavio4 - i] == 3) {
            printf("Erro: sobreposição entre navios!\n");
            return 1;
        }
        tabuleiro[linhaNavio4 + i][colunaNavio4 - i] = 3;
    }

    // === EXIBIÇÃO DO TABULEIRO ===
    printf("\n=== TABULEIRO BATALHA NAVAL ===\n\n");
    for (i = 0; i < 10; i++) {
        for (j = 0; j < 10; j++) {
            printf("%d ", tabuleiro[i][j]);
        }
        printf("\n");
    }

    printf("\nLegenda: 0 = Água | 3 = Navio\n");

    return 0;
}