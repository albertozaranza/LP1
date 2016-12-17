#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#define MAX 100 // Define o valor padrão de MAX para 100

// Estrutura da struct Cliente
struct Cliente{
    int id_cliente;
    int quant_conta;
    char nome[MAX];
    char cpf[MAX];
    char telefone[MAX];
    char municipio[MAX];
    char estado[MAX];
    double saldo;
    struct Cliente *prox;
};

// Estrutura da struct Conta
struct Conta{
    int id_conta;
    int numero_conta;
    int variacao;
    int id_cliente_conta;
    double saldo_conta;
    struct Conta *prox;
};

// Estrutura da struct Operação
struct Operacao{
    int id_operacao;
    char nome_operacao[MAX];
    struct Operacao *prox;
};

// Estrutura da struct Transações
struct Transacoes{
    struct tm data;
    int id_operacao_trans;
    int id_conta_origem;
    int id_conta_destino;
    double valor_trans;
    char descricao[MAX];
    struct Transacoes *prox;
};

// Estrutura da struct de Transações do cartão
struct Transacoes_cartao_credito{
    struct tm data_compra;
    int id_conta_trans_cc;
    char descricao[MAX];
    int qtde_parcelas;
    double valor_trans_cc;
    struct Transacoes_cartao_credito *prox;
};

// Inserção de clientes com ordenação numerica de acordo com o ID do cliente
void inserir_dados_cliente(struct Cliente *listaCliente, int id_cliente, char nome[], char cpf[], char telefone[], char municipio[], char estado[]){

    // Criação de um novo nó para a lista
    struct Cliente *novoNo = malloc(sizeof(struct Cliente));

    // Recepção dos dados para o novo nó
    novoNo->id_cliente = id_cliente;
    strcpy(novoNo->nome, nome);
    strcpy(novoNo->cpf, cpf);
    strcpy(novoNo->telefone, telefone);
    strcpy(novoNo->municipio, municipio);
    strcpy(novoNo->estado, estado);

    // Mudança para o novoNo da lista
    novoNo->prox = listaCliente->prox;
    listaCliente->prox = novoNo;
}

// Inserção de dados a conta
void inserir_dados_conta(struct Conta *listaConta, int id_conta, int numero_conta, int variacao, int id_cliente_conta){

    // Criação de um novo nó para a lista
    struct Conta *novoNo = malloc(sizeof(struct Conta));

    // Recepção dos dados para o novo nó
    novoNo->id_conta = id_conta;
    novoNo->numero_conta = numero_conta;
    novoNo->variacao = variacao;
    novoNo->id_cliente_conta = id_cliente_conta;

    // Mudança para o novoNo da lista
    novoNo->prox = listaConta->prox;
    listaConta->prox = novoNo;
}

// Inserção de dados sobre as operações
void inserir_dados_operacao(struct Operacao *listaOperacao, int id_operacao, char nome_operacao[]){

    // Criação de um novo nó para a lista
    struct Operacao *novoNo = malloc(sizeof(struct Operacao));

    // Recepção dos dados para o novo nó
    novoNo->id_operacao = id_operacao;
    strcpy(novoNo->nome_operacao, nome_operacao);

    // Mudança para o novoNo da lista
    novoNo->prox = listaOperacao->prox;
    listaOperacao->prox = novoNo;
}

// Inserção de dados sobre as transações
void inserir_dados_trasacoes(struct Transacoes *listaTransacoes, int data_dia, int data_mes, int data_ano, int id_operacao_trans, int id_conta_origem, int id_conta_destino, double valor_trans){

    // Criação de um novo nó para a lista
    struct Transacoes *novoNo = malloc(sizeof(struct Transacoes));

    // Recepção dos dados para o novo nó
    novoNo->data.tm_mday = data_dia;
    novoNo->data.tm_mon = data_mes;
    novoNo->data.tm_year = data_ano;
    novoNo->id_operacao_trans = id_operacao_trans;
    novoNo->id_conta_origem = id_conta_origem;
    novoNo->id_conta_destino = id_conta_destino;
    novoNo->valor_trans = valor_trans;
    if(id_operacao_trans == 1){
        strcpy(novoNo->descricao, "saque");
    }
    else if(id_operacao_trans == 2){
        strcpy(novoNo->descricao, "deposito");
    }
    else if(id_operacao_trans == 3){
        strcpy(novoNo->descricao, "transferencia");
    }

    // Mudança para o novoNo da lista
    novoNo->prox = listaTransacoes->prox;
    listaTransacoes->prox = novoNo;
}

// Inserção de dados sobre as transações do cartão de crédito
void inserir_dados_trasacoes_cc(struct Transacoes_cartao_credito *listaTransCard, int data_compra_dia, int data_compra_mes, int data_compra_ano, int id_conta_trans_cc, char descricao[], int qtde_parcelas, double valor_trans_cc){

    // Criação de um novo nó para a lista
    struct Transacoes_cartao_credito *novoNo = malloc(sizeof(struct Transacoes_cartao_credito));

    // Recepção dos dados para o novo nó
    novoNo->data_compra.tm_mday = data_compra_dia;
    novoNo->data_compra.tm_mon = data_compra_mes;
    novoNo->data_compra.tm_year = data_compra_ano;
    novoNo->id_conta_trans_cc = id_conta_trans_cc;
    strcpy(novoNo->descricao, descricao);
    novoNo->qtde_parcelas = qtde_parcelas;
    novoNo->valor_trans_cc = valor_trans_cc;

    // Mudança para o novoNo da lista
    novoNo->prox = listaTransCard->prox;
    listaTransCard->prox = novoNo;
}

