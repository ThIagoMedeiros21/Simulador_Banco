#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Dados
{
    char nome[100];
    long long int cpf;
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
        
        printf("Ainda não existe clientes Registados, digite 1 novamente para registrar\n");
        file = fopen("Contas.txt", "a");
        fclose(file);
    }
    else
    {
        long long int procurado;
        printf("Digite o CPF que deseja adicionar ");
        scanf("%lld", &procurado);

        while (fscanf(file, "%lld %s %c %f", &dados.cpf, dados.nome, &dados.conta, &dados.saldo) == 4)
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
            scanf("%lld", &dados.cpf);
            if (dados.cpf == procurado)
            {
                printf("Digite seu nome: ");
                scanf(" %s", dados.nome);
                printf("Para criar uma conta corrente digite 'c' ou para uma poupança digite 'p' ");
                scanf(" %c", &dados.conta);
                if (dados.conta == 'c')
                {
                    dados.saldo = 100.00;
                    fprintf(file, "%lld %s %c %f\n", dados.cpf, dados.nome, dados.conta, dados.saldo);
                    fclose(file);
                }
                else if (dados.conta == 'p')
                {
                    dados.saldo = 50.00;
                    fprintf(file, "%lld %s %c %f\n", dados.cpf, dados.nome, dados.conta, dados.saldo);
                    fclose(file);
                }
                else
                {
                    fclose(file);
                }
                printf("Conta criada com sucesso\n");
            }
            else
            {
                printf("Digite o cpf digitado antes\n");
                fclose(file);
                return;
            }
        }
    }
}

void apagar_Conta()
{
    FILE *file, *temp_file;
    Dados dados;
    file = fopen("Contas.txt", "r");
    if (file == NULL)
    {
        printf("Não Existe registro de contas\n");
        return;
    }
    else
    {
        int verificado = 0;
        temp_file = fopen("Tempo.txt", "w");
        if (temp_file == NULL)
        {
            printf("Erro ao criar o arquivo temporario\n");
            fclose(file);
            return;
        }
        long long int procurado;
        printf("Digite o CPF que voce deseja procurar: ");
        scanf("%lld", &procurado);
        while (fscanf(file, "%lld %s %c %f", &dados.cpf, dados.nome, &dados.conta, &dados.saldo) == 4)
        {
            if (procurado == dados.cpf)
            {
                verificado = 1;
                if (dados.saldo != 0.00)
                {
                    printf("CPF encontrado mas não pode ser apagado\n");
                    fprintf(temp_file, "%lld %s %c %f\n", dados.cpf, dados.nome, dados.conta, dados.saldo);
                }
                else
                {
                    printf("Conta apagada com sucesso\n");
                }
            }
            else
            {
                fprintf(temp_file, "%lld %s %c %f\n", dados.cpf, dados.nome, dados.conta, dados.saldo);
            }
        }
        if (!verificado)
        {
            printf("CPF não Encontrado\n");
            remove("Tempo.txt");
            return;
        }
        fclose(file);
        fclose(temp_file);
        remove("Contas.txt");
        rename("Tempo.txt", "Contas.txt");
    }
    return;
}

