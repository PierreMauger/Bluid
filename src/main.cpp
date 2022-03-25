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

    while (engine.isOpen()) {
        engine.eventHandler();
    }
    return 0;
}
