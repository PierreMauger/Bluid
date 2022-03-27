#include "Button.hpp"

std::string Button::to_string_float(float value)
{
    std::ostringstream out;

    out.precision(2);
    out << std::fixed << value;
    if (std::atof(out.str().c_str()) == 0.00 && std::atof(out.str().c_str()) == -0.00) {
        std::stringstream buffer;
        buffer << std::setprecision(0) << std::scientific << value;
        return buffer.str();
    }
    return out.str();
}

Button::Button(sf::Vector2f pos, std::string name, sf::Vector2f scale, float value)
{
    this->_scale = scale;
    this->_value = value - scale.x;
    this->_font.loadFromFile("ressources/Blue.ttf");

    this->_tempBox.setPosition({pos.x, pos.y});
    this->_tempBox.setSize({400, 100});
    this->_tempBox.setFillColor(sf::Color(0, 200, 200));
    this->_tempBox.setOutlineThickness(1);

    this->_emptyBox.setPosition({pos.x + 100, pos.y + 25});
    this->_emptyBox.setSize({200, 50});
    this->_emptyBox.setOutlineThickness(2);
    this->_emptyBox.setOutlineColor(sf::Color(0, 0, 255));
    this->_emptyBox.setFillColor(sf::Color(0, 0, 0, 0));

    this->_boxSlider.setPosition({pos.x + 100, pos.y + 25});
    this->_boxSlider.setSize({this->_value * 200 / (this->_scale.y - this->_scale.x), 50});
    this->_boxSlider.setFillColor(sf::Color(30, 150, 255));

    this->_pos = {this->_boxSlider.getPosition().x, this->_boxSlider.getPosition().y, 200, 50};

    this->_boxValue.setPosition({pos.x + 320, pos.y + 25});
    this->_boxValue.setSize({60, 50});
    this->_boxValue.setOutlineColor(sf::Color(0, 0, 255));
    this->_boxValue.setFillColor(sf::Color(135, 206, 240));
    this->_boxValue.setOutlineThickness(2);

    this->_textValue.setCharacterSize(20);
    this->_textValue.setFont(this->_font);
    this->_textValue.setFillColor(sf::Color(0, 0, 255));
    this->_textValue.setString(this->to_string_float(this->_value + this->_scale.x));
    this->_textValue.setOrigin({this->_textValue.getGlobalBounds().width / 2 + this->_textValue.getGlobalBounds().left, this->_textValue.getGlobalBounds().height + this->_textValue.getGlobalBounds().top});
    this->_textValue.setPosition({_boxValue.getGlobalBounds().left + (_boxValue.getGlobalBounds().width / 2), pos.y + 60});

    this->_name.setCharacterSize(20);
    this->_name.setFont(this->_font);
    this->_name.setFillColor(sf::Color(0, 0, 255));
    this->_name.setString(name);
    this->_name.setOrigin({0, this->_name.getGlobalBounds().height + this->_name.getGlobalBounds().top});
    this->_name.setPosition({pos.x, pos.y + 60});
}

void Button::draw(sf::RenderWindow &window)
{
    window.draw(this->_boxSlider);
    window.draw(this->_boxValue);
    window.draw(this->_name);
    window.draw(this->_textValue);
    window.draw(this->_emptyBox);
}

void Button::setValue(sf::Vector2i mousePos)
{
    if (this->_pos.contains({(float)mousePos.x, (float)mousePos.y})) {
        this->_value = (mousePos.x - this->_pos.left) * (this->_scale.y - this->_scale.x) / 200;
        this->_boxSlider.setSize({this->_value * 200 / (this->_scale.y - this->_scale.x), 50});
        this->_textValue.setString(to_string_float(this->_value + this->_scale.x));
    }
}

void Button::setValue(float value)
{
    this->_value = value - this->_scale.x;
    this->_boxSlider.setSize({this->_value * 200 / (this->_scale.y - this->_scale.x), 50});
    this->_textValue.setString(to_string_float(this->_value + this->_scale.x));
}

float Button::getValue(void)
{
    return this->_value + this->_scale.x;
}

sf::FloatRect Button::getPos(void)
{
    return this->_pos;
}
