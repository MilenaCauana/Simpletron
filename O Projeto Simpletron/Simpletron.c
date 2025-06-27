/* Milena Cauana - Simpletron
*
* - Montaremos um computador (por meio da t�cnica de simula��o baseada no software)
*   por meio do qual ser� poss�vel executar os programas em linguagem de m�quina.
*
* - Simpeltron: nome do computador que ser� criado. Ele roda programas escritor na
*   linguagem que ele entende diretamente (SML - Simpeltron Machine Language);
*
* - Toda informa��o � tratada em termos de palavras. Uma palavra � um n�mero de de-
*   cimal de quatro d�gitos com sinal, como +3364, -1293, +0007, -0001 e assim por
*   diante.
*
* - � equipado com uma mem�ria de 100 palavras, e essas palavras s�o referenciadas
*   por seus n�metos de local 00, 01, ..., 99.
*
* - Antes de executar um programa SML, temos que carregar, ou colocar o programa na
*   mem�ria. A primeira instru��o � sempre colocada no local 00. Cada instru��o ocupa
*   uma palavra da mem�ria, ou seja, as instru��es s�o n�meros deciamais de quatro d�-
*   gitos com sinal.
*
* - Os dois primeiros d�gitos de cada instru��o SML consistem no c�digo de opera��o,
*   que especifica a opera��o a ser realizada.
*
* - Os dois �ltimos d�gitos de uma instru��o SML consistem no operando, que � o endere�o
*   de mem�ria que cont�m a palavra � qual a opera��o se aplica.
*
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <math.h>
#include <stdbool.h>
#include <ctype.h>

#define MAX 75

/* LEMBRAR:
*  - N�o � para ser por vari�veis globais;
*/

#define MEMORIA 100 //O que ser� colocado no local 00 ser� sempre a primeira instru��o de cada programa
#define SENTINELA -99999
#define MAX_NUMBER 99999

//--- C�DIGO DE OPERA��O E SEU SINIFICADO ---

// --Opera��es de entrada/sa�da:
#define READ 10 //L� uma palavra do terminal para um local espec�fico na mem�ria
#define WRITE 11 //Escreve uma palavra de um local espec�fico na mem�ria para o terminal

// -- Opera��es de carregamento/armazenamento:
#define LOAD 20 //Carrega uma palavra de um local espec�fico na mem�ria para o acumulador
#define STORE 21 //Armazena uma palavra do acumulador para um local espec�fico na mem�ria

// --Opera��es aritm�ticas:
#define ADD 30 //Soma uma palavra de um local espec�fico na mem�ria � palavra no acumulador (deixa o resultado no acumulador)
#define SUBTRACT 31 //Subtrai uma palavra de um local espec�fico
#define DIVIDE 32 //Divide uma palavra de um local espec�fico nan mem�ria pela palavra no acumulador (deixa o resultado no acumulador)
#define MULTIPLY 33 //Multiplica uma palavra de um local esoec�fico na mem�ria pela palavra no acumulador (deixa o resultado no acumulador)
#define EXPONENTIATION 34
#define MODULO 35

// --Opera��es de transfer�ncia de controle:
#define BRANCH 40 //Desvia um local espec�fico na mem�ria
#define BRANCHNEG 41 //Desvia para um local espec�fico na mem�ria de o acumulador for negativo
#define BRANCHZERO 42 //Desvia para um local espec�fico na mem�ria se o acumulador for zero
#define HALT 43 //Para (halt). Ou seja, o programa concluiu sua tarefa


// -- Erros fatais:
enum Errors
{
    OPERAND_CODE_ERROR = 1,
    INTERVAL_ERROR,
    ADD_ERROR,
    SUBTRACT_ERROR,
    DIVIDE_ERROR,
    DIVIDE_ZERO,
    MULTIPLY_ERROR,
    EXPONENTIATION_ERROR,
    MODULO_ERROR
};