// Converte a data para dias
int convertToDay(struct tm data_dia){
    return(data_dia.tm_year*365+data_dia.tm_mon*30+data_dia.tm_mday);
}

// Converta a data em mes
int convertToMonth(int mes , int ano){
    return mes + ano*12;
}

// Pega o tempo real em segundos e faz a converção para o tempo real e a coloca na struct tm
struct tm *mesAtual(){

    // Struct para armazenar dados sobre a data e hora
    struct tm *mes_atual;

    // Pega o tempo real em segundos
    time_t segundos;
    time(&segundos);
    mes_atual = localtime(&segundos);

    // Conversão para mes e ano
    mes_atual->tm_mon+=1;
    mes_atual->tm_year+=1900;

return mes_atual;
}

 // Calculo do saldo de todas contas
void calcular_saldo(struct Cliente *listaCliente, struct Conta *listaConta , struct Transacoes *listaTransacoes){

    // Declaração de variável
    double saldo = 0, saldo_conta = 0;

    // Criação de listas auxiliares
    struct Cliente *auxCliente = listaCliente->prox;
    struct Conta *auxConta = listaConta->prox;
    struct Transacoes *auxTransacoes = listaTransacoes->prox;

    while(auxCliente != NULL){ // Percorre a lista de clientes
        auxConta = listaConta->prox; // Vai para o inicio da lista de contas
        while(auxConta != NULL){ // Percorre a lista de contas
            if(auxConta->id_cliente_conta == auxCliente->id_cliente){ // Filtro de conta
                auxTransacoes = listaTransacoes->prox; // Vai para o inicio da lista de transacoes
                while(auxTransacoes != NULL){ // Percorre a lista de transacoes
                    if(auxTransacoes->id_conta_origem == auxConta->id_conta){ // Verifica se a conta é origem
                        saldo-=auxTransacoes->valor_trans;
                        auxConta->saldo_conta-=auxTransacoes->valor_trans; // Atribui o saldo para cada conta
                    }
                    if(auxTransacoes->id_conta_destino == auxConta->id_conta){ // Verifica se a conta é destino
                        saldo+=auxTransacoes->valor_trans;
                        auxConta->saldo_conta+=auxTransacoes->valor_trans;
                    }
                    auxTransacoes = auxTransacoes->prox; // Vai para a proxima posicao da lista
                }
            }
            auxConta = auxConta->prox; // Vai para a proxima posicao da lista
        }
        auxCliente->saldo = saldo; // Atribui o saldo para cada cliente
        auxCliente = auxCliente->prox; // Vai para a proxima posicao da lista
        saldo = 0; // Reseta o saldo para o proximo cliente
    }
}

// Ordenação dos clientes pelo saldo
void ordenar_saldo(struct Cliente *listaCliente){

    // Criação de um nó final nulo
    struct Cliente *noFim = NULL;

    while(listaCliente->prox != noFim){ // Percorre a lista de clientes enquanto for diferente do no final
        struct Cliente *antAux = listaCliente; // Criação de uma lista auxiliar para valores anteriores
        struct Cliente *aux = listaCliente->prox; // Criação de uma lista auxiliar
        while(aux->prox != noFim){ // Percorre a lista auxiliar
            if(aux->saldo < aux->prox->saldo){ // Verificação de posições e troca
                struct Cliente *auxTroca = aux;
                aux = aux->prox;
                auxTroca->prox = auxTroca->prox->prox;
                antAux->prox = aux;
                aux->prox = auxTroca;
                antAux = aux;
                aux = auxTroca;
            }
            else{
                antAux = aux;
                aux = aux->prox;
            }
        }
        noFim = aux;
    }
}

// Ordenação de data das transações
void ordenar_transacoes_data(struct Transacoes *listaTransacoes){

    // Criação de um nó final nulo
    struct Transacoes *noFim = NULL;

    while(listaTransacoes->prox != noFim){ // Percorre a lista de transacoes enquanto for diferente do no final
        struct Transacoes *antAux = listaTransacoes; // Criação de uma lista auxiliar para valores anteriores
        struct Transacoes *aux = listaTransacoes->prox; // Criação de uma lista auxiliar
        while(aux->prox != noFim){ // Percorre a lista auxiliar
            if(convertToDay(aux->data) > convertToDay(aux->prox->data)){ // Verificação de posições e troca
                struct Transacoes *auxTroca = aux;
                aux = aux->prox;
                auxTroca->prox = auxTroca->prox->prox;
                antAux->prox = aux;
                aux->prox = auxTroca;
                antAux = aux;
                aux = auxTroca;
            }
            else{
                antAux = aux;
                aux = aux->prox;
            }
        }
        noFim = aux;
    }

}

