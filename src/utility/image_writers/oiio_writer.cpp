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

#include "oiio_writer.h"

#include "utility/containers/render_settings.h"

#include "OpenEXR/half.h"
#include "OpenImageIO/imageio.h"

using namespace OpenImageIO_v2_0;

void OIIOWriter::write(
    const IBuffer* buffer,
    const char*    filename,
    const int      x_res,
    const int      y_res)
{
    const int buffer_size = x_res * y_res * 4;

    auto pixels = new half[buffer_size];

    const TypeDesc pixel_type = TypeDesc::HALF;

    for (int i = 0; i < buffer_size; i++)
    {
        pixels[i] = static_cast<half>(buffer->get_pixels()[i]);
    }

    std::unique_ptr<ImageOutput> out = ImageOutput::create(filename);
    if (out == nullptr)
    {
        return;
    }

    const ImageSpec spec(x_res, y_res, 4, pixel_type);
    out->open(filename, spec);
    out->write_image(pixel_type, pixels);

    out->close();
}