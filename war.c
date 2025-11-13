#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define QTD_TERRITORIOS 5
#define TROPAS_INICIAIS 3

// Estrutura de dados
typedef struct
{
    char nome[30];
    char cor[10];
    int tropas;
    int conquistado;
} Territorio;

// Enum de missões possíveis
typedef enum
{
    DESTRUIR_VERDE,
    CONQUISTAR_TRES
} Missao;

// 🔧 Função para inicializar territórios automaticamente
void inicializarTerritorios(Territorio *territorios, const int qtd)
{
    const char *nomes[] = {"Norte", "Sul", "Leste", "Oeste", "Centro"};
    const char *cores[] = {"Vermelho", "Azul", "Verde", "Amarelo", "Roxo"};

    for (int i = 0; i < qtd; i++)
    {
        strcpy(territorios[i].nome, nomes[i]);
        strcpy(territorios[i].cor, cores[i]);
        territorios[i].tropas = TROPAS_INICIAIS;
        territorios[i].conquistado = 0;
    }
}

// 🗺️ Exibir o estado atual dos territórios
void exibirTerritorios(const Territorio *territorios, const int qtd)
{
    printf("\n===== MAPA ATUAL =====\n");
    for (int i = 0; i < qtd; i++)
    {
        printf("%d - %-8s | Cor: %-8s | Tropas: %-2d | %s\n",
               i + 1,
               territorios[i].nome,
               territorios[i].cor,
               territorios[i].tropas,
               territorios[i].tropas <= 0 ? "💀 Derrotado" : "Ativo");
    }
}

// 🎯 Simula um ataque entre dois territórios
void simularAtaque(Territorio *atacante, Territorio *defensor)
{
    if (atacante->tropas <= 0)
    {
        printf("\n⚠️ %s não tem tropas suficientes para atacar!\n", atacante->nome);
        return;
    }
    if (defensor->tropas <= 0)
    {
        printf("\n⚠️ %s já está derrotado!\n", defensor->nome);
        return;
    }

    int dadoAtaque = (rand() % 6) + 1;
    int dadoDefesa = (rand() % 6) + 1;

    printf("\n🎲 Dados:\n");
    printf("%s (Ataque): %d\n", atacante->nome, dadoAtaque);
    printf("%s (Defesa): %d\n", defensor->nome, dadoDefesa);

    if (dadoAtaque >= dadoDefesa)
    {
        defensor->tropas--;
        printf("💥 %s venceu a rodada!\n", atacante->nome);
        if (defensor->tropas <= 0)
        {
            printf("🏴 %s conquistou o território %s!\n", atacante->nome, defensor->nome);
            defensor->conquistado = 1;
        }
    }
    else
    {
        atacante->tropas--;
        printf("🛡️ %s resistiu ao ataque!\n", defensor->nome);
    }
}

// 🎯 Verifica se a missão foi concluída
int verificarMissao(const Territorio *territorios, const int qtd, const Missao missao)
{
    switch (missao)
    {
    case DESTRUIR_VERDE:
        for (int i = 0; i < qtd; i++)
        {
            if (strcmp(territorios[i].cor, "Verde") == 0 && territorios[i].tropas > 0)
                return 0; // Ainda não destruído
        }
        return 1; // Missão concluída

    case CONQUISTAR_TRES:
    {
        int conquistas = 0;
        for (int i = 0; i < qtd; i++)
        {
            if (territorios[i].conquistado)
                conquistas++;
        }
        return conquistas >= 3;
    }
    }
    return 0;
}

// 📜 Exibir a missão atual
void exibirMissao(const Missao missao)
{
    printf("\n===== SUA MISSÃO =====\n");
    if (missao == DESTRUIR_VERDE)
        printf("🎯 Destruir o exército VERDE!\n");
    else
        printf("🏆 Conquistar 3 territórios!\n");
}

// 🎮 Função principal do menu de jogo
void menuJogo(Territorio *territorios, const int qtd, const Missao missao)
{
    int opcao;
    do
    {
        printf("\n===== MENU PRINCIPAL =====\n");
        printf("1 - Atacar\n");
        printf("2 - Verificar Missão\n");
        printf("0 - Sair\n");
        printf("Escolha: ");
        scanf("%d", &opcao);

        switch (opcao)
        {
        case 1:
        {
            exibirTerritorios(territorios, qtd);
            int a, d;
            printf("\nEscolha o território atacante (1 a %d): ", qtd);
            scanf("%d", &a);
            printf("Escolha o território defensor (1 a %d): ", qtd);
            scanf("%d", &d);

            if (a >= 1 && a <= qtd && d >= 1 && d <= qtd && a != d)
                simularAtaque(&territorios[a - 1], &territorios[d - 1]);
            else
                printf("⚠️ Escolha inválida!\n");

            exibirTerritorios(territorios, qtd);
            break;
        }

        case 2:
            exibirMissao(missao);
            if (verificarMissao(territorios, qtd, missao))
                printf("\n🎉 MISSÃO CUMPRIDA! Você venceu o jogo!\n");
            else
                printf("\n🚧 Missão ainda não concluída. Continue lutando!\n");
            break;

        case 0:
            printf("\nEncerrando o jogo...\n");
            break;

        default:
            printf("\nOpção inválida!\n");
        }

    } while (opcao != 0 && !verificarMissao(territorios, qtd, missao));
}

int main()
{
    srand(time(NULL));

    Territorio *territorios = (Territorio *)calloc(QTD_TERRITORIOS, sizeof(Territorio));
    if (!territorios)
    {
        printf("Erro ao alocar memória!\n");
        return 1;
    }

    inicializarTerritorios(territorios, QTD_TERRITORIOS);

    // Sorteia uma missão aleatória
    Missao missao = (rand() % 2 == 0) ? DESTRUIR_VERDE : CONQUISTAR_TRES;
    exibirMissao(missao);
    exibirTerritorios(territorios, QTD_TERRITORIOS);

    menuJogo(territorios, QTD_TERRITORIOS, missao);

    free(territorios);
    printf("\n🏁 Fim de jogo. Obrigado por jogar!\n");
    return 0;
}
