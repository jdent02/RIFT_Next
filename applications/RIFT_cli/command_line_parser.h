#pragma once
#include "utility/containers/render_settings.h"

class CommandLineParser
{
  public:
    CommandLineParser() = default;

    static void print_help();

    static std::unique_ptr<RenderSettings> parse(int argc, char* argv[]);
};
