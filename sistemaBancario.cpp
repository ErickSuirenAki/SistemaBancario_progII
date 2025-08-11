//Discente: Erick Batista dos Santos
//2º Periodo de Ciência da Computação
//Disciplina: Programação 2


#include <stdio.h>
#include <stdlib.h>
#include <string.h>


//feito em sala de aula inicio
#define TF 100

struct cliente{
   int numConta;
   char nome[10];
   float saldo;
};

struct par {
    int numConta;
    int posdado;
};

void carregaTexto(struct cliente Tabela[TF], int &tl){
    FILE *arq;
    int numConta;
    char nome [10];
    float saldo;
    arq = fopen("poupanca.txt", "r");
    if(arq==NULL){
        printf("Arquivo nao encontrado");
    }
    else {
        while (!feof (arq))
        {
           fscanf(arq, "%d  %s  %f ", &numConta, nome, &saldo);
           Tabela[tl].numConta = numConta;
           strcpy(Tabela[tl].nome,nome);
           Tabela[tl].saldo= saldo;
           tl++;
        }
        fclose(arq);
        
    }



}

void exibeTabela (struct cliente Tabela[TF], int tl){
    int i;
    printf("\n===>Lista dos Clientes<===\n");
    for(i=0;i<tl;i++){
        printf("\nnumConta = %d\tNome = %s\tSaldo = %5.2f", Tabela[i].numConta, Tabela[i].nome, Tabela[i].saldo);
    }


}

void regravar(struct cliente Tabela[TF], int tl) {
    int i;
    FILE *arq =fopen("poupanca.txt", "w");
    arq =fopen("poupanca.txt", "w");
    if (arq == NULL) {
        printf("\nErro ao abrir o arquivo\n");
        return;
    }

    for (i = 0; i < tl; i++) {
        fprintf(arq, "%d %s %.2f\n", 
                Tabela[i].numConta, 
                Tabela[i].nome, 
                Tabela[i].saldo);
    }

    fclose(arq); 
}

int buscaExaustiva(struct cliente Tabela [TF], int tl, int conta){
    int posicao= -1;
    int i = 0;
    while(i<tl){
        if(conta ==Tabela[i].numConta){
            posicao = i;
        }i++;
    }
    return posicao;
}

void criar (struct cliente Tabela[TF],int &tl, struct par Indice[TF]){
    int i;
    for(i=0;i<tl;i++){
        Indice[i].numConta = Tabela[i].numConta;
        Indice[i].posdado = i;
    }
}
void ordenar (struct par Indice[TF],int &tl){
    int i, fim,j;
    par aux;
    for(fim = tl-1;fim>1; fim--){
        for(j=0;j<fim;j++){
            if(Indice[j].numConta>Indice[j+1].numConta){
                aux = Indice[j+1];
                Indice[j+1]= Indice[j];
                Indice[j] = aux;
            }
        }
    }

}

int buscaIndexada(struct par Indice[TF], int &tl, int numConta){
    int i =0;
    int posicao = -1;
    while(i<tl){
        if(numConta == Indice[i].numConta){
           posicao = Indice[i].posdado;
           break;
        }
        i++;
    } 

    return posicao;
}
//feito em sala de aula fim

//funções feitas no trabalho inicio

int deposito(struct cliente Tabela[TF], int tl, int numConta, float valor){
    int posicao = -1;
    int i;

   for(i=0; i < tl; i++) {
        if (Tabela[i].numConta == numConta) {
            posicao = i;
            break;
        } //faz uma busca para achar a conta procurada
    }
    Tabela[posicao].saldo = Tabela[posicao].saldo + valor; //altera o valor do saldo daquela conta
    return posicao; //retorna a posicao da conta na tabela principal


}


int saque(struct cliente Tabela[TF], int tl, int numConta, float valor){
    int posicao = -1;
    int i;

   for(i=0; i < tl; i++) {
        if (Tabela[i].numConta == numConta) {
            if(Tabela[i].saldo<valor){
                posicao = 0;
                break;
            } //faz uma busca para achar a conta procurad
            posicao = i;
            break;
        }
    }

    if(posicao == -1){
        return posicao; //se nao achar
    }
    else if(posicao == 0){
        return posicao; //se achar, mas nao tiver saldo
    }
    else {
        Tabela[posicao].saldo = Tabela[posicao].saldo - valor; //altera o saldo
        return posicao;
    }

}

void inserirCliente(struct cliente Tabela[TF], int &tl){
    int numConta,i,maior=0;
    char nome[10];
    float saldo;

    printf(("\nDigite seu nome:\n"));
    scanf("%s", nome);
    printf("\nDigite seu saldo inicial:\n");
    scanf("%f",&saldo);

    for (i = 0; i < tl; i++) {
        if (Tabela[i].numConta > maior) {
            maior = Tabela[i].numConta;
        }
    }maior++;// isso eh pra criar um numero pra conta de forma automatica

    Tabela[tl].saldo = saldo;
    strcpy(Tabela[tl].nome,nome);
    Tabela[tl].numConta = maior;
    tl++; //indica que mais um cliente na tabela
    printf("\nCliente Inserido com sucesso\n");
   


}

