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

#include "core/image_writers/jpeg_writer.h"
#include "core/image_writers/oiio_writer.h"
#include "core/image_writers/png_writer.h"
#include "utility/buffers/i_buffer.h"
#include "utility/buffers/rgba_buffer.h"
#include "utility/containers/scene.h"

struct FinalRenderController::Impl
{
    Scene*                                render_scene;
    RenderSettings                        settings;
    std::unique_ptr<IBuffer>              m_buffer;
    std::unique_ptr<renderer::IOutWriter> m_output_writer;
};

FinalRenderController::FinalRenderController()
  : m_impl_(new Impl)
{}

FinalRenderController::~FinalRenderController()
{
    delete m_impl_;
}

void FinalRenderController::add_settings(const RenderSettings settings)
{
    m_impl_->settings = settings;
}

void FinalRenderController::add_scene(Scene* render_scene)
{
    m_impl_->render_scene = render_scene;
}

void FinalRenderController::render()
{
    set_buffer();
    set_output_writer();
}

void FinalRenderController::cleanup() {}

RenderSettings& FinalRenderController::get_settings()
{
    return m_impl_->settings;
}

void FinalRenderController::set_output_writer()
{
    if (m_impl_->settings.m_output_writer == renderer::OPENIMAGEIO)
    {
        m_impl_->m_output_writer = std::make_unique<renderer::OIIOWriter>();
    }
    else if (m_impl_->settings.m_output_writer == renderer::PNG)
    {
        m_impl_->m_output_writer = std::make_unique<renderer::PngWriter>();
    }
    else if (m_impl_->settings.m_output_writer == renderer::JPEG)
    {
        m_impl_->m_output_writer = std::make_unique<renderer::JpegWriter>();
    }
}

void FinalRenderController::write_output()
{
    const int   x_res = m_impl_->settings.m_xres;
    const int   y_res = m_impl_->settings.m_yres;
    const char* output_path = m_impl_->settings.m_output_filepath;

    m_impl_->m_output_writer->write(
        m_impl_->m_buffer.get(), output_path, x_res, y_res);
}

void FinalRenderController::set_buffer()
{
    const int buffer_size{m_impl_->settings.m_xres * m_impl_->settings.m_yres *
                          4};
    m_impl_->m_buffer->reserve_buffer(buffer_size);
}

IBuffer* FinalRenderController::get_buffer()
{
    return m_impl_->m_buffer.get();
}

std::unique_ptr<IRenderController> FinalRenderControllerFactory::create()
{
    return std::make_unique<FinalRenderController>();
}
