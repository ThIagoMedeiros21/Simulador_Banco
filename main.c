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
        file = fopen("Contas.txt", "a");
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
            if (dados.cpf == procurado)
            {
                printf("Digite seu nome: ");
                scanf(" %[^\n]", dados.nome);
                printf("Para criar uma conta corrente digite 'c' ou para uma poupança digite 'p' ");
                scanf(" %c", &dados.conta);
                if (dados.conta == 'c')
                {
                    dados.saldo = 100.00;
                    fprintf(file, "%d %s %c %f\n", dados.cpf, dados.nome, dados.conta, dados.saldo);
                    fclose(file);
                }
                else if (dados.conta == 'p')
                {
                    dados.saldo = 50.00;
                    fprintf(file, "%d %s %c %f\n", dados.cpf, dados.nome, dados.conta, dados.saldo);
                    fclose(file);
                }
                else
                {
                    fclose(file);
                }
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
        int verificado=0;
        temp_file=fopen("Tempo.txt","w");
        if(temp_file==NULL){
            printf("Erro ao criar o arquivo temporario\n");
            fclose(file);
            return;
        }
        int procurado;
        printf("Digite o CPF que voce deseja procurar: ");
        scanf("%d", &procurado);
        while (fscanf(file, "%d %s %c %f", &dados.cpf, dados.nome, &dados.conta, &dados.saldo) == 4)
        {
            if (procurado == dados.cpf)
            {
                verificado=1;
                if (dados.saldo != 0.00)
                {
                    printf("CPF encontrado mas não pode ser apagado\n");
                    fprintf(temp_file, "%d %s %c %f\n", dados.cpf, dados.nome, dados.conta, dados.saldo);
                }
                else
                {
                    printf("Conta apagada com sucesso\n");
                }
            }
            else
            {
                fprintf(temp_file, "%d %s %c %f\n", dados.cpf, dados.nome, dados.conta, dados.saldo);
            }
        }
        if(!verificado){
            printf("CPF não Encontrado\n");
            remove("Tempo.txt");
        }
    fclose(file);
    fclose(temp_file);
    remove("Contas.txt");
    rename("Tempo.txt","Contas.txt");
}
    return;
}

void saque(){
    FILE *file, *temp_file;
    Dados dados;
    file=fopen("Contas.txt","r");
    if(file==NULL){
        printf("Arquivo não Criado\n");
        return;
    }
    else{
        int procurado;
        float saque;
        int verificado=0;
        temp_file=fopen("Tempo.txt","w");
        if(temp_file==NULL){
            printf("Erro na criação");
        }
        printf("Digite seu CPF ");
        scanf("%d",&procurado);
        printf("Digite o valor que deseja sacar ");
        scanf("%f",&saque);
        if(saque<0){
            fclose(temp_file);
            fclose(file);
            printf("Não se saca valor negativo");
            return;
        }
        while(fscanf(file,"%d %s %c %f",&dados.cpf,dados.nome,&dados.conta,&dados.saldo)==4){
        if(procurado==dados.cpf){
            verificado=1;
            if(dados.saldo==0){
               printf("Não existe saldo para ser resgatado nessa conta\n"); 
               fprintf(temp_file, "%d %s %c %f\n", dados.cpf, dados.nome, dados.conta, dados.saldo);
            }
            else{
                float resultado;
                resultado=dados.saldo-saque;
                if(saque>dados.saldo){
                    printf("Erro na transação\n");
                    fprintf(temp_file, "%d %s %c %f\n", dados.cpf, dados.nome, dados.conta, dados.saldo);
                }
                else{
                    fprintf(temp_file, "%d %s %c %f\n", dados.cpf, dados.nome, dados.conta, resultado);
                               
                } 
        }  
        }else{
            fprintf(temp_file, "%d %s %c %f\n", dados.cpf, dados.nome, dados.conta, dados.saldo);
        }
       
        }
     if(!verificado){
            printf("CPF não encontrado\n");
            remove("Tempo.txt");
        }    
    fclose(file);
    fclose(temp_file);
    remove("Contas.txt");
    rename("Tempo.txt","Contas.txt");
    }
    return; 
    //modificação em breve na função de saque para que só aconteça caso  exista o CPF informado pelo usuario
}

void deposito(){
    FILE *file, *temp_file;
    Dados dados;
    file=fopen("Contas.txt","r");
    if(file==NULL){
        printf("Não existe dado de nenhuma conta\n");
        return;
    }
    else{
        temp_file=fopen("Tempo.txt","w");
        if(temp_file==NULL){
            printf("Erro ao Criar o Arquivo\n");
            return;
        }
        else{
        int Procurado,verificado=0;
        float deposito,saldo_final;
        printf("Digite o CPF que deseja depositar ");
        scanf("%d",&Procurado);
        while(fscanf(file,"%d %s %c %f",&dados.cpf,dados.nome,&dados.conta,&dados.saldo)==4){
            if(Procurado==dados.cpf){
                verificado=1;
                printf("Digite o valor que deseja depositar ");
                scanf("%f",&deposito);
                if(deposito<0){
                    printf("Erro no deposito\n");
                    fclose(temp_file);
                    fclose(file);
                    return;
                }
                saldo_final=dados.saldo+deposito;
                fprintf(temp_file,"%d %s %c %f\n",dados.cpf,dados.nome,dados.conta,saldo_final);
            }
            else{
                fprintf(temp_file,"%d %s %c %f\n",dados.cpf,dados.nome,dados.conta,dados.saldo);
            }
        }
        if(!verificado){
            printf("CPF não encontrado\n");
            remove("Tempo.txt");
        }
        }
    fclose(file);
    fclose(temp_file);
    remove("Contas.txt");
    rename("Tempo.txt","Contas.txt");
            
    
    
}
    return;
}

void Pagamento_taxa(){
    FILE *file,*temp_file;
    Dados dados;
    file=fopen("Contas.txt","r");
    if(file==NULL){
        printf("Não há registros de CPF\n");
        return;
    }else{
        temp_file=fopen("Tempo.txt","w");
        if(temp_file==NULL){
            printf("Arquivo não pode ser inicializado\n");
        }
        else{
        int procurado,verificado=0;
        float saldo,taxa;
        printf("Digite o CPF que você deseja realizar o pagamento da taxa ");
        scanf("%d",&procurado);
        while(fscanf(file,"%d %s %c %f",&dados.cpf,dados.nome,&dados.conta,&dados.saldo)==4){
            if(procurado==dados.cpf){
                verificado=1;
                if(dados.conta=='c'){
                    taxa=25.0/100;
                    saldo=dados.saldo-(dados.saldo*taxa);
                    fprintf(temp_file,"%d %s %c %f\n",dados.cpf,dados.nome,dados.conta,saldo);
                    
                }
                else{
                    taxa=15.0/100;
                    saldo=dados.saldo-(dados.saldo*taxa);
                    fprintf(temp_file,"%d %s %c %f\n",dados.cpf,dados.nome,dados.conta,saldo);
                    }
            }
            else{
                    fprintf(temp_file,"%d %s %c %f\n",dados.cpf,dados.nome,dados.conta,dados.saldo);
                    }
            
        }
        if(!verificado){
            printf("CPF não encontrado\n");
            remove("Tempo.txt");
        }
        
    }
    fclose(file);
    fclose(temp_file);
    remove("Contas.txt");
    rename("Tempo.txt","Contas.txt");

    }
    return;
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
            printf("...\n");
        }
        else if (option == 6)
        {
            Pagamento_taxa();
        }
        else if (option == 7)
        {
            break;
        }
    }
    return 0;
}
