/*
** EPITECH PROJECT, 2022
** BLUID
** File description:
** ouais ouais ouais
*/

#include "Bluid.hpp"
#include "Button.hpp"

int main(int ac, char **av)
{
    if (ac != 3 || !std::atoi(av[1])) {
        std::cerr << "[Error] Provide a valid size of simulation and a scale" << std::endl;
        return 84;
    }
    BluidEngine engine(std::atoi(av[1]), std::atoi(av[2]));

    while (engine.isOpen()) {
        engine.eventHandler();
        engine.draw();
    }
    return 0;
}