// -- ESTRUTURA SIMPLETRON --
/* Para passar as informa��es como par�metros*/
typedef struct
{
    int memoria[MEMORIA];
    int acumulador;
    int contadorDeInstrucao;
    int registradorDeInstrucao;
    int codigoOperacao;
    int operando;
} Simpletron;

// --- MENSAGEM DE BOAS-VINDAS ---

/*Para facilitar, criarei uma fun��o que recebe uma string e exibe ela
* Colocarei a mensagem de boas vindas original, por�m, adicionarei que,
* o programa ser� lido atrav�s de um arquivo .txt
*/
void exibe(char *string)
{
    printf("*** %s ***\n", string);
}

void bemVindo()
{
    exibe("Bem vindo ao Simpeltron!");
    exibe("Favor digitar seu programa, uma instru��o");
    exibe("(ou palavra de dados) por vez. Mostrarei");
    exibe("o n�mero do local e uma interroga��o (?).");
    exibe("Voc�, ent�o, dever� digitar a palavra para esse");;
    exibe("local. Digite a sentinela - 99999 para");
    exibe("encerrar a entrada do seu programa");
}

// --- FUN��ES DO COMPUTADOR ---

/* Inicializa os componentes do Simpletron */
void initSimpletron(Simpletron *s)
{
    for (int i = 0; i < MEMORIA; i++)
    {
        s->memoria[i] = 0;
    }

    s->acumulador = 0;
    s->contadorDeInstrucao = 0;
    s->registradorDeInstrucao = 0;
    s->codigoOperacao = 0;
    s->operando = 0;
}

/* Fun��o que verifica se um valor est� dentro dos limites seguros */
bool estaNosLimites(int valor)
{
    return (valor >= -MAX_NUMBER && valor <= MAX_NUMBER);
}

/* Fun��o que verifica se uma instru��o lida � v�lida */
bool instrucaoValida(int instrucao)
{
    if (!estaNosLimites(instrucao) && instrucao != SENTINELA)
    {
        printf("\n\n******Instrucao Invalida: %+04d******\n", instrucao);
        return false;
    }
    return true;
}

/* Fun��o para imprimir o estado dos registradores e o conte�do da mem�ria (dump) */
void dump(Simpletron *s)
{
    printf("\nREGISTRADORES:\n");
    printf("acumulador              %+05d\n", s->acumulador);
    printf("contadorDeInstrucao          %02d\n", s->contadorDeInstrucao);
    printf("registradorDeInstrucao      %+05d\n", s->registradorDeInstrucao);
    printf("codigoOperacao               %02d\n", s->codigoOperacao);
    printf("operando                     %02d\n", s->operando);

    printf("\nMEMORIA:\n\n");
    int quantidade = 10; // Usando 10 para uma tabela 10x10

    printf("         ");
    for (int i = 0; i < quantidade; i++)
    {
        printf("%s%d      ", (i > 9) ? "" : " ", i);
    }
    printf("\n");

    for (int i = 0; i < MEMORIA; i += quantidade)
    {
        printf("%02d  ", i);
        for (int j = 0; j < quantidade; j++)
        {
            if (i + j >= MEMORIA) break;
            printf(" %+05d ", s->memoria[i + j]);
        }
        printf("\n");
    }
    printf("\n");
}

/* Fun��o que trata os erros fatais */
bool errosFatais(Simpletron *s, int codigoErro)
{
    dump(s);

    switch (codigoErro)
    {
        case OPERAND_CODE_ERROR:
            exibe("Codigo de Operacao invalido.");
            break;
        case INTERVAL_ERROR:
            exibe("Numero fora do intervalo -9999 a +9999.");
            break;
        case ADD_ERROR:
            exibe("A soma no acumulador ultrapassou os limites do registrador.");
            break;
        case SUBTRACT_ERROR:
            exibe("A subtracao no acumulador ultrapassou os limites do registrador.");
            break;
        case DIVIDE_ERROR:
            exibe("A divisao no acumulador ultrapassou os limites do registrador.");
            break;
        case DIVIDE_ZERO:
            exibe("Tentativa de divisao por zero.");
            break;
        case MULTIPLY_ERROR:
            exibe("A multiplicacao no acumulador ultrapassou os limites do registrador.");
            break;
        case EXPONENTIATION_ERROR:
            exibe("A exponenciacao no acumulador ultrapassou os limites do registrador.");
            break;
        case MODULO_ERROR:
            exibe("A divisao para o calculo do modulo ultrapassou os limites do registrador.");
            break;
        default:
            return false;
    }
    return true; // Ocorreu um erro fatal.
}

