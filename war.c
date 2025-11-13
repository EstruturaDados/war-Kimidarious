#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

/*
  Estrutura de dados composta (struct):
  Representa um território com nome, cor e quantidade de tropas.
*/
typedef struct {
    char nome[30];
    char cor[10];
    int tropas;
} Territorio;

/*
  Função: cadastrarTerritorios
  Descrição: Preenche os dados de cada território.
*/
void cadastrarTerritorios(Territorio *territorios, int qtd) {
    for (int i = 0; i < qtd; i++) {
        printf("\n--- Cadastro do Território %d ---\n", i + 1);

        printf("Nome: ");
        scanf(" %29[^\n]", territorios[i].nome);

        printf("Cor do exército: ");
        scanf(" %9s", territorios[i].cor);

        printf("Quantidade de tropas: ");
        scanf("%d", &territorios[i].tropas);
    }
}

/*
  Função: exibirTerritorios
  Descrição: Mostra o estado atual dos territórios.
*/
void exibirTerritorios(Territorio *territorios, int qtd) {
    printf("\n===== ESTADO ATUAL DOS TERRITÓRIOS =====\n");
    for (int i = 0; i < qtd; i++) {
        printf("\nTerritório %d:\n", i + 1);
        printf("Nome: %s\n", territorios[i].nome);
        printf("Cor: %s\n", territorios[i].cor);
        printf("Tropas: %d\n", territorios[i].tropas);
    }
}

/*
  Função: simularAtaque
  Descrição: Simula uma batalha entre dois territórios.
*/
void simularAtaque(Territorio *atacante, Territorio *defensor) {
    int dadoAtaque = (rand() % 6) + 1;   // valor entre 1 e 6
    int dadoDefesa = (rand() % 6) + 1;

    printf("\n🎲 Dados de batalha:\n");
    printf("%s (Ataque): %d\n", atacante->nome, dadoAtaque);
    printf("%s (Defesa): %d\n", defensor->nome, dadoDefesa);

    if (dadoAtaque >= dadoDefesa) {
        defensor->tropas--;
        printf("\n💥 %s venceu a batalha!\n", atacante->nome);
        if (defensor->tropas <= 0) {
            defensor->tropas = 0;
            printf("🏴 Território %s foi conquistado por %s!\n", defensor->nome, atacante->nome);
        }
    } else {
        printf("\n🛡️ %s resistiu ao ataque!\n", defensor->nome);
    }
}

int main() {
    srand(time(NULL)); // inicializa o gerador de números aleatórios

    int qtd = 5;
    Territorio *territorios;

    // Alocação dinâmica de memória
    territorios = (Territorio *)calloc(qtd, sizeof(Territorio));
    if (territorios == NULL) {
        printf("Erro ao alocar memória.\n");
        return 1;
    }

    printf("===== Cadastro de Territórios =====\n");
    cadastrarTerritorios(territorios, qtd);
    exibirTerritorios(territorios, qtd);

    int opcao;
    do {
        printf("\n===== FASE DE BATALHA =====\n");
        printf("Escolha o território atacante (1 a %d): ", qtd);
        int a;
        scanf("%d", &a);

        printf("Escolha o território defensor (1 a %d): ", qtd);
        int d;
        scanf("%d", &d);

        if (a >= 1 && a <= qtd && d >= 1 && d <= qtd && a != d) {
            simularAtaque(&territorios[a - 1], &territorios[d - 1]);
        } else {
            printf("⚠️ Escolha inválida! Tente novamente.\n");
        }

        exibirTerritorios(territorios, qtd);

        printf("\nDeseja realizar outra batalha? (1 - Sim / 0 - Não): ");
        scanf("%d", &opcao);
    } while (opcao != 0);

    // Libera a memória alocada dinamicamente
    free(territorios);

    printf("\nJogo encerrado. Obrigado por jogar!\n");
    return 0;
}
