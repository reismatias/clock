//
// Created by mathi on 16/01/2023.
//

#ifndef RELOGIOPONTO_CLOCK_H
#define RELOGIOPONTO_CLOCK_H

class Clock {
public:
    int seconds = 0;
    int minutes = 0;
    int hours = 0;
    int day = 1;
    int mouth = 1;
    int year = 2000;

    bool save1{};
    bool save2{};

    Clock() = default;

    void setDate() {
        //Altualiza os dados a partir do console:

        //Data;
        cout << "Digite o dia (DD): ";
        std::cin >> day;

        cout << "Digite o mes (MM): ";
        std::cin >> mouth;

        cout << "Digite o ano (AAAA): ";
        std::cin >> year;

        //Horas e minutos;
        cout << "Digite as horas (HH): ";
        std::cin >> hours;

        cout << "Digite os minutos (MM): ";
        std::cin >> minutes;

        seconds = 0;

        std::cout << "Dados alterados\n";
    }
};


#endif //RELOGIOPONTO_CLOCK_H
