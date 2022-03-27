/*
** EPITECH PROJECT, 2022
** BLUID
** File description:
** fluid
*/

#ifndef FLUID_HPP
#define FLUID_HPP

#define IX(x, y, size) ((x) + ((y) * (size)))

#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>

class FluidSquare {

    public:
        FluidSquare(int size, int iteration, float dt, float diffusion, float viscosity, float fade);
        virtual ~FluidSquare() = default;

        void step(void);
        void mouseDragged(sf::Vector2i actPos, sf::Vector2i lastPos);
        float getDensity(int i, int j);
        void setDiffusion(float diff);
        void setFade(float fade);
        void setDt(float dt);
        void setVisc(float visc);
        void setIteration(int it);

    private:
        int _size;
        int _iteration;

        float _dt;
        float _diff;
        float _visc;
        float _fade;

        std::vector<float> _s;
        std::vector<float> _density;

        std::vector<float> _Vx;
        std::vector<float> _Vy;

        std::vector<float> _Vx0;
        std::vector<float> _Vy0;

    private:

        void set_bound(int bound, std::vector<float> &bndValues);

        void diffuse(
            int bound,
            std::vector<float> &bndValues,
            std::vector<float> &bndValues0,
            float diff
        );

        void lin_solve(
            int bound,
            std::vector<float> &bndValues,
            std::vector<float> &bndValues0,
            float coef,
            float coef_all
        );

        void projectVelocValues(
            int toBrowse,
            std::vector<float> &velocX,
            std::vector<float> &velocY,
            std::vector<float> &p
        );
        void projectVelocBounds(
            int toBrowse,
            std::vector<float> &velocX,
            std::vector<float> &velocY,
            std::vector<float> &p,
            std::vector<float> &div
        );
        void project(
            std::vector<float> &velocX,
            std::vector<float> &velocY,
            std::vector<float> &p,
            std::vector<float> &div
        );

        float setCoordValue(float coord, float freq, float caseVal);
        float filterVal(float val);
        void advect(
            int b,
            std::vector<float> &d,
            std::vector<float> &d0,
            std::vector<float> &velocX,
            std::vector<float> &velocY
        );
};

#endif // FLUID_HPP
