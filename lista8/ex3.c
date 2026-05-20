#include <stdio.h>
#include <stdlib.h>
#include <string.h>


const char nome_template[10] = "irisX.csv";


typedef struct Flower Flower;
typedef struct FlowerSet FlowerSet;

struct Flower {
    double sepal_length;
    double sepal_width;

    double petal_length;
    double petal_width;

    char species[100];
};


struct FlowerSet {
    size_t num_flowers;
    Flower** flower_set;
};


// aloca e inicializa flor vazia
Flower* create_flower() {
    size_t s_flower = sizeof(Flower);
    Flower *flower = (Flower*) malloc(s_flower);

    if (flower == NULL) return NULL;

    memset(flower, 0, sizeof(Flower));

    return flower;
}


// aloca e inicializa flowerset vazio
FlowerSet** create_flowerset() {
    size_t s_flowerset = sizeof(FlowerSet);
    FlowerSet **flowerset = (FlowerSet**) malloc(s_flowerset);

    if (flowerset == NULL) return NULL;

    memset(flowerset, 0, sizeof(FlowerSet));

    return flowerset;
}


// retorna o nome de um arquivo csv
char* get_filename(size_t index) {
    size_t s_nome_arquivo = sizeof(char) * 10;
    char *nome_arquivo = NULL;

    nome_arquivo = (char*) malloc(s_nome_arquivo);

    if (nome_arquivo == NULL) return NULL;


    strcpy(nome_arquivo, nome_template);

    // colocando o nome correto do arquivo
    nome_arquivo[4] = index + '0';

    return nome_arquivo;
}



int read_line_csv(FILE *iris_csv, Flower *flower) {
    // leitura de uma linha
    int status_reading = fscanf(iris_csv,
        "%lf,%lf,%lf,%lf,%s",
        flower->sepal_length,
        flower->sepal_width,
        flower->petal_length,
        flower->petal_width,
        flower->species
    );

    return status_reading;
}


void print_flower(Flower *flower) {
    printf("Sepal Length: %lf\n", flower->sepal_length);
    printf("Sepal Width: %lf\n", flower->sepal_width);
    printf("Petal Length: %lf\n", flower->petal_length);
    printf("Petal Width: %lf\n", flower->petal_width);
    printf("Species: %s\n", flower->species);
}


// retorna 0 em caso de erro.
int read_csvs(int num_arquivos) {
    for (size_t i = 0; i < num_arquivos; i++)
    {
        char* nome_arquivo = get_filename(i);
        FILE *iris_csv = NULL;

        if ( (iris_csv = fopen(nome_arquivo, "r+")) == NULL) {
            printf("Nao foi possivel abrir o arquivo %s\n", nome_arquivo);
        } else {
            Flower* flower = create_flower();

            if (flower == NULL) return 0;


            int status_reading = read_line_csv(iris_csv, flower);

            if(status_reading == NULL) {
                printf("Nao foi possivel ler a linha do arquivo %s\n", nome_arquivo);
            }

            puts();

            if (feof(iris_csv)) {
                printf("index %d\n", i);
            }
        }
    }
    return 1;
}


int main(void) {
    size_t num_arquivos = 0;

    scanf("%zu", &num_arquivos);


    read_csvs(num_arquivos);


    return EXIT_SUCCESS;
}