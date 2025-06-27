#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Função para exibir mensagens padronizadas
void exibe(const char *string) {
    printf("*** %s ***\n", string);
}

// Função para gerar o programa "programa_complexo.txt"
void gerar_programa_complexo() {
    FILE *arquivo = fopen("programa_complexo.txt", "w"); // Abre o arquivo para escrita
    if (arquivo == NULL) {
        printf("Erro ao criar o arquivo programa_complexo.txt\n");
        return;
    }

    // Comentários para o programa Simpletron gerado:
    // Este programa soma números inteiros positivos inseridos pelo usuário
    // e conta quantos números foram somados, parando quando 0 é inserido.
    //
    // Endereços de memória usados:
    // 90: Armazena a SOMA total
    // 91: Armazena a CONTAGEM de números
    // 92: Armazena o NÚMERO atual lido do usuário
    // 93: Constante 1 (usada para incrementar a contagem)

    // Instruções SML (Simpletron Machine Language):

    // Loop de leitura e soma
    fprintf(arquivo, "1092\n");    // 00: READ 92       ; Lê um número do usuário e armazena em mem[92]
    fprintf(arquivo, "2092\n");    // 01: LOAD 92       ; Carrega o número lido para o acumulador
    fprintf(arquivo, "4210\n");    // 02: BRANCHZERO 10 ; Se o acumulador for ZERO (sentinela), pula para a instrução 10 (imprimir resultados)

    // Soma o número atual à soma total
    fprintf(arquivo, "2090\n");    // 03: LOAD 90       ; Carrega a soma atual para o acumulador
    fprintf(arquivo, "3092\n");    // 04: ADD 92        ; Soma o número lido (mem[92]) ao acumulador
    fprintf(arquivo, "2190\n");    // 05: STORE 90      ; Armazena a nova soma em mem[90]

    // Incrementa o contador de números
    fprintf(arquivo, "2091\n");    // 06: LOAD 91       ; Carrega a contagem atual para o acumulador
    fprintf(arquivo, "3093\n");    // 07: ADD 93        ; Adiciona 1 (mem[93]) à contagem
    fprintf(arquivo, "2191\n");    // 08: STORE 91      ; Armazena a nova contagem em mem[91]

    fprintf(arquivo, "4000\n");    // 09: BRANCH 00     ; Volta para o início do loop (lê o próximo número)

    // Imprime os resultados
    fprintf(arquivo, "1190\n");    // 10: WRITE 90      ; Imprime a SOMA total
    fprintf(arquivo, "1191\n");    // 11: WRITE 91      ; Imprime a CONTAGEM de números
    fprintf(arquivo, "4300\n");    // 12: HALT          ; Para a execução do programa

    // Áreas de dados na memória:
    fprintf(arquivo, "0000\n");    // 90: SOMA (inicialmente 0)
    fprintf(arquivo, "0000\n");    // 91: CONTAGEM (inicialmente 0)
    fprintf(arquivo, "0000\n");    // 92: NÚMERO LIDO (inicialmente 0)
    fprintf(arquivo, "0001\n");    // 93: CONSTANTE 1

    // Sentinela para o leitor de arquivos (não para o programa SML)
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
