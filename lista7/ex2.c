#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct Mecha Mecha;
typedef struct Esquadrao Esquadrao;


typedef struct {
    char nome[30];
    int atrib1;     // Atk: Dano Base   | Def: Blindagem Fixa | Utl: Recup. Base
    int atrib2;     // Atk: Custo Ener. | Def: Bônus de Slot   | Utl: Multiplicador
    
    // Função Modular: deve ser atribuída conforme o tipo do sistema.
    // m: ponteiro para o mecha dono do sistema.
    // slot: o índice da posição de entrada deste sistema no array sistemas[]
    // input: o dano base enviado pelo Wintermute para o combate.
    // output: onde deve ser gravado o resultado final da operação.
    void (*subrotina)(Mecha *m, int slot, int input, int *output);
} SubSistema;


struct Mecha {
    char id;                // Identificador único (0 até N-1)
    int energia_atual;
    int num_sistemas;
    int valor_wintermute;       // Contexto de dano enviado pelo Comando

    char modelo[50];

    SubSistema sistemas[]; // O Flexible Array Member (FAM)
};


struct Esquadrao {
    int n;
    int max_mechas;

    Mecha **elems;
};


SubSistema* alloc_subsistema() {
    size_t s_subsis = sizeof(SubSistema);
    SubSistema *subsis = NULL;

    subsis = (SubSistema*) malloc(s_subsis);

    if (subsis == NULL) return NULL;

    return subsis;
}


void op_defesa(Mecha *mecha, int slot, int input, int *output) {
    SubSistema *sistema = &(mecha->sistemas[slot]);

    int atrib1 = sistema->atrib1;
    int atrib2 = sistema->atrib2;

    char nome[30];

    strcpy( nome, sistema->nome);


    int dano_final = input - atrib1 - (slot * atrib2);

    if (dano_final < 0) {
        dano_final = 0;
    }


    (mecha->energia_atual) -= dano_final;

    printf("-> [DEFESA] %s | Dano final sofrido: %d\n", nome, dano_final);
}


void op_utilidade(Mecha *m, int slot, int input, int *output) {
    int atrib1 = m->sistemas[slot].atrib1;
    int atrib2 = m->sistemas[slot].atrib2;
    int energia = m->energia_atual;
    int recuperado = atrib1 + (slot * atrib2);

    char nome[30];

    strcpy(nome, m->sistemas[slot].nome);


    (m->energia_atual) += recuperado;

    printf("-> [UTILIDADE] %s | Energia atual: %d\n", nome, energia);
}


void op_ataque(Mecha *m, int slot, int input, int *output) {
    int atrib1 = m->sistemas[slot].atrib1;
    int atrib2 = m->sistemas[slot].atrib2;
    int energia = m->energia_atual;

    char nome[30];

    strcpy(nome, m->sistemas[slot].nome);


    if (energia < atrib2) {
        printf("-> [ATAQUE] %s | Energia insuficiente!\n", nome);
    } else {
        int dano = atrib1 + energia + slot - input;

        (m->energia_atual) -= dano;

        if ( m->energia_atual > 0 ) {
            (m->energia_atual) -= atrib2;
        } else {
            m->energia_atual = 0;
        }

        printf("-> [ATAQUE] %s | Dano causado: %d | Energia restante: %d\n", nome, dano, energia);
    }
}


// designar a funcao correta segundo a entrada
void escolher_funcao(char tipo, SubSistema *subsis) {
    switch(tipo) {
        case 'D':
            subsis->subrotina = op_defesa;
            break;
        case 'U':
            subsis->subrotina = op_utilidade;
            break;
        case 'A':
            subsis->subrotina = op_ataque;
            break;
    }
}


void receber_sistema(Mecha* mecha, SubSistema *subsis) {
    char tipo;
    char nome[30];

    int atrib1 = 0;
    int atrib2 = 0;
    int valor_wintermute = 0;

    scanf("%c", &tipo);
    scanf("%s", nome);
    scanf("%d", &atrib1);
    scanf("%d", &atrib2);
    scanf("%d", &valor_wintermute);

    mecha->valor_wintermute = valor_wintermute;

    subsis->atrib1 = atrib1;
    subsis->atrib2 = atrib2;

    strcpy( subsis->nome, nome );

    escolher_funcao(tipo, subsis);
}


Mecha* alloc_mecha(int num_sistemas) {
    size_t s_mecha = sizeof(Mecha) + sizeof(SubSistema) * num_sistemas;
    Mecha* mecha = NULL;

    mecha = (Mecha*) malloc(s_mecha);

    if (mecha == NULL) return NULL;

    return mecha;
}


int config_sistemas(int num_sistemas, Mecha* mecha) {
    // receber subsistemas
    for (int i = 0; i < num_sistemas; i++)
    {
        SubSistema *subsis = alloc_subsistema();

        if (subsis == NULL) return 0;


        receber_sistema(mecha, subsis);

        mecha->sistemas[i] = *subsis;
    }
    return 1;
}


