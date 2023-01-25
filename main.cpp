//Includes Bibliotecas Padrão
#include <iostream>
#include <chrono>
#include <thread>

//Includes Class
#include "Graphics.h"
#include "Clock.h"
#include "List.h"

using namespace std;

int main() {
    //Objetos lógicos;
    Clock c1;
    bool hasEnded;

    //Objetos da Lista;
    List l;
    Node *aux;

    //Objetos gráficos
    Graphics window;
    window.setBool(&hasEnded);
    window.setClock(&c1);

    //Inicia a thread filha responsável pela parte gráfica.
    window.start();
    cout << "> thread_1 iniciada!\n";

    while (!hasEnded) {
        //Verifica se a interface mandou gravar o último horário;
        if (c1.save1) {
            //Cria um nó na lista;
            l.createNewNode();
            aux = l.end;

            //Salva a data e as horas e minutos do inicio no nó criado;
            aux->dayL = c1.day;
            aux->mouthL = c1.mouth;
            aux->yearL = c1.year;

            aux->hoursS = c1.hours;
            aux->minutesS = c1.minutes;
            c1.save1 = false;

            cout << "> Inicio gravado!" << endl;
            cout << "==================================" << endl;
            cout << "> Inicio: " << aux->hoursS << ":" << aux->minutesS << endl;
            cout << "==================================" << endl;
        } else if (c1.save2) {
            //Salva as horas e os minutos do final e calcula quanto tempo passou;
            aux->hoursE = c1.hours;
            aux->minutesE = c1.minutes;
            aux->calculateTotal();
            c1.save2 = false;

            cout << "> Final gravado!" << endl;
            cout << "==================================" << endl;
            cout << "> Inicio: " << aux->hoursS << ":" << aux->minutesS << endl;
            cout << "> Fim: " << aux->hoursE << ":" << aux->minutesE << endl;
            cout << "> Total: " << aux->totalHours << ":" << aux->totalMinutes << endl;
            cout << "==================================" << endl;
        }

        //Lógica do relógio;
        if (c1.seconds >= 0 && c1.seconds < 60) {
            c1.seconds++;
        }
        if (c1.seconds == 60) {
            c1.seconds = 0;
            c1.minutes++;
        }
        if (c1.minutes == 60) {
            c1.minutes = 0;
            c1.hours++;
        }
        if (c1.hours == 24) {
            c1.hours = 0;
            c1.day++;
        }

        this_thread::sleep_for(chrono::milliseconds(1000));
    }
    window.join();

    cout << "> Gravando dados!" << endl;
    //Daqui em diante falta otimizar e comentar o código. :)

    //Lógica para salavar o log.
    FILE *arq;

    string fileName;
    string line;

    //Pega o primeiro nó para percorrer a lista do inicio.
    aux = l.first;
    int firstDay = aux->dayL;
    int firstMouth = aux->mouthL;

    int totalHoursD = 0;
    int totalMinutesD = 0;

    int totalH = 0;
    int totalM = 0;

    //Verifica se o nó está completo! Porque o totalHours só muda quando o segundo registro é feito.
    if (aux->totalHours != -1) {
        //AJUSTAR ESSA PARTE! Conforme a sua IDE, mude a referência de ../logs/
        fileName = "../logs/" + to_string(aux->mouthL) + "-" + to_string(aux->yearL) + ".txt";

        arq = fopen(fileName.c_str(), "wt");

        if (arq == nullptr)
            cout << "> Problemas na criação do arquivo." << endl;

        fprintf(arq, "%.2d/%.2d/%.2d\n", aux->dayL, aux->mouthL, aux->yearL);
    } else
        cout << "> Sem dados para gravar!" << endl;

    //Roda o loop enquanto o nó atual não for nulo e enquanto o nó estiver completo.
    while ((aux != nullptr) && (aux->totalHours != -1)) {
        if (aux->mouthL == firstMouth) {
            if (aux->dayL == firstDay) {
                fprintf(arq, "\t\t  %.2d:%.2d \t %.2d:%.2d \t %.2d:%.2d\n", aux->hoursS, aux->minutesS, aux->hoursE,
                        aux->minutesE, aux->totalHours, aux->totalMinutes);
                totalHoursD += aux->totalHours;
                totalMinutesD += aux->totalMinutes;

                totalH += aux->totalHours;
                totalM += aux->totalMinutes;

                //Verifica se o próximo exite e verifica se o próximo é um nó completo.
                if (aux->next == nullptr || aux->next->totalHours == -1) {
                    totalHoursD += totalMinutesD / 60;
                    totalMinutesD = totalMinutesD % 60;
                    fprintf(arq, "\t\t\t\t\t Total:  %.2d:%.2d\n", totalHoursD, totalMinutesD);

                    fprintf(arq, "\n");
                    totalH += totalM / 60;
                    totalM = totalM % 60;
                    fprintf(arq, "Total mensal: %.2d:%.2d\n", totalH, totalM);
                }

                aux = aux->next;
            } else {
                totalHoursD += totalMinutesD / 60;
                totalMinutesD = totalMinutesD % 60;
                fprintf(arq, "\t\t\t\t\t Total:  %.2d:%.2d\n", totalHoursD, totalMinutesD);

                totalHoursD = 0;
                totalMinutesD = 0;

                fprintf(arq, "\n");
                fprintf(arq, "%.2d/%.2d/%.2d\n", aux->dayL, aux->mouthL, aux->yearL);
                firstDay = aux->dayL;
            }
        } else {
            totalHoursD += totalMinutesD / 60;
            totalMinutesD = totalMinutesD % 60;
            fprintf(arq, "\t\t\t\t\t Total:  %.2d:%.2d\n", totalHoursD, totalMinutesD);

            totalHoursD = 0;
            totalMinutesD = 0;

            fprintf(arq, "\n");
            totalH += totalM / 60;
            totalM = totalM % 60;
            fprintf(arq, "Total mensal: %.2d:%.2d\n", totalH, totalM);
            fclose(arq);

            totalH = 0;
            totalM = 0;

            firstDay = aux->dayL;
            firstMouth = aux->mouthL;

            //AJUSTAR ESSA PARTE! Conforme a sua IDE, mude a referência de ../logs/
            fileName = "../logs/" + to_string(aux->mouthL) + "-" + to_string(aux->yearL) + ".txt";
            arq = fopen(fileName.c_str(), "wt");

            if (arq == nullptr)
                cout << "> Problemas na criação do arquivo." << endl;

            fprintf(arq, "%.2d/%.2d/%.2d\n", aux->dayL, aux->mouthL, aux->yearL);
        }
    }

    //Só tem arquivo para fechar caso tenha sido aberto alguma vez.
    if (l.first->totalHours != -1)
        fclose(arq);

    while (!l.empty())
        l.deleteElement();

    cout << "> Programa encerrado!" << endl;
    return 0;
}