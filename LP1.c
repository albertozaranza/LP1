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
                    }
                    if(auxTransacoes->id_conta_destino == auxConta->id_conta){ // Verifica se a conta é destino
                        saldo+=auxTransacoes->valor_trans;
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

// Inserção de clientes com ordenação numerica de acordo com o ID do cliente
void inserir_cliente_ordenado(struct Cliente *listaCliente, int id_cliente, char nome[], char cpf[], char telefone[], char municipio[], char estado[]){

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

// Função para imprimir a lista de todos os clientes
void imprimir_lista(struct Cliente *listaCliente, struct Conta *listaConta, struct Operacao *listaOperacao, struct Transacoes *listaTransacoes, struct Transacoes_cartao_credito *listaTransCard){

    char x[MAX];

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
    printf("\nDigite algum numero para sair: ");
    scanf("%s", x);
    return;
}

// Filtragem de clientes por estado
void listar_clientes_estado(struct Cliente *listaCliente, struct Conta *listaConta, char estado[]){

    system("cls"); // Limpar tela do cmd

    // Declaração de variável
    char x[MAX];

    // Criação de uma lista auxiliar
    struct Cliente *auxCliente = listaCliente->prox;
    struct Conta *auxConta = listaConta->prox;

    while(auxCliente != NULL){ // Percorre a lista de clientes
        auxCliente->quant_conta = 0; // Atribui a quantidade de contas do cliente para 0
        if(strcmp(estado,auxCliente->estado)==0){ // Filtro de estado
            auxConta = listaConta->prox; // Vai para o inicio da lista de contas
            while(auxConta != NULL){ // Percorre a lista de contas
                if(auxConta->id_cliente_conta == auxCliente->id_cliente){ // Filtro de conta
                    auxCliente->quant_conta++; // Faz a atribuição da quantidade de contas do cliente
                }
            auxConta = auxConta->prox; // Vai para a proxima posição da lista
            }
            // Ebixe o resultado da pesquisa
            printf("| ID: %d | Nome: %s | CPF: %s | Telefone: %s | Municipio: %s | Estado %s | Quantidade de contas: %d\n", auxCliente->id_cliente, auxCliente->nome, auxCliente->cpf, auxCliente->telefone, auxCliente->municipio, auxCliente->estado, auxCliente->quant_conta);
        }
        auxCliente = auxCliente->prox; // Vai para a proxima posição da lista
    }

    // Sai da função após digitar algo
    printf("\nDigite algum numero para sair: ");
    scanf("%s", x);
    return;
}

// Exibição de saldo total atual do cliente filtrado
void exibir_saldo_atual(struct Cliente *listaCliente, struct Conta *listaConta, struct Transacoes *listaTransacoes, char cpf[]){

    // Declaração de variável
    char x[MAX];
    double saldo = 0;
    double saldo_part = 0;

    // Criação de listas auxiliares
    struct Cliente *auxCliente = listaCliente->prox;
    struct Cliente *auxClienteAux = listaCliente->prox;
    struct Conta *auxContaAux = listaConta->prox;
    struct Transacoes *auxTransacoesAux = listaTransacoes->prox;


    // Laço para exibir o saldo total do cliente filtrado
    while(auxCliente != NULL){ // Percorre a lista de clientes
        if(!strcmp(cpf,auxCliente->cpf)){ // Filtro de CPF
            printf("-----------------------------------------------------------------------------------------------------------------------\n");
            printf("| Nome: %s | Valor: %.2lf |\n", auxCliente->nome, auxCliente->saldo);
            printf("-----------------------------------------------------------------------------------------------------------------------\n");
        }
        auxCliente = auxCliente->prox; // Vai para a proxima posição da lista
    }


    // Laço para exibir cada conta do cliente filtrado
    while(auxClienteAux != NULL){ // Percorre a lista de contas
        if(!strcmp(cpf,auxClienteAux->cpf)){ // Filtro de CPF
            while(auxContaAux != NULL){ // Percorre a lista de clientes
                if(auxContaAux->id_cliente_conta == auxClienteAux->id_cliente){ // Filtro de conta
                    auxTransacoesAux = listaTransacoes->prox; // Vai para o inicio da lista
                    saldo_part = 0; // Reseta o valor da variavel
                    while(auxTransacoesAux != NULL){ // Percorre a lista de transacões
                        if(auxTransacoesAux->id_conta_origem == auxContaAux->id_conta){ // Veifica se a conta é destino ou origem
                            saldo_part-=auxTransacoesAux->valor_trans;
                        }
                        if(auxTransacoesAux->id_conta_destino == auxContaAux->id_conta){ // Verifica se a conta é destino ou origem
                            saldo_part+=auxTransacoesAux->valor_trans;
                        }
                        auxTransacoesAux = auxTransacoesAux->prox; // Vai para a proxima posição da lista
                    }
                    printf("| Numero da conta: %d | Variacao: %d | Valor: %.2lf |\n", auxContaAux->numero_conta, auxContaAux->variacao ,saldo_part);
                }
                auxContaAux = auxContaAux->prox; // Vai para a proxima posição da lista
            }
        }
        auxClienteAux = auxClienteAux->prox; // Vai para a proxima posição da lista
    }
    printf("-----------------------------------------------------------------------------------------------------------------------\n");

    // Sai da função após digitar qualquer coisa
    printf("\nDigite algum numero para sair: ");
    scanf("%s", x);
    return;
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

// Converta a data em mes
int converter_para_mes(int mes , int ano){
    return mes + ano*12;
}

// Exibição da fatura de um cliente
void fatura_cartao(struct Cliente *listaCliente, struct Conta *listaConta, struct Transacoes_cartao_credito *listaTransCard, char cpf[], int data_mes, int data_ano){

    // Declaração de variável
    char x[MAX];
    int parcela = 0, parcela_mes_main = converter_para_mes(data_mes, data_ano), cont = 0;
    double total = 0;
    FILE *arquivo_fatura;

    // Criação de listas auxiliares
    struct Cliente *auxCliente = listaCliente->prox;
    struct Conta *auxConta = listaConta->prox;
    struct Transacoes_cartao_credito *auxTransCard = listaTransCard->prox;

    while(auxCliente != NULL){ // Percorre a lista de clients
        if(!strcmp(cpf,auxCliente->cpf)){ // Filtro de CPF
            printf("Cliente: %s\n", auxCliente->nome); // Exibe o cliente e logo em seguida escreve no arquivo
            arquivo_fatura = fopen("Fatura.txt", "w");
            fprintf(arquivo_fatura, "Cliente: %s\n", auxCliente->nome);
            while(auxConta != NULL){ // Percorre a lista de contas
                auxTransCard = listaTransCard->prox; // Vai para o inicio da lista de transacoes
                while(auxTransCard != NULL){ // Percorre a lista de transacoes, calcula as transacoes, as exibe e em seguida escreve no arquivo
                    int parcela_mes_func = converter_para_mes(auxTransCard->data_compra.tm_mon, auxTransCard->data_compra.tm_year);
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
    printf("\nValor total: %.2lf\n", total); // Exibe o valor total e minimo e em seguida os escreve no arquivo
    printf("Valor minimo: %.2lf\n", total/10);
    fprintf(arquivo_fatura, "\nValor total: %.2lf\n", total);
    fprintf(arquivo_fatura, "Valor minimo: %.2lf\n", total/10);
    fclose(arquivo_fatura);


    // Sai da função após digitar qualquer coisa
    printf("\nDigite algum numero para sair: ");
    scanf("%s", x);
    return;

}

// Listagem do saldo atual de todos os clientes
void listagem_saldo_atual(struct Cliente *listaCliente){

    // Criação de variável
    char x[MAX];

    // Criação de listas auxiliares
    struct Cliente *auxCliente = listaCliente->prox;

    // Laço para exibir a lista de clientes
    while(auxCliente != NULL){
        printf("| Nome: %s | CPF: %s | Saldo: %.2lf |\n", auxCliente->nome, auxCliente->cpf, auxCliente->saldo);
        auxCliente = auxCliente->prox;
    }

    // Sai da função após digitar qualquer coisa
    printf("\nDigite algum numero para sair: ");
    scanf("%d", &x);
    return;
}

// Pega o tempo real em segundos e faz a converção para o tempo real e a coloca na struct tm
struct tm *mesAtual(){

    // Struct para armazenar dados sobre a data e hora
    struct tm *mes_atual_;

    // Pega o tempo real em segundos
    time_t segundos;
    time(&segundos);
    mes_atual_ = localtime(&segundos);

    // Conversão para mes e ano
    mes_atual_->tm_mon += 1;
    mes_atual_->tm_year += 1900;

return mes_atual_;
}

// Exibe o extrato do mes atual
void extrato_mes_atual(struct Cliente *listaCliente, struct Conta *listaConta, struct Transacoes *listaTransacoes, char cpf[], int numero_conta){

    // Declaração de variável
    double saldo = 0, saldo_perdido = 0, saldo_mes_anterior = 0, saldo_mes_atual = 0;
    struct tm *mes_atual = mesAtual();
    char x[MAX];
    int cont = 0, cont_ = 0;

    // Criação de listas auxiliares (mes atual)
    struct Cliente *auxCliente = listaCliente->prox;
    struct Conta *auxConta = listaConta->prox;
    struct Transacoes *auxTransacoes = listaTransacoes->prox;

    // Criação de listas auxiliares (mes anterior)
    struct Cliente *auxClienteMesAnt = listaCliente->prox;
    struct Conta *auxContaMesAnt = listaConta->prox;
    struct Transacoes *auxTransacoesMesAnt = listaTransacoes->prox;

    // Laço para exibir o saldo do mes anterior
    // Mes anterior
    while(auxClienteMesAnt != NULL){ // Percorre a lista de clientes
        if(!strcmp(cpf,auxClienteMesAnt->cpf)){ // Filtro de CPF
            while(auxContaMesAnt != NULL){ // Percorre a lista de contas
                if(numero_conta == auxContaMesAnt->numero_conta){ // Filtro de conta
                    if(auxContaMesAnt->id_cliente_conta == auxClienteMesAnt->id_cliente){ // Filtro de cliente
                        auxTransacoesMesAnt = listaTransacoes->prox; // Vai para o inicio da lista de transacoes
                        while(auxTransacoesMesAnt != NULL){ // Percorre a lista de eransacoes
                            if(auxTransacoesMesAnt->id_conta_origem == auxContaMesAnt->id_conta){ // Verificação de origem e destino
                                if(mes_atual->tm_mon > auxTransacoesMesAnt->data.tm_mon){
                                    saldo_mes_anterior-=auxTransacoesMesAnt->valor_trans;
                                }
                            }
                            if(auxTransacoesMesAnt->id_conta_destino == auxContaMesAnt->id_conta){ // Verificação de origem e destino
                                if(mes_atual->tm_mon > auxTransacoesMesAnt->data.tm_mon){
                                    saldo_mes_anterior+=auxTransacoesMesAnt->valor_trans;
                                }
                            }
                            auxTransacoesMesAnt = auxTransacoesMesAnt->prox; // Vai para a proxima posicao da lista
                        }
                    }
                }
                auxContaMesAnt = auxContaMesAnt->prox; // Vai para a proxima posicao da lista
            }
        }
        auxClienteMesAnt = auxClienteMesAnt->prox; // Vai para a proxima posicao da lista
    }
    printf("Saldo do mes anterior: %.2lf\n\n", saldo_mes_anterior);

    // Laço para exibir o saldo e as transacoes do mes atual
    // Mes atual
    while(auxCliente != NULL){ // Percorre a lista de clientes
        if(!strcmp(cpf,auxCliente->cpf)){ // Filtro de CPF
            while(auxConta != NULL){ // Percorre a lista de contas
                if(numero_conta == auxConta->numero_conta){ // Filtro de conta
                    if(cont_ == 0){ // Exibe os dados do cliente apenas uma vez
                        printf("Nome: %s | CPF: %s | Conta: %d\n\n", auxCliente->nome, auxCliente->cpf, auxConta->numero_conta);
                        cont_ = 1;
                    }
                    if(auxConta->id_cliente_conta == auxCliente->id_cliente){ // Filtro de cliente
                        auxTransacoes = listaTransacoes->prox; // Vai para o inicio da lista de transacoes
                        while(auxTransacoes != NULL){ // Percorre a lista de transacoes
                            if(auxTransacoes->id_conta_origem == auxConta->id_conta){ // Verificação de origem e destino
                                saldo-=auxTransacoes->valor_trans;
                                saldo_perdido-=auxTransacoes->valor_trans;
                                if(mes_atual->tm_mon == auxTransacoes->data.tm_mon){
                                    saldo_mes_atual-=auxTransacoes->valor_trans;
                                    if(saldo_perdido!=0){
                                        printf("Data: %d/%d/%d | Variacao: %d | Valor: %.2lf\n", auxTransacoes->data.tm_mday, auxTransacoes->data.tm_mon, auxTransacoes->data.tm_year, auxConta->variacao, saldo_perdido);
                                        saldo_perdido = 0;
                                        cont = 1;
                                    }
                                    if(saldo!=0){
                                        printf("Data: %d/%d/%d | Variacao: %d | Valor: %.2lf\n", auxTransacoes->data.tm_mday, auxTransacoes->data.tm_mon, auxTransacoes->data.tm_year, auxConta->variacao, saldo);
                                        cont = 1;
                                    }
                                }
                            }
                            if(auxTransacoes->id_conta_destino == auxConta->id_conta){ // Verificação de origem e destino
                                saldo+=auxTransacoes->valor_trans;
                                if(mes_atual->tm_mon == auxTransacoes->data.tm_mon){
                                    saldo_mes_atual+=auxTransacoes->valor_trans;
                                    if(saldo!=0){
                                        printf("Data: %d/%d/%d | Variacao: %d | Valor: %.2lf\n", auxTransacoes->data.tm_mday, auxTransacoes->data.tm_mon, auxTransacoes->data.tm_year, auxConta->variacao, saldo);
                                        cont = 1;
                                    }
                                }
                            }
                            auxTransacoes = auxTransacoes->prox; // Vai para a proxima posicao da lista
                        }
                    }
                    saldo = 0;
                }
                auxConta = auxConta->prox; // Vai para a proxima posicao da lista
            }
        }
        auxCliente = auxCliente->prox; // Vai para a proxima posicao da lista
    }

    // Exibido se não tiverem sido feitas trasacoes neste mes
    if(cont==0){
        printf("Nao foram feitas transacoes neste mes\n");
    }

    printf("\nSaldo do mes atual: %.2lf \n", saldo_mes_atual);

    // Sai da função após digitar qualquer coisa
    printf("\nDigite algum numero para sair: ");
    scanf("%s", x);
    return;
}

// Exibe o extrato do mes anterior
void extrato_mes_anterior(struct Cliente *listaCliente, struct Conta *listaConta, struct Transacoes *listaTransacoes, char cpf[], int numero_conta, int data_mes, int data_ano){

    // Declaração de variável
    double saldo_mes_anterior = 0, saldo_mes_anterior_ = 0, saldo_atual = 0, saldo_global = 0;
    struct tm *mes_atual = mesAtual();
    char x[MAX];
    int cont = 0, cont_ = 0, var = 0;

    // Criação de listas auxiliares (mes anterior)
    struct Cliente *auxClienteMesAtual = listaCliente->prox;
    struct Conta *auxContaMesAtual = listaConta->prox;
    struct Transacoes *auxTransacoesMesAtual = listaTransacoes->prox;

    // Criação de listas auxiliares (mes anterior)
    struct Cliente *auxClienteMesAnt = listaCliente->prox;
    struct Conta *auxContaMesAnt = listaConta->prox;
    struct Transacoes *auxTransacoesMesAnt = listaTransacoes->prox;

    // Criação de listas auxiliares (mes atual)
    struct Cliente *auxCliente = listaCliente->prox;
    struct Conta *auxConta = listaConta->prox;
    struct Transacoes *auxTransacoes = listaTransacoes->prox;

    // Laço para exibir o saldo do mes anterior
    // Mes anterior
    while(auxClienteMesAnt != NULL){ // Percorre a lista de clientes
        if(!strcmp(cpf,auxClienteMesAnt->cpf)){ // Filtro de CPF
            while(auxContaMesAnt != NULL){ // Percorre a lista de contas
                if(numero_conta == auxContaMesAnt->numero_conta){ // Filtro de conta
                    if(auxContaMesAnt->id_cliente_conta == auxClienteMesAnt->id_cliente){ // Filtro de cliente
                        auxTransacoesMesAnt = listaTransacoes->prox; // Vai para o inicio da lista de transacoes
                        while(auxTransacoesMesAnt != NULL){ // Percorre a lista de eransacoes
                            if(auxTransacoesMesAnt->id_conta_origem == auxContaMesAnt->id_conta){ // Verificação de origem e destino
                                if(mes_atual->tm_mon > auxTransacoesMesAnt->data.tm_mon){
                                    saldo_mes_anterior_-=auxTransacoesMesAnt->valor_trans;
                                }
                            }
                            if(auxTransacoesMesAnt->id_conta_destino == auxContaMesAnt->id_conta){ // Verificação de origem e destino
                                if(mes_atual->tm_mon > auxTransacoesMesAnt->data.tm_mon){
                                    saldo_mes_anterior_+=auxTransacoesMesAnt->valor_trans;
                                }
                            }
                            auxTransacoesMesAnt = auxTransacoesMesAnt->prox; // Vai para a proxima posicao da lista
                        }
                    }
                }
                auxContaMesAnt = auxContaMesAnt->prox; // Vai para a proxima posicao da lista
            }
        }
        auxClienteMesAnt = auxClienteMesAnt->prox; // Vai para a proxima posicao da lista
    }

    saldo_global = saldo_mes_anterior_;

    // Laço para exibir o saldo do mes anterior ao filtrado
    // Mes anterior
    while(auxCliente != NULL){ // Percorre a lista de clientes
        if(!strcmp(cpf,auxCliente->cpf)){ // Filtro de CPF
            while(auxConta != NULL){ // Percorre a lista de contas
                if(numero_conta == auxConta->numero_conta){ // Filtro de conta
                    if(auxConta->id_cliente_conta == auxCliente->id_cliente){ // Filtro de cliente
                        auxTransacoes = listaTransacoes->prox; // Vai para o inicio da lista de transacoes
                        while(auxTransacoes != NULL){ // Percorre a lista de transacoes
                            if(auxTransacoes->id_conta_origem == auxConta->id_conta){ // Verificação de origem e destino
                                if(data_mes <= auxTransacoes->data.tm_mon && data_ano <= auxTransacoes->data.tm_year){
                                    saldo_mes_anterior-=auxTransacoes->valor_trans;
                                    var = 1;
                                }
                            }
                            if(auxTransacoes->id_conta_destino == auxConta->id_conta){ // Verificação de origem e destino
                                if(data_mes <= auxTransacoes->data.tm_mon && data_ano <= auxTransacoes->data.tm_year){
                                    saldo_mes_anterior+=auxTransacoes->valor_trans;
                                    var = 1;
                                }
                            }
                            auxTransacoes = auxTransacoes->prox; // Vai para a proxima posicao da lista
                        }
                    }
                }
                auxConta = auxConta->prox; // Vai para a proxima posicao da lista
            }
        }
        auxCliente = auxCliente->prox; // Vai para a proxima posicao da lista
    }
    if(var==0){
        printf("Saldo mes anterior: %.2lf\n\n ", saldo_global);
    }else{
        printf("Saldo do mes anterior: %.2lf\n\n", saldo_mes_anterior);
    }

    // Laço para exibir o saldo do mes pesquisado
    // Mes atual
    while(auxClienteMesAtual != NULL){ // Percorre a lista de clientes
        if(!strcmp(cpf,auxClienteMesAtual->cpf)){ // Filtro de CPF
            while(auxContaMesAtual != NULL){ // Percorre a lista de contas
                if(numero_conta == auxContaMesAtual->numero_conta){ // Filtro de conta
                    if(cont_ == 0){ // Exibe os dados do cliente apenas uma vez
                        printf("Nome: %s | CPF: %s | Conta: %d\n\n", auxClienteMesAtual->nome, auxClienteMesAtual->cpf, auxContaMesAtual->numero_conta);
                        cont_ = 1;
                    }
                    if(auxContaMesAtual->id_cliente_conta == auxClienteMesAtual->id_cliente){ // Filtro de cliente
                        auxTransacoesMesAtual = listaTransacoes->prox; // Vai para o inicio da lista de transacoes
                        while(auxTransacoesMesAtual != NULL){ // Percorre a lista de transacoes
                            if(auxTransacoesMesAtual->id_conta_origem == auxContaMesAtual->id_conta){ // Verificação de origem e destino
                                if(data_mes == auxTransacoesMesAtual->data.tm_mon && data_ano == auxTransacoesMesAtual->data.tm_year){
                                    printf("Data: %d/%d/%d | Valor: %.2lf\n", auxTransacoesMesAtual->data.tm_mday, auxTransacoesMesAtual->data.tm_mon, auxTransacoesMesAtual->data.tm_year, auxTransacoesMesAtual->valor_trans*(-1));
                                    saldo_atual-=auxTransacoesMesAtual->valor_trans;
                                    cont = 1;
                                }
                            }
                            if(auxTransacoesMesAtual->id_conta_destino == auxContaMesAtual->id_conta){ // Verificação de origem e destino
                                if(data_mes == auxTransacoesMesAtual->data.tm_mon && data_ano == auxTransacoesMesAtual->data.tm_year){
                                    printf("Data: %d/%d/%d | Valor: %.2lf\n", auxTransacoesMesAtual->data.tm_mday, auxTransacoesMesAtual->data.tm_mon, auxTransacoesMesAtual->data.tm_year, auxTransacoesMesAtual->valor_trans);
                                    saldo_atual+=auxTransacoesMesAtual->valor_trans;
                                    cont = 1;
                                }
                            }
                            auxTransacoesMesAtual = auxTransacoesMesAtual->prox; // Vai para a proxima posicao da lista
                        }
                    }
                }
                auxContaMesAtual = auxContaMesAtual->prox; // Vai para a proxima posicao da lista
            }
        }
        auxClienteMesAtual = auxClienteMesAtual->prox; // Vai para a proxima posicao da lista
    }

    // Exibido se não tiverem sido feitas trasacoes neste mes
    if(cont==0){
        printf("Nao foram feitas transacoes neste mes\n");
    }

    printf("\nSaldo do mes atual: %.2lf \n", saldo_atual);

    // Sai da função após digitar algo
    printf("\nDigite algum numero para sair: ");
    scanf("%s", x);
    return;
}

// Converte a data para dias
int converter_para_dia(struct tm data_dia){
    return(data_dia.tm_year*365+data_dia.tm_mon*30+data_dia.tm_mday);
}

// Ordenação de data das transações
void ordenar_transacoes_data(struct Transacoes *listaTransacoes){

    // Criação de um nó final nulo
    struct Transacoes *noFim = NULL;

    while(listaTransacoes->prox != noFim){ // Percorre a lista de transacoes enquanto for diferente do no final
        struct Transacoes *antAux = listaTransacoes; // Criação de uma lista auxiliar para valores anteriores
        struct Transacoes *aux = listaTransacoes->prox; // Criação de uma lista auxiliar
        while(aux->prox != noFim){ // Percorre a lista auxiliar
            if(converter_para_dia(aux->data) > converter_para_dia(aux->prox->data)){ // Verificação de posições e troca
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
            if(converter_para_dia(aux->data_compra) > converter_para_dia(aux->prox->data_compra)){ // Verificação de posições e troca
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

int main(){

    // Criação de variaveis
    int x, i=0, id_cliente, id_conta, numero_conta, variacao, id_cliente_conta, id_operacao, id_operacao_trans, id_conta_origem, id_conta_destino, id_conta_trans_cc, qtde_parcelas, data_dia, data_mes, data_ano, data_compra_dia, data_compra_mes, data_compra_ano;
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
        inserir_cliente_ordenado(listaCliente, id_cliente, nome, cpf, telefone, municipio, estado);
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
    //ordenar_transacoes_data(listaTransacoes);
    printf("Data ordenada.\n");

    // Ordena a lista em ordem crescente de clientes de acordo com a data das transacoes
    printf("Ordenando data das transacoes do cartao.\n");
    ordenar_transacoes_cartao_data(listaTransCard);
    printf("Data ordenada.\n");

    system("cls"); // Limpa o cmd

    // Laço de opções
    while(1){

        system("cls"); // Limpa o cmd

        // Opções
        printf("\rEscolha a opcao de entrada:\n");
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
            listar_clientes_estado(listaCliente, listaConta, estado);
        }
        else if(x==2){
            system("cls");
            printf("Digite o CPF do cliente:\n");
            scanf("%s", cpf);
            system("cls");
            exibir_saldo_atual(listaCliente, listaConta, listaTransacoes, cpf);
        }
        else if(x==3){
            system("cls");
            listagem_saldo_atual(listaCliente);
        }
        else if(x==4){
            system("cls");
            printf("Digite o CPF do cliente:\n");
            scanf("%s", cpf);
            system("cls");
            printf("Digite o numero da conta do cliente:\n");
            scanf("%d", &numero_conta);
            system("cls");
            extrato_mes_atual(listaCliente, listaConta, listaTransacoes, cpf, numero_conta);
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
            extrato_mes_anterior(listaCliente, listaConta, listaTransacoes, cpf, numero_conta, data_mes, data_ano);
        }
        else if(x==6){
            system("cls");
            printf("Digite o CPF do cliente:\n");
            scanf("%s", cpf);
            system("cls");
            printf("Informe o mes e o ano da busca no formato mm/aaaa:\n");
            scanf("%d/%d", &data_mes, &data_ano);
            system("cls");
            fatura_cartao(listaCliente, listaConta, listaTransCard, cpf, data_mes, data_ano);
        }
        else if(x==7){
            system("cls");
            imprimir_lista(listaCliente, listaConta, listaOperacao, listaTransacoes, listaTransCard);
        }
        else if(x==0){
            exit(0);
        }
        else{
            printf("Opcao invalida.\n");
        }
    }

return 0;
}
