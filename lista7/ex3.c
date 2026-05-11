#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>


typedef struct Cidadela Cidadela;
typedef struct Mensagem Mensagem;


struct Cidadela {
    char nome[50];
    char funcao[50];

    long long populacao;
    int grau_perigo;
};


struct Mensagem {
    char txt[1000];
    int txt_i;

    int maiusculas_pos[1000];
    int maiusculas_i;

    int exclamacao_pos[1000];
    int exclamacoes_i;

    int estrela_pos[1000];
    int estrelas_i;

    long long numero;

    int numeros_arr[1000];
    int numeros_i;

    int funcao[1000];
    int funcao_i;

    // guarda a posicao do primeiro espaço
    int espaco_duplo_pos[1000];
    int espaco_i;


    int is_especial;
    int size;

    Cidadela *cidadela;
};


// preencher array com um valor
void fill_arr(int val, int arr[]) {
    for (size_t i = 0; i < 1000; i++)
    {
        arr[i] = val;
    }
}


// colocar '\0' em todas as posicoes do array
void fill_str(char arr[], int n) {
    for (size_t i = 0; i < 1000; i++)
    {
        arr[i] = '\0';
    }
}


// coloca as posicoes como -1, e o texto como '\0'
void inicializar_mensagem(Mensagem *msg) {
    fill_arr( -1, msg->maiusculas_pos );
    fill_arr( -1, msg->exclamacao_pos );
    fill_arr( -1, msg->espaco_duplo_pos );
    fill_arr( -1, msg->estrela_pos );

    fill_str( msg->txt, 1000 );

    msg->txt_i = 0;
    msg->is_especial = 0;
    msg->size = 0;
    msg->numero = -1;

    msg->maiusculas_i = 0;
    msg->exclamacoes_i = 0;
    msg->estrelas_i = 0;
    msg->numeros_i = 0;
    msg->funcao_i = 0;
    msg->espaco_i = 0;
}


// pegar os espaços duplos da mensagem
void get_espacos(Mensagem *msg) {
    for (size_t i = 0; i < (msg->size) - 1;) {
        char ch1 = msg->txt[i];
        char ch2 = msg->txt[i + 1];

        if ((ch1 == ' ') && (ch2 == ' ')) {
            int espaco_i = msg->espaco_i;

            msg->espaco_duplo_pos[ espaco_i ] = i;
            (msg->espaco_i)++;

            i += 3;
        } else {
            i++;
        }
    }
}


// adicionar os caracteres maiusculos, e adicionar em `msg`
void get_maiusculas(Mensagem *msg) {
    for (size_t i = 0; i < (msg->size); i++)
    {
        char chr = msg->txt[i];

        int prev_i1 = i - 1;
        int prev_i2 = i - 2;
        int is_duplo_espaco = 0;

        if ((prev_i1 >= 0) && (prev_i2 >= 0)) {
            char letra1 = msg->txt[prev_i1];
            char letra2 = msg->txt[prev_i2];

            if ((letra1 == ' ') && (letra2 == ' ')) {
                is_duplo_espaco = 1;
            }
        }

        if ((isupper(chr)) && (!is_duplo_espaco)) {
            int maiuscula_i = msg->maiusculas_i;

            msg->maiusculas_pos[maiuscula_i] = i;
            (msg->maiusculas_i)++;
        }
    }
}


// adicionar os numeros, e adicionar em `msg`
void get_numeros(Mensagem *msg) {
    for (size_t i = 0; i < (msg->size); i++)
    {
        char digito_chr = msg->txt[i];

        if (isdigit(digito_chr)) {
            int numeros_i = msg->numeros_i;

            msg->numeros_arr[numeros_i] = i;
            (msg->numeros_i)++;
        }
    }
}


// adicionar os caracteres '*', e adicionar em `msg`
void get_estrela(Mensagem *msg) {
    for (size_t i = 0; i < (msg->size); i++)
    {
        char letra = msg->txt[i];

        if (letra == '*') {
            int estrela_i = msg->estrelas_i;

            msg->estrela_pos[estrela_i] = i;
            (msg->estrelas_i)++;
        }
    }
}


// adicionar os caracteres depois de espaços duplos,
// e adicionar em `msg`
void get_funcao(Mensagem *msg) {
    for (size_t i = 0; i < (msg->espaco_i); i++)
    {
        int funcao_i = msg->funcao_i;

        msg->funcao[funcao_i] = i;
        (msg->funcao_i)++;
    }
}


// adicionar os caracteres '*', e adicionar em `msg`
void get_exclamacao(Mensagem *msg) {
    for (size_t i = 0; i < (msg->size); i++) {
        char chr = msg->txt[i];

        if (chr == '!') {
            int exclamacoes_i = msg->exclamacoes_i;

            msg->exclamacao_pos[exclamacoes_i] = i;
            (msg->exclamacoes_i)++;
        }
    }

    if ((msg->exclamacoes_i) > 0) {
        msg->is_especial = 1;
    }
}


