#include "Button.hpp"

Button::Button(sf::Vector2f pos, std::string name, float scale)
{
    this->_value = 50;
    this->_scale = scale;
    this->_font.loadFromFile("ressources/Blue.ttf");
    this->_tempBox.setPosition({pos.x, pos.y});
    this->_tempBox.setSize({400, 100});
    this->_tempBox.setFillColor(sf::Color::Red);
    this->_box_slider.setPosition({pos.x + 100, pos.y + 25});
    this->_pos = {this->_box_slider.getPosition().x, this->_box_slider.getPosition().y, 200, 50};
    this->_box_slider.setSize({(float)this->_value, 50});
    this->_box_slider.setFillColor(sf::Color::Blue);
    this->_box_value.setPosition({pos.x + 320, pos.y + 25});
    this->_box_value.setSize({60, 50});
    this->_box_value.setFillColor(sf::Color::Green);
    this->_name.setCharacterSize(20);
    this->_name.setFont(this->_font);
    this->_name.setString(name);
    this->_text_value.setCharacterSize(20);
    this->_text_value.setFont(this->_font);
    this->_text_value.setString(std::to_string(_value));
    this->_text_value.setPosition({pos.x, pos.y + 50});
    this->_name.setPosition({pos.x, pos.y + 50});
}

void Button::draw(sf::RenderWindow &window)
{
    window.draw(this->_box_slider);
    window.draw(this->_box_value);
    window.draw(this->_name);
}

void Button::setValue(sf::Vector2i mousePos)
{
    if (this->_pos.contains({(float)mousePos.x, (float)mousePos.y})) {
        this->_value = mousePos.x - this->_pos.left;
        this->_box_slider.setSize({(float)this->_value, 50});
    }
}
