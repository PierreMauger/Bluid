/*
** EPITECH PROJECT, 2022
** BLUID
** File description:
** bluid
*/

#ifndef BUTTON_HPP
#define BUTTON_HPP

#include "Bluid.hpp"

class Button {
    private:
        sf::Text _name;
        sf::Font _font;
        sf::RectangleShape _box;
        sf::RectangleShape _tempBox;
        sf::FloatRect _pos;
        int _value;

    public:
        Button(sf::Vector2f pos, std::string name);
        ~Button() = default;
        void draw(sf::RenderWindow &window);
        void setValue(sf::Vector2i mousePos);
};

#endif // BUTTON_HPP
