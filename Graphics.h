//
// Created by mathi on 22/01/2023.
//

#ifndef RELOGIOPONTO_GRAPHICS_H
#define RELOGIOPONTO_GRAPHICS_H

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include "Thread.h"
#include "Text.h"
#include "Button.h"
#include "Clock.h"

class Graphics : public Thread {
private:
    //Objetos da janela gráfica;
    Text title;

    Text hours;
    Text minutes;
    Text seconds;

    Text day;
    Text mouth;
    Text year;

    Button set;
    Button end;
    Button startB;

    bool hasClicked = false;
    bool hasStarted = false;
    bool *hasEnded{};

    Clock *c1{};

    void run() override;

public:
    Graphics();
    ~Graphics() override;

    void setBool(bool *pBoolean);

    //Ponteiro utilizado para coletar os dados para a interface gráfica;
    void setClock(Clock *clock1);

    void update();
};


#endif //RELOGIOPONTO_GRAPHICS_H