/* Fun��o que armazena o programa na mem�ria a partir de um arquivo */
int lerPrograma(Simpletron *s, const char *arquivo)
{
    FILE *programa = fopen(arquivo, "r");
    if (!programa)
    {
        printf("\n*********\n");
        exibe("Arquivo nao encontrado!");
        return -1;
    }

    // Tentar detectar e pular o Byte Order Mark (BOM) UTF-8 --> Se o arquivo que estiver sendo lido tiver isso, ele n�o vai conseguir ler as instru��es, por isso � preciso tratar
    unsigned char bom[3];
    if (fread(bom, 1, 3, programa) == 3)
    {
        if (!(bom[0] == 0xEF && bom[1] == 0xBB && bom[2] == 0xBF))
        {
            fseek(programa, 0, SEEK_SET);
        }
    } else
    {
        fseek(programa, 0, SEEK_SET);
    }
    // FIM DO TRATAMENTO DO BOM

    const int TAM_INSTRUCAO = 10;
    char linha[TAM_INSTRUCAO];
    int instrucoesLidas = 0;
    int instrucao;

    while (fgets(linha, sizeof(linha), programa) != NULL && instrucoesLidas < MEMORIA)
    {
        linha[strcspn(linha, "\r\n")] = '\0';

        bool is_whitespace = true;
        for (int i = 0; linha[i] != '\0'; i++)
        {
            if (!isspace((unsigned char)linha[i]))
            {
                is_whitespace = false;
                break;
            }
        }
        if (is_whitespace)
        {
            continue;
        }

        if (sscanf(linha, "%d", &instrucao) != 1)
        {
            printf("\n\n******Erro de Leitura: Linha '%s' nao eh um numero valido.******\n", linha);
            fclose(programa);
            return 0; // Retorna 0 para indicar erro na leitura
        }

        if (instrucao == SENTINELA)
        {
            break;
        }

        if (!instrucaoValida(instrucao))
        {
            fclose(programa);
            return 0;
        }

        s->memoria[instrucoesLidas++] = instrucao;
    }

    if (programa != NULL)
    {
        fclose(programa);
    }

    return instrucoesLidas;
}


