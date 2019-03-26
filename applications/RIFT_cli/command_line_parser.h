#pragma once
#include "utility/containers/render_settings.h"


class CommandLineParser
{
  public:
    CommandLineParser() = default;

    static void print_help();

    static RenderSettings parse(const int argc, char* argv[]);
};
