#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef enum {
    TITULO,
    GENERO,
    ESTUDIO,
    CONSOLE,
    NOTA,
    ANO_LANCAMENTO,
} JogoParam;


typedef struct {
    char titulo[100];
    char genero[100];
    char estudio[100];
    char console[100];

    int nota;
    int ano_lancamento;
} Jogo;


typedef struct {
    size_t n;
    Jogo **lista;
} Colecao;


// adicionar jogo à colecao. 0 erro, 1 sucesso.
int add_jogo(Colecao *colecao, Jogo *jogo) {
    (colecao->n)++;

    int num_jogos = colecao->n;
    size_t s_lista_jogos = num_jogos * sizeof(Jogo*);

    Jogo **tmp = (Jogo**) realloc(colecao->lista, s_lista_jogos);

    if (tmp == NULL) return 0;

    colecao->lista = tmp;
    colecao->lista[num_jogos - 1] = jogo;

    return 1;
}


// alocar dinamicamente uma string, a partir de uma
// string de tamanho fixo. NULL em caso de erro
char* alloc_str(char input[]) {
    size_t s_input = strlen(input) * sizeof(char);

    char *str = (char*) malloc(s_input);

    if (str == NULL) return NULL;
    
    return str;
}


// desalocar os membros de jogo, e o proprio jogo
void dealloc_jogo(Jogo *jogo) {
    free( jogo->titulo );
    free( jogo->genero );
    free( jogo->estudio );
    free( jogo->console );

    free(jogo);
}


// desalocar os jogos de uma colecao, e a propria colecao
void dealloc_colecao(Colecao *colecao) {
    for (size_t i = 0; i < (colecao->n); i++)
    {
        dealloc_jogo( colecao->lista[i] );
    }
    free(colecao);
}


// printar mensagem dependendo da nota
void comentario_nota(int nota) {
    if ( nota > 7 ) {
        printf("AWESOME! Mais um GOTY pra minha coleção!\n");
    }

    if ( nota < 4 ) {
        printf("Era melhor jogar mais um jogo de Mahjong.\n");
    }
}


// receber jogo, com dados vindos do teclado
Jogo* receber_jogo() {
    char titulo[100];
    char genero[100];
    char estudio[100];
    char console[100];

    int nota = 0;
    int ano_lancamento = 0;


    scanf("%s", titulo);
    scanf("%s", genero);
    scanf("%s", estudio);
    scanf("%s", console);

    scanf("%d", &nota);
    scanf("%d", &ano_lancamento);


    size_t s_jogo = sizeof(Jogo);
    Jogo *jogo = (Jogo*) malloc(s_jogo);

    if (jogo == NULL) {
        dealloc_jogo(jogo);

        return NULL;
    }

    // construir jogo a partir dos dados
    strcpy( jogo->titulo, titulo );
    strcpy( jogo->genero, genero );
    strcpy( jogo->estudio, estudio );
    strcpy( jogo->console, console );

    jogo->nota = nota;
    jogo->ano_lancamento = ano_lancamento;


    comentario_nota(nota);

    return jogo;
}


// receber colecao, com dados vindos do teclado
Colecao* receber_colecao(int num_jogos) {
    size_t s_colecao = sizeof(Colecao);
    Colecao *colecao = (Colecao*) malloc(s_colecao);

    if (colecao == NULL) return NULL;

    // receber jogos
    for (int i = 0; i < num_jogos; i++)
    {
        Jogo* jogo = receber_jogo();

        // desalocar os jogos ja alocados
        if (jogo == NULL) {
            for (size_t j = i - 1; j >= 0; j--) {
                dealloc_jogo( colecao->lista[i] );
            }
            free(colecao);

            return NULL;
        }

        int status_add = add_jogo(colecao, jogo);

        if (status_add == 0) return NULL;
    }
    return colecao;
}


int select_jogo_param_int(Jogo *jogo, JogoParam param_id) {
    int param_selected = 0;

    switch(param_id) {
        case NOTA:
            param_selected = jogo->nota;
            break;
        case ANO_LANCAMENTO:
            param_selected = jogo->ano_lancamento;
            break;
    }

    return param_selected;
}


// filtrar uma colecao, com base num parametro do tipo int
Colecao* select_jogos_int(Colecao *colecao_db, int param_dado, JogoParam param_id) {
    size_t s_colecao_filtered = sizeof(Colecao);
    Colecao *colecao_filtered = (Colecao*) malloc(s_colecao_filtered);

    if (colecao_filtered == NULL) return NULL;


    colecao_filtered->n = 0;

    for (size_t i = 0; i < (colecao_db->n); i++)
    {
        Jogo *jogo_tmp = colecao_db->lista[i];

        int selected_param = select_jogo_param_int(jogo_tmp, param_id);

        if (selected_param == param_dado) {
            printf("%s\n", jogo_tmp->titulo );

            int status_added = add_jogo(colecao_filtered, jogo_tmp);
            if (status_added == 0) return NULL;
        }
    }

    return colecao_filtered;
}


