#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Função para exibir mensagens padronizadas
void exibe(const char *string) {
    printf("*** %s ***\n", string);
}

// Função para gerar o programa "ler_exibir_parar.txt"
void gerar_ler_exibir_parar() {
    FILE *arquivo = fopen("ler_exibir_parar.txt", "w"); // Abre o arquivo para escrita
    if (arquivo == NULL) {
        printf("Erro ao criar o arquivo ler_exibir_parar.txt\n");
        return;
    }

    fprintf(arquivo, "1009\n");    // READ 09
    fprintf(arquivo, "1109\n");    // WRITE 09
    fprintf(arquivo, "4300\n");    // HALT
    fprintf(arquivo, "0000\n");    // Local de memória 09 (para o valor a ser lido)
    fprintf(arquivo, "-99999\n");  // Sentinela

    fclose(arquivo); // Fecha o arquivo
    exibe("Arquivo 'ler_exibir_parar.txt' gerado com sucesso!");
}

// Função para gerar o programa "somar_dois_numeros.txt"
void gerar_somar_dois_numeros() {
    FILE *arquivo = fopen("somar_dois_numeros.txt", "w"); // Abre o arquivo para escrita
    if (arquivo == NULL) {
        printf("Erro ao criar o arquivo somar_dois_numeros.txt\n");
        return;
    }

    fprintf(arquivo, "1009\n");    // READ 09 (primeiro número)
    fprintf(arquivo, "1010\n");    // READ 10 (segundo número)
    fprintf(arquivo, "2009\n");    // LOAD 09
    fprintf(arquivo, "3010\n");    // ADD 10
    fprintf(arquivo, "2111\n");    // STORE 11 (resultado)
    fprintf(arquivo, "1111\n");    // WRITE 11
    fprintf(arquivo, "4300\n");    // HALT
    fprintf(arquivo, "0000\n");    // Local de memória 09
    fprintf(arquivo, "0000\n");    // Local de memória 10
    fprintf(arquivo, "0000\n");    // Local de memória 11
    fprintf(arquivo, "-99999\n");  // Sentinela

    fclose(arquivo); // Fecha o arquivo
    exibe("Arquivo 'somar_dois_numeros.txt' gerado com sucesso!");
}

// Função para gerar o programa "multiplicar_simples.txt"
void gerar_multiplicar_simples() {
    FILE *arquivo = fopen("multiplicar_simples.txt", "w"); // Abre o arquivo para escrita
    if (arquivo == NULL) {
        printf("Erro ao criar o arquivo multiplicar_simples.txt\n");
        return;
    }

    fprintf(arquivo, "1009\n");    // READ 09 (primeiro número)
    fprintf(arquivo, "1010\n");    // READ 10 (segundo número)
    fprintf(arquivo, "2009\n");    // LOAD 09
    fprintf(arquivo, "3310\n");    // MULTIPLY 10
    fprintf(arquivo, "2111\n");    // STORE 11 (resultado)
    fprintf(arquivo, "1111\n");    // WRITE 11
    fprintf(arquivo, "4300\n");    // HALT
    fprintf(arquivo, "0000\n");    // Local de memória 09
    fprintf(arquivo, "0000\n");    // Local de memória 10
    fprintf(arquivo, "0000\n");    // Local de memória 11
    fprintf(arquivo, "-99999\n");  // Sentinela

    fclose(arquivo); // Fecha o arquivo
    exibe("Arquivo 'multiplicar_simples.txt' gerado com sucesso!");
}

int main() {
    exibe("Iniciando a geracao dos arquivos de programa Simpletron...");

    gerar_ler_exibir_parar();
    gerar_somar_dois_numeros();
    gerar_multiplicar_simples();

    exibe("Todos os arquivos de programa Simpletron foram gerados.");

    return 0; // Retorna 0 para indicar sucesso
}
