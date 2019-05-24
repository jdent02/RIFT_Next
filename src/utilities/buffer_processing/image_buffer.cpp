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

#include "image_buffer.h"

ImageBuffer::ImageBuffer(int& x_res, int& y_res, const OutBufferFormat& format)
  : m_x_res_(x_res)
  , m_y_res_(y_res)
  , m_format_(format)
{
    const int pixel_count{x_res * y_res * format};
    m_pixels_.reserve(pixel_count);
    for (int x = 0; x < pixel_count; ++x)
        m_pixels_.emplace_back(0.f);
}

void ImageBuffer::build_buffer(const TileBuffer* input_buffer)
{
    for (auto& tile : input_buffer->get_tiles())
    {
        const int x_min = tile->m_x_min;
        const int x_max = tile->m_x_max;
        const int y_min = tile->m_y_min;
        const int y_max = tile->m_y_max;

        int pixel_index{0};

        for (int y = y_max - 1; y >= y_min; y--)
        {
            int buffer_start{m_x_res_ * m_format_ * y + x_min * m_format_};
            for (int x = x_min; x < x_max; x++)
            {
                Pixel& pixel = tile->get_layers().at(0)->get_pixels().at(pixel_index++);
                m_pixels_[buffer_start++] = pixel.get_channels()[0];
                m_pixels_[buffer_start++] = pixel.get_channels()[1];
                m_pixels_[buffer_start++] = pixel.get_channels()[2];
            }
        }
    }
}

std::vector<float>& ImageBuffer::get_pixels()
{
    return m_pixels_;
}

void ImageBuffer::clear_buffer()
{
    m_pixels_.clear();
}
