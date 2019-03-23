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

set (
    CAMERA_SOURCES
    objects/camera/i_camera.h
    objects/camera/thin_lens_camera.h
    objects/camera/thin_lens_camera.cpp
)

set (
    HITABLES_SOURCES
    objects/hitables/constant_medium.h
    objects/hitables/constant_medium.cpp
    objects/hitables/i_hitable.h
    objects/hitables/hitable_list.h
    objects/hitables/sphere.h
    objects/hitables/sphere.cpp
    objects/hitables/moving_sphere.h
    objects/hitables/moving_sphere.cpp
    objects/hitables/rect.cpp
    objects/hitables/rect.h
    objects/hitables/box.cpp
    objects/hitables/box.h
    objects/hitables/instancers.cpp
    objects/hitables/instancers.h
    objects/hitables/sky_sphere.h
)

set (
    CORE_SOURCES
    core/acceleration_structures/bvh_node.h
    core/acceleration_structures/bvh_node.cpp
    core/acceleration_structures/aabb.h
    core/acceleration_structures/aabb.cpp
    core/acceleration_structures/bvh_utils.h
    core/lighting_integrators/i_light_integrator.h
    core/lighting_integrators/direct_lighting.h
    core/lighting_integrators/direct_lighting.cpp
    core/lighting_integrators/light_sample_path.cpp
    core/lighting_integrators/light_sample_path.h
    core/lighting_integrators/path_tracer.h
    core/lighting_integrators/path_tracer.cpp
    core/rendering/render_controller.h
    core/rendering/render_controller.cpp
    core/rendering/render_worker.h
    core/rendering/render_worker.cpp
    core/rendering/color_functions.h
    core/image_writers/jpeg_writer.cpp
    core/image_writers/jpeg_writer.h
    core/image_writers/i_out_writer.h
    core/image_writers/png_writer.cpp
    core/image_writers/png_writer.h
    core/samplers/i_sampler.h
)

if(USE_PLUGINS)
    list(APPEND CORE_SOURCES
        core/image_writers/oiio_writer.h
        core/image_writers/oiio_writer.cpp
    )
endif()

set (
    MATERIAL_SOURCES
    materials/i_material.h
    materials/dielectric.h
    materials/dielectric.cpp
    materials/diffuse_light.h
    materials/lambertian.h
    materials/lambertian.cpp
    materials/metal.h
    materials/metal.cpp
)

set (
    TEXTURE_SOURCES
    textures/i_texture.h
    textures/constant_tex.h
    textures/checker_tex.h
    textures/checker_tex.cpp
    textures/noise_texture.h
    textures/image_texture.cpp
    textures/image_texture.h
    textures/sky_gradient.cpp
    textures/sky_gradient.h)

set (
    UTILITY_SOURCES
    utility/generators/scene_generator.h
    utility/generators/scene_generator.cpp
    utility/math_functions/maths.h
    utility/math_functions/scalars.h
    utility/noises/perlin.h
    utility/containers/scene.h
    utility/containers/scene.cpp
    utility/containers/settings_matrix.h
    utility/containers/render_settings.h
    utility/containers/render_settings.cpp
    utility/containers/param_array.h
    utility/containers/param_array.cpp
    utility/system/version.h
    utility/system/_dll/dll_symbol.h
    utility/system/_dll/dllmain.cpp
    utility/system/_dll/header.h
    utility/system/_dll/targetver.h
    utility/data_types/ray.h
    utility/data_types/vec3.h
    utility/data_types/hit_record.h
    utility/data_types/scatter_record.h
    utility/math_functions/pdfs/pdf.h
    utility/math_functions/utility_functions.h
    utility/math_functions/pdfs/cosine_pdf.h
    utility/math_functions/pdfs/hitable_pdf.h
    utility/math_functions/pdfs/mixture_pdf.h
    utility/math_functions/onb.h
    utility/math_functions/scatter_functions.h
    utility/rng/xoroshiro128.h
    utility/rng/xoroshiro128.cpp
    utility/rng/i_rand_generator.h
    utility/rng/drand48.cpp
    utility/rng/drand48.h
    utility/rift_pointer.h
)

set (
    CPP_SOURCES
    ${CAMERA_SOURCES}
    ${CORE_SOURCES}
    ${HITABLES_SOURCES}
    ${MATERIAL_SOURCES}
    ${RENDERING_SOURCES}
    ${TEXTURE_SOURCES}
    ${UTILITY_SOURCES}
)

add_library(
    RIFT
    SHARED
    ${CPP_SOURCES}
)

target_include_directories(
    RIFT
    PUBLIC
    SYSTEM
    .
)

target_compile_definitions(
    RIFT
    PUBLIC
    RIFT_EXPORT
)

if (MSVC)
    target_compile_definitions(
        RIFT
        PUBLIC
         _USE_MATH_DEFINES
    )
endif()

