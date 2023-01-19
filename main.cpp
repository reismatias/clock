//Includes Bibliotecas Padrão
#include <iostream>
#include <pthread.h>
#include <string>
#include <chrono>

//Includes Biblioteca Gráfica
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <thread>

//Includes Class
#include "Text.h"
#include "Button.h"
#include "Clock.h"

using namespace std;

//Variáveis Globais (e objetos globais)
Text hours;
Text minutes;
Text seconds;

Text day;
Text mouth;
Text year;

bool hasEnded;
pthread_t thread_2;

//Funções
void *clock(void *p);

int main() {
    //Window
    sf::RenderWindow window(sf::VideoMode(680, 380), L"relógio ponto", sf::Style::Titlebar | sf::Style::Close);
    sf::Event ev{};
    window.setFramerateLimit(30);

    //Criando os objetos
    Text title;

    Button set;
    Button start;
    Button end;

    //Passando os atributos dos objetos criados;
    title.setText("relogio ponto", 30, sf::Color::Black);
    title.setPosition(sf::Vector2f(250, 55));

    day.setText("00/", 28, sf::Color::Black);
    day.setPosition(sf::Vector2f(263, 95));

    mouth.setText("00/", 28, sf::Color::Black);
    mouth.setPosition(sf::Vector2f(313, 95));

    year.setText("0000", 28, sf::Color::Black);
    year.setPosition(sf::Vector2f(363, 95));

    hours.setText("00:", 28, sf::Color::Black);
    hours.setPosition(sf::Vector2f(275, 150));

    minutes.setText("00:", 28, sf::Color::Black);
    minutes.setPosition(sf::Vector2f(325, 150));

    seconds.setText("00", 28, sf::Color::Black);
    seconds.setPosition(sf::Vector2f(375, 150));

    set.setButton("INICIAR", {150, 50}, 20, sf::Color::Black, sf::Color::White);
    set.setPosition({270, 250});

    start.setButton("GRAVAR", {150, 50}, 20, sf::Color::Black, sf::Color::White);
    start.setPosition({270, 250});

    end.setButton("ENCERRAR", {150, 50}, 20, sf::Color::Black, sf::Color::White);
    end.setPosition({270, 250});

    //Duas flags para controlar o que aparece na tela;
    bool hasClicked = false;
    bool hasStarted = false;
    while (window.isOpen()) {
        //Apaga o frame antigo
        window.clear(sf::Color::White);

        //Renderiza os objetos na janela;
        title.drawTo(window);

        day.drawTo(window);
        mouth.drawTo(window);
        year.drawTo(window);

        hours.drawTo(window);
        minutes.drawTo(window);
        seconds.drawTo(window);

        //Controla a redenrização dos botões;
        if (!hasStarted)
            set.drawTo(window);

        if (hasStarted && !hasClicked)
            start.drawTo(window);

        if (hasClicked)
            end.drawTo(window);

        window.display();

        //Gerenciador de eventos
        while (window.pollEvent(ev)) {
            switch (ev.type) {
                //Gerencia eventos de encerramento da janela;
                case sf::Event::Closed:
                    window.close();
                    break;
                case sf::Event::KeyPressed:
                    if (ev.key.code == sf::Keyboard::Escape) {
                        window.close();
                    } else if (ev.key.code == sf::Keyboard::Space) { //Usado para resetar a data;
                        hasStarted = false;
                        set.setBackColor(sf::Color::Black);
                        hasEnded = true;
                    }
                    break;
                    //Gerencia eventos de click no mouse;
                case sf::Event::MouseButtonPressed:
                    if (!hasClicked && hasStarted && start.isMouseOver(window)) {
                        //TODO: Fazer o registro da data e da hora de inicio.
                        hasClicked = true;
                        cout << "gravou!" << endl;
                        end.setBackColor(sf::Color::Black);
                    } else if (hasClicked && end.isMouseOver(window)) {
                        //TODO: Fazer o registro da data e da hora de final.
                        cout << "end!" << endl;
                        end.setBackColor(sf::Color::Transparent);
                        hasClicked = false;
                    } else if (!hasStarted && set.isMouseOver(window)) {
                        //OBS.: É temporário, porque os valores chegarão da GUI
                        //Recebe os valores de entrada para data e hora;
                        string tm_string;
                        string points = ":";
                        string bar = "/";

                        //DATA
                        cout << "Digite o dia (DD): ";
                        getline(cin, tm_string);
                        day.setText(tm_string + bar, 28, sf::Color::Black);

                        cout << "Digite o mes (MM): ";
                        getline(cin, tm_string);
                        mouth.setText(tm_string + bar, 28, sf::Color::Black);

                        cout << "Digite o ano (AAAA): ";
                        getline(cin, tm_string);
                        year.setText(tm_string, 28, sf::Color::Black);

                        //HORA
                        cout << "Digite as horas (HH): ";
                        getline(cin, tm_string);
                        hours.setText(tm_string + points, 28, sf::Color::Black);

                        cout << "Digite os minutos (MM): ";
                        getline(cin, tm_string);
                        minutes.setText(tm_string + points, 28, sf::Color::Black);

                        seconds.setText("00", 28, sf::Color::Black);

                        //Cria a thread do relógio e coloca ela pra rodar;
                        hasEnded = false;
                        pthread_create(&thread_2, nullptr, clock, nullptr);

                        //Desativa o botão set e ativa o botão start;
                        set.setBackColor(sf::Color::Transparent);
                        start.setBackColor(sf::Color::Black);
                        hasStarted = true;
                    }
            }
        }
    }

    //TODO: Antes de encerrar, salvar as informações em um arquivo .txt

    cout << "Programa encerrado!\n";

    return 0;
}

void *clock(void *p) {
    string twoPoints = ":";
    string bar = "/";
    string zero = "0";

    Clock c1;
    cout << "thread_2 iniciada!\n";

    c1.day = stoi(day.returnString());
    c1.mouth = stoi(mouth.returnString());
    c1.year = stoi(year.returnString());

    c1.hours = stoi(hours.returnString());
    c1.minutes = stoi(minutes.returnString());
    c1.seconds = 00;

    while (!hasEnded) {
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

        if (c1.seconds < 10)
            seconds.setText(zero + to_string(c1.seconds), 28, sf::Color::Black);
        else
            seconds.setText(to_string(c1.seconds), 28, sf::Color::Black);
        minutes.setText(to_string(c1.minutes) + twoPoints, 28, sf::Color::Black);
        hours.setText(to_string(c1.hours) + twoPoints, 28, sf::Color::Black);
        day.setText(to_string(c1.day) + bar, 28, sf::Color::Black);

        this_thread::sleep_for(chrono::milliseconds(1000));
    }

    cout << "thread_2 encerrada!" << endl;
    return nullptr;
}