void ordenar_transacoes_cartao_data(struct Transacoes_cartao_credito *listaTransCard){

    // Criação de um nó final nulo
    struct Transacoes_cartao_credito *noFim = NULL;

    while(listaTransCard->prox != noFim){ // Percorre a lista de transacoes do cartao enquanto for diferente do no final
        struct Transacoes_cartao_credito *antAux = listaTransCard; // Criação de uma lista auxiliar para valores anteriores
        struct Transacoes_cartao_credito *aux = listaTransCard->prox; // Criação de uma lista auxiliar
        while(aux->prox != noFim){ // Percorre a lista auxiliar
            if(convertToDay(aux->data_compra) > convertToDay(aux->prox->data_compra)){ // Verificação de posições e troca
                struct Transacoes_cartao_credito *auxTroca = aux;
                aux = aux->prox;
                auxTroca->prox = auxTroca->prox->prox;
                antAux->prox = aux;
                aux->prox = auxTroca;
                antAux = aux;
                aux = auxTroca;
            }
            else{
                antAux = aux;
                aux = aux->prox;
            }
        }
        noFim = aux;
    }

}

// Filtragem de clientes por estado
int exibir_clientes_estado(struct Cliente *listaCliente, struct Conta *listaConta, char estado[]){

    // Declaracao de variavel
    int validaEstado = 0;

    // Criação de uma lista auxiliar
    struct Cliente *auxCliente = listaCliente->prox;
    struct Conta *auxConta = listaConta->prox;

    while(auxCliente != NULL){ // Percorre a lista de clientes
        auxCliente->quant_conta = 0; // Atribui a quantidade de contas do cliente para 0
        if(!strcmp(estado,auxCliente->estado)){ // Filtro de estado
            auxConta = listaConta->prox; // Vai para o inicio da lista de contas
            while(auxConta != NULL){ // Percorre a lista de contas
                if(auxConta->id_cliente_conta == auxCliente->id_cliente){ // Filtro de conta
                    auxCliente->quant_conta++; // Faz a atribuição da quantidade de contas do cliente
                }
            auxConta = auxConta->prox; // Vai para a proxima posição da lista
            }
            // Ebixe o resultado da pesquisa
            printf("| ID: %d | Nome: %s | CPF: %s | Telefone: %s | Municipio: %s | Estado: %s | Quantidade de contas: %d\n", auxCliente->id_cliente, auxCliente->nome, auxCliente->cpf, auxCliente->telefone, auxCliente->municipio, auxCliente->estado, auxCliente->quant_conta);
            validaEstado = 1;
        }
        auxCliente = auxCliente->prox; // Vai para a proxima posição da lista
    }

    if(validaEstado == 0){
        return -1;
    }else{
        printf("\n");
        system("pause"); // Sai da função após digitar algo
        return 0;
    }
}

// Exibição de saldo total atual do cliente filtrado
int exibir_saldo_atual(struct Cliente *listaCliente, struct Conta *listaConta, struct Transacoes *listaTransacoes, char cpf[]){

    // Declaracao de variavel
    int validaCpf = 0;

    // Criação de listas auxiliares
    struct Cliente *auxCliente = listaCliente->prox;
    struct Conta *auxConta = listaConta->prox;
    struct Transacoes *auxTransacoes = listaTransacoes->prox;

    // Laço para exibir cada conta do cliente filtrado
    while(auxCliente != NULL){ // Percorre a lista de contas
        if(!strcmp(cpf,auxCliente->cpf)){ // Filtro de CPF
            validaCpf = 1;
            printf("Nome: %s | Saldo total: %.2lf\n\n", auxCliente->nome, auxCliente->saldo);
            while(auxConta!= NULL){ // Percorre a lista de clientes
                if(auxConta->id_cliente_conta == auxCliente->id_cliente){ // Filtro de conta
                    printf("Numero da conta: %d | Variacao: %d | Valor: %.2lf\n", auxConta->numero_conta, auxConta->variacao , auxConta->saldo_conta);
                }
                auxConta = auxConta->prox; // Vai para a proxima posição da lista
            }
        }
        auxCliente = auxCliente->prox; // Vai para a proxima posição da lista
    }

    if(validaCpf == 0){
        return -1;
    }else{
        printf("\n");
        system("pause"); // Sai da função após digitar qualquer coisa
        return 0;
    }
}

// Listagem do saldo atual de todos os clientes
void exibir_saldo_clientes(struct Cliente *listaCliente){

    // Criação de listas auxiliares
    struct Cliente *auxCliente = listaCliente->prox;

    // Laço para exibir a lista de clientes
    while(auxCliente != NULL){
        printf("| Nome: %s | CPF: %s | Saldo: %.2lf |\n", auxCliente->nome, auxCliente->cpf, auxCliente->saldo);
        auxCliente = auxCliente->prox;
    }

    // Sai da função após digitar qualquer coisa
    printf("\n");
    system("pause");
    return;
}

