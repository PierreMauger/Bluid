#include "Button.hpp"

std::string to_string_float(float value, int accuracy = 6)
{
    std::ostringstream out;

    out.precision(accuracy);
    out << std::fixed << value;
    return out.str();
}

Button::Button(sf::Vector2f pos, std::string name, sf::Vector2f scale)
{
    this->_scale = scale;
    this->_value = (this->_scale.y - this->_scale.x) / 2;
    this->_font.loadFromFile("ressources/Blue.ttf");

    this->_tempBox.setPosition({pos.x, pos.y});
    this->_tempBox.setSize({400, 100});
    this->_tempBox.setFillColor(sf::Color::Red);

    this->_boxSlider.setPosition({pos.x + 100, pos.y + 25});
    this->_boxSlider.setSize({this->_value * 200 / (this->_scale.y - this->_scale.x), 50});
    this->_boxSlider.setFillColor(sf::Color::Blue);

    this->_pos = {this->_boxSlider.getPosition().x, this->_boxSlider.getPosition().y, 200, 50};

    this->_boxValue.setPosition({pos.x + 320, pos.y + 25});
    this->_boxValue.setSize({60, 50});
    this->_boxValue.setFillColor(sf::Color::Green);

    this->_text_value.setCharacterSize(20);
    this->_text_value.setFont(this->_font);
    this->_text_value.setString(to_string_float(this->_value + this->_scale.x, 1));
    this->_text_value.setOrigin({0, this->_text_value.getGlobalBounds().height + this->_text_value.getGlobalBounds().top});
    this->_text_value.setPosition({pos.x + 330, pos.y + 60});

    this->_name.setCharacterSize(20);
    this->_name.setFont(this->_font);
    this->_name.setString(name);
    this->_name.setOrigin({0, this->_name.getGlobalBounds().height + this->_name.getGlobalBounds().top});
    this->_name.setPosition({pos.x + 20, pos.y + 60});
}

void Button::draw(sf::RenderWindow &window)
{
    window.draw(this->_boxSlider);
    window.draw(this->_boxValue);
    window.draw(this->_name);
    window.draw(this->_text_value);
}

void Button::setValue(sf::Vector2i mousePos)
{
    if (this->_pos.contains({(float)mousePos.x, (float)mousePos.y})) {
        this->_value = (mousePos.x - this->_pos.left) * (this->_scale.y - this->_scale.x) / 200;
        this->_boxSlider.setSize({this->_value * 200 / (this->_scale.y - this->_scale.x), 50});
        this->_text_value.setString(to_string_float(this->_value + this->_scale.x, 1));
    }
}

float Button::getValue(void)
{
    return this->_value + this->_scale.x;
}
