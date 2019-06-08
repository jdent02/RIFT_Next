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

#include "png_writer.h"

#include "core/data_types/containers/render_settings.h"
#include "utilities/buffer_processing/unsigned_char_buffer.h"

void PngWriter::write(std::unique_ptr<TileBuffer>& buffer, const std::unique_ptr<RenderSettings>& render_settings)
{
    UnsignedCharBuffer pixel_buffer(render_settings->m_xres, render_settings->m_yres, RGB, render_settings);

    const std::string out_path = render_settings->m_output_path + ".png";

    pixel_buffer.build_buffer(buffer);

    stbi_write_png(
        out_path.c_str(),
        render_settings->m_xres,
        render_settings->m_yres,
        3,
        pixel_buffer.get_pixels().data(),
        render_settings->m_xres * 3);
}
