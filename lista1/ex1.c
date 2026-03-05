#include <stdio.h>
#include <stdlib.h>
#include <math.h>


typedef struct
{
    int dia;
    int mes;
    int ano;
} Data;


int calc_amor_porcent(Data data_atual, Data data_aniversario)
{
    int calc_amor = 0;

    calc_amor += data_aniversario.dia;
    calc_amor += data_atual.dia;

    calc_amor += data_aniversario.mes;
    calc_amor += data_atual.mes;

    calc_amor += data_aniversario.ano;
    calc_amor += data_atual.ano;
    
    calc_amor *= 7;
    calc_amor %= 101;

    return calc_amor;
}


void print_amor_porcent(int porcent_amor)
{
    printf("Amor: %u%% ", porcent_amor);

    if (porcent_amor < 20) {
        puts("Pessimo dia para se apaixonar.");
    } else if ((porcent_amor >= 20) && (porcent_amor <= 40)) {
        puts("Melhor manter o coracao <3 longe de perigo.");
    } else if ((porcent_amor > 40) && (porcent_amor < 70)) {
        puts("Se o papo e as ideias baterem, esta liberado pensar em algo.");
    } else if ((porcent_amor >= 70) && (porcent_amor <= 80)) {
        puts("Saia com o coracao aberto, mas lembre, nem toda troca de olhar "
            "em onibus e sinal de romance.");
    } else if ((porcent_amor > 80)) {
        puts("Um dia deslumbrantemente lindo para amar. Ps: Cuidado com a "
            "intensidade.");
    }
}


int calc_sorte_porcent(Data data_aniversario, Data data_atual)
{
    int porcent_sorte = 0;

    porcent_sorte += data_aniversario.dia * 9;
    porcent_sorte += data_atual.dia * 9;

    porcent_sorte += data_atual.mes * 9;
    porcent_sorte += data_aniversario.mes * 9;

    porcent_sorte += data_atual.ano - data_aniversario.ano;
    porcent_sorte %= 101;

    return porcent_sorte;
}


void print_sorte_porcent(int calc_sorte)
{
    printf("Sorte: %u%% ", calc_sorte);

    if (calc_sorte < 30) {
        puts("Nem jogue moedas pra cima hoje.");
    } else if ((calc_sorte >= 30) && (calc_sorte <= 50)) {
        puts("Melhor nao arriscar.");
    } else if ((calc_sorte > 50) && (calc_sorte < 80)) {
        puts("Por sua conta em risco.");
    } else if ((calc_sorte >= 80) && (calc_sorte <= 90)) {
        puts("Hoje vale a pena arriscar.");
    } else if (calc_sorte > 90) {
        printf("Nao tenha medo de virar cartas hoje.");
        printf(" Sem tigrinho nem jogos de azar, por favor!");
    }
}


int calc_trabalho_porcent(Data data_aniversario, Data data_atual)
{
    int porcent_trabalho = 0;

    porcent_trabalho += data_aniversario.ano;
    porcent_trabalho += data_atual.ano;

    porcent_trabalho -= data_aniversario.dia * 8;
    porcent_trabalho -= data_atual.dia * 8;

    porcent_trabalho -= data_aniversario.mes * 8;
    porcent_trabalho -= data_atual.mes * 8;

    porcent_trabalho %= 101;

    return porcent_trabalho;
}


void print_trabalho_porcent(int porcent_trabalho)
{
    printf("Trabalho: %u%% ", porcent_trabalho);

    if (porcent_trabalho < 40) {
        puts("Hoje nao sera um dia tao proveitoso, keep calm e faca o basico.");
    } else if ((porcent_trabalho >= 40) && (porcent_trabalho < 50)) {
        puts("Segura a emocao, nao xinga ninguem, nao esquece de beber agua.");
    } else if ((porcent_trabalho >= 50) && (porcent_trabalho < 70)) {
        puts("Um dia proveitoso com certeza, leve sua simpatia consigo.");
    } else if ((porcent_trabalho >= 70) && (porcent_trabalho < 85)) {
        puts("Boas vibracoes hoje, chances podem estar ao seu redor.");
    } else if (porcent_trabalho > 85) {
        puts("Use do maximo de networking possível hoje, dia bom para negocios.");
    }
}


int calc_cores_porcent(Data data_aniversario, Data data_atual)
{
    int calc_cores = 0;

    calc_cores += pow(data_aniversario.dia, 2);
    calc_cores += pow(data_atual.dia, 2);

    calc_cores += pow(data_aniversario.mes, 2);
    calc_cores += pow(data_atual.mes, 2);

    calc_cores += pow(data_aniversario.ano, 2);
    calc_cores += pow(data_atual.ano, 2);

    calc_cores %= 11;

    return calc_cores;
}


void print_cor_porcent(int id_cor)
{
    printf("Cor: ");
    switch (id_cor)
    {
        case 0:
            puts("Cinza.");
            break;
        case 1:
            puts("Vermelho.");
            break;
        case 2:
            puts("Laranja.");
            break;
        case 3:
            puts("Amarelo.");
            break;
        case 4:
            puts("Verde.");
            break;
        case 5:
            puts("Azul.");
            break;
        case 6:
            puts("Roxo.");
            break;
        case 7:
            puts("Marrom.");
            break;
        case 8:
            puts("Rosa.");
            break;
        case 9:
            puts("Preto.");
            break;
        case 10:
            puts("Branco.");
            break;
    }
}


int main(void)
{
    Data data_aniversario = {0, 0, 0};
    Data data_atual = {0, 0, 0};

    scanf("%d/%d/%d %d/%d/%d",
        &(data_aniversario.dia), &(data_aniversario.mes), &(data_aniversario.ano),
        &(data_atual.dia), &(data_atual.mes), &(data_atual.ano));
    

    int porcent_amor = calc_amor_porcent(data_aniversario, data_atual);
    print_amor_porcent(porcent_amor);
    
    int porcent_sorte = calc_sorte_porcent(data_aniversario, data_atual);
    print_sorte_porcent(porcent_sorte);

    int porcent_trabalho = calc_trabalho_porcent(data_aniversario, data_atual);
    print_trabalho_porcent(porcent_trabalho);

    int id_cor = calc_cores_porcent(data_aniversario, data_atual);
    print_cor_porcent(id_cor);


    return EXIT_SUCCESS;
}
