/*
** EPITECH PROJECT, 2022
** BLUID
** File description:
** ouais ouais ouais
*/

#include "Bluid.hpp"

void destroy();

int main(void)
{
    BluidEngine engine;
    sf::Vertex vertices[262144];
    sf::VertexBuffer buf(sf::Points, sf::VertexBuffer::Usage::Stream); //data stored in graphics memory (not re-transferred from system if not changed)

    buf.create(262144);
    while (engine.isOpen()) {
        engine.eventHandler();
        engine.getWindow().clear(sf::Color::Black);
        for (int i = 0; i < N; i++) {
            for (int j = 0, tmp; j < N; j++) {
                vertices[IX(i, j)].position = {i, j};
                vertices[IX(i, j)].color = {0, 0, (sf::Uint8)(20 - (engine.getDensity(i, j) * 10))};
                if (engine.getDensity(i, j) != 0)
                    std::cout << engine.getDensity(i, j) * 10 << std::endl;
            }
        }
        buf.update(vertices);
        engine.getWindow().draw(buf);
        engine.getWindow().display();
    }
    destroy();
    return 0;
}
