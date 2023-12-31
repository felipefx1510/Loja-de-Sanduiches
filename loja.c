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
    int quantidade;
    char notaFiscal[500]; // novo campo para armazenar a nota fiscal
    int id;
};

// Fun��o para validar o login
int validarLogin(char* nome, char* senha) {
    if ((strcmp(nome, "Felipe") == 0 && strcmp(senha, "gostoso") == 0) ||
        (strcmp(nome, "Alycia") == 0 && strcmp(senha, "Taylor23") == 0)) {
        return 1; // Credenciais v�lidas
    } else {
        return 0; // Credenciais inv�lidas
    }
}

// Fun��o para cadastrar um produto
void cadastrarProduto(struct Produto* estoque, int* totalProdutos) {
    char continuar = 'S';
    char buffer[50];
    while (toupper(continuar) == 'S') {
        printf("Digite o nome do produto: ");
        fgets(estoque[*totalProdutos].nome, 50, stdin);
        estoque[*totalProdutos].nome[strcspn(estoque[*totalProdutos].nome, "\n")] = 0; // remove a nova linha do final

        printf("Digite o pre�o do produto: ");
        fgets(buffer, 50, stdin);
        float preco;
        sscanf(buffer, "%f", &preco);
        estoque[*totalProdutos].preco = preco;

        printf("Digite a quantidade de estoque dispon�vel: ");
        fgets(buffer, 50, stdin);
        estoque[*totalProdutos].quantidade = atoi(buffer);

        (*totalProdutos)++;
        printf("Produto cadastrado com sucesso!\n");

        do {
            printf("Deseja cadastrar outro produto? (Digite S para sim, N para n�o): ");
            scanf(" %c", &continuar);
            while(getchar() != '\n'); // limpa o buffer de entrada

            if (toupper(continuar) != 'S' && toupper(continuar) != 'N') {
            printf("Entrada inv�lida. Por favor, digite S para sim ou N para n�o.\n");
             }
} while (toupper(continuar) != 'S' && toupper(continuar) != 'N');
    }
}

// Fun��o para listar produtos
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
        printf("%d. %s, R$ %s, Quantidade Dispon�vel: %d\n", 
               i + 1, 
               estoque[i].nome, 
               preco, 
               estoque[i].quantidade);
    }
}

// Fun��o para comprar produto
void comprarProduto(struct Produto* estoque, int totalProdutos, struct Compra* historicoCompras, int* totalCompras) {
    memset(historicoCompras, 0, sizeof(struct Compra) * 50);
    *totalCompras = 0;
    int codigoProduto;
    char continuar = 'S';
    int quantidadeTotal = 0;
    double valorTotal = 0.0;

    do {
        printf("Digite o c�digo do produto que deseja comprar: ");
        scanf("%d", &codigoProduto);
        while(getchar() != '\n'); // limpa o buffer de entrada

        // Verifica se o c�digo do produto � v�lido
        if (codigoProduto < 1 || codigoProduto > totalProdutos) {
            printf("C�digo de produto inv�lido.\n");
            continue;
        }

        // Ajusta o c�digo do produto para ser usado como �ndice do array (os �ndices do array come�am em 0)
        codigoProduto--;

        if (estoque[codigoProduto].quantidade > 0) {
            // Reduz a quantidade do produto no estoque
            estoque[codigoProduto].quantidade--;

            // Adiciona a compra ao hist�rico de compras
            historicoCompras[*totalCompras].id = *totalCompras + 1; // atribui um id �nico � compra
            strcpy(historicoCompras[*totalCompras].nomeProduto, estoque[codigoProduto].nome);
            historicoCompras[*totalCompras].precoProduto = estoque[codigoProduto].preco;
            historicoCompras[*totalCompras].quantidade = 1;

             // Gera a nota fiscal e a armazena na estrutura Compra
            char notaFiscal[500];
            sprintf(notaFiscal, "Produto: %s, Quantidade: %d, Pre�o: R$ %.2f\n", 
                estoque[codigoProduto].nome, 
                1, 
                estoque[codigoProduto].preco);
            strcpy(historicoCompras[*totalCompras].notaFiscal, notaFiscal);

            (*totalCompras)++;

            // Atualiza a quantidade total e o valor total
            quantidadeTotal++;
            valorTotal += estoque[codigoProduto].preco;

            // Imprime o pre�o do produto e o valor total
            printf("Pre�o do produto: R$ %.2f\n", estoque[codigoProduto].preco);
            printf("Valor total: R$ %.2lf\n", valorTotal);

            printf("Produto adicionado � compra com sucesso!\n");
        } else {
            printf("Produto indispon�vel no estoque.\n");
        }

        do {
        printf("Deseja continuar comprando? (Digite S para sim, N para n�o): ");
        scanf(" %c", &continuar);
        while(getchar() != '\n'); // limpa o buffer de entrada

        if (toupper(continuar) != 'S' && toupper(continuar) != 'N') {
            printf("Entrada inv�lida. Por favor, digite S para sim ou N para n�o.\n");
        }
    } while (toupper(continuar) != 'S' && toupper(continuar) != 'N');

} while (toupper(continuar) == 'S');

    printf("Compra finalizada com sucesso!\n");

    exibirNotaFiscal(historicoCompras, *totalCompras, quantidadeTotal, valorTotal);
}

