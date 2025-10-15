#include <stdio.h>

int main() {
    int tabuleiro[10][10]; // Matriz que representa o tabuleiro
    int i, j;

    // 1. Inicializar o tabuleiro com água (0) ---
    for (i = 0; i < 10; i++) {
        for (j = 0; j < 10; j++) {
            tabuleiro[i][j] = 0; // Preencher com água
        }
    }

    // 2. Definir as coordenadas iniciais dos navios ---
    // Navio 1: Horizontal
    int linhaNavio1 = 2; // Começa na linha 2
    int colunaNavio1 = 4; // Começa na coluna 4

    // Navio 2: Vertical
    int linhaNavio2 = 6; // Começa na linha 6
    int colunaNavio2 = 1; // Começa na coluna 1

    // 3. Verificar se os navios cabem dentro do tabuleiro ---
    if (colunaNavio1 + 3 > 10) {
        printf("Erro: o navio horizontal ultrapassa o limite do tabuleiro!\n");
        return 1;
    }
    if (linhaNavio2 + 3 > 10) {
        printf("Erro: o navio vertical ultrapassa o limite do tabuleiro!\n");
        return 1;
    }

    // 4. Posicionar o primeiro navio (horizontal) ---
    for (j = 0; j < 3; j++) {
        tabuleiro[linhaNavio1][colunaNavio1 + j] = 3;
    }

    // 5. Posicionar o segundo navio (vertical), verificando sobreposição ---
    for (i = 0; i < 3; i++) {
        if (tabuleiro[linhaNavio2 + i][colunaNavio2] == 3) {
            printf("Erro: os navios se sobrepõem!\n");
            return 1;
        }
        tabuleiro[linhaNavio2 + i][colunaNavio2] = 3;
    }

    // 6. Exibir o tabuleiro completo ---
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