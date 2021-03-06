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

#include "utilities/color_utilities.h"
#include "utilities/containers/render_buffers/view.h"
#include "utilities/containers/tiles/image_tile.h"
#include "utilities/containers/tiles/tile_buffer.h"
#include "utilities/data_structures/pixel.h"
#include "utilities/data_structures/ray.h"

RenderWorker::RenderWorker(
    const std::unique_ptr<Scene>&          scene,
    const std::unique_ptr<RenderSettings>& render_settings,
    std::unique_ptr<TileBuffer>&           tile_buffer,
    TilePool&                              tile_pool,
    ILightIntegratorList&                  integrator_list,
    IRenderSamplerList&                    sampler_list)
  : m_render_scene_(scene)
  , m_settings_(render_settings)
  , m_tile_buffer_(tile_buffer)
  , m_tile_pool_(tile_pool)
  , m_light_integrator_list_(integrator_list)
  , m_sampler_list_(sampler_list)
{}

void RenderWorker::execute(const uint64_t seed) const
{
    const std::unique_ptr<ILightIntegrator> lighting_integrator =
        m_light_integrator_list_.get_integrator(m_settings_->m_light_integrator)->create();

    std::unique_ptr<IRenderSampler> sampler = m_sampler_list_.get_sampler(m_settings_->m_sampler)->create(seed);

    while (query_tile_pool())
    {
        const TileOutline tile = m_tile_pool_.get_next_tile();
        run_loop(tile, lighting_integrator, sampler);
    }
}

void RenderWorker::run_loop(
    const TileOutline                        tile,
    const std::unique_ptr<ILightIntegrator>& lighting_integrator,
    std::unique_ptr<IRenderSampler>&         sampler) const
{
    const float inv_nx = 1.f / float(m_settings_->m_xres);
    const float inv_ny = 1.f / float(m_settings_->m_xres);
    const float inv_samples = 1.f / static_cast<float>(m_settings_->m_samples);

    std::unique_ptr<View> view_convert = std::make_unique<View>();
    view_convert->reserve_buffer(m_settings_->m_xres, m_settings_->m_yres);

    for (int j = tile.y_max - 1; j >= tile.y_min; j--)
    {
        for (int i = tile.x_min; i < tile.x_max; i++)
        {
            RGBColor col(0.f, 0.f, 0.f);

            for (int s = 0; s < m_settings_->m_samples; s++)
            {
                const SampleOffset sample_offset = sampler->generate_sample_offset();

                const float u = (float(i) + sample_offset.m_offset_x) * inv_nx;
                const float v = (float(j) + sample_offset.m_offset_y) * inv_ny;

                Ray r = m_render_scene_->get_cam()->get_ray(u, v);

                col += de_nan(
                    lighting_integrator->trace(r, m_render_scene_->get_world(), m_render_scene_->get_lights(), 0));
            }

            col *= inv_samples;

            view_convert->m_pixels.emplace_back(Pixel(col));
        }
    }

    std::unique_ptr<ImageTile> out_tile = std::make_unique<ImageTile>(tile.x_min, tile.y_min, tile.x_max, tile.y_max);

    out_tile->add_layer(std::move(view_convert));

    m_tile_buffer_->add_tile(std::move(out_tile));
}

bool RenderWorker::query_tile_pool() const
{
    return m_tile_pool_.get_pool_size() > 0;
}