// Exibe a nota fiscal
void exibirNotaFiscal(struct Compra* historicoCompras, int totalCompras, int quantidadeTotal, double valorTotal) {
    printf("\nNota Fiscal:\n");
    for (int i = 0; i < totalCompras; i++) {
        printf("Produto: %s, Quantidade: %d, Pre�o: R$ %.2f\n", 
               historicoCompras[i].nomeProduto, 
               historicoCompras[i].quantidade, 
               historicoCompras[i].precoProduto);
    }
    printf("Quantidade total de produtos: %d\n", quantidadeTotal);
    printf("Valor total da compra: R$ %.2lf\n", valorTotal);
}

// Fun��o para exibir o hist�rico de compras
void exibirHistoricoCompras(struct Compra* historicoCompras, int totalCompras) {
    printf("\nHist�rico de Compras:\n");
    for (int i = 0; i < totalCompras; i++) {
        printf("Compra %d\n", i + 1);
        printf("%s\n", historicoCompras[i].notaFiscal);
    }

    char verDetalhes;
    printf("Deseja ver os detalhes de uma compra? (Digite S para sim, N para n�o): ");
    scanf(" %c", &verDetalhes);
    while(getchar() != '\n'); // limpa o buffer de entrada

    while (toupper(verDetalhes) == 'S') {
        int numeroCompra;
        printf("Digite o n�mero da compra: ");
        scanf("%d", &numeroCompra);
        while(getchar() != '\n'); // limpa o buffer de entrada

        if (numeroCompra >= 1 && numeroCompra <= totalCompras) {
            printf("Detalhes da Compra %d:\n", numeroCompra);
            printf("Produto: %s, Quantidade: %d, Pre�o: R$ %.2f\n", 
                   historicoCompras[numeroCompra - 1].nomeProduto, 
                   historicoCompras[numeroCompra - 1].quantidade, 
                   historicoCompras[numeroCompra - 1].precoProduto);
        } else {
            printf("N�mero de compra inv�lido.\n");
        }

        printf("Deseja ver os detalhes de outra compra? (Digite S para sim, N para n�o): ");
        scanf(" %c", &verDetalhes);
        while(getchar() != '\n'); // limpa o buffer de entrada
    }
}

int main() {
    setlocale(LC_ALL, "Portuguese_Brazil");

    int funcao;
    int loginbemsucedido = 0;

    // Estrutura para armazenar produtos
    struct Produto estoque[50];
    int totalProdutos = 0;

    // Estrutura para armazenar o hist�rico de compras
    struct Compra historicoCompras[50];
    int totalCompras = 0;

    while (1) {
        // Menu
        printf("Selecione uma op��o:\n");
        printf("1. Entrar\n");
        printf("2. Sair\n");
        scanf("%d", &funcao);
        while(getchar() != '\n'); // limpa o buffer de entrada

        switch (funcao) {
            case 1:
                // Loop para solicitar as credenciais at� que sejam inseridas corretamente
                while (!loginbemsucedido) {
                    // Receber usu�rio e senha
                    char usuario[50];
                    char senha[50];

                    printf("Digite seu nome de usu�rio:\n");
                    scanf("%s", usuario);

                    printf("Digite sua senha:\n");
                    scanf("%s", senha);

                    // Validar o login
                    if (validarLogin(usuario, senha)) {
                        printf("Login bem-sucedido!\n");
                        loginbemsucedido = 1;
                    } else {
                        printf("Login falhou.\n Credenciais inv�lidas, tente novamente!\n");
                    }
                }

                // Ap�s o login bem-sucedido, exibir o menu adicional
                while (loginbemsucedido) {
                    printf("\nMenu Adicional:\n");
                    printf("1. Cadastrar Produto\n");
                    printf("2. Listar Produtos\n");
                    printf("3. Comprar Produto\n");
                    printf("4. Hist�rico de Compras\n");
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
                            printf("Op��o inv�lida. Tente novamente.\n");
                    }
                }
                break;

            case 2:
                printf("Saindo do programa.\n");
                return 0; // Encerra o programa

            default:
                printf("Op��o inv�lida. Tente novamente.\n");
        }
    }

    return 0;
}