void saque()
{
    FILE *file, *temp_file;
    Dados dados;
    file = fopen("Contas.txt", "r");
    if (file == NULL)
    {
        printf("Arquivo não Criado\n");
        return;
    }
    else
    {
        long long int procurado;
        float saque;
        int verificado = 0;
        temp_file = fopen("Tempo.txt", "w");
        if (temp_file == NULL)
        {
            printf("Erro na criação");
        }
        printf("Digite seu CPF ");
        scanf("%lld", &procurado);

        while (fscanf(file, "%lld %s %c %f", &dados.cpf, dados.nome, &dados.conta, &dados.saldo) == 4)
        {
            if (procurado == dados.cpf)
            {
                printf("Digite o valor que deseja sacar ");
                scanf("%f", &saque);
                if (saque < 0)
                {
                    fclose(temp_file);
                    fclose(file);
                    printf("Não se saca valor negativo");
                    return;
                }
                verificado = 1;
                if (dados.saldo == 0)
                {
                    printf("Não existe saldo para ser resgatado nessa conta\n");
                    fprintf(temp_file, "%lld %s %c %f\n", dados.cpf, dados.nome, dados.conta, dados.saldo);
                }
                else
                {
                    float resultado;
                    resultado = dados.saldo - saque;
                    if (saque > dados.saldo)
                    {
                        printf("Erro na transação\n");
                        fprintf(temp_file, "%lld %s %c %f\n", dados.cpf, dados.nome, dados.conta, dados.saldo);
                    }
                    else
                    {
                        fprintf(temp_file, "%lld %s %c %f\n", dados.cpf, dados.nome, dados.conta, resultado);
                    }
                }
            }
            else
            {
                fprintf(temp_file, "%lld %s %c %f\n", dados.cpf, dados.nome, dados.conta, dados.saldo);
            }
        }
        if (!verificado)
        {
            printf("CPF não encontrado\n");
            remove("Tempo.txt");
            return;
        }
        fclose(file);
        fclose(temp_file);
        remove("Contas.txt");
        rename("Tempo.txt", "Contas.txt");
    }
    return;
}

void deposito()
{
    FILE *file, *temp_file;
    Dados dados;
    file = fopen("Contas.txt", "r");
    if (file == NULL)
    {
        printf("Não existe dado de nenhuma conta\n");
        return;
    }
    else
    {
        temp_file = fopen("Tempo.txt", "w");
        if (temp_file == NULL)
        {
            printf("Erro ao Criar o Arquivo\n");
            return;
        }
        else
        {
            long long int Procurado;
            int verificado = 0;
            float deposito, saldo_final;
            printf("Digite o CPF que deseja depositar ");
            scanf("%lld", &Procurado);
            while (fscanf(file, "%lld %s %c %f", &dados.cpf, dados.nome, &dados.conta, &dados.saldo) == 4)
            {
                if (Procurado == dados.cpf)
                {
                    verificado = 1;
                    printf("Digite o valor que deseja depositar ");
                    scanf("%f", &deposito);
                    if (deposito < 0)
                    {
                        printf("Erro no deposito\n");
                        fclose(temp_file);
                        fclose(file);
                        return;
                    }
                    saldo_final = dados.saldo + deposito;
                    fprintf(temp_file, "%lld %s %c %f\n", dados.cpf, dados.nome, dados.conta, saldo_final);
                }
                else
                {
                    fprintf(temp_file, "%lld %s %c %f\n", dados.cpf, dados.nome, dados.conta, dados.saldo);
                }
            }

            if (!verificado)
            {
                printf("CPF não encontrado\n");
                remove("Tempo.txt");
                return;
            }
        }
        fclose(file);
        fclose(temp_file);
        remove("Contas.txt");
        rename("Tempo.txt", "Contas.txt");
    }
    return;
}

void Pagamento_taxa()
{
    FILE *file, *temp_file;
    Dados dados;
    file = fopen("Contas.txt", "r");
    if (file == NULL)
    {
        printf("Não há registros de CPF\n");
        return;
    }
    else
    {
        temp_file = fopen("Tempo.txt", "w");
        if (temp_file == NULL)
        {
            printf("Arquivo não pode ser inicializado\n");
        }
        else
        {
            long long int procurado;
            int verificado = 0;
            float saldo, taxa;
            printf("Digite o CPF que você deseja realizar o pagamento da taxa ");
            scanf("%lld", &procurado);
            while (fscanf(file, "%lld %s %c %f", &dados.cpf, dados.nome, &dados.conta, &dados.saldo) == 4)
            {
                if (procurado == dados.cpf)
                {
                    verificado = 1;
                    if (dados.conta == 'c')
                    {
                        taxa = 25.0 / 100;
                        saldo = dados.saldo - (dados.saldo * taxa);
                        fprintf(temp_file, "%lld %s %c %f\n", dados.cpf, dados.nome, dados.conta, saldo);
                    }
                    else
                    {
                        taxa = 15.0 / 100;
                        saldo = dados.saldo - (dados.saldo * taxa);
                        fprintf(temp_file, "%lld %s %c %f\n", dados.cpf, dados.nome, dados.conta, saldo);
                    }
                }
                else
                {
                    fprintf(temp_file, "%lld %s %c %f\n", dados.cpf, dados.nome, dados.conta, dados.saldo);
                }
            }
            if (!verificado)
            {
                printf("CPF não encontrado\n");
                remove("Tempo.txt");
                return;
            }
        }
        fclose(file);
        fclose(temp_file);
        remove("Contas.txt");
        rename("Tempo.txt", "Contas.txt");
        printf("taxa paga com sucesso\n");
    }
    return;
}

