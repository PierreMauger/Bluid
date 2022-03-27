/*
** EPITECH PROJECT, 2022
** BLUID
** File description:
** bluid
*/

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <iostream>
#include <cmath>

#define N 512
#define IX(x, y) ((x) + (y) * N)

class BluidEngine
{
    private:
        sf::RenderWindow _window;
        sf::Event _event;
        sf::Vector2i _actPos;
        sf::Vector2i _lastPos;

    public:
        BluidEngine(void);
        virtual ~BluidEngine() = default;
        bool isOpen(void);
        void update(void);
        void eventHandler(void);
        sf::RenderWindow &getWindow();
        sf::Vector2i getActPos();
        sf::Vector2i getLastPos();
        sf::Uint8 getDensity(int i, int j) const;
        void mouseDragged();
};
