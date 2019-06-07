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

#include "final_render_controller.h"

#include "core/data_types/tiles/tile_buffer.h"
#include "core/lighting_integrators/i_light_integrator_list.h"
#include "core/render_process/render_thread.h"
#include "core/render_process/tile_pool.h"

#include <ctime>
#include <thread>

struct FinalRenderController::Impl
{
    Impl(
        const std::unique_ptr<Scene>&          scene,
        const std::unique_ptr<RenderSettings>& settings,
        std::unique_ptr<TileBuffer>&           tile_buffer)
      : m_render_scene(scene)
      , m_settings(settings)
      , m_tile_buffer(tile_buffer)
    {}

    const std::unique_ptr<Scene>&          m_render_scene;
    const std::unique_ptr<RenderSettings>& m_settings;
    std::unique_ptr<TileBuffer>&           m_tile_buffer;
    TilePool                               m_tile_pool{};
    ILightIntegratorList                   m_light_integrator_list{};
    IRandGeneratorList                     m_rng_list{};
};

FinalRenderController::FinalRenderController(
    const std::unique_ptr<Scene>&          scene,
    const std::unique_ptr<RenderSettings>& settings,
    std::unique_ptr<TileBuffer>&           tile_buffer)
  : m_impl_(new Impl(scene, settings, tile_buffer))
{}

FinalRenderController::~FinalRenderController()
{
    delete m_impl_;
}

void FinalRenderController::render() const
{
    srand(static_cast<unsigned int>(time(nullptr)));

    m_impl_->m_tile_pool.create_pool(m_impl_->m_settings->m_xres, m_impl_->m_settings->m_yres, m_impl_->m_settings->m_tile_size);

    m_impl_->m_tile_buffer->set_number_of_tiles(m_impl_->m_tile_pool.get_pool_size());

    std::vector<std::thread> worker_threads;

    const int num_threads = m_impl_->m_settings->m_threads;

    worker_threads.reserve(num_threads);

    RenderWorker worker_template{m_impl_->m_render_scene,
                                 m_impl_->m_settings,
                                 m_impl_->m_tile_buffer,
                                 m_impl_->m_tile_pool,
                                 m_impl_->m_light_integrator_list,
                                 m_impl_->m_rng_list};

    for (int i = 0; i < m_impl_->m_settings->m_threads; ++i)
        worker_threads.emplace_back(
            std::thread(&RenderWorker::execute, &worker_template, static_cast<uint64_t>(rand())));

    for (auto& thread : worker_threads)
        thread.join();
}

void FinalRenderController::cleanup() {}

std::unique_ptr<IRenderController> FinalRenderControllerFactory::create(
    const std::unique_ptr<Scene>&          scene,
    const std::unique_ptr<RenderSettings>& settings,
    std::unique_ptr<TileBuffer>&           tile_buffer)
{
    return std::make_unique<FinalRenderController>(scene, settings, tile_buffer);
}
