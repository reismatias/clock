#include <iostream>
#include <pthread.h>
#include <string>

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include "Text.h"
#include "Button.h"
#include "Clock.h"

using namespace std;

void setDate(Text *o);

int main() {
    //Window
    sf::RenderWindow window(sf::VideoMode(680, 380), L"relógio ponto", sf::Style::Titlebar | sf::Style::Close);
    sf::Event ev{};
    window.setFramerateLimit(30);

    //Criando os objetos
    Text title;
    Text date;

    Text hours;
    Text minutes;
    Text seconds;

    Button set;

    Button start;
    Button end;

    //Passando os atributos dos objetos criados;
    title.setText("relogio ponto", 30, sf::Color::Black);
    title.setPosition(sf::Vector2f(250, 55));

    date.setText("01/01/2023", 28, sf::Color::Black);
    date.setPosition(sf::Vector2f(263, 95));

    hours.setText("23:", 28, sf::Color::Black);
    hours.setPosition(sf::Vector2f(275, 150));

    minutes.setText("59:", 28, sf::Color::Black);
    minutes.setPosition(sf::Vector2f(325, 150));

    seconds.setText("58", 28, sf::Color::Black);
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
        date.drawTo(window);
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
                        cout << "Digite a data(dd/mm/aaaa): ";
                        setDate(&date);
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

void setDate(Text *o) {
    //Recebe a data pelo console e registra no Text *o que foi recebido por parâmetro;
    string tm_string;
    getline(cin, tm_string);
    o->changeText(tm_string);
}