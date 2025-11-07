#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define TAM_STRING 30

// Estrutura do território
struct Territorio {
    char nome[TAM_STRING];
    char cor[10];
    int tropas;
};

// Função para limpar buffer
void limparBufferEntrada() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// Função para exibir todos os territórios
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

// Função que simula o ataque
void atacar(struct Territorio *atacante, struct Territorio *defensor) {
    if (strcmp(atacante->cor, defensor->cor) == 0) {
        printf("\nVocê não pode atacar um território da mesma cor!\n");
        return;
    }

    if (atacante->tropas < 1) {
        printf("\nO território atacante não tem tropas suficientes!\n");
        return;
    }

    int dadoAtacante = (rand() % 6) + 1;
    int dadoDefensor = (rand() % 6) + 1;

    printf("\nRolando dados...\n");
    printf("Atacante (%s) tirou: %d\n", atacante->nome, dadoAtacante);
    printf("Defensor (%s) tirou: %d\n", defensor->nome, dadoDefensor);

    if (dadoAtacante > dadoDefensor) {
        printf("\nO atacante venceu a batalha!\n");
        strcpy(defensor->cor, atacante->cor);
        defensor->tropas = atacante->tropas / 2;
    } else {
        printf("\nO defensor resistiu! O atacante perdeu 1 tropa.\n");
        atacante->tropas -= 1;
    }
}

// Função para liberar memória
void liberarMemoria(struct Territorio *mapa) {
    free(mapa);
}

int main() {
    srand(time(NULL));

    int totalTerritorios;
    printf("Quantos territórios deseja cadastrar? ");
    scanf("%d", &totalTerritorios);
    limparBufferEntrada();

    struct Territorio *mapa = (struct Territorio*) calloc(totalTerritorios, sizeof(struct Territorio));
    if (mapa == NULL) {
        printf("Erro ao alocar memória!\n");
        return 1;
    }

    // Cadastro dos territórios
    for (int i = 0; i < totalTerritorios; i++) {
        printf("\n--- Cadastro do território %d ---\n", i + 1);
        printf("Nome: ");
        fgets(mapa[i].nome, TAM_STRING, stdin);
        mapa[i].nome[strcspn(mapa[i].nome, "\n")] = '\0';

        printf("Cor: ");
        fgets(mapa[i].cor, 10, stdin);
        mapa[i].cor[strcspn(mapa[i].cor, "\n")] = '\0';

        printf("Tropas: ");
        scanf("%d", &mapa[i].tropas);
        limparBufferEntrada();
    }

    int opcao;
    do {
        printf("\n===============================================\n");
        printf("                 MENU DE OPÇÕES                 \n");
        printf("===============================================\n");
        printf("1 - Exibir territórios\n");
        printf("2 - Atacar\n");
        printf("0 - Sair\n");
        printf("Escolha: ");
        scanf("%d", &opcao);
        limparBufferEntrada();

        switch (opcao) {
            case 1:
                exibirTerritorios(mapa, totalTerritorios);
                break;

            case 2: {
                int indAtacante, indDefensor;
                exibirTerritorios(mapa, totalTerritorios);
                printf("Escolha o número do território atacante: ");
                scanf("%d", &indAtacante);
                printf("Escolha o número do território defensor: ");
                scanf("%d", &indDefensor);
                limparBufferEntrada();

                if (indAtacante < 1 || indAtacante > totalTerritorios ||
                    indDefensor < 1 || indDefensor > totalTerritorios) {
                    printf("\nEscolha inválida!\n");
                    break;
                }

                atacar(&mapa[indAtacante - 1], &mapa[indDefensor - 1]);
                exibirTerritorios(mapa, totalTerritorios);
                break;
            }

            case 0:
                printf("\nSaindo do programa...\n");
                break;

            default:
                printf("\nOpção inválida!\n");
                break;
        }
    } while (opcao != 0);

    liberarMemoria(mapa);
    return 0;
}
