//
// Created by mathi on 22/01/2023.
//

#include "Graphics.h"
#include <string>

#include <chrono>
#include <thread>

using namespace std;


Graphics::Graphics() = default;

Graphics::~Graphics() = default;

void Graphics::run() {
    std::cout << "thread_2 iniciada!\n";

    //Window;
    sf::RenderWindow window(sf::VideoMode(680, 380), L"relógio ponto", sf::Style::Titlebar | sf::Style::Close);
    sf::Event ev{};
    window.setFramerateLimit(30);

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

    startB.setButton("GRAVAR", {150, 50}, 20, sf::Color::Black, sf::Color::White);
    startB.setPosition({270, 250});

    end.setButton("ENCERRAR", {150, 50}, 20, sf::Color::Black, sf::Color::White);
    end.setPosition({270, 250});

    //Duas flags para controlar o que aparece na tela;
    hasClicked = false;
    hasStarted = false;
    while (window.isOpen()) {
        //Apaga o frame antigo;
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
            startB.drawTo(window);

        if (hasClicked)
            end.drawTo(window);

        window.display();
        update();

        //Gerenciador de eventos;
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
                    if (!hasClicked && hasStarted && startB.isMouseOver(window)) {
                        //TODO: Fazer o registro da data e da hora de inicio.

                        //Controla interface gráfica;
                        hasClicked = true;
                        end.setBackColor(sf::Color::Black);
                    } else if (hasClicked && end.isMouseOver(window)) {
                        //TODO: Fazer o registro da data e da hora de final.

                        //Controla interface gráfica;
                        end.setBackColor(sf::Color::Transparent);
                        hasClicked = false;
                    } else if (!hasStarted && set.isMouseOver(window)) {
                        //Desativa o botão set e ativa o botão start;

                        //Altualiza a partir do console a data e hora inicial do relógio;
                        c1->setDate();

                        //Controla interface gráfica;
                        set.setBackColor(sf::Color::Transparent);
                        startB.setBackColor(sf::Color::Black);
                        hasStarted = true;
                    }
            }
        }
    }

    window.close();
    std::cout << "thread_2 encerrada!\n";
    *hasEnded = true;
}

void Graphics::setBool(bool *pBoolean) {
    hasEnded = pBoolean;
}

void Graphics::setClock(Clock *clock1) {
    c1 = clock1;
}

void Graphics::update() {
    string twoPoints = ":";
    string bar = "/";
    string zero = "0";

    //Atualiza os valores exibidos na interface gráfica;
    if (c1->seconds < 10)
        seconds.setText(zero + to_string(c1->seconds), 28, sf::Color::Black);
    else
        seconds.setText(to_string(c1->seconds), 28, sf::Color::Black);

    if (c1->minutes < 10)
        minutes.setText(zero + to_string(c1->minutes) + twoPoints, 28, sf::Color::Black);
    else
        minutes.setText(to_string(c1->minutes) + twoPoints, 28, sf::Color::Black);

    if (c1->hours < 10)
        hours.setText(zero + to_string(c1->hours) + twoPoints, 28, sf::Color::Black);
    else
        hours.setText(to_string(c1->hours) + twoPoints, 28, sf::Color::Black);

    if (c1->day < 10)
        day.setText(zero + to_string(c1->day) + bar, 28, sf::Color::Black);
    else
        day.setText(to_string(c1->day) + bar, 28, sf::Color::Black);

    if (c1->mouth > 10)
        mouth.setText(to_string(c1->mouth) + bar, 28, sf::Color::Black);
    else
        mouth.setText(zero + to_string(c1->mouth) + bar, 28, sf::Color::Black);

    year.setText(to_string(c1->year), 28, sf::Color::Black);
}