/*
** EPITECH PROJECT, 2022
** FluidSquare
** File description:
** FluidSquare
*/

#include "FluidSquare.hpp"

FluidSquare::FluidSquare(int iteration, float dt, float diffusion, float viscosity)
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
    int toBrowse = SIZE_BOUND - 1;
    int minusTwo = SIZE_BOUND - 2;

    for (int i = 1; i < toBrowse; i++) {
        bndValues[IX(i, 0)] = bound == 2 ? -1 * bndValues[IX(i, 1)] : bndValues[IX(i, 1)];
        bndValues[IX(i, toBrowse)] = bound == 2 ? -1 * bndValues[IX(i, minusTwo)] : bndValues[IX(i, minusTwo)];
    }
    for (int j = 1; j < toBrowse; j++) {
        bndValues[IX(0, j)] = bound == 1 ? -1 * bndValues[IX(1, j)] : bndValues[IX(1, j)];
        bndValues[IX(toBrowse, j)] = bound == 1 ? -1 * bndValues[IX(minusTwo, j)] : bndValues[IX(minusTwo, j)];
    }
    bndValues[IX(0, 0)] = 0.5f * (bndValues[IX(1, 0)] + bndValues[IX(0, 1)]);
    bndValues[IX(0, toBrowse)] = 0.5f * (bndValues[IX(1, toBrowse)] + bndValues[IX(0, minusTwo)]);
    bndValues[IX(toBrowse, 0)] = 0.5f * (bndValues[IX(minusTwo, 0)] + bndValues[IX(toBrowse, 1)]);
    bndValues[IX(toBrowse, toBrowse)] = 0.5f * (bndValues[IX(minusTwo, toBrowse)] + bndValues[IX(toBrowse, minusTwo)]);
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
    int toBrowse = SIZE_BOUND - 1;
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

void FluidSquare::projectVelocValues(
    int toBrowse,
    std::array<float, NBR_VALUES> &velocX,
    std::array<float, NBR_VALUES> &velocY,
    std::array<float, NBR_VALUES> &p
)
{
    for (int j = 1; j < toBrowse; j++) {
        for (int i = 1; i < toBrowse; i++) {
            velocX[IX(i, j)] -= 0.5f * (p[IX(i + 1, j)] - p[IX(i - 1, j)]) * SIZE_BOUND;
            velocY[IX(i, j)] -= 0.5f * (p[IX(i, j + 1)] - p[IX(i, j - 1)]) * SIZE_BOUND;
        }
    }
    this->set_bound(1, velocX);
    this->set_bound(2, velocY);
}

void FluidSquare::projectVelocBounds(
    int toBrowse,
    std::array<float, NBR_VALUES> &velocX,
    std::array<float, NBR_VALUES> &velocY,
    std::array<float, NBR_VALUES> &p,
    std::array<float, NBR_VALUES> &div
)
{
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
}

void FluidSquare::project(
    std::array<float, NBR_VALUES> &velocX,
    std::array<float, NBR_VALUES> &velocY,
    std::array<float, NBR_VALUES> &p,
    std::array<float, NBR_VALUES> &div
)
{
    int toBrowse = SIZE_BOUND - 1;

    this->projectVelocBounds(toBrowse, velocX, velocY, p, div);
    this->projectVelocValues(toBrowse, velocX, velocY, p);
}

float FluidSquare::setCoordValue(float coord, float freq, float caseVal)
{
    float res = coord - freq * caseVal;

    if (res < 0.5f) {
        res = 0.5f;
    }
    else if (res > SIZE_BOUND + 0.5f) {
        res = SIZE_BOUND + 0.5f;
    }
    return res;
}

void FluidSquare::advect(
    int bound,
    std::array<float, NBR_VALUES> &d,
    std::array<float, NBR_VALUES> &d0,
    std::array<float, NBR_VALUES> &velocX,
    std::array<float, NBR_VALUES> &velocY
)
{
    float i0 = 0;
    float i1 = 0;
    float j0 = 0;
    float j1 = 0;
    float dtx = this->_dt * (SIZE_BOUND - 2);
    float dty = this->_dt * (SIZE_BOUND - 2);
    float s0 = 0;
    float s1 = 0;
    float t0 = 0;
    float t1 = 0;
    float x = 0;
    float y = 0;
    float ifloat = 1;
    float jfloat = 1;

    for (int j = 1; j < SIZE_BOUND - 1; j++, jfloat++) {
        for (int i = 1; i < SIZE_BOUND - 1; i++, ifloat++) {
            x = setCoordValue(ifloat, dtx, velocX[IX(i, j)]);
            y = setCoordValue(jfloat, dty, velocY[IX(i, j)]);

            i0 = int(x);
            i1 = i0 + 1.0f;
            j0 = int(y);
            j1 = j0 + 1.0f;
            s1 = x - i0;
            s0 = 1.0f - s1;
            t1 = y - j0;
            t0 = 1.0f - t1;

            d[IX(i, j)] =
                s0 * (t0 * d0[IX(int(i0), int(j0))] +
                t1 * d0[IX(int(i0), int(j1))]) +
                s1 * (t0 * d0[IX(int(i1), int(j0))] +
                t1 * d0[IX(int(i1), int(j1))]);
        }
    }
    set_bound(bound, d);
}
