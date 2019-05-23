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

#include <cstdio>
#include "core/data_types/containers/render_settings.h"
#include "core/data_types/tiles/tile_buffer.h"

struct TestRenderController::Impl
{
    RenderSettings* m_settings;
    TileBuffer*     tile_buffer;
};

TestRenderController::TestRenderController(
    Scene*          scene,
    RenderSettings* settings,
    TileBuffer*     tile_buffer)
  : m_impl_(new Impl)
{
    m_impl_->m_settings = settings;
    m_impl_->tile_buffer = tile_buffer;
}

TestRenderController::~TestRenderController()
{
    delete m_impl_;
}

void TestRenderController::render() const
{

    const int x_dim = m_impl_->m_settings->m_xres;
    const int y_dim = m_impl_->m_settings->m_yres;

    for (int j = y_dim - 1; j >= 0; j--)
    {
        for (int i = 0; i <x_dim; i++)
        {
            // float(i) / float(x_dim);
            // float(j) / float(y_dim);
            // 0.2;
            // 1.f;
        }
    }
}

void TestRenderController::cleanup()
{
    printf("Render cleanup\n");
}

std::unique_ptr<IRenderController> TestRenderControllerFactory::create(
    Scene*          scene,
    RenderSettings* settings,
    TileBuffer*     tile_buffer)
{
    return std::make_unique<TestRenderController>(scene, settings, tile_buffer);
}
