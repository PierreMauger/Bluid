/*
** EPITECH PROJECT, 2022
** BLUID
** File description:
** ouais ouais ouais
*/

#include "Bluid.hpp"

int main(void)
{
    BluidEngine engine;
    sf::CircleShape shape(15);
    shape.setOrigin({15, 15});
    while (engine.isOpen()) {
        engine.eventHandler();
        shape.setPosition({(float)engine.getActPos().x, (float)engine.getActPos().y});

        engine.getWindow().clear(sf::Color::Black);
        engine.getWindow().draw(shape);
        engine.getWindow().display();
    }
    return 0;
}
