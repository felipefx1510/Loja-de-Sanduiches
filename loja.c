#include <stdio.h>
#include <string.h>
#include <locale.h>

// Definindo a estrutura para representar um produto
struct Produto {
    char nome[50];
    float preco;
    int quantidade;
};

// estrutura compra
struct Compra {
    char nomeProduto[50];
    float precoProduto;
};

// Função para validar o login
int validarLogin(char* nome, char* senha) {
    if (strcmp(nome, "mistoquente") == 0 && strcmp(senha, "batatafrita123") == 0) {
        return 1; // Credenciais válidas
    } else {
        return 0; // Credenciais inválidas
    }
}

// Função para cadastrar um produto
void cadastrarProduto(struct Produto* estoque, int* totalProdutos) {
    int continuar = 1;
    while (continuar) {
        while(getchar() != '\n'); // limpa o buffer de entrada

        printf("Digite o nome do produto: ");
        fgets(estoque[*totalProdutos].nome, 50, stdin);
        estoque[*totalProdutos].nome[strcspn(estoque[*totalProdutos].nome, "\n")] = 0; // remove a nova linha do final

        printf("Digite o preço do produto: ");
        scanf("%f", &estoque[*totalProdutos].preco);
        while(getchar() != '\n'); // limpa o buffer de entrada

        printf("Digite a quantidade de estoque disponível: "); // novo prompt para a quantidade de estoque disponível
        scanf("%d", &estoque[*totalProdutos].quantidade);
        while(getchar() != '\n'); // limpa o buffer de entrada

        (*totalProdutos)++;
        printf("Produto cadastrado com sucesso!\n");

        printf("Deseja cadastrar outro produto? (Digite 0 para sair, qualquer outro número para continuar): ");
        scanf("%d", &continuar);
        while(getchar() != '\n'); // limpa o buffer de entrada

        (*totalProdutos)++;
        printf("Produto cadastrado com sucesso!\n");

        printf("Deseja cadastrar outro produto? (Digite 0 para sair, qualquer outro número para continuar): ");
        scanf("%d", &continuar);
        while(getchar() != '\n'); // limpa o buffer de entrada
    }
}

// Função para listar produtos
void listarProdutos(struct Produto* estoque, int totalProdutos) {
    printf("Lista de Produtos:\n");
    for (int i = 0; i < totalProdutos; i++) {
        printf("%d. Nome: %s, Preço: %.2f\n", i + 1, estoque[i].nome, estoque[i].preco);
    }
}

// Função para comprar produto
void comprarProduto(struct Produto* estoque, int totalProdutos, struct Compra* historicoCompras, int* totalCompras) {
    int escolha;
    listarProdutos(estoque, totalProdutos);

    printf("Digite o número do produto que deseja comprar: ");
    scanf("%d", &escolha);

    if (escolha >= 1 && escolha <= totalProdutos) {
        if (estoque[escolha - 1].quantidade > 0) {
            estoque[escolha - 1].quantidade--; // subtrai a quantidade do produto do estoque
            
            // Armazena as informações da compra no histórico de compras
            strcpy(historicoCompras[*totalCompras].nomeProduto, estoque[escolha - 1].nome);
            historicoCompras[*totalCompras].precoProduto = estoque[escolha - 1].preco;
            (*totalCompras)++;
            
            printf("Você comprou o produto: %s por %.2f\n", estoque[escolha - 1].nome, estoque[escolha - 1].preco);
        } else {
            printf("Desculpe, este produto está fora de estoque.\n");
        }
    } else {
        printf("Opção inválida.\n");
    }
}

// Função para exibir o histórico de compras
void exibirHistoricoCompras(struct Compra* historicoCompras, int totalCompras) {
    printf("Histórico de Compras:\n");
    for (int i = 0; i < totalCompras; i++)
    {
        printf("%d. Nome: %s, Preço: %.2f\n", i + 1, historicoCompras[i].nomeProduto, historicoCompras[i].precoProduto);
    }
    
}

int main() {
    setlocale(LC_ALL, "Portuguese_Brazil");

    int funcao;
    int loginbemsucedido = 0;

    // Estrutura para armazenar produtos
    struct Produto estoque[50];
    int totalProdutos = 0;

    // Estrutura para armazenar o histórico de compras
    struct Compra historicoCompras[50];
    int totalCompras = 0;

    while (1) {
        // Menu
        printf("Selecione uma opção:\n");
        printf("1. Entrar\n");
        printf("2. Sair\n");
        scanf("%d", &funcao);

        switch (funcao) {
            case 1:
                // Loop para solicitar as credenciais até que sejam inseridas corretamente
                while (!loginbemsucedido) {
                    // Receber usuário e senha
                    char usuario[50];
                    char senha[50];

                    printf("Digite seu nome de usuário:\n");
                    scanf("%s", usuario);

                    printf("Digite sua senha:\n");
                    scanf("%s", senha);

                    // Validar o login
                    if (validarLogin(usuario, senha)) {
                        printf("Login bem-sucedido!\n");
                        loginbemsucedido = 1;
                    } else {
                        printf("Login falhou.\n Credenciais inválidas, tente novamente!\n");
                    }
                }

                // Após o login bem-sucedido, exibir o menu adicional
                while (loginbemsucedido) {
                    printf("\nMenu Adicional:\n");
                    printf("1. Cadastrar Produto\n");
                    printf("2. Listar Produtos\n");
                    printf("3. Comprar Produto\n");
                    printf("4. Histórico de Compras\n");
                    printf("5. Sair\n");

                    scanf("%d", &funcao);

                    switch (funcao) {
                        case 1:
                            cadastrarProduto(estoque, &totalProdutos);
                            break;

                        case 2:
                            listarProdutos(estoque, totalProdutos);
                            break;

                        case 3:
                            comprarProduto(estoque, totalProdutos, historicoCompras, &totalCompras);
                            break;

                        case 4:
                            exibirHistoricoCompras(historicoCompras, totalCompras);
                            break;

                        case 5:
                            printf("Saindo do programa.\n");
                            return 0; // Encerra o programa

                        default:
                            printf("Opção inválida. Tente novamente.\n");
                    }
                }
                break;

            case 2:
                printf("Saindo do programa.\n");
                return 0; // Encerra o programa

            default:
                printf("Opção inválida. Tente novamente.\n");
        }
    }

    return 0;
}