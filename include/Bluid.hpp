/*
** EPITECH PROJECT, 2022
** BLUID
** File description:
** bluid
*/

#ifndef BLUID_HPP
#define BLUID_HPP

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <iostream>
#include <string>

#include "Button.hpp"

typedef struct pixel_s
{

} pixel_t;

class BluidEngine
{
private:
    sf::RenderWindow _window;
    sf::Event _event;
    sf::Vector2i _actPos;
    sf::Vector2i _lastPos;
    pixel_t **_map; // temp, waiting for pixelstruct
    std::vector<Button *> _buttonList;

public:
    BluidEngine(void);
    ~BluidEngine() = default;
    bool isOpen(void);
    void update(void);
    void eventHandler(void);
    void draw(void);
    sf::RenderWindow &getWindow(void);
    sf::Vector2i getActPos(void);
    sf::Vector2i getLastPos(void);
};

#endif // BLUID_HPP
