//
// Created by mathi on 16/01/2023.
//

#ifndef RELOGIOPONTO_CLOCK_H
#define RELOGIOPONTO_CLOCK_H

#include <time.h>

class Clock {
public:
    struct tm *dateHoursCurrent;
    time_t timeC;

    int seconds{};
    int minutes{};
    int hours{};
    int day{};
    int mouth{};
    int year{};

    bool save1{};
    bool save2{};

    //O relógio já inicia a data e o horário atual;
    Clock() {
        time(&timeC);
        dateHoursCurrent = localtime(&timeC);

        day = dateHoursCurrent->tm_mday;
        mouth = dateHoursCurrent->tm_mon + 1;
        year = dateHoursCurrent->tm_year + 1900;

        hours = dateHoursCurrent->tm_hour;
        minutes = dateHoursCurrent->tm_min;
        seconds = dateHoursCurrent->tm_sec;
    }

    //Reseta para a data e horário atual;
    void reset() {
        time(&timeC);
        dateHoursCurrent = localtime(&timeC);

        day = dateHoursCurrent->tm_mday;
        mouth = dateHoursCurrent->tm_mon + 1;
        year = dateHoursCurrent->tm_year + 1900;

        hours = dateHoursCurrent->tm_hour;
        minutes = dateHoursCurrent->tm_min;
        seconds = dateHoursCurrent->tm_sec;
    }

    void setStart() {
        //Altualiza os dados a partir do console:
        bool isRight = false;
        while (!isRight) {
            isRight = true;
            cout << "> Digite o dia (DD): ";
            std::cin >> day;

            cout << "> Digite o mes (MM): ";
            std::cin >> mouth;

            cout << "> Digite o ano (AAAA): ";
            std::cin >> year;

            //Horas e minutos;
            cout << "> Digite as horas (HH): ";
            std::cin >> hours;

            cout << "> Digite os minutos (MM): ";
            std::cin >> minutes;

            seconds = 0;

            //Verifica se os dados estão no formato correto;
            if (day > 31 || day < 0)
                isRight = false;
            if (mouth > 12 || mouth < 0)
                isRight = false;
            if (year > 9999 || year < 1000)
                isRight = false;
            if (hours > 23 || hours < 0)
                isRight = false;
            if (minutes > 60 || minutes < 0)
                isRight = false;

            if (!isRight)
                cout << "> Os dados não estão no formato correto!" << endl;

        }
        cout << "> Dados alterados!" << std::endl;
        cout << "==================================" << endl;
    }

    void setHours() {
        //Altualiza os dados a partir do console:
        bool isRight = false;
        while (!isRight) {
            isRight = true;

            cout << "> Digite as horas (HH): ";
            std::cin >> hours;

            cout << "> Digite os minutos (MM): ";
            std::cin >> minutes;

            seconds = 0;

            //Verifica se os dados estão no formato correto;
            if (hours > 23 || hours < 0)
                isRight = false;
            if (minutes > 60 || minutes < 0)
                isRight = false;

            if (!isRight)
                cout << "> Os dados nao estao no formato correto!" << endl;
        }
        cout << "> Dados alterados" << endl;
        cout << "==================================" << endl;
    }
};


#endif //RELOGIOPONTO_CLOCK_H
