// INCOMPLETO
// INCOMPLETO
// INCOMPLETO
// INCOMPLETO

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


const char nome_template[10] = "irisX.csv";


typedef struct Flower Flower;
typedef struct FlowerSet FlowerSet;
typedef struct FlowerSetData FlowerSetData;
typedef enum FlowerProp FlowerProp;


enum FlowerProp { SEPAL_W, SEPAL_L, PETAL_L, PETAL_W };


struct Flower {
    double sepal_length;
    double sepal_width;

    double petal_length;
    double petal_width;

    char species[100];
};


struct FlowerSet {
    size_t num_flowers;
    Flower** set;
    FlowerSetData *flowerset_data;
};


// estatisticas relacionadas a uma flor
struct FlowerSetData {
    double media_sepal_l;
    double media_sepal_w;
    
    double media_petal_l;
    double media_petal_w;

    unsigned moda_species;
};


// aloca e inicializa flor vazia.
// a aloca acontece com `realloc()`.
Flower* realloc_flower() {
    Flower *flower = NULL;
    Flower *tmp = realloc(flower, sizeof(Flower));

    if (tmp == NULL) {
        return NULL;
    } else {
        flower = tmp;
    }


    memset(flower, 0, sizeof(Flower));

    return flower;
}


// aloca e inicializa flowerset vazio.
// retorna NULL em caso de erro.
FlowerSet* alloc_flowerset() {
    FlowerSet *flowerset = malloc( sizeof(FlowerSet) );

    if (flowerset == NULL) return NULL;

    memset(flowerset, 0, sizeof(FlowerSet));

    return flowerset;
}


void add_flower_to_set(Flower *flower, FlowerSet *flowerset) {
    size_t last_pos = flowerset->num_flowers;

    flowerset->set[last_pos] = flower;
    (flowerset->num_flowers)++;
}


// retorna o nome de um arquivo csv
char* get_filename(size_t index) {
    char *nome_arquivo = malloc( 10 * sizeof(char) );

    if (nome_arquivo == NULL) return NULL;

    // colocando o nome correto do arquivo
    strcpy(nome_arquivo, nome_template);
    nome_arquivo[4] = index + '0';

    return nome_arquivo;
}


void print_flower_caracteristicas(Flower *flower) {
    printf("### CARACTERISTICAS\n");
    printf("Sepal Length: %lf\n",   flower->sepal_length);
    printf("Sepal Width: %lf\n",    flower->sepal_width);
    printf("Petal Length: %lf\n",   flower->petal_length);
    printf("Petal Width: %lf\n",    flower->petal_width);
    printf("Species: %s\n",         flower->species);
}


void print_flower_estatisticas(FlowerSetData *flower_data) {
    printf("### ESTATISTICAS");
    printf("Sepal Length (media): %lf\n", flower_data->media_sepal_l);
    printf("Sepal Width  (media): %lf\n", flower_data->media_sepal_w);
    printf("Petal Length (media): %lf\n", flower_data->media_petal_l);
    printf("Petal Width  (media): %lf\n", flower_data->media_petal_w);
    printf("Species      (moda) : %d\n" , flower_data->moda_species);
}


void print_flower(Flower *flower, FlowerSetData *flowerset_data, char *nome_arquivo) {
    printf("Arquivo: %s\n", nome_arquivo);
    print_flower_caracteristicas(flower);
    print_flower_estatisticas(flowerset_data);
    printf("\n");
}


// retorna um vetor com todas as instancias
// de uma propriedade, num flowerset. em caso
// de erro retorna NULL.
double* get_prop_flowers(FlowerSet *flowerset, FlowerProp PROP) {
    size_t num_flowers = flowerset->num_flowers;

    double *props_arr = malloc( num_flowers * sizeof(double) );
    if (props_arr == NULL) return NULL;

    for (size_t i = 0; i < num_flowers; i++)
    {
        switch (PROP)
        {
            case SEPAL_W:
                props_arr[i] = flowerset->set[i]->sepal_width;
                break;
            case SEPAL_L:
                props_arr[i] = flowerset->set[i]->sepal_length;
                break;
            case PETAL_W:
                props_arr[i] = flowerset->set[i]->petal_width;
                break;
            case PETAL_L:
                props_arr[i] = flowerset->set[i]->petal_length;
                break;
        }
    }

    return props_arr;
}


double media_aritmetica(size_t n, double *arr) {
    double soma = 0;

    for (size_t i = 0; i < n; i++)
    {
        soma += arr[i];
    }

    double media = soma / n;

    return media;
}


void registrar_media(FlowerSetData *flower_data, double media, FlowerProp PROP) {
    switch (PROP) {
        case SEPAL_L:
            flower_data->media_sepal_l = media;
            break;
        case SEPAL_W:
            flower_data->media_sepal_w = media;
            break;
        case PETAL_L:
            flower_data->media_petal_l = media;
            break;
        case PETAL_W:
            flower_data->media_petal_w = media;
            break;
    }
}


// pega as estatisticas do `flowerset` inteiro, e coloca dentro de `flowerset`
FlowerSetData* get_flower_data(FlowerSet *flowerset) {
    FlowerSetData *flowerset_data = malloc( sizeof(FlowerSetData) );
    if (flowerset_data == NULL) return NULL;

    // calcular as medias de todas as propriedades das flores
    for (size_t PROP = SEPAL_W; PROP < PETAL_W; PROP++)
    {
        double* prop_arr = get_prop_flowers(flowerset, SEPAL_L);
        if (prop_arr == NULL) return NULL;

        double media = media_aritmetica(flowerset->num_flowers, prop_arr);
        registrar_media(flowerset_data, media, PROP);
    }

    // falta moda
    return flowerset_data;
}


// le os dados do arquivo `iris_csv`, e coloca os dados em `flowerset`
int read_flowers_csv(FILE *iris_csv, FlowerSet *flowerset) {
    int status_reading = 1;

    do {
        Flower *flower = realloc_flower();
        if (flower == NULL) return 0;

        int status_reading = fscanf(iris_csv,
            " %lf,%lf,%lf,%lf,%99s",
            &(flower->sepal_length),
            &(flower->sepal_width),
            &(flower->petal_length),
            &(flower->petal_width),
            flower->species
        );

        if (status_reading == EOF) return 0;

        add_flower_to_set(flower, flowerset);
    } while(status_reading != EOF);

    FlowerSetData* flowerset_data = get_flower_data(flowerset);
    flowerset->flowerset_data = flowerset_data;

    return 1;
}


// retorna 0 em caso de erro.
int read_csvs(int num_arquivos) {
    for (size_t i = 0; i < num_arquivos; i++)
    {
        char* nome_arquivo = get_filename(i);
        FILE *iris_csv = NULL;

        if ( (iris_csv = fopen(nome_arquivo, "r")) == NULL) {
            printf("Nao foi possivel abrir o arquivo %s\n", nome_arquivo);
        } else {
            FlowerSet *flowerset = alloc_flowerset();
            if (flowerset == NULL) return 0;

            int status_reading = read_flowers_csv(iris_csv, flowerset);

            if (status_reading == 0) {
                printf("Nao foi possivel ler a linha do arquivo %s\n", nome_arquivo);
            }


            if (feof(iris_csv)) {
                int closing_status = fclose(iris_csv);
                if (closing_status == EOF) return 0;
            }
        }
    }
    return 1;
}


int main(void) {
    size_t num_arquivos = 0;
    scanf("%zu", &num_arquivos);

    int read_status = read_csvs(num_arquivos);
    if (read_status == 0) return EXIT_FAILURE;

    return EXIT_SUCCESS;
}