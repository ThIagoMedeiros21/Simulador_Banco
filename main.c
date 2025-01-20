#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Dados
{
    char nome[100];
    int cpf;
    float saldo;
    char conta;
} Dados;

void criar_Conta()
{
    FILE *file;
    Dados dados;
    file = fopen("Contas.txt", "r");
    if (file == NULL)
    {
        fclose(file);
        printf("Ainda não existe clientes Registados, digite 1 novamente para registrar\n");
        file=fopen("Contas.txt","a");
    }
    else
    {
        int procurado;
        printf("Digite o CPF que deseja adicionar ");
        scanf("%d", &procurado);

        while (fscanf(file, "%d %s %c %f", &dados.cpf, dados.nome, &dados.conta, &dados.saldo) == 4)
        {
            if (procurado == dados.cpf)
            {
                printf("Já existe conta com esse CPF\n");
                fclose(file);
                return;
            }
        }
        fclose(file);

        file = fopen("Contas.txt", "a");
        if (file == NULL)
        {
            printf("Erro ao abrir");
            return;
        }
        else
        {
            printf("Digite o CPF novamente ");
            scanf("%d", &dados.cpf);
            //Preciso adicionar uma verificação para que seja evitado criação de contas com mesmo cpf
            printf("Digite seu nome: ");
            scanf(" %[^\n]", dados.nome); 
            printf("Para criar uma conta corrente digite 'c' ou para uma poupança digite 'p' ");
            scanf(" %c", &dados.conta);
            if (dados.conta == 'c')
            {
                dados.saldo = 100.00;
            }
            else if (dados.conta == 'p')
            {
                dados.saldo = 50.00;
            }
            fprintf(file, "%d %s %c %f\n", dados.cpf, dados.nome, dados.conta, dados.saldo);

            fclose(file);
        }
    }
}

int main()
{
    int option;
    while (1)
    {
        printf("SEJA BEM VINDO AO BANCO BRASECO!!\nDIGITE:\n1-CRIAR CONTA\n2-EXCLUIR CONTA\n3-SACAR\n4-DEPOSITO,\n5-TRANSFERIR\n6-PAGAMENTO DA TAXA MENSAL\n7-SAIR ");
        scanf("%d", &option);
        if (option == 1)
        {
            criar_Conta();
        }
        else if (option == 2)
        {
            printf("...\n");
        }
        else if (option == 3)
        {
            printf("...\n");
        }
        else if (option == 4)
        {
            printf("...\n");
        }
        else if (option == 5)
        {
            printf("...\n");
        }
        else if (option == 6)
        {
            printf("...\n");
        }
        else if (option == 7)
        {
            break;
        }
    }
    return 0;
}
