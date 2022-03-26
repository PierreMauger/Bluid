/*
** EPITECH PROJECT, 2022
** FluidSquare
** File description:
** FluidSquare
*/

#include "FluidSquare.hpp"

FluidSquare::FluidSquare(std::size_t iteration, float dt, float diffusion, float viscosity)
{
    this->_iteration = iteration;
    this->_dt = dt;
    this->_diff = diffusion;
    this->_visc = viscosity;
}

void FluidSquare::step(void)
{
    this->diffuse(1, this->_Vx0, this->_Vx, this->_visc);
    this->diffuse(2, this->_Vy0, this->_Vy, this->_visc);

    this->project(this->_Vx0, this->_Vy0, this->_Vx, this->_Vy);

    this->advect(1, this->_Vx, this->_Vx0, this->_Vx0, this->_Vy0);
    this->advect(2, this->_Vy, this->_Vy0, this->_Vx0, this->_Vy0);

    this->project(this->_Vx, this->_Vy, this->_Vx0, this->_Vy0);

    this->diffuse(0, this->_s, this->_density, this->_diff);
    this->advect(0, this->_density, this->_s, this->_Vx, this->_Vy);
}

void FluidSquare::addDensity(int x, int y, float amount)
{
    this->_density[IX(x, y)] += amount;
}

void FluidSquare::addVelocity(int x, int y, float amountX, float amountY)
{
    std::size_t index = IX(x, y);

    this->_Vx[index] += amountX;
    this->_Vy[index] += amountY;
}

void FluidSquare::set_bound(int bound, std::array<float, NBR_VALUES> &bndValues)
{
    for (int i = 1; i < SIZE_BOUND - 1; i++) {
        bndValues[IX(i, 0)] = bound == 2 ? -1 * bndValues[IX(i, 1)] : bndValues[IX(i, 1)];
        bndValues[IX(i, SIZE_BOUND - 1)] = bound == 2 ? -1 * bndValues[IX(i, SIZE_BOUND - 2)] : bndValues[IX(i, SIZE_BOUND - 2)];
    }
    for (int j = 1; j < SIZE_BOUND - 1; j++) {
        bndValues[IX(0, j)] = bound == 1 ? -1 * bndValues[IX(1, j)] : bndValues[IX(1, j)];
        bndValues[IX(SIZE_BOUND - 1, j)] = bound == 1 ? -1 * bndValues[IX(SIZE_BOUND - 2, j)] : bndValues[IX(SIZE_BOUND - 2, j)];
    }
    bndValues[IX(0, 0)] = 0.5f * (bndValues[IX(1, 0)] + bndValues[IX(0, 1)]);
    bndValues[IX(0, SIZE_BOUND - 1)] = 0.5f * (bndValues[IX(1, SIZE_BOUND - 1)] + bndValues[IX(0, SIZE_BOUND - 2)]);
    bndValues[IX(SIZE_BOUND - 1, 0)] = 0.5f * (bndValues[IX(SIZE_BOUND - 2, 0)] + bndValues[IX(SIZE_BOUND - 1, 1)]);
    bndValues[IX(SIZE_BOUND - 1, SIZE_BOUND - 1)] = 0.5f * (bndValues[IX(SIZE_BOUND - 2, SIZE_BOUND - 1)] + bndValues[IX(SIZE_BOUND - 1, SIZE_BOUND - 2)]);
}

void FluidSquare::diffuse(
    int bound,
    std::array<float, NBR_VALUES> &bndValues,
    std::array<float, NBR_VALUES> &bndValues0,
    float diff
)
{
    float coef = this->_dt * diff * (SIZE_BOUND - 2) * (SIZE_BOUND - 2);

    this->lin_solve(bound, bndValues, bndValues0, coef, 1 + 4 * coef);
}

void FluidSquare::lin_solve(
    int bound,
    std::array<float, NBR_VALUES> &bndValues,
    std::array<float, NBR_VALUES> &bndValues0,
    float coef,
    float coef_all
)
{
    std::size_t toBrowse = SIZE_BOUND - 1;
    float cRecip = 1.0 / coef_all;

    for (int k = 0; k < this->_iteration; k++) {
        for (int j = 1; j < toBrowse; j++) {
            for (int i = 1; i < toBrowse; i++) {
                bndValues[IX(i, j)] = (
                    bndValues0[IX(i, j)] + coef * (
                        bndValues[IX(i + 1, j)] +
                        bndValues[IX(i - 1, j)] +
                        bndValues[IX(i, j + 1)] +
                        bndValues[IX(i, j - 1)]
                    )
                ) * cRecip;
            }
        }
        this->set_bound(bound, bndValues);
    }
}

void FluidSquare::project(
    std::array<float, NBR_VALUES> &velocX,
    std::array<float, NBR_VALUES> &velocY,
    std::array<float, NBR_VALUES> &p,
    std::array<float, NBR_VALUES> &div
)
{
    std::size_t toBrowse = SIZE_BOUND - 1;

    for (int j = 1; j < toBrowse; j++) {
        for (int i = 1; i < toBrowse; i++) {
            div[IX(i, j)] = -0.5f * (
                velocX[IX(i + 1, j)] -
                velocX[IX(i - 1, j)] +
                velocY[IX(i, j + 1)] -
                velocY[IX(i, j - 1)]
            ) / SIZE_BOUND;
            p[IX(i, j)] = 0;
        }
    }
    this->set_bound(0, div);
    this->set_bound(0, p);
    this->lin_solve(0, p, div, 1, 4);
    for (int j = 1; j < toBrowse; j++) {
        for (int i = 1; i < toBrowse; i++) {
            velocX[IX(i, j)] -= 0.5f * (p[IX(i + 1, j)] - p[IX(i - 1, j)]) * SIZE_BOUND;
            velocY[IX(i, j)] -= 0.5f * (p[IX(i, j + 1)] - p[IX(i, j - 1)]) * SIZE_BOUND;
        }
    }
    this->set_bound(1, velocX);
    this->set_bound(2, velocY);
}
