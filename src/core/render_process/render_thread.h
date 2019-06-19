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

#include "core/lighting_integrators/i_light_integrator_list.h"
#include "core/render_process/tile_pool.h"
#include "utilities/containers/render_settings.h"
#include "utilities/containers/scene.h"
#include "utilities/rng/i_rand_generator_list.h"

class RenderWorker
{
  public:
    RenderWorker(
        const std::unique_ptr<Scene>&          scene,
        const std::unique_ptr<RenderSettings>& render_settings,
        std::unique_ptr<TileBuffer>&           tile_buffer,
        TilePool&                              tile_pool,
        ILightIntegratorList&                  integrator_list,
        IRandGeneratorList&                    rng_list);

    void execute(uint64_t seed) const;

    void run_loop(
        TileOutline                              tile,
        const std::unique_ptr<ILightIntegrator>& lighting_integrator,
        std::unique_ptr<IRandGenerator>&         rng) const;

    bool query_tile_pool() const;

  private:
    const std::unique_ptr<Scene>&          m_render_scene_;
    const std::unique_ptr<RenderSettings>& m_settings_;
    std::unique_ptr<TileBuffer>&           m_tile_buffer_;
    TilePool&                              m_tile_pool_;
    ILightIntegratorList&                  m_light_integrator_list_;
    IRandGeneratorList&                    m_rng_list_;
};
