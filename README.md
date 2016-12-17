Instituto Federal de Educação, Ciência e Tecnologia do Ceará (IFCE) - Campus Aracati
CURSO: BACHARELADO EM CIÊNCIA DA COMPUTAÇÃO
DISCIPLINA: LINGUAGEM DE PROGRAMAÇÃO I - PROF°(ª): RAQUEL SILVEIRA
ALUNO(A): ALBERTO ZARANZA VALENÇA DE FREITAS
PROJETO PRÁTICO



Projeto: Sistema de Controle de Operações Financeiras

Descrição do Sistema:
O sistema de controle de operações financeiras consiste em um instrumento para auxiliar a
operadora na consolidação da transações financeiras realizadas pelos clientes. Os dados são
mantidos em arquivo .txt organizado na seguinte estrutura:

*cliente*
id_cliente, nome, cpf, telefone, municipio, estado;

*conta*
id_conta, numero_conta, variacao, id_cliente;

*operacao*
id_operacao, nome;

*transacoes*
data, id_operacao, id_conta_origem, id_conta_destino, valor;

*transacoes_cartao_credito*
data_compra, id_conta, descricao, qtde_parcelas, valor;

Por exemplo:
*cliente*
001, Carlos Antonio, 001.001.001-01, (88) 3421-1010, Aracati, CE;
002, Joao Jose, 002.002.002.002-02, (88) 3421-2020, Aracati, CE;
003, Carla Maria, 003.003.003-03, (88) 99999-0303, Aracati, CE;

*conta*
001, 12345, 000, 001;
002, 12345, 010, 001;
003, 67890, 010, 002;
004, 13579, 000, 003;

*operacao*
001, saque;
002, depósito;
003, transferência;

*transacoes*
01/10/2016, 002, 000, 001, 500;
02/10/2016, 001, 001, 000, 100;
03/10/2016, 003, 001, 002, 200;

*transacoes_cartao_credito*
01/10/2016, 001, Americanas SP, 2, 299.00;
01/10/2016, 001, Saraiva SP, 1, 52.50;
02/10/2016, 004, Submarino SP, 5, 599.00;



As observações abaixo apresentam as principais características dos sistema de controle de
operações financeiras:

• A variação da conta representa o tipo de conta, sendo:
  000: conta corrente
  010: conta poupança
  020: conta poupança

• Cada cliente poderá ter várias contas bancárias. Um mesmo número de conta poderá ter as
variações 000, 010 e/ou 020. Não é permitido para um mesmo número de conta ter duas
variações 000, 010 ou 020.

• Somente as contas associadas a variação 000 terão a opção de cartão de crédito.

• As operações representam o tipo de transação financeira que o cliente poderá realizar,
sendo:
  001: saque (com função de debitar o valor na conta origem)
  002: depósito (com função de creditar o valor na conta destino)
  003: transferência (com função de debitar o valor na conta origem e creditar na conta
  destino)

• Para as transações de saque não será informada a conta destino, sendo este valor
preenchido com 000.

• Para as transações de depósito não será informada a conta origem, sendo este valor
preenchido com 000.

• As faturas de cartão de crédito apresentarão as compras do mês anterior (além das
compras parceladas), ou seja, a fatura do mês de outubro/2016 constará as compras
realizadas entre o dia 01 a 30 de setembro/2016.

• As compras parceladas constarão nas faturas dos n (conforme quantidade de parcelas)
meses posteriores a data da realização da compra, cujo valor será o valor da compra
dividido pela quantidade de parcelas.
O sistema deve realizar a consolidação dos dados, apresentando o resultado conforme as
opções abaixo:
1. Listagem de clientes por estado: Representa a listagem dos clientes por estado.
Filtro: estado
Resultado: id do cliente, nome, CPF, telefone, município e quantidade de contas
que o cliente possui.
2. Saldo atual do cliente: Representa a listagem do saldo atual do cliente em cada conta.
Filtro: CPF do cliente
Resultado: nome do cliente e saldo total, além da listagem das contas contendo
número da conta, variação e saldo da conta.
Obs.:
(i) o saldo total corresponde ao somatório do saldo de cada conta do cliente;
(ii) o saldo de cada conta é calculado da seguinte forma:
saldo = transações de depósito + transações de transferência cuja conta
é a conta destino – transações de saque – transações de transferência
cuja conta é conta origem
3. Listagem do saldo dos clientes: Representa a listagem de todos os clientes com o
saldo de cada cliente.
Sem filtro
Resultado: nome do cliente, CPF e saldo total das contas do usuário.
Obs.: Os dados devem ser exibidos em ordem decrescente pelo saldo.
4. Extrato bancário (mês atual): Representa a listagem das transações realizadas pelo
cliente no mês atual.
Filtro: CPF do cliente e número da conta
Resultado: saldo anterior, transações (data, descrição, valor) e saldo atual
Obs.:
(i) o saldo anterior representará o saldo da conta do cliente no mês anterior ao
atual;
(ii) para as transações de saque e transferência (cuja conta é conta origem), o
valor deve ser exibido negativo;
(iii) o saldo corresponde o saldo atual, calculado conforme o item 2;
(iv) as transações devem ser exibidas em ordem crescente por data.

5. Extrato bancário (mês anterior): Representa a listagem das transações realizadas pelo
cliente no mês especificado pelo usuário.
Filtro: CPF do cliente, número da conta e mês/ano.
Resultado: saldo anterior, transações (data, descrição, valor) e saldo do mês
Obs.:
(i) o saldo anterior representará o saldo da conta do cliente no mês anterior ao
mês informado pelo usuário;
(ii) para as transações de depósito e transferência, o valor deve ser exibido
negativo;
(iii) o saldo do mês especificado pelo usuário, calculado conforme descrito no
item 2, com as transações realizadas até o mês especificado pelo usuário;
(iv) as transações devem ser exibidas em ordem crescente por data.

6. Fatura do cartão de crédito: Representa o detalhamento das compras realizadas pelo
cliente.
Filtro: CPF do cliente e mês/ano.
Resultado:
Nome do cliente
Listagem das compras realizadas, contendo: data, descrição e valor.
Valor total da fatura
Valor mínimo da fatura
Obs.:
(i) Para as compras parcelas, a descrição deve conter o número da parcela e a
quantidade total de parcelas, por exemplo, Americanas SP 1/3
(correspondendo a parcela 1 do total de 3 parcelas);
(ii) O valor mínimo da fatura corresponde a 10% do valor total;
(iii) As compras devem ser exibidas em ordem crescente por data.
(iv) A fatura deve ser armazenada em um arquivo.



Restrições de Implementação:

• Utilização de structs e listas simplesmente encadeadas para armazenamento dos dados.

• Organização do código em funções.

• Para as operações de ordenação, utilização de um dos algoritmos de ordenação: Insertion
Sort, Bubble Sort ou Selection Sort.

• Permitidas apenas funções das bibliotecas stdio.h, stdlib.h, string.h e time.h.

• Indispensável o uso de comentários nas funções e em trechos complexos do código.
