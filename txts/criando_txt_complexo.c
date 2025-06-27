#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Fun��o para exibir mensagens padronizadas
void exibe(const char *string) {
    printf("*** %s ***\n", string);
}

// Fun��o para gerar o programa "programa_complexo.txt"
void gerar_programa_complexo() {
    FILE *arquivo = fopen("programa_complexo.txt", "w"); // Abre o arquivo para escrita
    if (arquivo == NULL) {
        printf("Erro ao criar o arquivo programa_complexo.txt\n");
        return;
    }

    // Coment�rios para o programa Simpletron gerado:
    // Este programa soma n�meros inteiros positivos inseridos pelo usu�rio
    // e conta quantos n�meros foram somados, parando quando 0 � inserido.
    //
    // Endere�os de mem�ria usados:
    // 90: Armazena a SOMA total
    // 91: Armazena a CONTAGEM de n�meros
    // 92: Armazena o N�MERO atual lido do usu�rio
    // 93: Constante 1 (usada para incrementar a contagem)

    // Instru��es SML (Simpletron Machine Language):

    // Loop de leitura e soma
    fprintf(arquivo, "1092\n");    // 00: READ 92       ; L� um n�mero do usu�rio e armazena em mem[92]
    fprintf(arquivo, "2092\n");    // 01: LOAD 92       ; Carrega o n�mero lido para o acumulador
    fprintf(arquivo, "4210\n");    // 02: BRANCHZERO 10 ; Se o acumulador for ZERO (sentinela), pula para a instru��o 10 (imprimir resultados)

    // Soma o n�mero atual � soma total
    fprintf(arquivo, "2090\n");    // 03: LOAD 90       ; Carrega a soma atual para o acumulador
    fprintf(arquivo, "3092\n");    // 04: ADD 92        ; Soma o n�mero lido (mem[92]) ao acumulador
    fprintf(arquivo, "2190\n");    // 05: STORE 90      ; Armazena a nova soma em mem[90]

    // Incrementa o contador de n�meros
    fprintf(arquivo, "2091\n");    // 06: LOAD 91       ; Carrega a contagem atual para o acumulador
    fprintf(arquivo, "3093\n");    // 07: ADD 93        ; Adiciona 1 (mem[93]) � contagem
    fprintf(arquivo, "2191\n");    // 08: STORE 91      ; Armazena a nova contagem em mem[91]

    fprintf(arquivo, "4000\n");    // 09: BRANCH 00     ; Volta para o in�cio do loop (l� o pr�ximo n�mero)

    // Imprime os resultados
    fprintf(arquivo, "1190\n");    // 10: WRITE 90      ; Imprime a SOMA total
    fprintf(arquivo, "1191\n");    // 11: WRITE 91      ; Imprime a CONTAGEM de n�meros
    fprintf(arquivo, "4300\n");    // 12: HALT          ; Para a execu��o do programa

    // �reas de dados na mem�ria:
    fprintf(arquivo, "0000\n");    // 90: SOMA (inicialmente 0)
    fprintf(arquivo, "0000\n");    // 91: CONTAGEM (inicialmente 0)
    fprintf(arquivo, "0000\n");    // 92: N�MERO LIDO (inicialmente 0)
    fprintf(arquivo, "0001\n");    // 93: CONSTANTE 1

    // Sentinela para o leitor de arquivos (n�o para o programa SML)
    fprintf(arquivo, "-99999\n");

    fclose(arquivo); // Fecha o arquivo
    exibe("Arquivo 'programa_complexo.txt' gerado com sucesso!");
}

int main() {
    exibe("Iniciando a geracao do arquivo de programa Simpletron complexo...");

    gerar_programa_complexo();

    exibe("O arquivo 'programa_complexo.txt' foi gerado.");

    return 0; // Retorna 0 para indicar sucesso
}
