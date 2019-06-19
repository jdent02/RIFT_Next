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

#include "test_render_controller.h"

#include "utilities/containers/render_buffers/view.h"
#include "utilities/containers/render_settings.h"
#include "utilities/containers/tiles/image_tile.h"
#include "utilities/containers/tiles/tile_buffer.h"
#include "utilities/data_structures/pixel.h"
#include "utilities/image_writers/pgm_writer.h"

#include <cstdio>

struct TestRenderController::Impl
{
    Impl(const std::unique_ptr<RenderSettings>& settings, std::unique_ptr<TileBuffer>& tile_buffer)
      : m_settings(settings)
      , m_tile_buffer(tile_buffer)
    {}
    const std::unique_ptr<RenderSettings>& m_settings;
    std::unique_ptr<TileBuffer>&           m_tile_buffer;
};

TestRenderController::TestRenderController(
    const std::unique_ptr<Scene>&          scene,
    const std::unique_ptr<RenderSettings>& settings,
    std::unique_ptr<TileBuffer>&           tile_buffer)
  : m_impl_(new Impl(settings, tile_buffer))
{}

TestRenderController::~TestRenderController()
{
    delete m_impl_;
}

void TestRenderController::render() const
{

    const int x_dim = m_impl_->m_settings->m_xres;
    const int y_dim = m_impl_->m_settings->m_yres;

    std::unique_ptr<View> view_convert = std::make_unique<View>();

    view_convert->reserve_buffer(m_impl_->m_settings->m_xres, m_impl_->m_settings->m_yres);

    for (int j = y_dim - 1; j >= 0; j--)
    {
        for (int i = 0; i < x_dim; i++)
        {
            view_convert->m_pixels.emplace_back(Pixel(3, float(i) / float(x_dim), float(j) / float(y_dim), 0.2f));
        }
    }

    std::unique_ptr<ImageTile> out_tile = std::make_unique<ImageTile>(0, 0, x_dim, y_dim);

    out_tile->add_layer(std::move(view_convert));

    m_impl_->m_tile_buffer->add_tile(std::move(out_tile));
}

void TestRenderController::cleanup()
{
    printf("Render cleanup\n");
}

std::unique_ptr<IRenderController> TestRenderControllerFactory::create(
    const std::unique_ptr<Scene>&          scene,
    const std::unique_ptr<RenderSettings>& settings,
    std::unique_ptr<TileBuffer>&           tile_buffer)
{
    return std::make_unique<TestRenderController>(scene, settings, tile_buffer);
}
