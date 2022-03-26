/*
** EPITECH PROJECT, 2022
** BLUID
** File description:
** bluid
*/

#include "Bluid.hpp"
#include "Button.hpp"

BluidEngine::BluidEngine(void)
{
    this->_window.create(sf::VideoMode(1920, 1080), "Bluid", sf::Style::Fullscreen);
    this->_window.setFramerateLimit(60);
    this->_lastPos = {0, 0};
    this->_actPos = {0, 0};
    this->_buttonList.push_back(new Button({this->_window.getSize().x - 400.f,   0}, "ratio", {3, 4}));
    this->_buttonList.push_back(new Button({this->_window.getSize().x - 400.f, 100}, "L", {0, 200}));
    this->_buttonList.push_back(new Button({this->_window.getSize().x - 400.f, 200}, "palu", {-1, 1}));
}

void BluidEngine::eventHandler(void)
{
    while (this->_window.pollEvent(this->_event)) {
        if (this->_event.type == sf::Event::Closed)
            this->_window.close();
        if (this->_event.type == sf::Event::KeyPressed)
            if (this->_event.key.code == sf::Keyboard::Escape)
                this->_window.close();
    }

    if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
        this->_lastPos = this->_actPos;
        this->_actPos = sf::Mouse::getPosition(this->_window);
        if (this->_lastPos.x != this->_actPos.x && this->_lastPos.y != this->_actPos.y) {
            std::cout << "last: " << this->_lastPos.x << " " << this->_lastPos.y << std::endl;
            std::cout << "act: " << this->_actPos.x << " " << this->_actPos.y << std::endl;
        }
        for (Button *button : this->_buttonList)
            button->setValue(this->_actPos);
    }
}

bool BluidEngine::isOpen()
{
    return this->_window.isOpen();
}

sf::RenderWindow &BluidEngine::getWindow(void)
{
    return this->_window;
}

sf::Vector2i BluidEngine::getActPos(void)
{
    return this->_actPos;
}

sf::Vector2i BluidEngine::getLastPos(void)
{
    return this->_lastPos;
}

void BluidEngine::draw(void)
{
    this->_window.clear(sf::Color::Black);
    for (Button *button : this->_buttonList)
        button->draw(this->_window);
    this->_window.display();
}
