#include <stdio.h>
#include <stdlib.h>

#define TAM 10       // tamanho do tabuleiro
#define NAVIO 3      // valor que representa navio
#define HABIL 5      // valor que representa área afetada pela habilidade
#define AGUA 0       // água

// Tamanho das matrizes de habilidade (usar matriz ímpar para facilitar centralização)
#define HAB_TAM 5
#define HAB_CENTRO (HAB_TAM / 2)

// Protótipos
void inicializarTabuleiro(int tab[TAM][TAM]);
void posicionarNaviosExemplo(int tab[TAM][TAM]);
void criarCone(int mat[HAB_TAM][HAB_TAM]);
void criarCruz(int mat[HAB_TAM][HAB_TAM]);
void criarOctaedro(int mat[HAB_TAM][HAB_TAM]);
void sobreporHabilidade(int tab[TAM][TAM], int mat[HAB_TAM][HAB_TAM], int origemLinha, int origemColuna);
void exibirTabuleiro(int tab[TAM][TAM]);

int main() {
    int tabuleiro[TAM][TAM];
    int cone[HAB_TAM][HAB_TAM];
    int cruz[HAB_TAM][HAB_TAM];
    int octaedro[HAB_TAM][HAB_TAM];

    // 1) Inicializa tabuleiro com água
    inicializarTabuleiro(tabuleiro);

    // 2) Posiciona navios (exemplo — mantém os navios retos e diagonais do nível anterior)
    posicionarNaviosExemplo(tabuleiro);

    // 3) Construir (dinamicamente) as matrizes de habilidade usando loops e condicionais
    criarCone(cone);       // cone apontando para baixo (topo no centro da linha 0)
    criarCruz(cruz);       // cruz com origem no centro
    criarOctaedro(octaedro); // losango (vista frontal do octaedro)

    // 4) Definir pontos de origem no tabuleiro para cada habilidade
    // Observação: coordenadas definidas diretamente no código (simplificação)
    int origemConeLinha = 3, origemConeColuna = 4;
    int origemCruzLinha = 1, origemCruzColuna = 7;
    int origemOctLinha  = 7, origemOctColuna  = 3;

    // 5) Sobrepor as matrizes de habilidade ao tabuleiro (cuidado com limites)
    sobreporHabilidade(tabuleiro, cone, origemConeLinha, origemConeColuna);
    sobreporHabilidade(tabuleiro, cruz, origemCruzLinha, origemCruzColuna);
    sobreporHabilidade(tabuleiro, octaedro, origemOctLinha, origemOctColuna);

    // 6) Exibir o tabuleiro final
    exibirTabuleiro(tabuleiro);

    return 0;
}

/* Inicializa o tabuleiro 10x10 com água (0) */
void inicializarTabuleiro(int tab[TAM][TAM]) {
    for (int i = 0; i < TAM; i++) {
        for (int j = 0; j < TAM; j++) {
            tab[i][j] = AGUA;
        }
    }
}

/* Posiciona 4 navios de tamanho 3 — 2 retos e 2 diagonais — usando coordenadas fixas.
   Validação simples de sobreposição não é necessária aqui (escolhemos coordenadas sem conflito).
*/
void posicionarNaviosExemplo(int tab[TAM][TAM]) {
    int tamanho = 3;

    // Navio 1: Horizontal (linha 2, coluna 4) -> ocupa (2,4),(2,5),(2,6)
    int l1 = 2, c1 = 4;
    for (int k = 0; k < tamanho; k++) tab[l1][c1 + k] = NAVIO;

    // Navio 2: Vertical (linha 6, coluna 1) -> ocupa (6,1),(7,1),(8,1)
    int l2 = 6, c2 = 1;
    for (int k = 0; k < tamanho; k++) tab[l2 + k][c2] = NAVIO;

    // Navio 3: Diagonal principal ↘ (linha 0, coluna 0) -> (0,0),(1,1),(2,2)
    int l3 = 0, c3 = 0;
    for (int k = 0; k < tamanho; k++) tab[l3 + k][c3 + k] = NAVIO;

    // Navio 4: Diagonal secundária ↙ (linha 0, coluna 9) -> (0,9),(1,8),(2,7)
    int l4 = 0, c4 = 9;
    for (int k = 0; k < tamanho; k++) tab[l4 + k][c4 - k] = NAVIO;
}