void relatorioOrdenado(struct cliente Tabela[TF], struct par Indice[TF], int tl) {
    int posicaoTabela;
    criar(Tabela, tl, Indice); //usa a funcao pra criar o indice
    ordenar(Indice, tl); // usa a funcao pra ordenar o indice

    printf("\nRelatorio ordenado por numero da conta:\n");

    for(int i = 0; i < tl; i++) {
        posicaoTabela = Indice[i].posdado; // ordem que o numero ta na tabela principal
        printf("\nnumConta = %d\tNome = %s\tSaldo = %5.2f",
             Tabela[posicaoTabela].numConta, Tabela[posicaoTabela].nome, Tabela[posicaoTabela].saldo);
    }
}
//funções feitas no trabalho fim

int main(){
    //feito em sala de aula inicio
    int tl = 0;
    int opcao = 0;
    int numConta;
    float valor;
    int posicao;

    struct cliente Tabela[TF];
    struct par Indice[TF];

    while(opcao!=-10){
        printf("\n\n1-Leitura da tabela carrega tabela");
        printf("\n2-Exibe a tabela dos clientes");
        printf("\n3-Regrava a tabela no arquivo de text");
        printf("\n4-Busca uma conta (exaustiva)");
        printf("\n5-Ordena (indexada)");
        printf("\n6-Busca ordenada (indexada)");
        printf("\n7-Deposito");
        printf("\n8-Saque");
        printf("\n9-Inserir novo Cliente");
        printf("\n10-Relatorio Ordenado\n");
        scanf("\n%d", &opcao);



        switch (opcao){
        case 1:
            carregaTexto(Tabela,tl);
            printf("\n\nTabela carregada com %d clientes", tl);
            break;

        case 2:
            exibeTabela(Tabela, tl);
            printf("\n\n");
            break;

        case 3:
            regravar(Tabela,tl);
            printf("\nTexto regravado");
            break;

        case 4:
            printf("\nQual conta procurar?");
            scanf("%d", &numConta);
            posicao = buscaExaustiva(Tabela, tl, numConta);
            if(posicao==-1){
                printf("\nNao encontrou a conta");
            }
            else {
                printf("\nPosicao = %d conta = %d nome = %s saldo  = %5.2f",
                     posicao, Tabela[posicao].numConta, Tabela[posicao].nome, Tabela[posicao].saldo);
            }
            break;

        case 5:
            criar (Tabela, tl, Indice);
            printf("\nCriou indice desordenado");
            ordenar(Indice,tl);
            printf("\nIndice ordenado");
            break;

        case 6:
            printf("\nEntre com a conta a ser procurada: ");
            scanf("%d", &numConta);
            posicao = buscaIndexada(Indice, tl, numConta);
            if(posicao==-1){
                printf("\nNao encontrou");

            }else {
                printf("\nEncontrou na tabela principal na posicao %d", posicao);
            }
                printf("\nConta %d nome %s saldo %5.2f", Tabela[posicao].numConta,
                     Tabela[posicao].nome, Tabela[posicao].saldo);
                break;
        //feito em sala de aula fim

        //feito no trabalho inicio
        case 7:
            printf("\nEntre com a conta para deposito: ");
            scanf("%d", &numConta);
            posicao = buscaExaustiva(Tabela, tl, numConta); //ver se a conta existe
            if(posicao==-1){
                printf("\nNao encontrou a conta");
            }
            else {
                printf("\nconta = %d nome = %s saldo  = %5.2f", Tabela[posicao].numConta,
                     Tabela[posicao].nome, Tabela[posicao].saldo);
                printf("\nQuanto deseja depositar?\n");
                scanf("%f", &valor);
                posicao = deposito(Tabela, tl, numConta, valor); //se exitir realiza o deposito
                printf("\nconta = %d nome = %s saldo  = %5.2f", Tabela[posicao].numConta,
                     Tabela[posicao].nome, Tabela[posicao].saldo);
                printf("\nDeposito realizado!\n\n");
                regravar(Tabela, tl); //regrava o valor alterado no arquivo

            }
            break;

        case 8:
            printf("\nEntre com a conta para saque:");
            scanf("%d", &numConta);
            posicao = buscaExaustiva(Tabela, tl, numConta); //ver se a conta existe
            if(posicao==-1){
                printf("\nNao encontrou a conta");
            }
            else {
                printf("\nconta = %d nome = %s saldo  = %5.2f", Tabela[posicao].numConta, 
                     Tabela[posicao].nome, Tabela[posicao].saldo);
                printf("\nQuanto deseja sacar?\n");
                scanf("%f", &valor);
                posicao = saque(Tabela, tl, numConta, valor);//se exitir, mas nao tem saldo
                if(posicao == 0){
                    printf("\nConta localizada, mas saldo insuficiente");}
                else{
                    printf("\nconta = %d nome = %s saldo  = %5.2f", Tabela[posicao].numConta, //se exitir e tiver saldo realiza o deposito
                     Tabela[posicao].nome, Tabela[posicao].saldo);
                    printf("\nSaque realizado!\n\n");
                    regravar(Tabela, tl); //regrava o valor alterado no arquivo

                }
                

            }
            break;


        case 9:
            printf("\nInsercao de novo cliente\n");
            inserirCliente(Tabela,tl); //inere o cliente
            regravar(Tabela,tl); // grava o cliente no aquivo


        case 10:
            relatorioOrdenado(Tabela,Indice,tl); //precisa regravar no arquivo a tabela ordenada? *nao precisa

        //feito no trabalho fim

        } //switch


    }//while

    return 0;

}//main