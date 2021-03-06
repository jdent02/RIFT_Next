# Released under MIT License

# Copyright (c) 2018 Jonathan Dent.

# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:

# The above copyright notice and this permission notice shall be included in
# all copies or substantial portions of the Software.

# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
# SOFTWARE.

set(
    CLI_SOURCES
    main.cpp
    command_line_parser.h
    command_line_parser.cpp
)

add_executable(
    RIFT.cli
    ${CLI_SOURCES}
)

set_property (TARGET RIFT.cli APPEND PROPERTY
    COMPILE_DEFINITIONS_RELEASE "_NDEBUG"
)

target_include_directories(
    RIFT.cli
    PUBLIC
    .
    ..
)

set(
    CMAKE_C_FLAGS_RELEASE
    "/Zi /O2 /Ob2 /Oi /Ot /Oy /MD /GS- /GL"
)

set(
    CMAKE_CXX_FLAGS_RELEASE
    "/Zi /O2 /Ob2 /Oi /Ot /Oy /MD /GS- /GL"
)

set(
    CMAKE_EXE_LINKER_FLAGS_RELEASE
    "/OPT:REF /OPT:ICF /LTCG /INCREMENTAL:NO"
)

target_link_libraries(
    RIFT.cli
    RIFT
)

#Post build
if(MSVC)
add_copy_target_to_sandbox_command (RIFT.cli)
endif()

source_group(
    "" FILES
    main.cpp
    command_line_parser.h
    command_line_parser.cpp
)