void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}


void bubble_sort(int *arr, int n) {
    for (size_t i = 0; i < n - 1; i++)
    {
        for (size_t j = 0; j < n - i - 1; j++)
        {
            if (arr[j] > arr[j + 1]) {
                swap( &arr[j], &arr[j+1] );
            }
        }
    }
}


long long montar_numero(Mensagem *msg) {
    // quantidade de casas decimais
    int qtd_casas = msg->numeros_i;
    long long num = 0;

    // indica a casa decimal do numero
    int j = 1;

    for (size_t i = qtd_casas; i >= 1; i--)
    {
        num += msg->numeros_arr[i] * pow(10, j);
        j++;
    }

    return num;
}


Mensagem* alloc_msg() {
    size_t s_msg = sizeof(Mensagem);
    Mensagem* msg = NULL;

    msg = (Mensagem*) malloc(s_msg);

    if (msg == NULL) return NULL;

    return msg;
}


Cidadela* alloc_cidadela() {
    size_t s_cidadela = sizeof(Cidadela);
    Cidadela *cidadela = NULL;

    cidadela = (Cidadela*) malloc(s_cidadela);

    if (cidadela == NULL) return NULL;

    return cidadela;
}


void config_cidadela(Cidadela *cidadela, Mensagem *msg) {
    cidadela->grau_perigo = msg->exclamacoes_i;
    cidadela->populacao = montar_numero(msg);

    size_t last_pos1 = 0;

    for (size_t i = 0; i < (msg->maiusculas_i); i++)
    {
        int pos = msg->maiusculas_pos[i];
        char letra = msg->txt[pos];

        cidadela->nome[i] = letra;

        last_pos1 = i;
    }

    cidadela->nome[last_pos1 + 1] = '\0';

    printf("###%d\n", msg->maiusculas_i);
    printf("###%s\n", cidadela->nome);


    size_t last_pos2 = 0;

    for (size_t i = 0; i < (msg->espaco_i); i++)
    {
        int pos_espaco = msg->espaco_duplo_pos[i];
        char letra = msg->txt[pos_espaco + 2];

        cidadela->funcao[i] = letra;

        last_pos2 = i;
    }

    cidadela->funcao[last_pos2 + 1] = '\0';
    printf("##%s\n", cidadela->funcao);
}


// recebe uma mensagem alocada e faz a configuracao inicial,
// inicializando e preenchendo seus dados
Mensagem* config_msg(Mensagem *msg, char input[]) {
    inicializar_mensagem(msg);
    strcpy( msg->txt, input );

    msg->size = strlen( msg->txt );

    get_exclamacao(msg);
    get_maiusculas(msg);
    get_estrela(msg);
    get_espacos(msg);
    get_funcao(msg);
    get_numeros(msg);


    Cidadela* cidadela = alloc_cidadela();

    config_cidadela(cidadela, msg);

    msg->cidadela = cidadela;
}


// receber entrada do teclado
void recebe_txt(char buffer[], char input[]) {
    while( fgets(input, sizeof(input), stdin) != NULL ) {
        strcat(buffer, input);
    }
}


void print_diagnostico(int populacao_grande, int perigoso) {
        if (populacao_grande && perigoso) {
            printf("Talvez seja melhor desistir...\n");
        } else if (populacao_grande) {
            printf("Um lugar denso, vai ser difícil achar ela.\n");
        } else if (perigoso) {
            printf("Vai ser complicado entrar lá.\n");
        }
}


int main(void) {
    char input[1000];
    char buffer[1000];

    fill_str(input, 1000);
    fill_str(buffer, 1000);
    recebe_txt(buffer, input);


    Mensagem* msg = alloc_msg();

    if (msg == NULL) return EXIT_FAILURE;

    inicializar_mensagem(msg);
    config_msg(msg, buffer);


    if (msg->is_especial == 0) {
        printf("Gingrey ainda não foi achada, vamos esperar mais um pouco.\n");
    } else {
        long long populacao = msg->cidadela->populacao;
        int grau_perigo = msg->cidadela->grau_perigo;
        char nome[50];
        
        strcpy( nome, msg->cidadela->nome );

        printf("Gingrey foi encontrada em %s, uma cidadela com %lld mil habitantes cuja função é %d e periculosidade P.\n", nome, populacao, grau_perigo);


        int populacao_grande = (populacao > 1000000);
        int perigoso = (grau_perigo > 3);

        print_diagnostico(populacao_grande, perigoso);
    }

    return EXIT_SUCCESS;
}