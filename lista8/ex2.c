#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <inttypes.h>


typedef struct Packet Packet;
typedef struct PacketElems PacketElems;
typedef struct PacketStream PacketStream;

typedef union PacketData PacketData;

typedef enum Mask Mask;


enum Mask {
    MASK_ID          = 0b00000000000000000000001111111111,
    MASK_STATUS      = 0b00000000000000000001110000000000,
    MASK_BATTERY     = 0b00000000000000000010000000000000,
    MASK_TEMPERATURA = 0b00000011111111111100000000000000,
    MASK_PARIDADE    = 0b11111100000000000000000000000000,
};


// Pacote estruturado
struct PacketElems {
    uint32_t id_sensor       : 10;
    uint32_t status          : 3;
    uint32_t is_low_energy   : 1;
    int32_t temperatura      : 12;
    uint32_t paridade        : 6;
};


// Union que armazena: pacote bruto ou pacote estruturado
// `raw_packet`: dados do pacote codificado
// `packet_elems`: estrutura com os dados decodificados
union PacketData {
    uint32_t raw_packet; 
    PacketElems *packet_elems;
};


// `is_raw`: se os dados do pacote estao codificados
// `packet_data`: union que guarda os dados codificados ou decodificados
struct Packet {
    int is_raw;
    PacketData *packet_data;
};


// `packets`: stream de pacotes
// `n`: numero de pacotes na rede
struct PacketStream {
    size_t n;
    Packet** packets;
};


// aplica uma mascara, com bitwise AND, de bits ao inteiro, e desloca para a direita
uint32_t filter_signal(uint32_t raw_packet, Mask MASK, unsigned shift) {
    uint32_t filtered_signal = (raw_packet & MASK) >> shift;

    return filtered_signal;
}


// adiciona os componentes de `packet_elems`, usando bitwise OR,
// a um inteiro unsigned
uint32_t build_raw_packet(PacketElems *packet_elems) {
    uint32_t raw_packet = 0;

    raw_packet |= ((packet_elems->id_sensor)         << 0);
    raw_packet |= ((packet_elems->status)            << 10);
    raw_packet |= ((packet_elems->is_low_energy)     << 13);
    raw_packet |= ((packet_elems->temperatura)       << 14);
    raw_packet |= ((packet_elems->paridade)          << 26);

    return raw_packet;
}


// pega a forma codificada do pacote, mas nao o modifica.
// seja ja eh bruto, retorna 0, e 1 em sucesso.
uint32_t get_raw_packet(Packet *packet) {
    if (packet->is_raw) return 0;

    PacketElems *packet_elems = packet->packet_data->packet_elems;
    uint32_t raw_packet = build_raw_packet(packet_elems);

    return raw_packet;
}


// transforma (union) o pacote em forma codificada.
// retorna 0 em caso de erro, e 1 em sucesso.
int encode_packet(Packet *packet) {
    if (packet->is_raw) return 0;

    PacketElems *packet_elems = packet->packet_data->packet_elems;
    uint32_t raw_packet = build_raw_packet(packet_elems);

    // atualizando o pacote
    packet->is_raw = 1;
    packet->packet_data->raw_packet = raw_packet;

    return 1;
}


// uint32_t shift_two_complement(uint32_t raw_packet, Mask MASK, unsigned int shift) {
//     uint32_t temperatura = (raw_packet & MASK) >> 16;
//     int is_signal = temperatura >> 32;

//     return temperatura;
// }


// separa os componentes de um pacote bruto em um `packet_elems`.
void filter_raw_packet(uint32_t raw_packet, PacketElems *packet_elems) {
    packet_elems->id_sensor      = filter_signal(raw_packet, MASK_ID, 0);
    packet_elems->status         = filter_signal(raw_packet, MASK_STATUS, 10);
    packet_elems->is_low_energy  = filter_signal(raw_packet, MASK_BATTERY, 13);
    packet_elems->temperatura    = filter_signal(raw_packet, MASK_TEMPERATURA, 14);
    packet_elems->paridade       = filter_signal(raw_packet, MASK_PARIDADE, 26);
}


// transforma o pacote em forma decodificada/estruturada.
// retorna 0 em caso de erro, 1 em sucesso.
int decode_packet(Packet *packet) {
    if (packet->is_raw == 0) return 0;

    uint32_t raw_packet = packet->packet_data->raw_packet;
    size_t s_packet_elems = sizeof(PacketElems);
    PacketElems *packet_elems = (PacketElems*) malloc(s_packet_elems);

    if (packet_elems == NULL) return 0;


    filter_raw_packet(raw_packet, packet_elems);

    packet->packet_data->packet_elems = packet_elems;
    packet->is_raw = 0;

    return 1;
}


// aloca, mas nao inicializa
PacketElems* alloc_packet_elems() {
    PacketElems* packet_elems = malloc(sizeof(PacketElems));

    if (packet_elems == NULL) return NULL;

    return packet_elems;
}


// inicializa um pacote bruto 0, ou um pacote estruturado nao inicializado.
// em caso de erro retorna NULL.
PacketData* initialize_packet_data(int is_raw, PacketData *packet_data) {
    if (is_raw) {
        packet_data->raw_packet = 0;
    } else {
        PacketElems* packet_elems = alloc_packet_elems();

        if (packet_elems == NULL) return NULL;

        packet_data->packet_elems = packet_elems;
    }

    return packet_data;
}


// aloca um `PacketData` codificado ou nao, nao inicializado.
// em caso de erro retorna NULL.
PacketData* alloc_packet_data(int is_raw) {
    PacketData* packet_data = malloc( sizeof(PacketData) );

    if (packet_data == NULL) return NULL;

    initialize_packet_data(is_raw, packet_data);

    return packet_data;
}