// Exibe o extrato do mes atual
int extrato_mes_atual(struct Cliente *listaCliente, struct Conta *listaConta, struct Transacoes *listaTransacoes, char cpf[], int numero_conta){

    // Declaração de variável
    double saldo_anterior = 0, saldo_atual = 0;
    struct tm *mes_atual = mesAtual();
    int cont = 0, var = 0, validaCpf = 0, validaConta = 0;

    // Criação de listas auxiliares (mes atual)
    struct Cliente *auxCliente = listaCliente->prox;
    struct Conta *auxConta = listaConta->prox;
    struct Transacoes *auxTransacoes = listaTransacoes->prox;

    while(auxCliente != NULL){
        if(!strcmp(cpf, auxCliente->cpf)){
            validaCpf = 1;
            while(auxConta != NULL){
                if(cont == 0){ // Exibe os dados do cliente apenas uma vez
                    printf("Nome: %s\n\n", auxCliente->nome);
                    cont = 1;
                }
                if(numero_conta == auxConta->numero_conta){
                    validaConta = 1;
                    auxTransacoes = listaTransacoes->prox;
                    while(auxTransacoes != NULL){
                            if(auxTransacoes->id_conta_origem == auxConta->id_conta){
                                if(convertToMonth(mes_atual->tm_mon, mes_atual->tm_year) > convertToMonth(auxTransacoes->data.tm_mon, auxTransacoes->data.tm_year)){
                                    saldo_anterior-=auxTransacoes->valor_trans;
                                }
                                if(convertToMonth(mes_atual->tm_mon, mes_atual->tm_year) == convertToMonth(auxTransacoes->data.tm_mon, auxTransacoes->data.tm_year)){
                                    saldo_atual-=auxTransacoes->valor_trans;
                                    printf("Data: %d/%d/%d | Valor: %.2lf | Descricao: %s\n", auxTransacoes->data.tm_mday, auxTransacoes->data.tm_mon, auxTransacoes->data.tm_year, auxTransacoes->valor_trans*(-1), auxTransacoes->descricao);
                                    var = 1;
                                }
                            }
                            if(auxTransacoes->id_conta_destino == auxConta->id_conta){
                                if(convertToMonth(mes_atual->tm_mon, mes_atual->tm_year) > convertToMonth(auxTransacoes->data.tm_mon, auxTransacoes->data.tm_year)){
                                    saldo_anterior+=auxTransacoes->valor_trans;
                                }
                                if(convertToMonth(mes_atual->tm_mon, mes_atual->tm_year) == convertToMonth(auxTransacoes->data.tm_mon, auxTransacoes->data.tm_year)){
                                    saldo_atual+=auxTransacoes->valor_trans;
                                    printf("Data: %d/%d/%d | Valor: %.2lf | Descricao: %s\n", auxTransacoes->data.tm_mday, auxTransacoes->data.tm_mon, auxTransacoes->data.tm_year, auxTransacoes->valor_trans, auxTransacoes->descricao);
                                    var = 1;
                                }
                            }
                            auxTransacoes = auxTransacoes->prox;
                    }
                }
                auxConta = auxConta->prox;
            }
        }
        auxCliente = auxCliente->prox;
    }
    if(validaCpf == 1 && validaConta == 1){

        // Exibido se não tiverem sido feitas trasacoes neste mes
        if(var == 0){
            printf("\n\nNao foram feitas transacoes neste mes\n\n");
        }

        printf("\nSaldo do mes anterior: %.2lf\n", saldo_anterior);

        printf("\nSaldo do mes atual: %.2lf \n", saldo_atual+saldo_anterior);

        // Sai da função após digitar qualquer coisa
        printf("\n");
        system("pause");
        return 0;
    }
    else if(validaCpf == 0){
        return -1;
    }
    else if(validaCpf == 1 && validaConta == 0){
        return -2;
    }
}

// Exibe o extrato do mes anterior
int extrato_mes_anterior(struct Cliente *listaCliente, struct Conta *listaConta, struct Transacoes *listaTransacoes, char cpf[], int numero_conta, int data_mes, int data_ano){

    // Declaração de variável
    double saldo_anterior = 0, saldo_atual = 0;
    struct tm *mes_atual = mesAtual();
    int cont = 0, var = 0, validaCpf = 0, validaConta = 0;

    // Criação de listas auxiliares (mes atual)
    struct Cliente *auxCliente = listaCliente->prox;
    struct Conta *auxConta = listaConta->prox;
    struct Transacoes *auxTransacoes = listaTransacoes->prox;

    while(auxCliente != NULL){
        if(!strcmp(cpf, auxCliente->cpf)){
            validaCpf = 1;
            while(auxConta != NULL){
                if(cont == 0){ // Exibe os dados do cliente apenas uma vez
                    printf("Nome: %s\n\n", auxCliente->nome);
                    cont = 1;
                }
                if(numero_conta == auxConta->numero_conta){
                    validaConta = 1;
                    auxTransacoes = listaTransacoes->prox;
                    while(auxTransacoes != NULL){
                            if(auxTransacoes->id_conta_origem == auxConta->id_conta){
                                if(convertToMonth(data_mes, data_ano) > convertToMonth(auxTransacoes->data.tm_mon, auxTransacoes->data.tm_year)){
                                    saldo_anterior-=auxTransacoes->valor_trans;
                                }
                                if(convertToMonth(data_mes, data_ano) == convertToMonth(auxTransacoes->data.tm_mon, auxTransacoes->data.tm_year)){
                                    saldo_atual-=auxTransacoes->valor_trans;
                                    printf("Data: %d/%d/%d | Valor: %.2lf | Descricao: %s\n", auxTransacoes->data.tm_mday, auxTransacoes->data.tm_mon, auxTransacoes->data.tm_year, auxTransacoes->valor_trans*(-1), auxTransacoes->descricao);
                                    var = 1;
                                }
                            }
                            if(auxTransacoes->id_conta_destino == auxConta->id_conta){
                                if(convertToMonth(data_mes, data_ano) > convertToMonth(auxTransacoes->data.tm_mon, auxTransacoes->data.tm_year)){
                                    saldo_anterior+=auxTransacoes->valor_trans;
                                }
                                if(convertToMonth(data_mes, data_ano) == convertToMonth(auxTransacoes->data.tm_mon, auxTransacoes->data.tm_year)){
                                    saldo_atual+=auxTransacoes->valor_trans;
                                    printf("Data: %d/%d/%d | Valor: %.2lf | Descricao: %s\n", auxTransacoes->data.tm_mday, auxTransacoes->data.tm_mon, auxTransacoes->data.tm_year, auxTransacoes->valor_trans, auxTransacoes->descricao);
                                    var = 1;
                                }
                            }
                            auxTransacoes = auxTransacoes->prox;
                    }
                }
                auxConta = auxConta->prox;
            }
        }
        auxCliente = auxCliente->prox;
    }
    if(validaCpf == 1 && validaConta == 1){
        // Exibido se não tiverem sido feitas trasacoes neste mes
        if(var == 0){
            printf("\nNao foram feitas transacoes neste mes\n\n");
        }

        printf("\nSaldo do mes anterior: %.2lf\n", saldo_anterior);

        printf("\nSaldo do mes atual: %.2lf \n", saldo_atual+saldo_anterior);

        // Sai da função após digitar qualquer coisa
        printf("\n");
        system("pause");
        return 0;
    }
    else if(validaCpf == 0){
        return -1;
    }
    else if(validaCpf == 1 && validaConta == 0){
        return -2;
    }
}

