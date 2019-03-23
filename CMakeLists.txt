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

cmake_minimum_required(VERSION 3.0.0)

set (CMAKE_CONFIGURATION_TYPES "Debug;Release;Profile;Ship" CACHE STRING "" FORCE)

project(RIFT_renderer VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 14)

set (version_major    0)
set (version_minor    1)
set (version_patch    0)
set (version_maturity alpha)

configure_file (
    ${PROJECT_SOURCE_DIR}/src/utility/system/version.h.in
    ${PROJECT_SOURCE_DIR}/src/utility/system/version.h
)

# Options
option(USE_PLUGINS "Enable external plugins" Off)
set(RIFT_DEPENDENCIES_DIR "" CACHE PATH "Path to dependencies dirctory")

if (USE_PLUGINS)
    add_definitions(-DRIFT_USE_PLUGINS)
    add_definitions(-DOIIO_STATIC_BUILD)
    set (Boost_USE_STATIC_LIBS TRUE)
    find_package (Boost 1.66 REQUIRED COMPONENTS chrono date_time filesystem regex system thread)
endif()

IF(CMAKE_BUILD_TYPE MATCHES RELEASE)
  add_definitions(-DNDEBUG)
ENDIF()

add_subdirectory(
    applications/RIFT_cli
)

add_subdirectory(
    src
)

