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

#include "pgm_writer.h"

#include "core/data_types/buffers/view.h"
#include "core/data_types/containers/render_settings.h"
#include "utilities/buffer_processing/unsigned_char_buffer.h"

#include <cstdio>

void PgmWriter::write(UnsignedCharBuffer& buffer, RenderSettings* render_settings)
{
    FILE* out_file = fopen("../output.pgm", "w");

    fprintf(out_file, "P3\n%i %i\n255\n", render_settings->m_xres, render_settings->m_yres);

    int pixel_index = 0;

    for (int i = 0; i < render_settings->m_xres * render_settings->m_yres; i++)
    {
        const int r = int(buffer.get_pixels().at(pixel_index++) * 254);
        const int g = int(buffer.get_pixels().at(pixel_index++) * 254);
        const int b = int(buffer.get_pixels().at(pixel_index++) * 254);

        fprintf(out_file, "%i %i %i\n", r, g, b);
    }

    fclose(out_file);
}
