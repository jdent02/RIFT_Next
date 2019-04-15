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

#include "command_line_parser.h"
#include "core/rendering/final_render_controller.h"
#include "core/rendering/i_render_controller.h"
#include "core/rendering/test_render_controller.h"
#include "utility/containers/render_settings.h"
#include "utility/containers/scene.h"
#include "utility/generators/scene_generator.h"
#include "utility/image_writers/oiio_writer.h"
#include "utility/image_writers/png_writer.h"

#include <cstdio>
#include <ctime>

int main(const int argc, char* argv[])
{
    const time_t start_time = time(nullptr);

    const std::unique_ptr<RenderSettings> settings =
        CommandLineParser::parse(argc, argv);

    std::unique_ptr<IBuffer> pixel_buffer = RgbaBufferFactory::create();

    const std::unique_ptr<IRenderController> engine =
        TestRenderControllerFactory::create(settings.get(), pixel_buffer.get());

    pixel_buffer->reserve_buffer(settings->m_xres * settings->m_yres * 4);

    engine->render();

    OIIOWriter::write(
        pixel_buffer.get(),
        settings->m_output_filepath,
        settings->m_xres,
        settings->m_yres);

    // generate scene
    // set up render controller
    // do render
    // write outputs
    // delete render controller
    // cleanup?

    const time_t end_time = time(nullptr);

    printf(
        "Render Finished; Total Time: %f\n",
        static_cast<double>(end_time - start_time));

    return 0;
}
