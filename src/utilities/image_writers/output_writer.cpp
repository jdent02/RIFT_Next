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

#include "output_writer.h"

#include "utilities/buffer_processing/half_buffer.h"
#include "utilities/buffer_processing/unsigned_char_buffer.h"
#include "utilities/containers/render_settings.h"

#include "OpenEXR/ImfRgbaFile.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#define STBI_MSC_SECURE_CRT
#include "stb_image_write.h"

using namespace Imf_2_3;

void OutputWriter::write(std::unique_ptr<TileBuffer>& buffer, const std::unique_ptr<RenderSettings>& render_settings)
{
    if (render_settings->m_output_writer == JPEG)
    {
        UnsignedCharBuffer pixel_buffer(render_settings->m_xres, render_settings->m_yres, RGB, render_settings);

        pixel_buffer.build_buffer(buffer);

        const std::string out_path = render_settings->m_output_path + ".jpg";

        stbi_write_jpg(
            out_path.c_str(), render_settings->m_xres, render_settings->m_yres, 3, pixel_buffer.m_pixels.data(), 75);
    }
    else if (render_settings->m_output_writer == PNG)
    {
        UnsignedCharBuffer pixel_buffer(render_settings->m_xres, render_settings->m_yres, RGB, render_settings);

        pixel_buffer.build_buffer(buffer);

        const std::string out_path = render_settings->m_output_path + ".png";

        stbi_write_png(
            out_path.c_str(),
            render_settings->m_xres,
            render_settings->m_yres,
            3,
            pixel_buffer.m_pixels.data(),
            3 * render_settings->m_xres);
    }
    else if (render_settings->m_output_writer == OPENEXR)
    {
        HalfBuffer pixel_buffer(render_settings->m_xres, render_settings->m_yres, RGBA, render_settings);

        pixel_buffer.build_buffer(buffer);

        const std::string out_path = render_settings->m_output_path + ".exr";

        RgbaOutputFile file(out_path.c_str(), render_settings->m_xres, render_settings->m_yres, WRITE_RGBA);

        file.setFrameBuffer(pixel_buffer.m_pixels.data(), 1, render_settings->m_xres);

        file.writePixels(render_settings->m_yres);
    }
}
