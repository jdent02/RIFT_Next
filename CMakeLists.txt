# Released under MIT License

# Copyright (c) 2019 Jonathan Dent.

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

cmake_minimum_required(VERSION 3.0.0)

set (CMAKE_CONFIGURATION_TYPES "Debug;Release" CACHE STRING "" FORCE)

project(RIFT_renderer VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 14)

set(RIFT_DEPENDENCIES_DIR ${PROJECT_SOURCE_DIR}/dependencies)

set (version_major    0)
set (version_minor    1)
set (version_patch    0)
set (version_maturity alpha)

configure_file (
    ${PROJECT_SOURCE_DIR}/src/utilities/system/version.h.in
    ${PROJECT_SOURCE_DIR}/src/utilities/system/version.h
)

macro (slashes_to_backslashes output input)
    string (REGEX REPLACE "/" "\\\\" ${output} ${input})
endmacro ()

macro (get_sandbox_bin_path path)
    slashes_to_backslashes (${path} ${PROJECT_SOURCE_DIR})
    set (${path} ${${path}}\\stage\\vc$(PlatformToolsetVersion)\\$(ConfigurationName))
endmacro ()

macro (add_copy_target_to_sandbox_command target)
    get_sandbox_bin_path (bin_path)

    # Copy the .exe and the PDB file (except in Ship configuration).
    add_custom_command (TARGET ${target} POST_BUILD
        COMMAND if not exist "${bin_path}" mkdir "${bin_path}"
        COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:${target}> "${bin_path}"
        COMMAND if $<CONFIG> == "Debug" ${CMAKE_COMMAND} -E copy "$<TARGET_PDB_FILE:${target}>" "${bin_path}"
    )
endmacro ()

add_subdirectory(
    applications/RIFT_cli
)

add_subdirectory(
    src
)