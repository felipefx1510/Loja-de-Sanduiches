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
    struct Produto produtos[50]; // array para armazenar os produtos comprados
    int totalProdutos; // total de produtos na compra
    char notaFiscal[500]; // novo campo para armazenar a nota fiscal
    int id;
    int quantidadeComprada[50]; // array para armazenar a quantidade de cada produto comprado
};

// Função para validar o login
int validarLogin(char* nome, char* senha) {
    if ((strcmp(nome, "Felipe") == 0 && strcmp(senha, "gostoso") == 0) ||
        (strcmp(nome, "Alycia") == 0 && strcmp(senha, "Taylor23") == 0)) {
        return 1; // Credenciais válidas
    } else {
        return 0; // Credenciais inválidas
    }
}

// Função para cadastrar um produto
void cadastrarProduto(struct Produto* estoque, int* totalProdutos) {
    char continuar = 'S';
    char buffer[50];
    while (toupper(continuar) == 'S') {
        printf("Digite o nome do produto: ");
        fgets(estoque[*totalProdutos].nome, 50, stdin);
        estoque[*totalProdutos].nome[strcspn(estoque[*totalProdutos].nome, "\n")] = 0; // remove a nova linha do final

        printf("Digite o preço do produto: ");
        fgets(buffer, 50, stdin);
        float preco;
        sscanf(buffer, "%f", &preco);
        estoque[*totalProdutos].preco = preco;

        printf("Digite a quantidade de estoque disponível: ");
        fgets(buffer, 50, stdin);
        estoque[*totalProdutos].quantidade = atoi(buffer);

        (*totalProdutos)++;
        printf("Produto cadastrado com sucesso!\n");

        do {
            printf("Deseja cadastrar outro produto? (Digite S para sim, N para não): ");
            scanf(" %c", &continuar);
            while(getchar() != '\n'); // limpa o buffer de entrada

            if (toupper(continuar) != 'S' && toupper(continuar) != 'N') {
            printf("Entrada inválida. Por favor, digite S para sim ou N para não.\n");
             }
} while (toupper(continuar) != 'S' && toupper(continuar) != 'N');
    }
}

// Função para listar produtos
void listarProdutos(struct Produto* estoque, int totalProdutos) {
    printf("Lista de Produtos:\n");
    for (int i = 0; i < totalProdutos; i++) {
        char preco[50];
        sprintf(preco, "%.2f", estoque[i].preco);
        for (int j = 0; preco[j]; j++) {
            if (preco[j] == '.') {
                preco[j] = ',';
            }
        }
        printf("%d. %s, R$ %s, Quantidade Disponível: %d\n", 
               i + 1, 
               estoque[i].nome, 
               preco, 
               estoque[i].quantidade);
    }
}

// Função para comprar produto
void comprarProduto(struct Produto* estoque, int totalProdutos, struct Compra* historicoCompras, int* totalCompras) {
    int codigoProduto;
    char continuar = 'S';
    int quantidadeTotal = 0;
    double valorTotal = 0.0;

    // Inicializa uma nova compra
    struct Compra novaCompra;
    novaCompra.totalProdutos = 0;

    do {
        printf("Digite o código do produto que deseja comprar: ");
        scanf("%d", &codigoProduto);
        while(getchar() != '\n'); // limpa o buffer de entrada

        // Verifica se o código do produto é válido
        if (codigoProduto < 1 || codigoProduto > totalProdutos) {
            printf("Código de produto inválido.\n");
            continue;
        }

        // Ajusta o código do produto para ser usado como índice do array (os índices do array começam em 0)
        codigoProduto--;

        if (estoque[codigoProduto].quantidade > 0) {
            // Reduz a quantidade do produto no estoque
            estoque[codigoProduto].quantidade--;

            // Adiciona o produto à nova compra
            novaCompra.produtos[novaCompra.totalProdutos] = estoque[codigoProduto];
            novaCompra.quantidadeComprada[novaCompra.totalProdutos] = 1; // adiciona 1 à quantidade comprada do produto
            novaCompra.totalProdutos++;

            // Atualiza a quantidade total e o valor total
            quantidadeTotal++;
            valorTotal += estoque[codigoProduto].preco;

            // Imprime o preço do produto e o valor total
            printf("Preço do produto: R$ %.2f\n", estoque[codigoProduto].preco);
            printf("Valor total: R$ %.2lf\n", valorTotal);

            printf("Produto adicionado à compra com sucesso!\n");
        } else {
            printf("Produto indisponível no estoque.\n");
        }

        do {
            printf("Deseja continuar comprando? (Digite S para sim, N para não): ");
            scanf(" %c", &continuar);
            while(getchar() != '\n'); // limpa o buffer de entrada

            if (toupper(continuar) != 'S' && toupper(continuar) != 'N') {
                printf("Entrada inválida. Por favor, digite S para sim ou N para não.\n");
            }
        } while (toupper(continuar) != 'S' && toupper(continuar) != 'N');

    } while (toupper(continuar) == 'S');

    // Adiciona a nova compra ao histórico de compras
    historicoCompras[*totalCompras] = novaCompra;
    (*totalCompras)++;

    printf("Compra finalizada com sucesso");

    exibirNotaFiscal(historicoCompras, *totalCompras, quantidadeTotal, valorTotal);
}

// Exibe a nota fiscal
void exibirNotaFiscal(struct Compra* historicoCompras, int totalCompras, int quantidadeTotal, double valorTotal) {
    printf("\nNota Fiscal:\n");
    for (int i = 0; i < totalCompras; i++) {
        for (int j = 0; j < historicoCompras[i].totalProdutos; j++) {
            printf("Produto: %s, Quantidade: %d, Preço: R$ %.2f\n", 
                   historicoCompras[i].produtos[j].nome, 
                   1, 
                   historicoCompras[i].produtos[j].preco);
        }
    }
    printf("Quantidade total de produtos: %d\n", quantidadeTotal);
    printf("Valor total da compra: R$ %.2lf\n", valorTotal);
}

// Função para exibir o histórico de compras
void exibirHistoricoCompras(struct Compra* historicoCompras, int totalCompras) {
    int numeroCompra;
    printf("\nHistórico de Compras:\n");
    for (int i = 0; i < totalCompras; i++) {
        printf("Compra %d\n", i + 1);
    }
    printf("Digite a nota que deseja abrir: ");
    scanf("%d", &numeroCompra);
    while(getchar() != '\n'); // limpa o buffer de entrada

    // Verifica se o número da compra é válido
    if (numeroCompra < 1 || numeroCompra > totalCompras) {
        printf("Número de compra inválido.\n");
        return;
    }

    // Ajusta o número da compra para ser usado como índice do array (os índices do array começam em 0)
    numeroCompra--;

    printf("Compra %d\n", numeroCompra + 1);
    for (int j = 0; j < historicoCompras[numeroCompra].totalProdutos; j++) {
        printf("Produto: %s, Quantidade: %d, Preço: R$ %.2f\n", 
               historicoCompras[numeroCompra].produtos[j].nome, 
               historicoCompras[numeroCompra].quantidadeComprada[j], 
               historicoCompras[numeroCompra].produtos[j].preco);
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
        while(getchar() != '\n'); // limpa o buffer de entrada

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
                    while(getchar() != '\n'); // limpa o buffer de entrada
                    
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