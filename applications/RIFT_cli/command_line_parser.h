#pragma once

#include "utility/containers/render_settings.h"

class CommandLineParser
{
  public:
    CommandLineParser() = default;

    void print_help();

    void parse(int argc, char* argv[], rift::RenderSettings* settings);

  private:
    int convert_number(size_t& length, const char* number);
};
