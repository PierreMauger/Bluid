#include "Button.hpp"

Button::Button(sf::Vector2f pos, std::string name)
{
    this->_value = 50;
    this->_font.loadFromFile("ressources/Blue.ttf");
    this->_tempBox.setPosition({pos.x, pos.y});
    this->_tempBox.setSize({300, 100});
    this->_tempBox.setFillColor(sf::Color::Red);
    this->_box.setPosition({pos.x + 100, pos.y + 25});
    this->_box.setSize({(float)this->_value, 50});
    this->_box.setFillColor(sf::Color::Blue);
    this->_name.setCharacterSize(20);
    this->_name.setFont(this->_font);
    this->_name.setString(name);
    std::cout << "Height " << this->_name.getGlobalBounds().height << std::endl;
    // this->_name.setOrigin({0, this->_name.getGlobalBounds().height});
    this->_name.setPosition({pos.x, pos.y + 50});
}

Button::~Button()
{

}

void Button::draw(sf::RenderWindow &window)
{
    window.draw(this->_tempBox);
    window.draw(this->_box);
    window.draw(this->_name);
}

void Button::setValue(sf::Vector2i mousePos)
{

}
