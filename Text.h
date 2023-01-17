//
// Created by mathi on 14/01/2023.
//

#ifndef RELOGIOPONTO_TEXT_H
#define RELOGIOPONTO_TEXT_H

#include <string>

class Text {
private:
    sf::Text text;
    sf::Font tFont;
    std::string textS;

public:
    Text() = default;

    void setText(const std::string &t, int size, sf::Color textColor) {
        tFont.loadFromFile("C:/Windows/Fonts/Arial.ttf");
        text.setString(t);
        textS = t;
        text.setFillColor(textColor);
        text.setFont(tFont);
        text.setStyle(sf::Text::Bold);
    }

    void setPosition(sf::Vector2f pos) {
        text.setPosition(pos);
    }

    void drawTo(sf::RenderWindow &window) {
        window.draw(text);
    }

    void changeText(const std::string t) {
        text.setString(t);
    }

    std::basic_string<char> returnString() {
        return textS;
    }
};


#endif //RELOGIOPONTO_TEXT_H
