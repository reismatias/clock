//
// Created by mathi on 14/01/2023.
//

#ifndef RELOGIOPONTO_BUTTON_H
#define RELOGIOPONTO_BUTTON_H

class Button {
private:
    sf::RectangleShape button;

    sf::Text text;
    sf::Font bFont;

public:
    Button() = default;

    void setButton(const std::string &t, sf::Vector2f size, int charSize, sf::Color bgColor, sf::Color textColor) {
        bFont.loadFromFile("../public/Roboto.ttf");

        text.setString(t);
        text.setFillColor(textColor);
        text.setCharacterSize(charSize);
        text.setFont(bFont);
        text.setStyle(sf::Text::Bold);

        button.setSize(size);
        button.setFillColor(bgColor);

    }

    void setBackColor(sf::Color color) {
        button.setFillColor(color);
    }

    void setTextColor(sf::Color color) {
        text.setFillColor(color);
    }

    void setPosition(sf::Vector2f pos) {
        button.setPosition(pos);

        float xPos = (pos.x + button.getGlobalBounds().width / 3) - (text.getGlobalBounds().width / 4);
        float yPos = (pos.y + button.getGlobalBounds().height / 3) - (text.getGlobalBounds().height / 4);

        text.setPosition(xPos, yPos);
    }

    void drawTo(sf::RenderWindow &window) {
        window.draw(button);
        window.draw(text);
    }

    bool isMouseOver(sf::RenderWindow &window) {
        double mouseX = sf::Mouse::getPosition(window).x + 0.1;
        double mouseY = sf::Mouse::getPosition(window).y + 0.1;

        float btnPosX = button.getPosition().x;
        float btnPosY = button.getPosition().y;

        float btnxPosWidth = button.getPosition().x + button.getLocalBounds().width;
        float btnyPosHeight = button.getPosition().y + button.getLocalBounds().height;

        if (mouseX < btnxPosWidth && mouseX > btnPosX && mouseY < btnyPosHeight && mouseY > btnPosY) {
            return true;
        }
        return false;
    }
};


#endif //RELOGIOPONTO_BUTTON_H
