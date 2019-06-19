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

#include "unsigned_char_buffer.h"

#include "utilities/containers/render_settings.h"
#include "utilities/data_structures/pixel.h"
#include "utilities/maths/maths.h"

#include <cmath>

UnsignedCharBuffer::UnsignedCharBuffer(
    int&                                   x_res,
    int&                                   y_res,
    const OutBufferFormat&                 format,
    const std::unique_ptr<RenderSettings>& render_settings)
  : m_render_settings(render_settings)
  , m_format(format)
{
    const int pixel_count = x_res * y_res * format;
    m_pixels = std::vector<unsigned char>(pixel_count, 0);
}

void UnsignedCharBuffer::build_buffer(std::unique_ptr<TileBuffer>& input_buffer)
{
    for (auto& tile : input_buffer->get_tiles())
    {
        const int x_min = tile->m_x_min;
        const int x_max = tile->m_x_max;
        const int y_min = tile->m_y_min;
        const int y_max = tile->m_y_max;

        auto pixel_iterator = tile->get_layers().at(0)->m_pixels.begin();

        for (int y = y_max - 1; y >= y_min; y--)
        {
            int buffer_index =
                (m_render_settings->m_yres - 1 - y) * (m_render_settings->m_xres * m_format) + x_min * m_format;

            for (int x = x_min; x < x_max; x++)
            {
                Pixel& pixel = *pixel_iterator++;
                for (int i = 0; i < m_format; ++i)
                {
                    auto value = fast_sqrt(pixel.m_pixel_data.at(i)) * 254;
                    isnan(value) ? value = static_cast<unsigned char>(0) : value;
                    m_pixels[buffer_index++] = value;
                }
            }
        }
    }
}