// Exibição da fatura de um cliente
int fatura_cartao(struct Cliente *listaCliente, struct Conta *listaConta, struct Transacoes_cartao_credito *listaTransCard, char cpf[], int data_mes, int data_ano){

    // Declaração de variável
    int parcela = 0, parcela_mes_main = convertToMonth(data_mes, data_ano), cont = 0, var = 0, validaCpf = 0;
    double total = 0;
    FILE *arquivo_fatura;
    arquivo_fatura = fopen("Fatura.txt", "w");

    // Criação de listas auxiliares
    struct Cliente *auxCliente = listaCliente->prox;
    struct Conta *auxConta = listaConta->prox;
    struct Transacoes_cartao_credito *auxTransCard = listaTransCard->prox;

    while(auxCliente != NULL){ // Percorre a lista de clients
        if(!strcmp(cpf,auxCliente->cpf)){ // Filtro de CPF
            validaCpf = 1;
            printf("Cliente: %s\n", auxCliente->nome); // Exibe o cliente e logo em seguida escreve no arquivo
            fprintf(arquivo_fatura, "Cliente: %s\n", auxCliente->nome);
            while(auxConta != NULL){ // Percorre a lista de contas
                auxTransCard = listaTransCard->prox; // Vai para o inicio da lista de transacoes
                while(auxTransCard != NULL){ // Percorre a lista de transacoes, calcula as transacoes, as exibe e em seguida escreve no arquivo
                    int parcela_mes_func = convertToMonth(auxTransCard->data_compra.tm_mon, auxTransCard->data_compra.tm_year);
                    if(auxConta->id_conta == auxTransCard->id_conta_trans_cc && auxCliente->id_cliente == auxConta->id_cliente_conta && (parcela_mes_main - parcela_mes_func) <= auxTransCard->qtde_parcelas){
                        if(cont == 0){
                            printf("\nConta: %d\n\n", auxConta->numero_conta);
                            fprintf(arquivo_fatura, "\nConta: %d\n\n", auxConta->numero_conta);
                            cont = 1;
                        }
                        parcela = parcela_mes_main - parcela_mes_func;
                        if(parcela>0){
                            printf("Data: %d/%d/%d | Descricao: %s | Valor: %.2lf | Parcela %d/%d\n",auxTransCard->data_compra.tm_mday, auxTransCard->data_compra.tm_mon, auxTransCard->data_compra.tm_year, auxTransCard->descricao, auxTransCard->valor_trans_cc/auxTransCard->qtde_parcelas, parcela, auxTransCard->qtde_parcelas);
                            total+=auxTransCard->valor_trans_cc/auxTransCard->qtde_parcelas;
                            var = 1;

                            fprintf(arquivo_fatura, "Data: %d/%d/%d | Descricao: %s | Valor: %.2lf | Parcela %d/%d\n",auxTransCard->data_compra.tm_mday, auxTransCard->data_compra.tm_mon, auxTransCard->data_compra.tm_year, auxTransCard->descricao, auxTransCard->valor_trans_cc, parcela, auxTransCard->qtde_parcelas);
                        }
                    }
                auxTransCard = auxTransCard->prox; // Vai para a proxima posição da lista
                }
            auxConta = auxConta->prox; // Vai para a proxima posição da lista
            cont = 0; // Reseta o contador
            }
        }
    auxCliente = auxCliente->prox; // Vai para a proxima posição da lista
    }
    if(var == 1 && validaCpf == 1){
        printf("\nValor total: %.2lf\n", total); // Exibe o valor total e minimo e em seguida os escreve no arquivo
        printf("Valor minimo: %.2lf\n", total/10);
        fprintf(arquivo_fatura, "\nValor total: %.2lf\n", total);
        fprintf(arquivo_fatura, "Valor minimo: %.2lf\n", total/10);
    }else if(var == 0 && validaCpf == 1){
        printf("\nNao foram feitas transacoes nesse mes.\n");
        fprintf(arquivo_fatura, "\nNao foram feitas transacoes nesse mes.\n");
    }
    printf("\n");
    system("pause"); // Sai da função após digitar qualquer coisa
    fclose(arquivo_fatura);


    if(validaCpf == 0){
        return -1;
    }else{
        system("cls");
        printf("Arquivo gerado com sucesso.\n\n");
        printf("Diretorio:\n\n"); system("dir"); printf("\n");
        system("pause"); // Sai da função após digitar qualquer coisa
        return 0;
    }

}

