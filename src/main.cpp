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
    BluidEngine engine(512);

    while (engine.isOpen()) {
        engine.eventHandler();
        engine.draw();
    }
    return 0;
}