# Optional libraries for OpenImageIO
if(USE_PLUGINS)
    target_include_directories(
        RIFT
        PUBLIC
        ${RIFT_DEPENDENCIES_DIR}/oiio-release/include
        ${RIFT_DEPENDENCIES_DIR}/ilmbase-release/include
        ${RIFT_DEPENDENCIES_DIR}/ilmbase-release/include/OpenEXR
        ${RIFT_DEPENDENCIES_DIR}/openexr-release/include
        ${Boost_INCLUDE_DIRS}
    )
    set(
        OPEN_EXR_LIBS
        ${RIFT_DEPENDENCIES_DIR}/openexr-release/lib/IlmImf-2_2.lib
        ${RIFT_DEPENDENCIES_DIR}/openexr-release/lib/IlmImfUtil-2_2.lib
        ${RIFT_DEPENDENCIES_DIR}/ilmbase-release/lib/Half.lib
        ${RIFT_DEPENDENCIES_DIR}/ilmbase-release/lib/IlmThread-2_2.lib
        ${RIFT_DEPENDENCIES_DIR}/ilmbase-release/lib/Iex-2_2.lib
        ${RIFT_DEPENDENCIES_DIR}/ilmbase-release/lib/IexMath-2_2.lib
        ${RIFT_DEPENDENCIES_DIR}/ilmbase-release/lib/Imath-2_2.lib
    )

    set(
        ZLIB_LIBS
        ${RIFT_DEPENDENCIES_DIR}/zlib-release/lib/zlibstatic.lib
    )

    set(
        OIIO_LIBS
        ${RIFT_DEPENDENCIES_DIR}/oiio-release/lib/OpenImageIO.lib
        ${RIFT_DEPENDENCIES_DIR}/oiio-release/lib/OpenImageIO_Util.lib
    )

    set(
        TIFF_LIB
        ${RIFT_DEPENDENCIES_DIR}/libtiff-release/lib/libtiff.lib
        )

    set(
        PNG_LIB
        ${RIFT_DEPENDENCIES_DIR}/libpng-release/lib/libpng16_static.lib
    )

    set(
        JPEG_LIB
        ${RIFT_DEPENDENCIES_DIR}/libjpeg-turbo-release/lib/jpeg-static.lib
    )

    target_link_libraries(
        RIFT
        ${OPEN_EXR_LIBS}
        ${ZLIB_LIBS}
        ${TIFF_LIB}
        ${Boost_LIBRARIES}
        ${OIIO_LIBS}
        ${PNG_LIB}
        ${JPEG_LIB}
    )
endif()

if (MSVC)
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
endif()

# Visual Studio folder layout
source_group(
    "src\\core\\acceleration_structures" REGULAR_EXPRESSION
    core/acceleration_structures/.*
)

source_group(
    "src\\core\\image_writers" REGULAR_EXPRESSION
    core/image_writers/.*
)

source_group(
    "src\\core\\lighting_integrators" REGULAR_EXPRESSION
    core/lighting_integrators/.*
)

source_group(
    "src\\core\\rendering" REGULAR_EXPRESSION
    core/rendering/.*
)

source_group(
    "src\\core\\samplers" REGULAR_EXPRESSION
    core/samplers/.*
)

source_group(
    "src\\materials" REGULAR_EXPRESSION
    materials/.*
)

source_group(
    "src\\object\\cameras" REGULAR_EXPRESSION
    objects/camera/.*
)

source_group(
    "src\\object\\hitables" REGULAR_EXPRESSION
    objects/hitables/.*
)

source_group(
    "src\\textures" REGULAR_EXPRESSION
    textures/.*
)

source_group(
    "src\\third_party" REGULAR_EXPRESSION
    third_party/.*
)

source_group(
    "src\\utility" REGULAR_EXPRESSION
    utility/.*
)

source_group(
    "src\\utility\\containers" REGULAR_EXPRESSION
    utility/containers/.*
)

source_group(
    "src\\utility\\data_types" REGULAR_EXPRESSION
    utility/data_types/.*
)

source_group(
    "src\\utility\\generators" REGULAR_EXPRESSION
    utility/generators/.*
)

source_group(
    "src\\utility\\math_functions" REGULAR_EXPRESSION
    utility/math_functions/.*
)

source_group(
    "src\\utility\\math_functions\\pdf" REGULAR_EXPRESSION
    utility/math_functions/pdfs.*
)

source_group(
    "src\\utility\\noises" REGULAR_EXPRESSION
    utility/noises/.*
)

source_group(
    "src\\utility\\rng" REGULAR_EXPRESSION
    utility/rng/.*
)

source_group(
    "src\\utility\\qmc" REGULAR_EXPRESSION
    utility/qmc/.*
)

source_group(
    "src\\utility\\system" REGULAR_EXPRESSION
    utility/system/.*
)


source_group(
    "src\\utility\\system\\_dll" REGULAR_EXPRESSION
    utility/system/_dll/.*
)