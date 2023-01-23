//Includes Bibliotecas Padrão
#include <iostream>
#include <chrono>
#include <thread>

//Includes Class
#include "Graphics.h"
#include "Clock.h"

using namespace std;

int main() {
    //Objetos lógicos;
    int end = 0;
    Clock c1;
    bool hasEnded;

    //Objetos gráficos
    Graphics window;
    window.setBool(&hasEnded);
    window.setClock(&c1);

    //Inicia a thread filha responsável pela parte gráfica.
    window.start();
    cout << "thread_1 iniciada!\n";

    while (end != 1) {
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

        //TODO: Lógica para salvar os dados!

        this_thread::sleep_for(chrono::milliseconds(1000));
        if (hasEnded) {
            cout << "Janela encerrada, digite 1 para encerrar o sistema!\n>";
            cin >> end;
        }
    }
    window.join();

    //TODO: Antes de encerrar, salvar as informações em um arquivo.txt

    cout << "Programa encerrado!\n";

    return 0;
}