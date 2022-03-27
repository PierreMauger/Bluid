/*
** EPITECH PROJECT, 2022
** BLUID
** File description:
** bluid
*/

#include "Bluid.hpp"
#include "Button.hpp"

BluidEngine::BluidEngine(std::size_t size, std::size_t scale) : _vertices(size * size * scale * scale) ,_fluid(size, 4, 0.2f, 0.0000001f, 0.0000001f, 0.99)
{
    this->_window.create(sf::VideoMode(1920, 1080), "Bluid", sf::Style::Fullscreen);
    this->_window.setFramerateLimit(60);
    this->_lastPos = {0, 0};
    this->_actPos = {0, 0};
    this->_size = size;
    this->_scale = scale;
    this->_buttonList.push_back(new Button({this->_window.getSize().x - 400.f,   0}, "diffusion", {0.000000001f, 0.0000090f}, 0.0000001f));
    this->_buttonList.push_back(new Button({this->_window.getSize().x - 400.f,  70}, "viscosity", {0.00000000f, 0.0000100f}, 0.0000005f));
    this->_buttonList.push_back(new Button({this->_window.getSize().x - 400.f, 280}, "fading", {0.9, 1}, 0.99));
    this->_buttonList.push_back(new Button({this->_window.getSize().x - 400.f, 140}, "timestep", {0.01, 1}, 0.2));
    this->_buttonList.push_back(new Button({this->_window.getSize().x - 400.f, 210}, "realism", {1, 12}, 4));
    this->_buf.create(size * size * scale * scale);
    this->_logoTexture.loadFromFile("ressources/logo.png");
    this->_logoSprite.setTexture(this->_logoTexture);
    this->_logoSprite.setPosition({this->_window.getSize().x - 300.f, 400});
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
                this->_fluid.setDiffusion(0.0000009f);
                this->_fluid.setVisc(0.0000003f);
                this->_fluid.setFade(0.99);
                this->_fluid.setDt(0.2);
                this->_fluid.setIteration(4);
                this->_buttonList[0]->setValue(0.0000009f);
                this->_buttonList[1]->setValue(0.0000003f);
                this->_buttonList[2]->setValue(0.99);
                this->_buttonList[3]->setValue(0.2);
                this->_buttonList[4]->setValue(4);
            }
        }
    }
    if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
        this->_lastPos = this->_actPos;
        this->_actPos = sf::Mouse::getPosition(this->_window);
        if (this->_actPos.x < (int)this->_size * (int)this->_scale && this->_actPos.y < (int)this->_size * (int)this->_scale) {
            this->_fluid.mouseDragged(
                {_actPos.x / (int)this->_scale, _actPos.y / (int)this->_scale},
                {_lastPos.x / (int)this->_scale, _lastPos.y / (int)this->_scale}
            );
        }
        for (Button *button : this->_buttonList) {
            button->setValue(this->_actPos);
        }
        if (this->_buttonList[0]->getPos().contains({(float)_actPos.x, (float)_actPos.y}))
            this->_fluid.setDiffusion(this->_buttonList[0]->getValue());
        if (this->_buttonList[1]->getPos().contains({(float)_actPos.x, (float)_actPos.y}))
            this->_fluid.setVisc(this->_buttonList[1]->getValue());
        if (this->_buttonList[2]->getPos().contains({(float)_actPos.x, (float)_actPos.y}))
            this->_fluid.setFade(this->_buttonList[2]->getValue());
        if (this->_buttonList[3]->getPos().contains({(float)_actPos.x, (float)_actPos.y}))
            this->_fluid.setDt(this->_buttonList[3]->getValue());
        if (this->_buttonList[4]->getPos().contains({(float)_actPos.x, (float)_actPos.y}))
            this->_fluid.setIteration(this->_buttonList[4]->getValue());
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

    this->_window.clear(sf::Color(0, 0, 30));
    for (int j = 0; j < (int)this->_size; j++) {
        for (int i = 0; i < (int)this->_size; i++) {
            color = 40 + (this->_fluid.getDensity(i, j) * 2000);
            for (int y = 0; y < (int)this->_scale; y++) {
                for (int x = 0; x < (int)this->_scale; x++) {
                    _vertices[IX(i * this->_scale + x, j * this->_scale + y, this->_size * this->_scale)].position = {(float)(i * this->_scale + x), (float)(j * this->_scale + y)};
                    _vertices[IX(i * this->_scale + x, j * this->_scale + y, this->_size * this->_scale)].color = {0, 0, (sf::Uint8)(color > 255 ? 255 : color)};
                }
            }
        }
    }
    for (Button *button : this->_buttonList)
        button->draw(this->_window);
    this->_buf.update(&this->_vertices[0]);
    this->_window.draw(this->_buf);
    for (Button *button : this->_buttonList)
        button->draw(this->_window);
    this->_window.draw(this->_logoSprite);
    this->_window.display();
}
