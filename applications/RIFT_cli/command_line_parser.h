#pragma once

#include "utility/containers/render_settings.h"

class CommandLineParser
{
  public:
    CommandLineParser() = default;

    static void print_help();

    void parse(const int argc, char* argv[], rift::RenderSettings* settings) const;

  private:
    int convert_number(size_t& length, const char* number) const;
};
