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

#include "core/rendering/tile_pool.h"
#include "utility/buffers/rgba_buffer.h"
#include "utility/containers/scene.h"

struct FinalRenderController::Impl
{
    Scene*         render_scene;
    RenderSettings settings;
    RgbaBuffer*    m_buffer;
    TilePool       m_tile_pool;
};

FinalRenderController::FinalRenderController()
  : m_impl_(new Impl)
{}

FinalRenderController::~FinalRenderController()
{
    delete m_impl_;
}

void FinalRenderController::render() const
{
    m_impl_->m_tile_pool.create_pool(
        m_impl_->settings.m_xres, m_impl_->settings.m_yres, 32);
}

void FinalRenderController::cleanup() {}

std::unique_ptr<IRenderController> FinalRenderControllerFactory::create()
{
    return std::make_unique<FinalRenderController>();
}