/* FUN��O QUE DE FATO EXECUTA AS INSTRU��ES V�LIDAS
* Retorna true se a execu��o deve parar, false caso contr�rio */
bool executarInstrucao(Simpletron *s)
{
    switch (s->codigoOperacao)
    {
        case READ:
            printf("Digite um numero para a posicao de memoria %02d: ", s->operando);
            scanf("%d", &s->memoria[s->operando]);
            if (!estaNosLimites(s->memoria[s->operando]))
            {
                return errosFatais(s, INTERVAL_ERROR);
            }
            break;
        case WRITE:
            printf("\n%d\n", s->memoria[s->operando]);
            break;
        case LOAD:
            s->acumulador = s->memoria[s->operando];
            break;
        case STORE:
            s->memoria[s->operando] = s->acumulador;
            break;
        case ADD:
            s->acumulador += s->memoria[s->operando];
            if (!estaNosLimites(s->acumulador))
            {
                return errosFatais(s, ADD_ERROR);
            }
            break;
        case SUBTRACT:
            s->acumulador -= s->memoria[s->operando];
            if (!estaNosLimites(s->acumulador))
            {
                return errosFatais(s, SUBTRACT_ERROR);
            }
            break;
        case DIVIDE:
            if (s->memoria[s->operando] == 0)
            {
                return errosFatais(s, DIVIDE_ZERO);
            }
            s->acumulador /= s->memoria[s->operando];
            if (!estaNosLimites(s->acumulador))
            {
                return errosFatais(s, DIVIDE_ERROR);
            }
            break;
        case MULTIPLY:
            s->acumulador *= s->memoria[s->operando];
            if (!estaNosLimites(s->acumulador))
            {
                return errosFatais(s, MULTIPLY_ERROR);
            }
            break;
        case EXPONENTIATION:
            s->acumulador = (int)pow(s->acumulador, s->memoria[s->operando]);
            if (!estaNosLimites(s->acumulador))
            {
                return errosFatais(s, EXPONENTIATION_ERROR);
            }
            break;
        case MODULO:
            if (s->memoria[s->operando] == 0)
            {
                return errosFatais(s, DIVIDE_ZERO);
            }
            s->acumulador %= s->memoria[s->operando];
            if (!estaNosLimites(s->acumulador))
            {
                return errosFatais(s, MODULO_ERROR);
            }
            break;
        case BRANCH:
            s->contadorDeInstrucao = s->operando;
            return false; // N�o incrementa o contador de instru��o ap�s o branch
        case BRANCHNEG:
            if (s->acumulador < 0)
            {
                s->contadorDeInstrucao = s->operando;
                return false;
            }
            break;
        case BRANCHZERO:
            if (s->acumulador == 0)
            {
                s->contadorDeInstrucao = s->operando;
                return false;
            }
            break;
        case HALT:
            return true;
        default:
            return errosFatais(s, OPERAND_CODE_ERROR);
    }

    s->contadorDeInstrucao++; // Incrementa o contador para a pr�xima instru��o (exceto em BRANCH)
    return false; // A opera��o � v�lida e a execu��o continua
}

/* Fun��o que executa o programa */
void executarPrograma(Simpletron *s, int numInstrucoes)
{
    while (s->contadorDeInstrucao < numInstrucoes)
    {
        s->registradorDeInstrucao = s->memoria[s->contadorDeInstrucao];
        s->codigoOperacao = s->registradorDeInstrucao / 100;
        s->operando = s->registradorDeInstrucao % 100;

        if (s->operando < 0 || s->operando >= MEMORIA)
        {
            errosFatais(s, OPERAND_CODE_ERROR); // Ou um erro mais espec�fico de operando inv�lido
            break;
        }

        if (executarInstrucao(s))
        {
            break;
        }
    }

    if (s->codigoOperacao == HALT)
    {
        exibe("Execucao encerrada!");
        dump(s);
    } else
    {
        exibe("Execucao encerrada com erro!");
    }
}

void rodarPrograma(Simpletron *s, const char *arquivo)
{
    int instrucoesLidas = lerPrograma(s, arquivo);
    if (instrucoesLidas > 0)
    {
        exibe("Programa carregado com sucesso! Iniciando execucao...");
        executarPrograma(s, instrucoesLidas);
    } else if (instrucoesLidas == 0)
    {
         exibe("Erro ao ler o programa do arquivo.");
    }
}

// --- MAIN ---
int main()
{
    setlocale(LC_ALL, "Portuguese");

    Simpletron simpletron;
    initSimpletron(&simpletron);

    char arquivoTXT[MAX];

    bemVindo();

    printf("\n===========================================\n");
    exibe("PARA ESTA IMPLEMENTACAO:");
    exibe("O programa sera lido atraves de um arquivo .txt.");
    exibe("Forneca o arquivo que contem o programa que sera executado.");
    printf("Caminho para o arquivo (.txt): ");
    scanf("%s", arquivoTXT);

    rodarPrograma(&simpletron, arquivoTXT);

    return 0;
}
