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

#include "core/data_types/tiles/tile_buffer.h"

#include <vector>

struct RenderSettings;

enum OutBufferFormat
{
    SINGLE = 1,
    RGB = 3,
    RGBA = 4
};

class UnsignedCharBuffer
{
  public:
    UnsignedCharBuffer(int& x_res, int& y_res, const OutBufferFormat& format, RenderSettings* render_settings);

    void build_buffer(const TileBuffer* input_buffer);

    std::vector<unsigned char>& get_pixels();

    void clear_buffer();

  private:
    RenderSettings*            m_render_settings_;
    OutBufferFormat            m_format_;
    std::vector<unsigned char> m_pixels_;
};