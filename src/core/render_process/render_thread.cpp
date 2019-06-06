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

#include "render_thread.h"

#include "core/data_types/accumulators/alpha_accumulator.h"
#include "core/data_types/accumulators/i_accumulator.h"
#include "core/data_types/accumulators/rgb_accumulator.h"
#include "utilities/rng/drand48.h"

#include <mutex>

RenderWorker::RenderWorker(
    const std::unique_ptr<Scene>&          scene,
    const std::unique_ptr<RenderSettings>& render_settings,
    std::unique_ptr<TileBuffer>&     tile_buffer,
    std::unique_ptr<TilePool>&       tile_pool,
    ILightIntegratorList&            integrator_list,
    IRandGeneratorList&              rng_list)
  : m_render_scene_(scene)
  , m_settings_(render_settings)
  , m_tile_buffer_(tile_buffer)
  , m_tile_pool_(tile_pool)
  , m_light_integrator_list_(integrator_list)
  , m_rng_list_(rng_list)
{}

void RenderWorker::execute(const uint64_t seed)
{
    std::unique_ptr<IRandGenerator> rng = m_rng_list_.get_integrator(m_settings_->m_rng)->create();

    std::vector<std::unique_ptr<IAccumulator>> accumulators;

    accumulators.emplace_back(std::make_unique<RgbAccumulator>());
    accumulators.emplace_back(std::make_unique<AlphaAccumulator>());

    std::unique_ptr<ILightIntegrator> lighting_integrator =
        m_light_integrator_list_.get_integrator(m_settings_->m_light_integrator)->create();

    rng->seed_gen(seed);

    if (query_tile_pool())
    {
        const TileOutline tile = m_tile_pool_->get_next_tile();
    }
}

bool RenderWorker::query_tile_pool() const
{
    return m_tile_pool_->get_pool_size() > 0;
}
