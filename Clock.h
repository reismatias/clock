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
        day = -1;
        mouth = -1;
        year = -1;
        hours = -1;
        minutes = -1;

        cout << "> Digite o dia (DD):" << endl;
        while (day < 1 || day > 24) {
            printf("> ");
            day = isInteger();
        }

        cout << "> Digite o mes (MM):" << endl;
        while (mouth < 1 || mouth > 12) {
            printf("> ");
            mouth = isInteger();
        }

        cout << "> Digite o ano (AAAA):" << endl;
        while (year < 1000 || year > 9999) {
            printf("> ");
            year = isInteger();
        }

        //Horas e minutos;

        cout << "> Digite as horas (HH):" << endl;
        while (hours < 0 || hours > 23) {
            printf("> ");
            hours = isInteger();
        }

        cout << "> Digite os minutos (MM):" << endl;
        while (minutes < 0 || minutes > 60) {
            printf("> ");
            minutes = isInteger();
        }

        seconds = 0;

        cout << "> Dados alterados!" << std::endl;
        cout << "==================================" << endl;
    }

    void setHours() {
        //Altualiza os dados a partir do console:
        hours = -1;
        minutes = -1;

        cout << "> Digite as horas (HH):" << endl;
        while (hours < 0 || hours > 23) {
            printf("> ");
            hours = isInteger();
        }

        cout << "> Digite os minutos (MM):" << endl;
        while (minutes < 0 || minutes > 60) {
            printf("> ");
            minutes = isInteger();
        }

        seconds = 0;

        cout << "> Dados alterados" << endl;
        cout << "==================================" << endl;
    }

    int isInteger() {
        int x;
        while (scanf("%d", &x) != 1) {
            static char temp[256];
            fgets(temp, sizeof(temp), stdin);
            printf("> Digite somente numeros: ");
        }
        return x;
    }

};


#endif //RELOGIOPONTO_CLOCK_H