// Função para imprimir a lista de todos os clientes
void imprimir_lista(struct Cliente *listaCliente, struct Conta *listaConta, struct Operacao *listaOperacao, struct Transacoes *listaTransacoes, struct Transacoes_cartao_credito *listaTransCard){

    // Criação de listas auxiliares
    struct Cliente *auxCliente = listaCliente->prox;
    struct Conta *auxConta = listaConta->prox;
    struct Operacao *auxOperacao = listaOperacao->prox;
    struct Transacoes *auxTransacoes = listaTransacoes->prox;
    struct Transacoes_cartao_credito *auxTransCard = listaTransCard->prox;

    // Laço para exibição das listas
    printf("-----------------------------------------------------------------------------------------------------------------------\n");
    while(auxCliente != NULL){ // Percorre a lista de clientes
       printf("| ID: %d | Nome: %s | CPF: %s | Telefone: %s | Municipio: %s | Estado: %s |\n", auxCliente->id_cliente, auxCliente->nome, auxCliente->cpf, auxCliente->telefone, auxCliente->municipio, auxCliente->estado, auxCliente->saldo);
       auxCliente = auxCliente->prox; // Vai para a proxima posição da lista
    }
    printf("-----------------------------------------------------------------------------------------------------------------------\n");
    while(auxConta != NULL){ // Percorre a lista de contas
       printf("| ID da Conta: %d | Numero: %d | Variacao: %d | ID do Cliente: %d |\n", auxConta->id_conta, auxConta->numero_conta, auxConta->variacao, auxConta->id_cliente_conta);
       auxConta = auxConta->prox; // Vai para a proxima posição da lista
    }
    printf("-----------------------------------------------------------------------------------------------------------------------\n");
    while(auxOperacao != NULL){ // Percorre a lista de operacoes
       printf("| ID da Operacao: %d | Nome: %s |\n", auxOperacao->id_operacao, auxOperacao->nome_operacao);
       auxOperacao = auxOperacao->prox; // Vai para a proxima posição da lista
    }
    printf("-----------------------------------------------------------------------------------------------------------------------\n");
    while(auxTransacoes != NULL){ // Percorre a lista de transacoes
       printf("| Data: %d/%d/%d | ID da Operacao: %d | ID Conta Origem: %d | ID Conta Destino: %d | Valor: %.2lf |\n", auxTransacoes->data.tm_mday, auxTransacoes->data.tm_mon, auxTransacoes->data.tm_year, auxTransacoes->id_operacao_trans, auxTransacoes->id_conta_origem, auxTransacoes->id_conta_destino, auxTransacoes->valor_trans);
       auxTransacoes = auxTransacoes->prox; // Vai para a proxima posição da lista
    }
    printf("-----------------------------------------------------------------------------------------------------------------------\n");
    while(auxTransCard != NULL){ // Percorre a lista de transacoes do cartao
       printf("| Data da compra: %d/%d/%d | ID da conta: %d | Descricao: %s | Quantidade de parcelas: %d | Valor: %.2lf |\n", auxTransCard->data_compra.tm_mday, auxTransCard->data_compra.tm_mon, auxTransCard->data_compra.tm_year, auxTransCard->id_conta_trans_cc, auxTransCard->descricao, auxTransCard->qtde_parcelas, auxTransCard->valor_trans_cc);
       auxTransCard = auxTransCard->prox; // Vai para a proxima posição da lista
    }
    printf("-----------------------------------------------------------------------------------------------------------------------\n");

    // Sai da função após digitar algo
    printf("\n");
    system("pause");
    return;
}

