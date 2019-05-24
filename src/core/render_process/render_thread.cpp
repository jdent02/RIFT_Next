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

bool query_tile_pool(TilePool* tile_pool, std::mutex& mutex)
{
    std::lock_guard<std::mutex> lock(mutex);

    return tile_pool->get_pool_size() > 0;
}

void run_renderer(
    std::mutex&           mutex,
    const uint64_t        seed,
    Scene*                scene,
    RenderSettings*       render_settings,
    TilePool*             tile_pool,
    TileBuffer*           tile_buffer,
    ILightIntegratorList& integrator_list,
    IRandGeneratorList&   rng_list)
{
    std::unique_ptr<IRandGenerator> rng = rng_list.get_integrator(render_settings->m_rng)->create();

    std::vector<std::unique_ptr<IAccumulator>> accumulators;
    
    accumulators.emplace_back(std::make_unique<RgbAccumulator>());
    accumulators.emplace_back(std::make_unique<AlphaAccumulator>());

    std::unique_ptr<ILightIntegrator> lighting_integrator =
        integrator_list.get_integrator(render_settings->m_light_integrator)->create();

    rng->seed_gen(seed);

    if (query_tile_pool(tile_pool, mutex))
    {
        std::lock_guard<std::mutex> lock(mutex);

        const TileOutlinePackage package = tile_pool->get_next_tile();

        std::cout << "\nX = " << package.m_tile_outline.x_min << " " << package.m_tile_outline.x_max << "\n"
                  << "X = " << package.m_tile_outline.y_min << " " << package.m_tile_outline.y_max << "\n";
    }
}
