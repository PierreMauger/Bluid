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
        sf::Text _textValue;
        sf::Font _font;
        sf::RectangleShape _boxSlider;
        sf::RectangleShape _boxValue;
        sf::RectangleShape _tempBox;
        sf::RectangleShape _emptyBox;
        sf::FloatRect _pos;
        float _value;
        sf::Vector2f _scale;

    public:
        Button(sf::Vector2f pos, std::string name, sf::Vector2f scale, float value);
        ~Button() = default;
        void draw(sf::RenderWindow &window);
        void setValue(sf::Vector2i mousePos);
        void setValue(float value);
        float getValue(void);
        sf::FloatRect getPos(void);
        std::string to_string_float(float value);
};

#endif // BUTTON_HPP
