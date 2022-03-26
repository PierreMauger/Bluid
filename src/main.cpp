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
    Button button1({500, 500}, "ratio", 100);
    while (engine.isOpen()) {
        if (engine.eventHandler())
            button1.setValue(engine.getActPos());
        engine.draw(button1);
    }
    return 0;
}
