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

#include "core/lighting_integrators/i_light_integrator.h"
#include "utilities/image_writers/i_out_writer.h"

#include <thread>

struct RenderSettings
{
    int m_threads{static_cast<int>(std::thread::hardware_concurrency())};
    int m_xres{1920};
    int m_yres{1080};
    int m_samples{100};
    IntegratorEnum m_light_integrator{PATH_TRACING};
    OutWriterEnum  m_output_writer{OPENIMAGEIO};
    const char*    m_output_filepath{"../../../image_vcpp.exr"};
};