// recebe mecha, pelo teclado. retorna NULL em caso de erro
Mecha* criar_mecha() {
    char id = 0;
    char modelo[50];

    int num_sistemas = 0;
    int energia = 0;
    int valor_wintermute = 0;

    scanf("%c", &id);
    scanf("%s", modelo);
    scanf("%d", &energia);
    scanf("%d", &num_sistemas);


    Mecha* mecha = alloc_mecha(num_sistemas);

    if (mecha == NULL) return NULL;


    mecha->id = id;
    mecha->num_sistemas = num_sistemas;
    mecha->energia_atual = energia;
    mecha->valor_wintermute = valor_wintermute;

    strcpy( mecha->modelo, modelo );


    int status_sistemas = config_sistemas(num_sistemas, mecha);

    if (status_sistemas == 0) return NULL;

    return mecha;
}


Esquadrao* alloc_esquadrao(int num_mechas) {
    size_t s_mechas = sizeof(Mecha*) * num_mechas;

    Mecha** mechas = NULL;

    mechas = (Mecha**) malloc(s_mechas);

    if (mechas == NULL) return NULL;


    size_t s_esquadrao = sizeof(Esquadrao);

    Esquadrao *esquadrao = (Esquadrao*) malloc(s_esquadrao);

    if (esquadrao == NULL) return NULL;


    esquadrao->n = 0;
    esquadrao->max_mechas = num_mechas;
    esquadrao->elems = mechas;

    return esquadrao;
}


// cria um conjunto de mechas, ou retorna NULL em caso de erro
Esquadrao* criar_esquadrao(int num_mechas) {
    Esquadrao* esquadrao = alloc_esquadrao(num_mechas);

    if (esquadrao == NULL) return NULL;

    // criando e adicionando mechas
    for (int i = 0; i < num_mechas; i++)
    {
        Mecha* mecha = criar_mecha();

        if (mecha == NULL) return NULL;

        esquadrao->elems[i] = mecha;

        (esquadrao->n)++;
    }

    return esquadrao;
}


void dealloc_sistemas(Mecha *mecha) {
    int num_sistemas = mecha->num_sistemas;

    for (int j = 0; j < num_sistemas; j++)
    {
        SubSistema *subsis = &(mecha->sistemas[j]);

        free(subsis);
    }
}


// desalocar o esquadrao e todos os seus componentes
void dealloc_esquadrao(Esquadrao *esquadrao) {
    int max_mechas = esquadrao->max_mechas;

    for (int i = 0; i < max_mechas; i++)
    {
        Mecha *mecha = esquadrao->elems[i];

        dealloc_sistemas(mecha);

        free(mecha);
    }
    free(esquadrao);
}


void swap(int *a, int *b) {
    int tmp = *a;
    *a = *b;
    *b = tmp;
}


void bubble_sort(int *arr, int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                swap( &arr[j], &arr[j+1] );
            }
        }
    }
}


int* get_mechas_id(Esquadrao *esquadrao) {
    int s_ids = sizeof(int) * (esquadrao->n);
    int* ids = NULL;

    ids = (int*) malloc(s_ids);

    if (ids == NULL) return NULL;


    int num_mechas = esquadrao->n;
    int num_ids = 0;

    // coletar os ids
    for (int i = 0; i < num_mechas; i++)
    {
        ids[i] = esquadrao->elems[i]->id;
        num_ids++;
    }

    return ids;
}


// printar os dados da mecha
void print_mecha(Mecha *mecha) {
    char id = mecha->id;
    int energia = mecha->energia_atual;
    char modelo[50];

    strcpy( modelo, mecha->modelo );

    printf("ID: %d | MECHA: %s | ENERGIA: %d\n", id, modelo, energia);
}


// executar e printar simulacao
void rodar_simulacao(Mecha *mecha) {
    int num_sistemas = mecha->num_sistemas;

    for (int j = 0; j < num_sistemas; j++)
    {
        int wintermute = mecha->valor_wintermute;

        SubSistema *subsys = &(mecha->sistemas[j]);

        subsys->subrotina(mecha, j, wintermute, NULL);
    }
}


int print_relatorio(Esquadrao *esquadrao) {
    int num_mechas = esquadrao->n;
    int *ids_mechas = get_mechas_id(esquadrao);

    if (ids_mechas == NULL) return 0;

    bubble_sort(ids_mechas, num_mechas);

    
    printf("[RELATORIO DE MISSÃO: OPERAÇÃO LANÇA DE NETUNO]\n");

    for (int i = 0; i < num_mechas; i++)
    {
        Mecha *mecha = esquadrao->elems[i];

        print_mecha(mecha);
        rodar_simulacao(mecha);

        printf("ENERGIA FINAL: %d\n", mecha->energia_atual);
        printf("-----------------------------------------\n");
        printf("Esquadrao pronto para o combate.\n");
    }

    return 1;
}


int main(void) {
    int num_mechas = 0;

    scanf("%d", &num_mechas);


    Esquadrao *esquadrao = criar_esquadrao(num_mechas);

    if (esquadrao == NULL) return EXIT_FAILURE;


    int status_relatorio = print_relatorio(esquadrao);

    if (status_relatorio == 0) return EXIT_FAILURE;


    // dealloc_esquadrao(esquadrao);

    return EXIT_SUCCESS;
}