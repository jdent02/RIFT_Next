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

#include "core/lighting_integrators/i_light_integrator.h"
#include "utilities/image_writers/i_out_writer.h"
#include "utilities/system/version.h"
#include "utilities/utility_functions.h"

#include <cstdio>
#include <cstring>
#include <memory>
#include <thread>

std::unique_ptr<RenderSettings> CommandLineParser::parse(const int argc, char* argv[])
{
    std::string integrator_string{"Path Tracer"};

    std::unique_ptr<RenderSettings> settings = std::make_unique<RenderSettings>();

    for (int i = 0; i < argc; i++)
    {
        if (!static_cast<bool>(strcmp(argv[i], "--threads")))
        {
            char* temp_threads = argv[i + 1];

            const size_t str_len = strlen(temp_threads);

            settings->m_threads = convert_number(str_len, temp_threads);
        }
        else if (!static_cast<bool>(strcmp(argv[i], "--tile_size")))
        {
            char* temp_tile_size = argv[i + 1];

            const size_t str_len = strlen(temp_tile_size);

            settings->m_tile_size = convert_number(str_len, temp_tile_size);
        }
        else if (!static_cast<bool>(strcmp(argv[i], "--resolution")))
        {
            char* x = argv[i + 1];

            const size_t x_len = strlen(x);

            settings->m_xres = convert_number(x_len, x);

            char* y = argv[i + 2];

            const size_t y_len = strlen(y);

            settings->m_yres = convert_number(y_len, y);
        }
        else if (!static_cast<bool>(strcmp(argv[i], "--filepath")))
        {
            settings->m_output_path = argv[i + 1];
        }
        else if (!static_cast<bool>(strcmp(argv[i], "--integrator")))
        {
            if (!static_cast<bool>(strcmp(argv[i + 1], "path")))
            {
                settings->m_light_integrator = PATH_TRACING;
            }
            else if (!static_cast<bool>(strcmp(argv[i + 1], "direct")))
            {
                settings->m_light_integrator = DIRECT_LIGHTING;

                integrator_string = "Direct Lighting";
            }
            else if (!static_cast<bool>(strcmp(argv[i + 1], "importance")))
            {
                settings->m_light_integrator = LIGHT_SAMPLE_PATH_TRACING;

                integrator_string = "Material Importance Sampling";
            }
        }
        else if (!static_cast<bool>(strcmp(argv[i], "--samples")))
        {
            char* sample_num = argv[i + 1];

            const size_t str_len = strlen(sample_num);

            settings->m_samples = convert_number(str_len, sample_num);
        }
        else if (!static_cast<bool>(strcmp(argv[i], "--help")))
        {
            print_help();
        }
        else if (!static_cast<bool>(strcmp(argv[i], "--writer")))
        {
            if (!static_cast<bool>(strcmp(argv[i + 1], "jpeg")))
            {
                settings->m_output_writer = JPEG;
            }
            if (!static_cast<bool>(strcmp(argv[i + 1], "openexr")))
            {
                settings->m_output_writer = OPENEXR;
            }

        }
    }

    printf(
        "Render Settings:\n"
        "Resolution: %i %i\n"
        "Number of Samples: %i\n"
        "Integrator: %s\n"
        "Rendering Threads: %i\n"
        "Tile Size: %i\n",
        settings->m_xres,
        settings->m_yres,
        settings->m_samples,
        integrator_string.c_str(),
        settings->m_threads,
        settings->m_tile_size);

    return settings;
}

void CommandLineParser::print_help()
{
    printf(
        "RIFT Renderer version %s\n\n"
        "Options:\n\n"
        "   --threads: Number of rendering threads.  Defaults to system max if not specified\n"
        "   --tile_size: Squared size of the rendered tiles\n"
        "   --samples: Number of rendering samples.  This will be split amongst the available threads\n"
        "   --resolution: Resolution of the render in width and height\n"
        "   --filepath: Output filepath for the rendered image.  The extension type will be automatically added\n"
        "   --writer: Image writer for renders, options are openexr, png or jpeg\n",
        VERSION_STRING);

    exit(EXIT_SUCCESS);
}
