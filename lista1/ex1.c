#include <stdio.h>
#include <stdlib.h>
#include <math.h>


int main(void)
{
    int dia_aniversario = 0;
    int mes_aniversario = 0;
    int ano_aniversario = 0;

    int dia_atual = 0;
    int mes_atual = 0;
    int ano_atual = 0;


    scanf("%d/%d/%d %d/%d/%d",
        &dia_aniversario, &mes_aniversario, &ano_aniversario,
        &dia_atual, &mes_atual, &ano_atual);
    

    int calc_amor = 0;

    calc_amor += dia_aniversario;
    calc_amor += dia_atual;

    calc_amor += mes_aniversario;
    calc_amor += mes_atual;

    calc_amor += ano_aniversario;
    calc_amor += ano_atual;
    
    calc_amor *= 7;
    calc_amor %= 101;

    printf("Amor: %u%% ", calc_amor);

    if (calc_amor < 20) {
        puts("Pessimo dia para se apaixonar.");
    } else if ((calc_amor >= 20) && (calc_amor <= 40)) {
        puts("Melhor manter o coracao <3 longe de perigo.");
    } else if ((calc_amor > 40) && (calc_amor < 70)) {
        puts("Se o papo e as ideias baterem, esta liberado pensar em algo.");
    } else if ((calc_amor >= 70) && (calc_amor <= 80)) {
        puts("Saia com o coracao aberto, mas lembre, nem toda troca de olhar "
            "em onibus e sinal de romance.");
    } else if ((calc_amor > 80)) {
        puts("Um dia deslumbrantemente lindo para amar. Ps: Cuidado com a "
            "intensidade.");
    }
    
    
    int calc_sorte = 0;

    calc_sorte += dia_aniversario * 9;
    calc_sorte += dia_atual * 9;

    calc_sorte += mes_atual * 9;
    calc_sorte += mes_aniversario * 9;

    calc_sorte += ano_atual - ano_aniversario;
    calc_sorte %= 101;

    printf("Sorte: %u%% ", calc_sorte);

    if (calc_sorte < 30) {
        printf("Nem jogue moedas pra cima hoje.");
        printf(" Sem tigrinho nem jogos de azar, por favor!\n");
    } else if ((calc_sorte >= 30) && (calc_sorte <= 50)) {
        printf("Melhor nao arriscar.");
        printf(" Sem tigrinho nem jogos de azar, por favor!\n");
    } else if ((calc_sorte > 50) && (calc_sorte < 80)) {
        printf("Por sua conta em risco.");
        printf(" Sem tigrinho nem jogos de azar, por favor!\n");
    } else if ((calc_sorte >= 80) && (calc_sorte <= 90)) {
        printf("Hoje vale a pena arriscar.");
        printf(" Sem tigrinho nem jogos de azar, por favor!\n");
    } else if (calc_sorte > 90) {
        printf("Nao tenha medo de virar cartas hoje.");
        printf(" Sem tigrinho nem jogos de azar, por favor!\n");
    }


    int calc_trabalho = 0;

    calc_trabalho += ano_aniversario;
    calc_trabalho += ano_atual;

    calc_trabalho -= dia_aniversario * 8;
    calc_trabalho -= dia_atual * 8;

    calc_trabalho -= mes_aniversario * 8;
    calc_trabalho -= mes_atual * 8;

    calc_trabalho %= 101;

    printf("Trabalho: %u%% ", calc_trabalho);

    if (calc_trabalho < 40) {
        puts("Hoje nao sera um dia tao proveitoso, keep calm e faca o basico.");
    } else if ((calc_trabalho >= 40) && (calc_trabalho < 50)) {
        puts("Segura a emocao, nao xinga ninguem, nao esquece de beber agua.");
    } else if ((calc_trabalho >= 50) && (calc_trabalho < 70)) {
        puts("Um dia proveitoso com certeza, leve sua simpatia consigo.");
    } else if ((calc_trabalho >= 70) && (calc_trabalho < 85)) {
        puts("Boas vibracoes hoje, chances podem estar ao seu redor.");
    } else if (calc_trabalho > 85) {
        puts("Use do maximo de networking possível hoje, dia bom para negocios.");
    }


    int calc_cores = 0;

    calc_cores += pow(dia_aniversario, 2);
    calc_cores += pow(dia_atual, 2);

    calc_cores += pow(mes_aniversario, 2);
    calc_cores += pow(mes_atual, 2);

    calc_cores += pow(ano_aniversario, 2);
    calc_cores += pow(ano_atual, 2);

    calc_cores %= 11;

    printf("Cor: ");

    switch (calc_cores)
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


    return EXIT_SUCCESS;
}
