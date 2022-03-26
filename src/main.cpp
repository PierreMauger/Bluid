/*
** EPITECH PROJECT, 2022
** BLUID
** File description:
** ouais ouais ouais
*/

#include "Bluid.hpp"
#include "Button.hpp"

int main(void)
{
    BluidEngine engine;
    Button button1({500, 500}, "mmmm");
    sf::CircleShape shape(15);
    shape.setOrigin({15, 15});
    while (engine.isOpen()) {
        if (engine.eventHandler())
            button1.setValue(engine.getActPos());
        shape.setPosition({(float)engine.getActPos().x, (float)engine.getActPos().y});

        engine.getWindow().clear(sf::Color::Black);
        engine.getWindow().draw(shape);
        button1.draw(engine.getWindow());
        engine.getWindow().display();
    }
    return 0;
}
