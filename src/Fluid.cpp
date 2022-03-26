/*
** EPITECH PROJECT, 2022
** FluidSquare
** File description:
** FluidSquare
*/

#include "FluidSquare.hpp"

FluidSquare::FluidSquare(int size, int iteration, float dt, float diffusion, float viscosity) :
_s(size * size, 0),
_density(size * size, 0),
_Vx(size * size, 0),
_Vy(size * size, 0),
_Vx0(size * size, 0),
_Vy0(size * size, 0)
{
    this->_size = size;
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

void FluidSquare::set_bound(int bound, std::vector<float> &bndValues)
{
    int toBrowse = this->_size - 1;
    int minusTwo = this->_size - 2;

    for (int i = 1; i < toBrowse; i++) {
        bndValues[IX(i, 0, this->_size)] = bound == 2 ? -1 * bndValues[IX(i, 1, this->_size)] : bndValues[IX(i, 1, this->_size)];
        bndValues[IX(i, toBrowse, this->_size)] = bound == 2 ? -1 * bndValues[IX(i, minusTwo, this->_size)] : bndValues[IX(i, minusTwo, this->_size)];
    }
    for (int j = 1; j < toBrowse; j++) {
        bndValues[IX(0, j, this->_size)] = bound == 1 ? -1 * bndValues[IX(1, j, this->_size)] : bndValues[IX(1, j, this->_size)];
        bndValues[IX(toBrowse, j, this->_size)] = bound == 1 ? -1 * bndValues[IX(minusTwo, j, this->_size)] : bndValues[IX(minusTwo, j, this->_size)];
    }
    bndValues[IX(0, 0, this->_size)] = 0.5f * (bndValues[IX(1, 0, this->_size)] + bndValues[IX(0, 1, this->_size)]);
    bndValues[IX(0, toBrowse, this->_size)] = 0.5f * (bndValues[IX(1, toBrowse, this->_size)] + bndValues[IX(0, minusTwo, this->_size)]);
    bndValues[IX(toBrowse, 0, this->_size)] = 0.5f * (bndValues[IX(minusTwo, 0, this->_size)] + bndValues[IX(toBrowse, 1, this->_size)]);
    bndValues[IX(toBrowse, toBrowse, this->_size)] = 0.5f * (bndValues[IX(minusTwo, toBrowse, this->_size)] + bndValues[IX(toBrowse, minusTwo, this->_size)]);
}

void FluidSquare::diffuse(
    int bound,
    std::vector<float> &bndValues,
    std::vector<float> &bndValues0,
    float diff
)
{
    float coef = this->_dt * diff * (this->_size - 2) * (this->_size - 2);

    this->lin_solve(bound, bndValues, bndValues0, coef, 1 + 4 * coef);
}

void FluidSquare::lin_solve(
    int bound,
    std::vector<float> &bndValues,
    std::vector<float> &bndValues0,
    float coef,
    float coef_all
)
{
    int toBrowse = this->_size - 1;
    float cRecip = 1.0 / coef_all;

    for (int k = 0; k < this->_iteration; k++) {
        for (int j = 1; j < toBrowse; j++) {
            for (int i = 1; i < toBrowse; i++) {
                bndValues[IX(i, j, this->_size)] = (
                    bndValues0[IX(i, j, this->_size)] + coef * (
                        bndValues[IX(i + 1, j, this->_size)] +
                        bndValues[IX(i - 1, j, this->_size)] +
                        bndValues[IX(i, j + 1, this->_size)] +
                        bndValues[IX(i, j - 1, this->_size)]
                    )
                ) * cRecip;
            }
        }
        this->set_bound(bound, bndValues);
    }
}

void FluidSquare::projectVelocValues(
    int toBrowse,
    std::vector<float> &velocX,
    std::vector<float> &velocY,
    std::vector<float> &p
)
{
    for (int j = 1; j < toBrowse; j++) {
        for (int i = 1; i < toBrowse; i++) {
            velocX[IX(i, j, this->_size)] -= 0.5f * (p[IX(i + 1, j, this->_size)] - p[IX(i - 1, j, this->_size)]) * this->_size;
            velocY[IX(i, j, this->_size)] -= 0.5f * (p[IX(i, j + 1, this->_size)] - p[IX(i, j - 1, this->_size)]) * this->_size;
        }
    }
    this->set_bound(1, velocX);
    this->set_bound(2, velocY);
}

void FluidSquare::projectVelocBounds(
    int toBrowse,
    std::vector<float> &velocX,
    std::vector<float> &velocY,
    std::vector<float> &p,
    std::vector<float> &div
)
{
    for (int j = 1; j < toBrowse; j++) {
        for (int i = 1; i < toBrowse; i++) {
            div[IX(i, j, this->_size)] = -0.5f * (
                velocX[IX(i + 1, j, this->_size)] -
                velocX[IX(i - 1, j, this->_size)] +
                velocY[IX(i, j + 1, this->_size)] -
                velocY[IX(i, j - 1, this->_size)]
            ) / this->_size;
            p[IX(i, j, this->_size)] = 0;
        }
    }
    this->set_bound(0, div);
    this->set_bound(0, p);
    this->lin_solve(0, p, div, 1, 4);
}

void FluidSquare::project(
    std::vector<float> &velocX,
    std::vector<float> &velocY,
    std::vector<float> &p,
    std::vector<float> &div
)
{
    int toBrowse = this->_size - 1;

    this->projectVelocBounds(toBrowse, velocX, velocY, p, div);
    this->projectVelocValues(toBrowse, velocX, velocY, p);
}

float FluidSquare::setCoordValue(float coord, float freq, float caseVal)
{
    float res = coord - freq * caseVal;

    if (res < 0.5f) {
        res = 0.5f;
    }
    else if (res > this->_size + 0.5f) {
        res = this->_size + 0.5f;
    }
    return res;
}

void FluidSquare::advect(
    int bound,
    std::vector<float> &d,
    std::vector<float> &d0,
    std::vector<float> &velocX,
    std::vector<float> &velocY
)
{
    float i0 = 0;
    float i1 = 0;
    float j0 = 0;
    float j1 = 0;
    float dtx = this->_dt * (this->_size - 2);
    float dty = this->_dt * (this->_size - 2);
    float s0 = 0;
    float s1 = 0;
    float t0 = 0;
    float t1 = 0;
    float x = 0;
    float y = 0;
    float ifloat = 1;
    float jfloat = 1;

    for (int j = 1; j < this->_size - 1; j++, jfloat++) {
        for (int i = 1; i < this->_size - 1; i++, ifloat++) {
            x = setCoordValue(ifloat, dtx, velocX[IX(i, j, this->_size)]);
            y = setCoordValue(jfloat, dty, velocY[IX(i, j, this->_size)]);

            i0 = int(x);
            i1 = i0 + 1.0f;
            j0 = int(y);
            j1 = j0 + 1.0f;
            s1 = x - i0;
            s0 = 1.0f - s1;
            t1 = y - j0;
            t0 = 1.0f - t1;

            d[IX(i, j, this->_size)] =
                s0 * (t0 * d0[IX(int(i0), int(j0), this->_size)] +
                t1 * d0[IX(int(i0), int(j1), this->_size)]) +
                s1 * (t0 * d0[IX(int(i1), int(j0), this->_size)] +
                t1 * d0[IX(int(i1), int(j1), this->_size)]);
        }
    }
    set_bound(bound, d);
}

void FluidSquare::mouseDragged(sf::Vector2i actPos, sf::Vector2i lastPos)
{
    _density[IX(actPos.x, actPos.y, this->_size)] += 100;
    _Vx[IX(actPos.x, actPos.y, this->_size)] += actPos.x - lastPos.x;
    _Vy[IX(actPos.x, actPos.y, this->_size)] += actPos.y - lastPos.y;
}

float FluidSquare::getDensity(int i, int j)
{
    return _density[IX(i, j, this->_size)];
}
