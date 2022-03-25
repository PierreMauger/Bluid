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

public:
    BluidEngine(void);
    ~BluidEngine() = default;
    bool isOpen(void);
    void update(void);
    void eventHandler(void);
    sf::RenderWindow &getWindow();
    sf::Vector2i getActPos();
    sf::Vector2i getLastPos();
};
