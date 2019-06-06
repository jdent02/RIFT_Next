// Released under MIT License

// Copyright (c) 2018 Jonathan Dent.

// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:

// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.

// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#pragma once

#include <cmath>
#include <iostream>

class RGBColor
{
  public:
    RGBColor() = default;

    RGBColor(float e0, float e1, float e2);

    // Getters.
    float r() const { return m_e[0]; }

    float g() const { return m_e[1]; }

    float b() const { return m_e[2]; }

    // Operator overloads.
    const RGBColor& operator+() const { return *this; }

    RGBColor operator-() const { return {-m_e[0], -m_e[1], -m_e[2]}; }

    float operator[](const int i) const { return m_e[i]; }

    float& operator[](const int i) { return m_e[i]; }

    RGBColor& operator+=(const RGBColor& v2);

    RGBColor& operator-=(const RGBColor& v2);

    RGBColor& operator*=(const RGBColor& v2);

    RGBColor& operator/=(const RGBColor& v2);

    RGBColor& operator*=(float t);

    RGBColor& operator/=(float t);

    float m_e[3]{};
};

inline RGBColor& RGBColor::operator+=(const RGBColor& v2)
{
    m_e[0] += v2.m_e[0];
    m_e[1] += v2.m_e[1];
    m_e[2] += v2.m_e[2];
    return *this;
}

inline RGBColor& RGBColor::operator-=(const RGBColor& v2)
{
    m_e[0] -= v2.m_e[0];
    m_e[1] -= v2.m_e[1];
    m_e[2] -= v2.m_e[2];
    return *this;
}

inline RGBColor& RGBColor::operator*=(const RGBColor& v2)
{
    m_e[0] *= v2.m_e[0];
    m_e[1] *= v2.m_e[1];
    m_e[2] *= v2.m_e[2];
    return *this;
}

inline RGBColor& RGBColor::operator/=(const RGBColor& v2)
{
    m_e[0] /= v2.m_e[0];
    m_e[1] /= v2.m_e[1];
    m_e[2] /= v2.m_e[2];
    return *this;
}

inline RGBColor& RGBColor::operator*=(const float t)
{
    m_e[0] *= t;
    m_e[1] *= t;
    m_e[2] *= t;
    return *this;
}

inline RGBColor& RGBColor::operator/=(const float t)
{
    m_e[0] /= t;
    m_e[1] /= t;
    m_e[2] /= t;
    return *this;
}

inline RGBColor::RGBColor(const float e0, const float e1, const float e2)
{
    m_e[0] = e0;
    m_e[1] = e1;
    m_e[2] = e2;
}

// Non method operator overloads
inline std::istream& operator>>(std::istream& is, RGBColor& t)
{
    is >> t.m_e[0] >> t.m_e[1] >> t.m_e[2];
    return is;
}

inline std::ostream& operator<<(std::ostream& os, const RGBColor& t)
{
    os << t.m_e[0] << " " << t.m_e[1] << " " << t.m_e[2];
    return os;
}

inline RGBColor operator+(const RGBColor& v1, const RGBColor& v2)
{
    return RGBColor{
        v1.m_e[0] + v2.m_e[0], v1.m_e[1] + v2.m_e[1], v1.m_e[2] + v2.m_e[2]};
}

inline RGBColor operator-(const RGBColor& v1, const RGBColor& v2)
{
    return RGBColor{
        v1.m_e[0] - v2.m_e[0], v1.m_e[1] - v2.m_e[1], v1.m_e[2] - v2.m_e[2]};
}

inline RGBColor operator*(const RGBColor& v1, const RGBColor& v2)
{
    return RGBColor{
        v1.m_e[0] * v2.m_e[0], v1.m_e[1] * v2.m_e[1], v1.m_e[2] * v2.m_e[2]};
}

inline RGBColor operator/(const RGBColor& v1, const RGBColor& v2)
{
    return RGBColor{
        v1.m_e[0] / v2.m_e[0], v1.m_e[1] / v2.m_e[1], v1.m_e[2] / v2.m_e[2]};
}

inline RGBColor operator*(const float t, const RGBColor& v)
{
    return RGBColor{t * v.m_e[0], t * v.m_e[1], t * v.m_e[2]};
}

inline RGBColor operator/(const RGBColor& v, float const t)
{
    return RGBColor{v.m_e[0] / t, v.m_e[1] / t, v.m_e[2] / t};
}

inline RGBColor operator*(const RGBColor& v, const float t)
{
    return RGBColor{v.m_e[0] * t, v.m_e[1] * t, v.m_e[2] * t};
}