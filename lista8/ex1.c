#include <stdio.h>
#include <stdlib.h>


unsigned char MASK_VALUE = 0b11110000;
unsigned char MASK_MODE  = 0b00001110;
unsigned char MASK_FALHA = 0b00000001;


typedef struct SinalElems SinalElems;
typedef struct Sinal Sinal;

typedef union SinalData SinalData;


// elementos isolados do sinal
struct SinalElems {
    unsigned char value : 4;
    unsigned char op_mode : 3;
    unsigned char is_falha : 1;
};

// sinal por inteiro, em forma bruta ou decomposta
union SinalData {
    unsigned char raw_byte;
    SinalElems sinal_elems;
};


struct Sinal {
    // if 1, then `raw_byte` is being used; if 0, then `sinal_elems`
    int is_raw; 

    union SinalData sinal_data;
};


// decodifica o sinal em seus elementos.
// retorna 0 em caso de erro.
int decode_sinal(Sinal *sinal) {
    if (sinal->is_raw == 0) return 0;


    SinalElems sinal_elems = { 0, 0, 0 };

    unsigned char raw_byte = sinal->sinal_data.raw_byte;

    // construindo o sinal decodificado
    // printf("%d", sizeof(unsigned char));
    sinal_elems.value = (raw_byte & MASK_VALUE) >> 4;
    sinal_elems.op_mode = (raw_byte & MASK_MODE) >> 1;
    sinal_elems.is_falha = (raw_byte & MASK_FALHA);

    // trocando o sinal codificado pelo decodificado
    sinal->sinal_data.sinal_elems = sinal_elems;
    sinal->is_raw = 0;


    return 1;
}


// decodifica o sinal e printa na tela.
// retorna 0 em caso de erro.
int print_sinal(Sinal sinal) {
    unsigned char raw_byte = sinal.sinal_data.raw_byte;

    int status_decoding = decode_sinal(&sinal);
    if (status_decoding == 0) return EXIT_FAILURE;


    SinalElems sinal_elems = sinal.sinal_data.sinal_elems;

    unsigned char erro = sinal_elems.is_falha;
    unsigned char modo = sinal_elems.op_mode;
    unsigned char leitura = sinal_elems.value;


    printf("Byte bruto: %hhu | Erro: %hhu | Modo: %hhu | Leitura: %hhu",
        raw_byte, erro, modo, leitura);


    return 1;
}


Sinal build_raw_signal(unsigned char raw_signal) {
    Sinal signal;

    signal.is_raw = 1;
    signal.sinal_data.raw_byte = raw_signal;

    return signal;
}


int main(void) {
    unsigned char raw_byte = 0;

    scanf("%hhu", &raw_byte);


    Sinal sinal = build_raw_signal(raw_byte);

    print_sinal(sinal);


    return EXIT_SUCCESS;
}