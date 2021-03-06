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

#include "rgb_color.h"

#include <vector>

class Pixel
{
  public:
    // Create greyscale pixel
    explicit Pixel(const float i)
    {
        m_pixel_data.reserve(1);

        m_pixel_data.push_back(i);
    }

    // Create RGB pixel
    Pixel(const float r, const float g, const float b)
    {
        m_pixel_data.reserve(3);

        m_pixel_data.push_back(r);
        m_pixel_data.push_back(g);
        m_pixel_data.push_back(b);
    }

    // Create RGBA pixel
    Pixel(const float r, const float g, const float b, const float a)
    {
        m_pixel_data.reserve(4);

        m_pixel_data.push_back(r);
        m_pixel_data.push_back(g);
        m_pixel_data.push_back(b);
        m_pixel_data.push_back(a);
    }

    // Create pixel from RGBColor
    explicit Pixel(const RGBColor& color_in)
    {
        m_pixel_data.reserve(3);

        m_pixel_data.push_back(color_in.r());
        m_pixel_data.push_back(color_in.g());
        m_pixel_data.push_back(color_in.b());
    }

    std::vector<float> m_pixel_data;
};
