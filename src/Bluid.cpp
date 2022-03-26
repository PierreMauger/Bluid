/*
** EPITECH PROJECT, 2022
** BLUID
** File description:
** bluid
*/

#include "Bluid.hpp"

BluidEngine::BluidEngine(void)
{
    this->_window.create(sf::VideoMode(1920, 1080), "Bluid");
    this->_window.setFramerateLimit(60);
    this->_lastPos = {0, 0};
    this->_actPos = {0, 0};
}

bool BluidEngine::eventHandler(void)
{
    while (this->_window.pollEvent(this->_event))
        if (this->_event.type == sf::Event::Closed)
            this->_window.close();

    if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
        this->_lastPos = this->_actPos;
        this->_actPos = sf::Mouse::getPosition(this->_window);
        if (this->_lastPos.x != this->_actPos.x && this->_lastPos.y != this->_actPos.y) {
            std::cout << "last: " << this->_lastPos.x << " " << this->_lastPos.y << std::endl;
            std::cout << "act: " << this->_actPos.x << " " << this->_actPos.y << std::endl;
        }
        return (true);
    }
    return (false);
}

bool BluidEngine::isOpen()
{
    return this->_window.isOpen();
}

sf::RenderWindow &BluidEngine::getWindow()
{
    return this->_window;
}

sf::Vector2i BluidEngine::getActPos()
{
    return this->_actPos;
}

sf::Vector2i BluidEngine::getLastPos()
{
    return this->_lastPos;
}
