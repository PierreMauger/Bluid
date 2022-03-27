/*
** EPITECH PROJECT, 2022
** BLUID
** File description:
** bluid
*/

#include "Bluid.hpp"
#include "Button.hpp"

BluidEngine::BluidEngine(std::size_t size) : _fluid(size, 8, 0.2, 0.0000001f, 0.0000005f)
{
    this->_window.create(sf::VideoMode(1920, 1080), "Bluid", sf::Style::Fullscreen);
    this->_window.setFramerateLimit(60);
    this->_lastPos = {0, 0};
    this->_actPos = {0, 0};
    this->_size = size;
    this->_buttonList.push_back(new Button({this->_window.getSize().x - 400.f,   0}, "diffusion", {0.000000001f, 0.0000090f}, 0.0000001f));
    this->_buttonList.push_back(new Button({this->_window.getSize().x - 400.f, 70}, "viscosity", {0.00000000f, 0.0000100f}, 0.0000005f));
    this->_buttonList.push_back(new Button({this->_window.getSize().x - 400.f, 140}, "timestep", {0, 1}, 0.2));
    this->_buttonList.push_back(new Button({this->_window.getSize().x - 400.f, 210}, "iteration", {1, 12}, 8));
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
        if (this->_event.type == sf::Event::KeyPressed) {
            if (this->_event.key.code == sf::Keyboard::Escape)
                this->_window.close();
            if (this->_event.key.code == sf::Keyboard::R) {
                this->_fluid.setDiffusion(0.0000005f);
                this->_fluid.setDt(0.2);
                this->_fluid.setInteration(8);
                this->_buttonList[0]->setValue(0.0000001f);
                this->_buttonList[1]->setValue(0.0000005f);
                this->_buttonList[2]->setValue(0.2);
                this->_buttonList[3]->setValue(8);
            }
        }
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
        if (this->_buttonList[0]->getPos().contains({(float)_actPos.x, (float)_actPos.y}))
            this->_fluid.setDiffusion(this->_buttonList[0]->getValue());
        if (this->_buttonList[1]->getPos().contains({(float)_actPos.x, (float)_actPos.y}))
            this->_fluid.setVisc(this->_buttonList[1]->getValue());
        if (this->_buttonList[2]->getPos().contains({(float)_actPos.x, (float)_actPos.y}))
            this->_fluid.setDt(this->_buttonList[2]->getValue());
        if (this->_buttonList[3]->getPos().contains({(float)_actPos.x, (float)_actPos.y}))
            this->_fluid.setInteration(this->_buttonList[3]->getValue());
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
    for (std::size_t j = 0; j < this->_size; j++) {
        for (std::size_t i = 0; i < this->_size; i++) {
            _vertices[IX(i, j, this->_size)].position = {(float)i, (float)j};
            color = 40 + (this->_fluid.getDensity(i, j) * 2000);
            _vertices[IX(i, j, this->_size)].color = {0, 0, (sf::Uint8)(color > 255 ? 255 : color)};
        }
    }
    this->_buf.update(this->_vertices);
    this->_window.draw(this->_buf);
    this->_window.display();
}
