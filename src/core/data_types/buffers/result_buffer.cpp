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

#include "rgba_buffer.h"

#include "core/data_types/pixel_types/pixel.h"
#include "core/data_types/vec3.h"

#include <vector>

struct RgbaBuffer::Impl
{
    std::vector<Pixel> m_pixels;
};

RgbaBuffer::RgbaBuffer()
  : m_impl_(new Impl)
{}

RgbaBuffer::~RgbaBuffer()
{
    delete m_impl_;
}

void RgbaBuffer::reserve_buffer(const int x_res, const int y_res) const
{
    const int pixel_count = x_res * y_res;
    m_impl_->m_pixels.reserve(pixel_count);
}

std::vector<Pixel>& RgbaBuffer::get_pixels() const
{
    return m_impl_->m_pixels;
}

std::unique_ptr<RgbaBuffer> RgbaBufferFactory::create()
{
    return std::unique_ptr<RgbaBuffer>();
}