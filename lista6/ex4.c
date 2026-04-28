#include <stdio.h>
#include <stdlib.h>


typedef struct {
    int size_x;
    int size_y;
    int n;

    int **grade;
} SensorRede;


typedef struct {
    int n;
    int *comandos;
} Pipeline;


typedef struct {
    int x;
    int y;
    int val;
} SensorVal;


// receber entradas do teclado
void receber_matriz(SensorRede *sensores) {
    for (size_t i = 0; i < (sensores->size_x); i++)
    {
        for (size_t j = 0; j < (sensores->size_y); j++)
        {
            int n_tmp = 0;

            scanf("%d", &n_tmp);

            sensores->grade[i][j] = n_tmp;
        }
    }
}


int aloc_rede(SensorRede *sensores) {
    size_t s_linhas = sizeof(int*) * (sensores->size_x);

    // alocar linhas
    sensores->grade = malloc(s_linhas);
    if (sensores->grade == NULL) return 0;

    // alocar colunas
    for (size_t i = 0; i < (sensores->size_x); i++)
    {
        size_t s_coluna = sizeof(int) * (sensores->size_y);

        sensores->grade[i] = malloc(s_coluna);

        if (sensores->grade[i] == NULL) return 0;
    }
    return 1;
}


SensorRede* criar_rede(int num_linhas, int num_cols) {
    int num_elems = num_linhas * num_cols;

    size_t s_sensores = sizeof(SensorRede);
    SensorRede *sensores = malloc(s_sensores);

    if (sensores == NULL) return NULL;


    sensores->n = num_elems;
    sensores->size_x = num_linhas;
    sensores->size_y = num_cols;

    int status_aloc = aloc_rede(sensores);
    if (status_aloc == 0) return NULL;

    return sensores;
}


void dealoc_colunas_rede(SensorRede *sensores) {
    for (size_t i = 0; i < (sensores->size_x); i++)
    {
        free(sensores->grade[i]);
    }
}


void print_rede(SensorRede *sensores) {
    for (size_t i = 0; i < (sensores->size_x); i++)
    {
        for (size_t j = 0; j < (sensores->size_y); j++)
        {
            printf("%d ", sensores->grade[i][j] );
        }
        printf("\n");
    }
}


int calibracao_op(int sensor_val) {
    return sensor_val + 5;
}


int saturacao_op(int sensor_val) {
    int resultado = (sensor_val > 80) ? 80 : sensor_val;

    return resultado;
}


int amplificador_op(int sensor_val) {
    int resultado = sensor_val * 2;

    return resultado;
}


int aplic_comando(SensorRede *sensores, int op_id, int (*ops[])(int sensor_val)) {
    for (size_t i = 0; i < (sensores->size_x); i++)
    {
        for (size_t j = 0; j < (sensores->size_y); j++)
        {
            int sensor_val = sensores->grade[i][j];
            int resultado = ops[op_id](sensor_val);

            sensores->grade[i][j] = resultado;
        }
    }
}


// executa um conjunto de comandos de uma pipeline
int process_pipeline(Pipeline *pipe, int (*ops[])(int), SensorRede *sensores) {
    int resultado = 0;

    for (size_t i = 0; i < (pipe->n); i++)
    {
        switch ( pipe->comandos[i] )
        {
            case 1:
                aplic_comando(sensores, 0, ops);
                break;
            case 2:
                aplic_comando(sensores, 1, ops);
                break;
            case 3:
                aplic_comando(sensores, 2, ops);
                break;
        }
    }

    return resultado;
}


// quantidade de argumentos, incluindo o comando,
// a ser recebido
int get_num_args() {
    int num_comandos = 0;


    return num_comandos;
}


Pipeline* recebe_comandos_pipe(Pipeline *pipe, int comando, int num_comandos) {
    for (size_t i = 0; i < num_comandos; i++)
    {
        // alocar espaço para mais um comando
        (pipe->n)++;

        size_t s_comandos = sizeof(int) * (pipe->n);

        int *tmp = (int*) realloc( pipe->comandos , s_comandos );

        if (tmp == NULL) {
            free( pipe->comandos );
            return NULL;
        }

        pipe->comandos = tmp;


        // adicionar comando
        if (comando == 4) {
            int arg = 0;

            scanf("%d", &arg);

            pipe->comandos[ (pipe->n) - 1 ] = arg;
        } else {
            pipe->comandos[ (pipe->n) - 1 ] = comando;
        }
    }

    return pipe;
}


int (*ops[3])(int) = {
    calibracao_op,
    saturacao_op,
    amplificador_op,
};


// pegar o valor do sensor com maior valor
SensorVal* max_matrix(SensorRede *sensores) {
    int max = 0;
    int max_x = 0;
    int max_y = 0;

    for (size_t i = 0; i < (sensores->size_x); i++)
    {
        for (size_t j = 0; j < (sensores->size_y); j++) {
            int tmp = sensores->grade[i][j];

            if (tmp > max) {
                max = tmp;
                max_x = i;
                max_y = j;
            }
        }
    }

    size_t s_sensor_val = sizeof(SensorVal);

    SensorVal *sensor_val = (SensorVal*) malloc(s_sensor_val);

    if (sensor_val == NULL) return NULL;


    sensor_val->x = max_x;
    sensor_val->y = max_y;
    sensor_val->val = max;

    return sensor_val;
}


int main(void) {
    int num_linhas = 0;
    int num_cols = 0;

    scanf("%d", &num_linhas);
    scanf("%d", &num_cols);


    SensorRede* sensores = criar_rede(num_linhas, num_cols);
    if (sensores == NULL) return EXIT_FAILURE;

    receber_matriz(sensores);


    // receber comandos, colocar numa pipeline
    // e processa-los
    while (1) {
        int comando = 0;

        scanf("%d", &comando);

        if (comando == 0) break;


        int num_comandos = 1;

        if (comando == 4) {
            scanf("%d", &num_comandos);
        } else {
            num_comandos = 1;
        }


        size_t s_pipe = sizeof(Pipeline);
        Pipeline *pipe = (Pipeline*) malloc(s_pipe);

        if (pipe == NULL) return EXIT_FAILURE;

        pipe->n = 0;
        pipe->comandos = NULL;


        recebe_comandos_pipe(pipe, comando, num_comandos);
        process_pipeline(pipe, ops, sensores);


        free(pipe->comandos);
        free(pipe);
    }


    printf("Matriz processada:\n");
    print_rede(sensores);


    SensorVal *max_val = max_matrix(sensores);

    int pos_x = max_val->x;
    int pos_y = max_val->y;

    printf("\nSensor critico: %d\n", max_val->val );
    printf("Posicao: (%d,%d)", pos_x, pos_y);


    dealoc_colunas_rede(sensores);
    free(sensores);

    return EXIT_SUCCESS;
}