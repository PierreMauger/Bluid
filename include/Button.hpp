/*
** EPITECH PROJECT, 2022
** BLUID
** File description:
** bluid
*/

#ifndef BUTTON_HPP
#define BUTTON_HPP

#include <SFML/Graphics.hpp>
#include <iomanip>

class Button {
    private:
        sf::Text _name;
        sf::Text _text_value;
        sf::Font _font;
        sf::RectangleShape _boxSlider;
        sf::RectangleShape _boxValue;
        sf::RectangleShape _tempBox;
        sf::FloatRect _pos;
        float _value;
        sf::Vector2f _scale;

    public:
        Button(sf::Vector2f pos, std::string name, sf::Vector2f scale);
        ~Button() = default;
        void draw(sf::RenderWindow &window);
        void setValue(sf::Vector2i mousePos);
        float getValue(void);
};

#endif // BUTTON_HPP