// selecionar um parametro de um jogo, dado seu id
char* select_jogo_param_char(Jogo *jogo, JogoParam param_id) {
    char *param_selected;

    switch (param_id) {
        case TITULO:
            param_selected = jogo->titulo;
            break;
        case GENERO:
            param_selected = jogo->genero;
            break;
        case ESTUDIO:
            param_selected = jogo->estudio;
            break;
        case CONSOLE:
            param_selected = jogo->console;
            break;
    }

    return param_selected;
}


// filtrar uma colecao, com base num parametro do tipo string
Colecao* select_jogos_str(Colecao *colecao_db, char param_dado[], JogoParam param_id) {
    size_t s_colecao_filtered = sizeof(Colecao);
    Colecao *colecao_filtered = (Colecao*) malloc(s_colecao_filtered);

    if (colecao_filtered == NULL) return NULL;


    colecao_filtered->n = 0;

    for (size_t i = 0; i < (colecao_db->n); i++)
    {
        Jogo *jogo_tmp = colecao_db->lista[i];
        char *player_param = select_jogo_param_char(jogo_tmp, param_id);
        int is_msm_param = 0;
        
        if (param_id == TITULO) {
            is_msm_param = param_dado[0] == player_param[0];
        } else {
            is_msm_param = strcmp( param_dado, player_param ) == 0;
        }

        if (is_msm_param) {
            printf("%s\n", jogo_tmp->titulo);
            add_jogo(colecao_filtered, jogo_tmp);
        }
    }

    return colecao_filtered;
}


// imprime os jogos de um console
void print_console(Colecao *colecao_db, char console_dado[]) {
    Colecao *colecao = select_jogos_str(colecao_db, console_dado, CONSOLE);

    int qtd_selecionados = colecao->n;

    if (qtd_selecionados > 0) {
        printf("Tenho %d jogos || %s.\n", qtd_selecionados, console_dado);
    } else {
        printf("Nenhum jogo tem esse parâmetro Sr Sr Wilson.\n");
    }
}


// imprime os jogos lancados num ano especifico.
int print_ano(Colecao *colecao_db, int ano_dado) {
    Colecao *colecao = select_jogos_int(colecao_db, ano_dado, ANO_LANCAMENTO);

    int qtd_selecionados = colecao->n;

    if (qtd_selecionados > 0) {
        printf("Tenho %d jogos || %d.\n", qtd_selecionados, ano_dado);
    } else {
        printf("Nenhum jogo tem esse parâmetro Sr Sr Wilson.\n");
    }
}


// imprime os jogos que comecam com uma letra especifica.
void print_letra(Colecao *colecao_db, char letra_dada) {
    char letra[2];

    letra[0] = letra_dada;
    letra[1] = '\0';

    Colecao *colecao = select_jogos_str(colecao_db, letra, TITULO);

    int qtd_selecionados = colecao->n;

    if (qtd_selecionados > 0) {
        printf("Tenho %d jogos || %c.\n", qtd_selecionados, letra_dada);
    } else {
        printf("Nenhum jogo tem esse parâmetro Sr Sr Wilson.\n");
    }
}


// imprime os jogos de um estudio
void print_studio(Colecao *colecao_db, char estudio_dado[]) {
    Colecao *colecao = select_jogos_str(colecao_db, estudio_dado, ESTUDIO);

    int qtd_selecionados = colecao->n;

    if (qtd_selecionados > 0) {
        printf("Tenho %d jogos || %s.\n", qtd_selecionados, estudio_dado);
    } else {
        printf("Nenhum jogo tem esse parâmetro Sr Sr Wilson.\n");
    }
}


void print_colecao(Colecao *colecao) {
    for (size_t i = 0; i < (colecao->n); i++) {
        Jogo *jogo_tmp = colecao->lista[i];

        printf("%s %d\n", jogo_tmp->titulo, jogo_tmp->nota );
    }
}


// receber funcoes a serem executadas
void receber_comandos(Colecao *colecao) {
    char comando[50];
    char param[50];

    while ( scanf("%s", comando) != EOF ) {
        if ( strcmp(comando, "printColecao") == 0 ) {
            print_colecao(colecao);
        }

        scanf("%s", param);

        if ( strcmp(comando, "printAno") == 0 ) {
            int ano = atoi(param);

            print_ano(colecao, ano);
        } else if ( strcmp(comando, "printConsole") == 0 ) {
            print_console(colecao, param);
        } else if ( strcmp(comando, "printLetra") == 0 ) {
            print_letra(colecao, param[0]);
        } else if ( strcmp(comando, "printStudio") == 0 ) {
            print_studio(colecao, param);
        }
    }
}


int main(void) {
    int num_jogos = 0;

    scanf("%d", &num_jogos);


    Colecao *colecao = receber_colecao(num_jogos);

    if (colecao == NULL) return EXIT_FAILURE;

    receber_comandos(colecao);


    printf("Enjoei de jogar, agora vou ver TV.\n");

    free(colecao);

    return EXIT_SUCCESS;
}