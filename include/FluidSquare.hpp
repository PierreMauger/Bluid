/*
** EPITECH PROJECT, 2022
** BLUID
** File description:
** fluid
*/

#ifndef FLUID_HPP
#define FLUID_HPP

#define SIZE_BOUND 512
#define NBR_VALUES SIZE_BOUND * SIZE_BOUND

#define IX(x, y) (x + y * SIZE_BOUND)

#include <array>

class FluidSquare {

    public:
        FluidSquare(std::size_t iteration, float dt, float diffusion, float viscosity);
        ~FluidSquare() = default;

        void step(void);
        void addDensity(int x, int y, float amount);
        void addVelocity(int x, int y, float amountX, float amountY);

    private:
        // To delete
        // std::size_t _size;
        std::size_t _iteration;

        float _dt;
        float _diff;
        float _visc;

        std::array<float, NBR_VALUES> _s;
        std::array<float, NBR_VALUES> _density;

        std::array<float, NBR_VALUES> _Vx;
        std::array<float, NBR_VALUES> _Vy;

        std::array<float, NBR_VALUES> _Vx0;
        std::array<float, NBR_VALUES> _Vy0;

    private:

        void set_bound(int bound, std::array<float, NBR_VALUES> &bndValues);

        void diffuse(
            int bound,
            std::array<float, NBR_VALUES> &bndValues,
            std::array<float, NBR_VALUES> &bndValues0,
            float diff
        );

        void lin_solve(
            int bound,
            std::array<float, NBR_VALUES> &bndValues,
            std::array<float, NBR_VALUES> &bndValues0,
            float coef,
            float coef_all
        );

        void project(
            std::array<float, NBR_VALUES> &velocX,
            std::array<float, NBR_VALUES> &velocY,
            std::array<float, NBR_VALUES> &p,
            std::array<float, NBR_VALUES> &div
        );

};

#endif // FLUID_HPP