int main(){

    // Criação de variaveis
    int x, i = 0, validaDado = 0,id_cliente, id_conta, numero_conta, variacao, id_cliente_conta, id_operacao, id_operacao_trans, id_conta_origem, id_conta_destino, id_conta_trans_cc, qtde_parcelas, data_dia, data_mes, data_ano, data_compra_dia, data_compra_mes, data_compra_ano;
    char nome[MAX], cpf[MAX], telefone[MAX], municipio[MAX], estado[MAX], aux[MAX], nome_operacao[MAX], descricao[MAX];
    double valor_trans, valor_trans_cc;

    // Criação das listas
    struct Cliente *listaCliente = malloc(sizeof(struct Cliente));
    listaCliente->prox = NULL;

    struct Conta *listaConta = malloc(sizeof(struct Conta));
    listaConta->prox = NULL;

    struct Operacao *listaOperacao = malloc(sizeof(struct Operacao));
    listaOperacao->prox = NULL;

    struct Transacoes *listaTransacoes = malloc(sizeof(struct Transacoes));
    listaTransacoes->prox = NULL;

    struct Transacoes_cartao_credito *listaTransCard = malloc(sizeof(struct Transacoes_cartao_credito));
    listaTransCard->prox = NULL;

    // Leitura do arquivo
    FILE *arquivo;
    arquivo = fopen("arquivo.txt", "r");

    fscanf(arquivo, "%s\n", aux);
    while(fscanf(arquivo, "%d, %[^,], %[^,], %[^,], %[^,], %[^;];\n", &id_cliente, nome, cpf, telefone, municipio, estado) == 6){
        printf("\rLendo clientes -> %d de 500", i+1);
        inserir_dados_cliente(listaCliente, id_cliente, nome, cpf, telefone, municipio, estado);
        i++;
        if(i==500){
            printf("\rClientes lidos -> %d de 500\n                ", i);
            i=0;
        }
    }
    fscanf(arquivo, "\n%s\n", aux);
    while(fscanf(arquivo, "%d, %d, %d, %d;\n", &id_conta, &numero_conta, &variacao, &id_cliente_conta) == 4){
        printf("\rLendo contas -> %d de 5000", i+1);
        inserir_dados_conta(listaConta, id_conta, numero_conta, variacao, id_cliente_conta);
        i++;
        if(i==5000){
            printf("\rContas lidas -> %d de 5000\n                ", i);
            i=0;
        }
    }
    fscanf(arquivo, "\n%s\n", aux);
    while(fscanf(arquivo, "%d, %[^;];\n", &id_operacao, nome_operacao) == 2){
        printf("\rLendo operacoes -> %d de 3", i+1);
        inserir_dados_operacao(listaOperacao, id_operacao, nome_operacao);
        i++;
        if(i==3){
            printf("\rOperacoes lidas -> %d de 3                \n", i);
            i=0;
        }
    }
    fscanf(arquivo, "\n%s\n", aux);
    while(fscanf(arquivo, "%d/%d/%d, %d, %d, %d, %lf;\n", &data_dia, &data_mes, &data_ano, &id_operacao_trans, &id_conta_origem, &id_conta_destino, &valor_trans) == 7){
        printf("\rLendo transacoes -> %d de 500000", i+1);
        inserir_dados_trasacoes(listaTransacoes, data_dia, data_mes, data_ano, id_operacao_trans, id_conta_origem, id_conta_destino, valor_trans);
        i++;
        if(i==500000){
            printf("\rTransasoes lidas -> %d de 500000\n                ", i);
            i=0;
        }
    }
    fscanf(arquivo, "\n%s\n", aux);
    while(fscanf(arquivo, "%d/%d/%d, %d, %[^,], %d, %lf;\n", &data_compra_dia, &data_compra_mes, &data_compra_ano, &id_conta_trans_cc, descricao, &qtde_parcelas, &valor_trans_cc) != EOF){
        printf("\rLendo transacoes do cartao -> %d de 50000", i+1);
        inserir_dados_trasacoes_cc(listaTransCard, data_compra_dia, data_compra_mes, data_compra_ano, id_conta_trans_cc, descricao, qtde_parcelas, valor_trans_cc);
        i++;
        if(i==50000){
            printf("\rTransacoes do cartao lidas -> %d de 50000\n", i);
            i=0;
        }
    }
    fclose(arquivo);

    printf("Arquivo lido.\n");

    // Calcula saldo dos clientes
    printf("Calculando saldo dos clientes.\n");
    calcular_saldo(listaCliente, listaConta, listaTransacoes);
    printf("Saldo calculado.\n");

    // Ordena a lista em ordem decrescente de clientes de acordo com o saldo do cliente
    printf("Ordenando saldo.\n");
    ordenar_saldo(listaCliente);
    printf("Saldo ordenado.\n");

    // Ordena a lista em ordem crescente de clientes de acordo com a data das transacoes
    printf("Ordenando data das transacoes.\n");
    ordenar_transacoes_data(listaTransacoes);
    printf("Data ordenada.\n");

    // Ordena a lista em ordem crescente de clientes de acordo com a data das transacoes
    printf("Ordenando data das transacoes do cartao.\n");
    ordenar_transacoes_cartao_data(listaTransCard);
    printf("Data ordenada.\n");

    printf("\n");
    system("pause");

    system("cls"); // Limpa o cmd

    // Laço de opções
    while(1){

        system("cls"); // Limpa o cmd

        // Opções
        printf("Escolha a opcao de entrada:\n");
        printf("1 - Listagem de clientes por estado;\n");
        printf("2 - Saldo atual do cliente;\n");
        printf("3 - Listagem do saldo dos clientes;\n");
        printf("4 - Extrato bancario (mes atual);\n");
        printf("5 - Extrato bancario (mes anterior);\n");
        printf("6 - Fatura do cartao de credito;\n");
        printf("7 - Imprimir listas;\n");
        printf("0 - Sair.\n");

        printf("Opcao: ");
        scanf("%d", &x);

        if(x==1){
            system("cls");
            printf("Digite o estado que deseja filtrar:\n");
            scanf("%s", estado);
            system("cls");
            strupr(estado);
            validaDado = exibir_clientes_estado(listaCliente, listaConta, estado);
            if(validaDado == -1){
                while(validaDado == -1){
                    printf("Estado nao encontrado.\n\n");
                    system("pause");
                    system("cls");
                    printf("Digite novamente o estado que deseja filtrar:\n");
                    scanf("%s", estado);
                    system("cls");
                    strupr(estado);
                    validaDado = exibir_clientes_estado(listaCliente, listaConta, estado);
                }
            }
        }

        else if(x==2){
            system("cls");
            printf("Digite o CPF do cliente:\n");
            scanf("%s", cpf);
            system("cls");
            validaDado = exibir_saldo_atual(listaCliente, listaConta, listaTransacoes, cpf);
            if(validaDado == -1){
                while(validaDado == -1){
                    printf("CPF nao encontrado.\n\n");
                    system("pause");
                    system("cls");
                    printf("Digite novamente o CPF do cliente:\n");
                    scanf("%s", cpf);
                    system("cls");
                    validaDado = exibir_saldo_atual(listaCliente, listaConta, listaTransacoes, cpf);
                }
            }
        }

        else if(x==3){
            system("cls");
            exibir_saldo_clientes(listaCliente);
        }

        else if(x==4){
            system("cls");
            printf("Digite o CPF do cliente:\n");
            scanf("%s", cpf);
            system("cls");
            printf("Digite o numero da conta do cliente:\n");
            scanf("%d", &numero_conta);
            system("cls");
            validaDado = extrato_mes_atual(listaCliente, listaConta, listaTransacoes, cpf, numero_conta);
            if(validaDado == -1){
                while(validaDado == -1){
                    printf("CPF nao encontrado.\n\n");
                    system("pause");
                    system("cls");
                    printf("Digite novamente o CPF do cliente:\n");
                    scanf("%s", cpf);
                    system("cls");
                    validaDado = extrato_mes_atual(listaCliente, listaConta, listaTransacoes, cpf, numero_conta);
                    if(validaDado == -2){
                        while(validaDado == -2){
                            printf("\nConta nao encontrada.\n\n");
                            system("pause");system("cls");
                            printf("Digite o numero da conta do cliente:\n");
                            scanf("%d", &numero_conta);
                            system("cls");
                            validaDado = extrato_mes_atual(listaCliente, listaConta, listaTransacoes, cpf, numero_conta);
                        }
                    }
                }
            }
        }

        else if(x==5){
            system("cls");
            printf("Digite o CPF do cliente:\n");
            scanf("%s", cpf);
            system("cls");
            printf("Digite o numero da conta do cliente:\n");
            scanf("%d", &numero_conta);
            system("cls");
            printf("Informe o mes e o ano da busca no formato mm/aaaa:\n");
            scanf("%d/%d", &data_mes, &data_ano);
            system("cls");
            validaDado = extrato_mes_anterior(listaCliente, listaConta, listaTransacoes, cpf, numero_conta, data_mes, data_ano);
            if(validaDado == -1){
                while(validaDado == -1){
                    printf("CPF nao encontrado.\n\n");
                    system("pause");
                    system("cls");
                    printf("Digite novamente o CPF do cliente:\n");
                    scanf("%s", cpf);
                    system("cls");
                    validaDado = extrato_mes_anterior(listaCliente, listaConta, listaTransacoes, cpf, numero_conta, data_mes, data_ano);
                    if(validaDado == -2){
                        while(validaDado == -2){
                            printf("\nConta nao encontrada.\n\n");
                            system("pause");system("cls");
                            printf("Digite o numero da conta do cliente:\n");
                            scanf("%d", &numero_conta);
                            system("cls");
                            validaDado = extrato_mes_anterior(listaCliente, listaConta, listaTransacoes, cpf, numero_conta, data_mes, data_ano);
                        }
                    }
                }
            }
        }

        else if(x==6){
            system("cls");
            printf("Digite o CPF do cliente:\n");
            scanf("%s", cpf);
            system("cls");
            printf("Informe o mes e o ano da busca no formato mm/aaaa:\n");
            scanf("%d/%d", &data_mes, &data_ano);
            system("cls");
            validaDado = fatura_cartao(listaCliente, listaConta, listaTransCard, cpf, data_mes, data_ano);
            if(validaDado == -1){
                while(validaDado == -1){
                    printf("CPF nao encontrado.\n\n");
                    system("pause");
                    system("cls");
                    printf("Digite novamente o CPF do cliente:\n");
                    scanf("%s", cpf);
                    system("cls");
                    validaDado = fatura_cartao(listaCliente, listaConta, listaTransCard, cpf, data_mes, data_ano);
                }
            }
        }

        else if(x==7){
            system("cls");
            imprimir_lista(listaCliente, listaConta, listaOperacao, listaTransacoes, listaTransCard);
        }

        else if(x==0){
            exit(0);
        }

        else{
            system("cls");
            printf("Opcao invalida.\n");
            printf("\n");
            system("pause");
        }
    }

return 0;
}
