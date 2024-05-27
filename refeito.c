#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_PROD_NAME 50

float calcularDesconto(float total){
    if (total >= 2000){
        return 0.20 * total;
    } else if (total >= 1000){
        return 0.15 * total;
    } else if (total >= 500){
        return 0.10 * total;
    } else {
        return 0;
    }
}

struct Produto {
    char nome[200];
    int quantidade;
    float preco;
    float subtotal;
};


struct Produto Produtos[60];

int main(){
    char regioes[3][20] = {"Norte", "Nordeste", "Sul"};
    float total = 0;
    char produto[MAX_PROD_NAME];
    int quantidade;
    float preco;
    int opcao;

    //struct Produto* Produtos = (struct Produto*)malloc(60 * sizeof(struct Produto*));

    printf("Escolha uma regiao do Brasil:\n");
    for (int i = 0; i < 3; i++){
        printf("%d. %s\n", i+1, regioes[i]);
    }
    
    scanf("%d", &opcao);

    if (opcao < 1 || opcao > 3){
        printf("Opcao invalida!\n");
        return 1;
    }

    printf("Voce escolheu a regiao: %s\n", regioes[opcao - 1]);

    printf("MENU:\n");
    printf("1. Informar produto\n");
    printf("2. Sair\n");
    scanf("%d", &opcao);

    int i = 0;
    while (opcao != 2){
        if (opcao == 1){
            printf("Informe o nome do produto: ");
            scanf("%s", Produtos[i].nome);
            printf("Informe a quantidade: ");
            scanf("%d", &quantidade);
            printf("Informe o preco unitario: ");
            scanf("%f", &preco);

            float subtotal = quantidade * preco;

            Produtos[i].quantidade = quantidade;
            Produtos[i].preco = preco;
            Produtos[i].subtotal = subtotal;

            i++;

            printf("Subtotal: %.2f\n", subtotal);
            total += subtotal;
        } else {
            printf("Opcao invalida!\n");
        }

        printf("MENU:\n");
        printf("1. Informar produto\n");
        printf("2. Sair\n");
        scanf("%d", &opcao);
    }

    int j;
    for (j = 0; j < i; j++){
        printf("-----------------------------\n");
        printf("Produto: %s\n", Produtos[j].nome);
        printf("Quantidade: %d\n", Produtos[j].quantidade);
        printf("Preço: %.2f\n", Produtos[j].preco);
        printf("Subtotal: %.2f\n", Produtos[j].subtotal);
        printf("-----------------------------\n");
    }

    printf("-----------------------------\n");
    printf("Valor bruto: %.2f\n", total);

    float desconto = calcularDesconto(total);
    float valor_liquido = total - desconto;

    printf("Valor liquido a pagar: %.2f\n", valor_liquido);
    printf("-----------------------------\n");

    return 0;
    
}