void Transferencia()
{
    FILE *file, *temp_file;
    Dados dados;
    file = fopen("Contas.txt", "r");
    if (file == NULL)
    {
        printf("Não existe registros de CPF\n");
        return;
    }

    else
    {
        long long int CPF1, CPF2;
        int CPF1_Encontrado = 0, CPF2_Encontrado = 0;
        float saldo1, saldo2, total;
        printf("Digite o seu CPF ");
        scanf("%lld", &CPF1);
        while (fscanf(file, "%lld %s %c %f", &dados.cpf, dados.nome, &dados.conta, &dados.saldo) == 4)
        {
            if (CPF1 == dados.cpf)
            {
                printf("CPF encontrado\n");
                CPF1_Encontrado = 1;
                saldo1 = dados.saldo;
            }
        }
        fclose(file);
        if (!CPF1_Encontrado)
        {
            printf("CPF não encontrado\n");
            return;
        }
        file = fopen("Contas.txt", "r");
        printf("Digite o CPF do segundo usuario ");
        scanf("%lld", &CPF2);
        if (CPF1 == CPF2)
        {
            printf("Não se pode fazer transferencia para o mesmo CPF\n");
            return;
        }
        while (fscanf(file, "%lld %s %c %f", &dados.cpf, dados.nome, &dados.conta, &dados.saldo) == 4)
        {
            if (CPF2 == dados.cpf)
            {
                printf("CPF encontrado\n");
                CPF2_Encontrado = 1;
                saldo2 = dados.saldo;
            }
        }
        fclose(file);
        if (!CPF2_Encontrado)
        {
            printf("CPF não encontrado\n");
            return;
        }
        printf("Digite o Valor que você deseja transferir ");
        scanf("%f", &total);
        if (total == 0 || total > saldo1 || total < 0)
        {
            printf("Erro na transferencia\n");
            return;
        }
        saldo1 -= total;
        saldo2 += total;
        file = fopen("Contas.txt", "r");
        if (file == NULL)
        {
            printf("O arquivo não existe\n");
        }
        temp_file = fopen("Tempo.txt", "w");
        if (temp_file == NULL)
        {
            printf("Erro ao criar o arquivo\n");
        }
        else
        {
            while (fscanf(file, "%lld %s %c %f", &dados.cpf, dados.nome, &dados.conta, &dados.saldo) == 4)
            {
                if (dados.cpf == CPF1)
                {
                    fprintf(temp_file, "%lld %s %c %f\n", CPF1, dados.nome, dados.conta, saldo1);
                }
                else if (dados.cpf == CPF2)
                {
                    fprintf(temp_file, "%lld %s %c %f\n", CPF2, dados.nome, dados.conta, saldo2);
                }
                else
                {
                    fprintf(temp_file, "%lld %s %c %f\n", dados.cpf, dados.nome, dados.conta, dados.saldo);
                }
            }
        }
        fclose(file);
        fclose(temp_file);
        remove("Contas.txt");
        rename("Tempo.txt", "Contas.txt");
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
            apagar_Conta();
        }
        else if (option == 3)
        {
            saque();
        }
        else if (option == 4)
        {
            deposito();
        }
        else if (option == 5)
        {
            Transferencia();
        }
        else if (option == 6)
        {
            Pagamento_taxa();
        }
        else if (option == 7)
        {
            printf("Obrigado por utilizar o Banco Brasesco");
            break;
        }
    }
    return 0;
}
