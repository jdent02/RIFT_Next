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
#include "utilities/rng/i_rand_generator.h"

#include <string>
#include <thread>

struct RenderSettings
{
    int            m_threads{static_cast<int>(std::thread::hardware_concurrency())};
    int            m_xres{640};
    int            m_yres{640};
    int            m_tile_size{64};
    int            m_samples{32};
    std::string    m_output_path{"../out_tiles.jpg"};
    OutWriterEnum  m_output_writer{JPEG};
    RngEnum        m_rng{RAND_48};
    IntegratorEnum m_light_integrator{PATH_TRACING};
};