// inicializar pacote na configuracao padrao, sempre com memset 0,
// caso `is_raw` seja 1, entao `is_raw` no pacote sera 1.
// `is_raw` (argumento): inicializar como codificado (1) ou decodificado (0).
void initialize_packet(Packet *packet, int is_raw) {
    if (is_raw) {
        memset(packet, 0, sizeof(Packet));
        packet->is_raw = 1;
    } else {
        packet->is_raw = 0;
        memset(packet->packet_data->packet_elems, 0, sizeof(Packet));
    }
}


// alocar e inicializar um `Packet`.
// `is_raw`: inicializar como codificado (1) ou decodificado (0).
// em caso de erro, retorna NULL.
Packet* create_packet(int is_raw) {
    Packet* packet = malloc(sizeof(Packet));
    if (packet == NULL) return NULL;

    PacketData* packet_data = alloc_packet_data(is_raw);
    if (packet_data == NULL) return NULL;

    packet->is_raw = is_raw;
    packet->packet_data = packet_data;

    return packet;
}


// adiciona mais um pacote, inicializado, à rede
int realloc_packet_stream(PacketStream *packet_stream) {
    size_t n_old = packet_stream->n;
    size_t n_new = 0;

    // dobrando a quantidade de pacotes
    if (n_old == 0) {
        n_new = 1;
    } else {
        n_new = n_old * 2;
    }


    // realocar a nova quantidade de pacotes
    size_t s_packets_arr = n_new * sizeof(Packet*);
    Packet** tmp = realloc(packet_stream->packets, s_packets_arr);

    if (tmp == NULL) {
        return 0;
    } else {
        packet_stream->packets = tmp;
    }

    return 1;
}


// aloca e inicializar rede vazia
PacketStream* create_packet_stream() {
    size_t s_packet_stream = sizeof(PacketStream);
    PacketStream* packet_stream = malloc(s_packet_stream);

    if (packet_stream == NULL) return NULL;


    memset(packet_stream, 0, s_packet_stream);

    return packet_stream;
}


// adicionar pacote inicializado padrao
int add_packet_stream(PacketStream* packet_stream, Packet *packet) {
    int status_realloc = realloc_packet_stream(packet_stream);
    if (status_realloc == 0) return 0;

    size_t n = packet_stream->n;
    packet_stream->packets[n] = packet;
    (packet_stream->n)++;

    return 1;
}


// recebe os pacotes codificados pelo teclado, decodifica-os,
// e armazena-os na stream
int receive_packets(PacketStream* packet_stream) {
    uint32_t raw_packet = 1;

    while (1) {
        scanf("%" SCNx32, &raw_packet);

        // saida bem sucedida do laço
        if (raw_packet == 0) return 1;


        Packet *packet = create_packet(1);
        if (packet == NULL) return 0;

        packet->packet_data->raw_packet = raw_packet;

        int status_decoding = decode_packet(packet);
        if (status_decoding == 0) return 0;

        int status_added = add_packet_stream(packet_stream, packet);
        if (status_added == 0) return 0;
    }

    return 1;
}


// desalocar o stream e todos os seus pacotes
void free_packet_stream(PacketStream* packet_stream) {
    size_t num_packets = packet_stream->n;

    // desalocar os pacotes da stream
    for (size_t i = 0; i < num_packets; i++)
    {
        Packet *packet = packet_stream->packets[i];
        int is_raw = packet->is_raw;

        // desalocar o pacote estruturado
        if (is_raw) {
            free( packet->packet_data->packet_elems );
            free( packet->packet_data );
        }

        // desalocar o pacote, estruturado ou nao
        free( packet->packet_data );
    }

    free(packet_stream);
}


void print_pacote(int position, PacketElems *packet_elems, uint32_t raw_packet) {
    uint32_t id = packet_elems->id_sensor;
    uint32_t is_bateria_baixa = packet_elems->is_low_energy;
    uint32_t status = packet_elems->status;
    int32_t temperatura = packet_elems->temperatura;

    printf("Pacote [%d] - ", position + 1);
    printf("Dado Bruto: 0x%" PRIX32 "\n", raw_packet);
    printf("ID do Sensor : %" PRIu32 "\n", id);
    printf("Status : %" PRIu32 "\n", status);

    if (is_bateria_baixa) {
        printf("Bateria Baixa: SIM (ALERTA)\n");
    } else {
        printf("Bateria Baixa: Nao\n");
    }

    printf("Temperatura : %" PRId32 " graus\n", temperatura);
    printf("--------------------------------------\n-----------\n");
}


int print_packet_stream(PacketStream* packet_stream) {
    size_t num_packets = packet_stream->n;

    for (size_t i = 0; i < num_packets; i++)
    {
        Packet *packet = packet_stream->packets[i];
        PacketElems *packet_elems = packet->packet_data->packet_elems;
        uint32_t raw_packet = 0;

        // decodificar o pacote, caso esteja codificado.
        // caso esteja decodificado, apenas gerar o pacote
        // bruto, sem o modificar.
        if (packet->is_raw) {
            raw_packet = packet->packet_data->raw_packet;

            int status_decoded = decode_packet(packet);
            if (status_decoded == 0) return 0;
        } else {
            raw_packet = get_raw_packet(packet);
            packet_elems = packet->packet_data->packet_elems;
        }

        print_pacote(i, packet_elems, raw_packet);
    }

    return 1;
}


int main(void) {
    PacketStream* packet_stream = create_packet_stream();
    if (packet_stream == NULL) return EXIT_FAILURE;

    int status_received = receive_packets(packet_stream);
    if (status_received == 0) return EXIT_FAILURE;

    print_packet_stream(packet_stream);
    free_packet_stream(packet_stream);

    return EXIT_SUCCESS;
}