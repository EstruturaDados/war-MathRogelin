#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define TAM_STRING 30

// Estrutura para guardar informações dos territórios
struct Territorio {
    char nome[TAM_STRING];
    char cor[10];
    int tropas;
};

// Variável global para guardar a cor do jogador
char corJogador[10];

// Função para limpar o buffer (tirar o enter do teclado)
void limparBufferEntrada() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// Mostra todos os territórios do mapa
void exibirTerritorios(struct Territorio *mapa, int total) {
    printf("\n===============================================\n");
    printf("               MAPA ATUALIZADO                 \n");
    printf("===============================================\n");
    for (int i = 0; i < total; i++) {
        printf("Território %d:\n", i + 1);
        printf(" - Nome: %s\n", mapa[i].nome);
        printf(" - Cor: %s\n", mapa[i].cor);
        printf(" - Tropas: %d\n\n", mapa[i].tropas);
    }
}

// Função que faz o ataque entre dois territórios
void atacar(struct Territorio *atacante, struct Territorio *defensor) {
    // Verifica se é o mesmo território
    if (strcmp(atacante->cor, defensor->cor) == 0) {
        printf("\nVocê não pode atacar um território da mesma cor!\n");
        return;
    }

    // Verifica se tem tropas pra atacar
    if (atacante->tropas < 2) {
        printf("\nO território atacante precisa ter pelo menos 2 tropas!\n");
        return;
    }

    // Sorteia os dados de 1 até 6
    int dadoAtacante = (rand() % 6) + 1;
    int dadoDefensor = (rand() % 6) + 1;

    printf("\nRolando dados...\n");
    printf("Atacante (%s) tirou: %d\n", atacante->nome, dadoAtacante);
    printf("Defensor (%s) tirou: %d\n", defensor->nome, dadoDefensor);

    // Se o atacante ganhar
    if (dadoAtacante > dadoDefensor) {
        printf("\nO atacante venceu a batalha!\n");
        // O defensor muda pra cor do atacante
        strcpy(defensor->cor, atacante->cor);
        // O defensor fica com metade das tropas do atacante
        defensor->tropas = atacante->tropas / 2;
        // O atacante perde essas tropas
        atacante->tropas -= defensor->tropas;
    } else {
        // Se o defensor ganhar
        printf("\nO defensor resistiu! O atacante perdeu 1 tropa.\n");
        atacante->tropas -= 1;
    }

    // Mostra resultado
    printf("\nResultado final:\n");
    printf("%s (Atacante) - Tropas: %d\n", atacante->nome, atacante->tropas);
    printf("%s (Defensor) - Tropas: %d\n", defensor->nome, defensor->tropas);
}

// Função que sorteia uma missão aleatória
void atribuirMissao(char* destino, char* missoes[], int totalMissoes) {
    int indice = rand() % totalMissoes;
    strcpy(destino, missoes[indice]);
}

// Mostra a missão do jogador
void exibirMissao(const char* missao) {
    printf("\n--- SUA MISSÃO ---\n%s\n", missao);
    printf("------------------\n");
}

// Função que verifica se o jogador cumpriu a missão
int verificarMissao(char* missao, struct Territorio* mapa, int tamanho) {
    // Se a missão for "Conquistar N territórios"
    if (strncmp(missao, "Conquistar ", 11) == 0) {
        int alvo;
        sscanf(missao + 11, "%d", &alvo);

        int conquistados = 0;
        for (int i = 0; i < tamanho; i++) {
            if (strcmp(mapa[i].cor, corJogador) == 0)
                conquistados++;
        }
        return (conquistados >= alvo);
    }

    // Se for "Eliminar todas as tropas da cor X"
    if (strncmp(missao, "Eliminar todas as tropas da cor ", 33) == 0) {
        char corAlvo[10];
        strcpy(corAlvo, missao + 33);

        for (int i = 0; i < tamanho; i++) {
            if (strcmp(mapa[i].cor, corAlvo) == 0 && mapa[i].tropas > 0)
                return 0; // ainda tem inimigo
        }
        return 1; // missão cumprida
    }

    return 0; // se não for nenhum tipo conhecido
}

// Libera a memória alocada
void liberarMemoria(struct Territorio *mapa, char *missao) {
    free(mapa);
    free(missao);
}
