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

#include "rgba_accumulator.h"

#include "core/data_types/buffers/rgba_buffer.h"

#include <memory>

void RgbaAccumulator::add_sample(
    HitRecord&     hrec,
    ScatterRecord& srec,
    Ray&           r,
    Ray&           scattered)
{}

std::unique_ptr<IBuffer> RgbaAccumulator::export_to_buffer()
{
    std::unique_ptr<RgbaBuffer> buffer = std::make_unique<RgbaBuffer>();

    const float inv_sample_count{1.f / m_samples_[0].size()};

    for (auto& pixel : m_samples_)
    {
        RGBColor out_pixel(0.f, 0.f, 0.f);
        for (auto& sample : pixel)
        {
            out_pixel += sample;
        }

        out_pixel /= inv_sample_count;

        buffer->get_pixels().emplace_back(
            out_pixel.r(), out_pixel.g(), out_pixel.b());
    }

    return buffer;
}
