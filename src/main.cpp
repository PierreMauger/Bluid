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
    if ((ac == 2 && std::string(av[1]) == "-h") || ac != 3 ||
        !std::atoi(av[1]) || !std::atoi(av[2])) {
        std::cout << "\033[1;34mBluid\033[0m\n\tA fluid simulation program made"
        << " in C++ with SFML.\n\tCreated for an Epitech game jam in 2 days by "
        << "4 2nd year students:\n\tPierre HAMEL, Dorian AYOUL, Pierre MAUGER &"
        << " Xavier TONNELIER\n\nARGUMENTS\n\t-h\tsee help\n\t[size] [scale]\t"
        << "start with a valid simulation size and scale (resolution)\n\n"
        << "USER INTERACTION\n\tDrag left click across the top-left simulation "
        << "square\n\tto manipulate the fluid. Drag left click on a top-right\n"
        << "\tsimulation parameter slider to change its value.\n\tPress ESCAPE "
        << "to end the simulation." << std::endl;
        return 0;
    }
    BluidEngine engine(std::atoi(av[1]), std::atoi(av[2]));

    while (engine.isOpen()) {
        engine.eventHandler();
        engine.draw();
    }
    return 0;
}
