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
#include "core/data_types/accumulators/i_accumulator.h"
#include "core/data_types/containers/render_settings.h"
#include "core/data_types/containers/scene.h"
#include "core/data_types/tiles/tile_buffer.h"
#include "core/render_process/i_render_controller.h"
#include "core/render_process/tile_pool.h"
#include "utilities/rng/i_rand_generator.h"

class RenderThread
{
  public:
    RenderThread() = default;

    RenderThread(
        Scene*          scene,
        RenderSettings* render_settings,
        TilePool*       tile_pool,
        TileBuffer*     tile_buffer);

    void operator()();

    void render_tile(TileOutline& tile_outline);

    bool query_tile_pool();

    TileOutlinePackage get_tile();

  private:
    Scene*                                     m_scene_;
    RenderSettings*                            m_render_settings_;
    TilePool*                                  m_tile_pool_;
    TileBuffer*                                m_tile_buffer_;
    std::unique_ptr<IRandGenerator>            m_rng_;
    std::unique_ptr<ILightIntegrator>          m_lighting_integrator_;
    std::vector<std::unique_ptr<IAccumulator>> m_accumulators_;
};
