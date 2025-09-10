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

// --- Função Principal (main) ---
// Função principal que orquestra o fluxo do jogo, chamando as outras funções em ordem.

// bibliotecas
#include <stdio.h> //básico
#include <string.h> //string - texto ou cadeia de caracteres
// constante global para por limite de cadastro na array
#define MAX_TERRITORIO 5
#define TAM_STRING 30
// criando um struct ou molde
struct territorio{
    char nome[30];
    char cor[10];
    int tropas;
};
// função pra limpar os \n dos scanf()
void limparBufferEntrada(){
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}
// função principal
int main() {
    // 1. Configuração Inicial (Setup):
    // - Define o locale para português.
    // - Inicializa a semente para geração de números aleatórios com base no tempo atual.
    // - Aloca a memória para o mapa do mundo e verifica se a alocação foi bem-sucedida.
    // - Preenche os territórios com seus dados iniciais (tropas, donos, etc.).
    // - Define a cor do jogador e sorteia sua missão secreta.

    // 2. Laço Principal do Jogo (Game Loop):
    // - Roda em um loop 'do-while' que continua até o jogador sair (opção 0) ou vencer.
    // - A cada iteração, exibe o mapa, a missão e o menu de ações.
    // - Lê a escolha do jogador e usa um 'switch' para chamar a função apropriada:
    //   - Opção 1: Inicia a fase de ataque.
    //   - Opção 2: Verifica se a condição de vitória foi alcançada e informa o jogador.
    //   - Opção 0: Encerra o jogo.
    // - Pausa a execução para que o jogador possa ler os resultados antes da próxima rodada.

    // 3. Limpeza:
    // - Ao final do jogo, libera a memória alocada para o mapa para evitar vazamentos de memória.

    // define array para guarda struct com molde pronto e define seu limite 5
    struct territorio cadastro[MAX_TERRITORIO];
    // variavel para checar se a quantidade de territorios preenchidos foi completada
    int totalTerritorios = 0;
    // variavel para saber a opcao do usuário foi cadastro (1), lista (2) ou sair (0)
    int opcao;

    
    // loop de perguntas
    do{
        printf("===============================================\n\n");
        printf("WAR ESTRUTURADO - CADASTRO INICIAL\n");
        printf("===============================================\n\n");
        printf(" 1 - Cadastrar territorio\n");
        printf(" 2 - Listar os territorios\n");
        printf(" 0 - Sair do programa\n");
        printf("-----------------------------------------------\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao){
        case 1:
            // coferir se é possível cadastrar, se totalTerritorios for menos que MAX_TERRITORIO (5)
            if (totalTerritorios < MAX_TERRITORIO){
                for (int i = 0; i < MAX_TERRITORIO; i++){
                    // criar uma enumeração no título
                    printf("\n----- Cadastrar territorio %d -----\n", totalTerritorios + 1);
                    // Nome
                    printf("\nNome do Territorio (America, Europa, Asia):");
                    fgets(cadastro[totalTerritorios].nome, TAM_STRING, stdin);
                    // Cor da tropa
                    printf("Cor das tropas (amarelo, azul, branco):");
                    fgets(cadastro[totalTerritorios].cor, TAM_STRING, stdin);
                    // acessar o nome e cor e colocar no lugar de \n por \0 (fim do programa), strcspn vai fazer isso procurando em cada letra
                    cadastro[totalTerritorios].nome[strcspn(cadastro[totalTerritorios].nome, "\n")] = '\0';
                    cadastro[totalTerritorios].cor[strcspn(cadastro[totalTerritorios].cor, "\n")] = '\0';
                    // faço a pergunta com scanf ( que não ler o \n), para limpar o Buffer depois
                    printf("Numero de tropas: ");
                    scanf("%d", &cadastro[totalTerritorios].tropas);
                    limparBufferEntrada();
                    // atualizo a variavel
                    totalTerritorios++;
                }
                
                printf("\nTerritorios cadastrados com sucesso!\n");

            }else{
                printf("Todos os territórios preenchidos! Nao e possivel cadastrar mais tropas.\n");
            }
            
            printf("===============================================\n");
            printf("          MAPA DO MUNDO - ESTADO ATUAL          \n");
            printf("===============================================\n\n");

            for (int i = 0; i < MAX_TERRITORIO; i++){
                printf("Territorio %d: \n", i + 1);
                printf(" - Nome: %s\n", cadastro[i].nome);
                printf(" - Cor: %s \n", cadastro[i].cor);
                printf(" - Tropas: %d \n\n", cadastro[i].tropas);
            }
            
            break;
        
        case 2:
            /* code */
            break;
        case 0:
            /* code */
            break;
        
        default:
            break;
        }
        
    } while (opcao != 0); //repetir se diferente de zero


    return 0;
}

// --- Implementação das Funções ---

// alocarMapa():
// Aloca dinamicamente a memória para o vetor de territórios usando calloc.
// Retorna um ponteiro para a memória alocada ou NULL em caso de falha.

// inicializarTerritorios():
// Preenche os dados iniciais de cada território no mapa (nome, cor do exército, número de tropas).
// Esta função modifica o mapa passado por referência (ponteiro).

// liberarMemoria():
// Libera a memória previamente alocada para o mapa usando free.

// exibirMenuPrincipal():
// Imprime na tela o menu de ações disponíveis para o jogador.

// exibirMapa():
// Mostra o estado atual de todos os territórios no mapa, formatado como uma tabela.
// Usa 'const' para garantir que a função apenas leia os dados do mapa, sem modificá-los.

// exibirMissao():
// Exibe a descrição da missão atual do jogador com base no ID da missão sorteada.

// faseDeAtaque():
// Gerencia a interface para a ação de ataque, solicitando ao jogador os territórios de origem e destino.
// Chama a função simularAtaque() para executar a lógica da batalha.

// simularAtaque():
// Executa a lógica de uma batalha entre dois territórios.
// Realiza validações, rola os dados, compara os resultados e atualiza o número de tropas.
// Se um território for conquistado, atualiza seu dono e move uma tropa.

// sortearMissao():
// Sorteia e retorna um ID de missão aleatório para o jogador.

// verificarVitoria():
// Verifica se o jogador cumpriu os requisitos de sua missão atual.
// Implementa a lógica para cada tipo de missão (destruir um exército ou conquistar um número de territórios).
// Retorna 1 (verdadeiro) se a missão foi cumprida, e 0 (falso) caso contrário.

// limparBufferEntrada():
// Função utilitária para limpar o buffer de entrada do teclado (stdin), evitando problemas com leituras consecutivas de scanf e getchar.
