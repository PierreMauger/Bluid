/*
** EPITECH PROJECT, 2022
** BLUID
** File description:
** bluid
*/

#include "Bluid.hpp"
#include "Button.hpp"

BluidEngine::BluidEngine(std::size_t size) : _fluid(size, 8, 0.2f, 0.0000001f, 0.0000001f)
{
    this->_window.create(sf::VideoMode(1920, 1080), "Bluid", sf::Style::Fullscreen);
    this->_window.setFramerateLimit(60);
    this->_lastPos = {0, 0};
    this->_actPos = {0, 0};
    this->_size = size;
    this->_buttonList.push_back(new Button({this->_window.getSize().x - 400.f,   0}, "diffusion", {0.000000001f, 0.0000009f}, 0.00000005f));
    this->_buttonList.push_back(new Button({this->_window.getSize().x - 400.f, 70}, "viscosity", {0.00000001f, 0.0000010f}, 0.0000001f));
    this->_buttonList.push_back(new Button({this->_window.getSize().x - 400.f, 140}, "timestep", {-1, 1}, 0.8));
    this->_buttonList.push_back(new Button({this->_window.getSize().x - 400.f, 210}, "iteration", {1, 12}, 4));
    this->_buf.create(size * size);
}

BluidEngine::~BluidEngine(void)
{
    for (Button *button : this->_buttonList)
        delete button;
    //add destructors
}

void BluidEngine::eventHandler(void)
{
    while (this->_window.pollEvent(this->_event)) {
        if (this->_event.type == sf::Event::Closed)
            this->_window.close();
        if (this->_event.type == sf::Event::KeyPressed)
            if (this->_event.key.code == sf::Keyboard::Escape)
                this->_window.close();
    }
    if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
        this->_lastPos = this->_actPos;
        this->_actPos = sf::Mouse::getPosition(this->_window);
        if (this->_actPos.x < (int)this->_size && this->_actPos.y < (int)this->_size) {
            this->_fluid.mouseDragged(_actPos, _lastPos);
        }
        for (Button *button : this->_buttonList) {
            button->setValue(this->_actPos);
        }
    }
    _fluid.step();
}

bool BluidEngine::isOpen()
{
    return this->_window.isOpen();
}

sf::RenderWindow &BluidEngine::getWindow(void)
{
    return this->_window;
}

sf::Vector2i BluidEngine::getActPos(void)
{
    return this->_actPos;
}

sf::Vector2i BluidEngine::getLastPos(void)
{
    return this->_lastPos;
}

void BluidEngine::draw(void)
{
    int color = 0;

    this->_window.clear(sf::Color::Black);
    for (Button *button : this->_buttonList)
        button->draw(this->_window);
    for (int j = 0; j < this->_size; j++) {
        for (int i = 0; i < this->_size; i++) {
            _vertices[IX(i, j, this->_size)].position = {(float)i, (float)j};
            color = 40 + (this->_fluid.getDensity(i, j) * 2000);
            _vertices[IX(i, j, this->_size)].color = {0, 0, (sf::Uint8)(color > 255 ? 255 : color)};
        }
    }
    this->_buf.update(this->_vertices);
    this->_window.draw(this->_buf);
    this->_window.display();
}
