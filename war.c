// ============================================================================
//         PROJETO WAR ESTRUTURADO - DESAFIO DE CÓDIGO
// ============================================================================
//        
// ============================================================================
//
// OBJETIVOS:
// - Modularizar completamente o código em funções especializadas.
// - Implementar um sistema de missões para um jogador.
// - Criar uma função para verificar se a missão foi cumprida.
// - Utilizar passagem por referência (ponteiros) para modificar dados e
//   passagem por valor/referência constante (const) para apenas ler.
// - Foco em: Design de software, modularização, const correctness, lógica de jogo.
//
// ============================================================================

// Inclusão das bibliotecas padrão necessárias para entrada/saída, alocação de memória, manipulação de strings e tempo.

// --- Constantes Globais ---
// Definem valores fixos para o número de territórios, missões e tamanho máximo de strings, facilitando a manutenção.

// --- Estrutura de Dados ---
// Define a estrutura para um território, contendo seu nome, a cor do exército que o domina e o número de tropas.

// --- Protótipos das Funções ---
// Declarações antecipadas de todas as funções que serão usadas no programa, organizadas por categoria.
// Funções de setup e gerenciamento de memória:
// Funções de interface com o usuário:
// Funções de lógica principal do jogo:
// Função utilitária:


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Estrutura que representa um território
typedef struct {
    char nome[30];
    char cor[10];
    int tropas;
} Territorio;

// Cadastro dos territórios
void cadastrarTerritorios(Territorio *mapa, int quantidade) {

    for(int i = 0; i < quantidade; i++) {

        printf("\n=== Território %d ===\n", i + 1);

        printf("Nome: ");
        scanf("%29s", mapa[i].nome);

        printf("Cor do exército: ");
        scanf("%9s", mapa[i].cor);

        printf("Quantidade de tropas: ");
        scanf("%d", &mapa[i].tropas);
    }
}

// Exibe todos os territórios
void exibirTerritorios(Territorio *mapa, int quantidade) {

    printf("\n======= MAPA =======\n");

    for(int i = 0; i < quantidade; i++) {

        printf("\nTerritório %d\n", i);

        printf("Nome: %s\n", mapa[i].nome);
        printf("Cor: %s\n", mapa[i].cor);
        printf("Tropas: %d\n", mapa[i].tropas);
    }
}

// Função que simula um ataque
void atacar(Territorio *atacante, Territorio *defensor) {

    int dadoAtacante = rand() % 6 + 1;
    int dadoDefensor = rand() % 6 + 1;

    printf("\n===== BATALHA =====\n");
    printf("%s lançou %d\n", atacante->nome, dadoAtacante);
    printf("%s lançou %d\n", defensor->nome, dadoDefensor);

    if(dadoAtacante > dadoDefensor) {

        printf("\nO atacante venceu!\n");

        strcpy(defensor->cor, atacante->cor);

        defensor->tropas = atacante->tropas / 2;

        atacante->tropas -= defensor->tropas;
    }
    else {

        printf("\nO defensor venceu!\n");

        if(atacante->tropas > 1)
            atacante->tropas--;
    }
}

// Libera memória
void liberarMemoria(Territorio *mapa) {

    free(mapa);
}

int main() {

    srand(time(NULL));

    int quantidade;

    printf("Quantidade de territórios: ");
    scanf("%d", &quantidade);

    // Alocação dinâmica
    Territorio *mapa = (Territorio*) calloc(quantidade, sizeof(Territorio));

    if(mapa == NULL) {
        printf("Erro na alocação de memória.\n");
        return 1;
    }

    cadastrarTerritorios(mapa, quantidade);

    exibirTerritorios(mapa, quantidade);

    int atacante, defensor;

    printf("\nEscolha o índice do território atacante: ");
    scanf("%d", &atacante);

    printf("Escolha o índice do território defensor: ");
    scanf("%d", &defensor);

    // Validação
    if(atacante >= 0 && atacante < quantidade &&
       defensor >= 0 && defensor < quantidade) {

        if(strcmp(mapa[atacante].cor, mapa[defensor].cor) == 0) {

            printf("\nNão é permitido atacar um território da mesma cor.\n");

        } else {

            atacar(&mapa[atacante], &mapa[defensor]);

            exibirTerritorios(mapa, quantidade);
        }

    } else {

        printf("\nÍndices inválidos.\n");
    }

    liberarMemoria(mapa);

    return 0;
}