/* Cria matriz de habilidade "Cone" (apontando para baixo).
   Estratégia:
   - Matriz de tamanho ímpar HAB_TAM, centro em HAB_CENTRO.
   - O "topo" do cone fica na linha 0, coluna HAB_CENTRO.
   - Para cada linha r (0..HAB_TAM-1) ativamos colunas comportando um triângulo:
       col ∈ [centro - r, centro + r] (limitado à matriz)
*/
void criarCone(int mat[HAB_TAM][HAB_TAM]) {
    // Inicializa tudo com 0
    for (int i = 0; i < HAB_TAM; i++) {
        for (int j = 0; j < HAB_TAM; j++) {
            mat[i][j] = 0;
        }
    }

    // Construção dinâmica do cone com condicionais
    for (int linha = 0; linha < HAB_TAM; linha++) {
        // A largura do cone na linha 'linha' deve aumentar com 'linha'
        int raio = linha; // expansão por linha
        for (int col = HAB_CENTRO - raio; col <= HAB_CENTRO + raio; col++) {
            if (col >= 0 && col < HAB_TAM) {
                mat[linha][col] = 1; // área afetada
            }
        }
    }
}

/* Cria matriz de habilidade "Cruz".
   Estratégia:
   - Marca a linha central inteira e a coluna central inteira com 1.
*/
void criarCruz(int mat[HAB_TAM][HAB_TAM]) {
    // Inicializa com 0
    for (int i = 0; i < HAB_TAM; i++)
        for (int j = 0; j < HAB_TAM; j++)
            mat[i][j] = 0;

    // Linha central
    for (int c = 0; c < HAB_TAM; c++) mat[HAB_CENTRO][c] = 1;

    // Coluna central
    for (int r = 0; r < HAB_TAM; r++) mat[r][HAB_CENTRO] = 1;
}

/* Cria matriz de habilidade "Octaedro" vista frontal (losango).
   Estratégia:
   - Usar distância Manhattan (|dr| + |dc|) para definir o losango.
   - Pontos com |dr| + |dc| <= raio serão 1.
   - raio = HAB_CENTRO garante que o losango ocupe toda a matriz possível.
*/
void criarOctaedro(int mat[HAB_TAM][HAB_TAM]) {
    int raio = HAB_CENTRO; // por exemplo, para HAB_TAM=5, raio=2

    for (int r = 0; r < HAB_TAM; r++) {
        for (int c = 0; c < HAB_TAM; c++) {
            int dr = abs(r - HAB_CENTRO);
            int dc = abs(c - HAB_CENTRO);
            if (dr + dc <= raio) mat[r][c] = 1;
            else mat[r][c] = 0;
        }
    }
}

/* Sobrepõe a matriz de habilidade 'mat' ao tabuleiro 'tab', centrando a matriz
   em (origemLinha, origemColuna). Se uma célula da habilidade == 1, marca-se
   a posição do tabuleiro com HABIL (valor 5), respeitando limites do tabuleiro.
   Observação de simplificação: sobreposição simplesmente sobrescreve o que estiver
   no tabuleiro (inclusive navios). Se preferir manter navios visíveis, pode-se
   alterar a lógica para não sobrescrever valores == NAVIO.
*/
void sobreporHabilidade(int tab[TAM][TAM], int mat[HAB_TAM][HAB_TAM], int origemLinha, int origemColuna) {
    // A posição (origemLinha, origemColuna) do tabuleiro corresponde ao elemento
    // mat[HAB_CENTRO][HAB_CENTRO] da matriz de habilidade.

    for (int r = 0; r < HAB_TAM; r++) {
        for (int c = 0; c < HAB_TAM; c++) {
            if (mat[r][c] == 1) {
                int alvoLinha = origemLinha + (r - HAB_CENTRO);
                int alvoColuna = origemColuna + (c - HAB_CENTRO);

                // Verifica limites do tabuleiro (simplificação: apenas aplica quando dentro)
                if (alvoLinha >= 0 && alvoLinha < TAM && alvoColuna >= 0 && alvoColuna < TAM) {
                    // Aplicar a área afetada:
                    // - Escolhemos sobrescrever com HABIL (5) mesmo que exista navio (3).
                    // - Se preferir manter navios visíveis, checar tab[alvoLinha][alvoColuna] != NAVIO antes de sobrescrever.
                    tab[alvoLinha][alvoColuna] = HABIL;
                }
            }
        }
    }
}

/* Exibe o tabuleiro no console com formatação simples.
   0 = água, 3 = navio, 5 = habilidade
*/
void exibirTabuleiro(int tab[TAM][TAM]) {
    printf("\n=== TABULEIRO BATALHA NAVAL (0=Agua, 3=Navio, 5=Habilidade) ===\n\n");
    for (int i = 0; i < TAM; i++) {
        for (int j = 0; j < TAM; j++) {
            printf("%d ", tab[i][j]);
        }
        printf("\n");
    }
    printf("\nLegenda: 0 = Água | 3 = Navio | 5 = Área afetada pela habilidade\n");
}
