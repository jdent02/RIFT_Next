#Released under MIT License

#Copyright(c) 2018 Jonathan Dent.

#Permission is hereby granted, free of charge, to any person obtaining a copy
#of this software and associated documentation files(the "Software"), to deal
#in the Software without restriction, including without limitation the rights
#to use, copy, modify, merge, publish, distribute, sublicense, and / or sell
#copies of the Software, and to permit persons to whom the Software is
#furnished to do so, subject to the following conditions:

#The above copyright notice and this permission notice shall be included in
#all copies or substantial portions of the Software.

#THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
#IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
#FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE
#AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
#LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
#OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
#SOFTWARE.

set (
    HITABLES_SOURCES
    objects/camera/i_camera.h
    objects/camera/thin_lens_camera.h
    objects/camera/thin_lens_camera.cpp
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
    core/data_types/buffers/rgba_buffer.h
    core/data_types/buffers/rgba_buffer.cpp
    core/data_types/buffers/pixels.h
    core/data_types/buffers/tile_buffer.h
    core/data_types/buffers/tile_buffer.cpp
    core/data_types/containers/render_settings.h
    core/data_types/containers/scene.h
    core/data_types/containers/scene.cpp
    core/data_types/containers/texture_store.h
    core/data_types/containers/texture_store.cpp
    core/data_types/hit_record.h
    core/data_types/ray.h
    core/data_types/scatter_record.h
    core/data_types/vec3.h
    core/lighting_integrators/i_light_integrator.h
    core/lighting_integrators/direct_lighting.h
    core/lighting_integrators/direct_lighting.cpp
    core/lighting_integrators/light_sample_path.cpp
    core/lighting_integrators/light_sample_path.h
    core/lighting_integrators/path_tracer.h
    core/lighting_integrators/path_tracer.cpp
    core/raytracing/pdfs/cosine_pdf.h
    core/raytracing/pdfs/hitable_pdf.h
    core/raytracing/pdfs/mixture_pdf.h
    core/raytracing/pdfs/pdf.h
    core/raytracing/aabb.h
    core/raytracing/aabb.cpp
    core/raytracing/bvh_node.h
    core/raytracing/bvh_node.cpp
    core/raytracing/bvh_utils.h
    core/raytracing/onb.h
    core/raytracing/scatter_functions.h
    core/raytracing/utility_functions.h
    core/render_process/tile_pool.h
    core/render_process/tile_pool.cpp
    core/render_process/final_render_controller.h
    core/render_process/final_render_controller.cpp
    core/render_process/test_render_controller.h
    core/render_process/test_render_controller.cpp
    core/render_process/final_render_controller.h
    core/render_process/i_render_controller.h
)

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
    utilities/generators/scene_generator.h
    utilities/generators/scene_generator.cpp
    utilities/maths/maths.h
    utilities/maths/scalars.h
    utilities/noises/perlin.h
    utilities/rng/drand48.h
    utilities/rng/drand48.cpp
    utilities/rng/xoroshiro128.h
    utilities/rng/xoroshiro128.cpp
    utilities/system/version.h
    utilities/system/_dll/dll_symbol.h
    utilities/system/_dll/dllmain.cpp
    utilities/system/_dll/header.h
    utilities/system/_dll/targetver.h
    utilities/color_utilities.h
    utilities/utility_functions.h
)

if(USE_PLUGINS)
    list(APPEND UTILITY_SOURCES
        utilities/image_writers/oiio_writer.h
        utilities/image_writers/oiio_writer.cpp
    )
endif()

set (
    CPP_SOURCES
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

if (MSVC)
    target_compile_definitions(
        RIFT
        PUBLIC
         _USE_MATH_DEFINES
    )
endif()

#Optional libraries for OpenImageIO
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
        optimized ${RIFT_DEPENDENCIES_DIR}/openexr-release/lib/IlmImf-2_2.lib
        optimized ${RIFT_DEPENDENCIES_DIR}/openexr-release/lib/IlmImfUtil-2_2.lib
        optimized ${RIFT_DEPENDENCIES_DIR}/ilmbase-release/lib/Half.lib
        optimized ${RIFT_DEPENDENCIES_DIR}/ilmbase-release/lib/IlmThread-2_2.lib
        optimized ${RIFT_DEPENDENCIES_DIR}/ilmbase-release/lib/Iex-2_2.lib
        optimized ${RIFT_DEPENDENCIES_DIR}/ilmbase-release/lib/IexMath-2_2.lib
        optimized ${RIFT_DEPENDENCIES_DIR}/ilmbase-release/lib/Imath-2_2.lib
        debug ${RIFT_DEPENDENCIES_DIR}/openexr-debug/lib/IlmImf-2_2.lib
        debug ${RIFT_DEPENDENCIES_DIR}/openexr-debug/lib/IlmImfUtil-2_2.lib
        debug ${RIFT_DEPENDENCIES_DIR}/ilmbase-debug/lib/Half.lib
        debug ${RIFT_DEPENDENCIES_DIR}/ilmbase-debug/lib/IlmThread-2_2.lib
        debug ${RIFT_DEPENDENCIES_DIR}/ilmbase-debug/lib/Iex-2_2.lib
        debug ${RIFT_DEPENDENCIES_DIR}/ilmbase-debug/lib/IexMath-2_2.lib
        debug ${RIFT_DEPENDENCIES_DIR}/ilmbase-debug/lib/Imath-2_2.lib
    )

    set(
        ZLIB_LIBS
        optimized ${RIFT_DEPENDENCIES_DIR}/zlib-release/lib/zlibstatic.lib
        debug ${RIFT_DEPENDENCIES_DIR}/zlib-debug/lib/zlibstaticd.lib
    )

    set(
        OIIO_LIBS
        optimized ${RIFT_DEPENDENCIES_DIR}/oiio-release/lib/OpenImageIO.lib
        optimized ${RIFT_DEPENDENCIES_DIR}/oiio-release/lib/OpenImageIO_Util.lib
        debug ${RIFT_DEPENDENCIES_DIR}/oiio-debug/lib/OpenImageIO.lib
        debug ${RIFT_DEPENDENCIES_DIR}/oiio-debug/lib/OpenImageIO_Util.lib
    )

    set(
        TIFF_LIB
        optimized ${RIFT_DEPENDENCIES_DIR}/libtiff-release/lib/libtiff.lib
        debug ${RIFT_DEPENDENCIES_DIR}/libtiff-debug/lib/libtiff.lib
        )

    set(
        PNG_LIB
        optimized ${RIFT_DEPENDENCIES_DIR}/libpng-release/lib/libpng16_static.lib
        debug ${RIFT_DEPENDENCIES_DIR}/libpng-debug/lib/libpng16_staticd.lib
    )

    set(
        JPEG_LIB
        optimized ${RIFT_DEPENDENCIES_DIR}/libjpeg-turbo-release/lib/jpeg-static.lib
        debug ${RIFT_DEPENDENCIES_DIR}/libjpeg-turbo-debug/lib/jpeg-static.lib
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

    set(
        CMAKE_SHARED_LINKER_FLAGS_RELEASE
        "/OPT:REF /OPT:ICF /LTCG /INCREMENTAL:NO"
    )
endif()

#Visual Studio folder layout
source_group(
    "src\\core\\data_types\\buffers" REGULAR_EXPRESSION
    core/data_types/buffers/.*
)

source_group(
    "src\\core\\data_types\\containers" REGULAR_EXPRESSION
    core/data_types/containers/.*
)

source_group(
    "src\\core\\data_types" REGULAR_EXPRESSION
    core/data_types/.*
)

source_group(
    "src\\core\\lighting_integrators" REGULAR_EXPRESSION
    core/lighting_integrators/.*
)

source_group(
    "src\\core\\raytracing" REGULAR_EXPRESSION
    core/raytracing/.*
)

source_group(
    "src\\core\\render_process" REGULAR_EXPRESSION
    core/render_process/.*
)

source_group(
    "src\\materials" REGULAR_EXPRESSION
    materials/.*
)

source_group(
    "src\\objects\\cameras" REGULAR_EXPRESSION
    objects/camera/.*
)

source_group(
    "src\\objects\\hitables" REGULAR_EXPRESSION
    objects/hitables/.*
)

source_group(
    "src\\textures" REGULAR_EXPRESSION
    textures/.*
)

source_group(
    "src\\utilities" REGULAR_EXPRESSION
    utilities/.*
)

source_group(
    "src\\utilities\\image_writers" REGULAR_EXPRESSION
    utilities/image_writers/.*
)

source_group(
    "src\\utilities\\generators" REGULAR_EXPRESSION
    utilities/generators/.*
)

source_group(
    "src\\utilities\\maths" REGULAR_EXPRESSION
    utilities/maths/.*
)

source_group(
    "src\\utilities\\noises" REGULAR_EXPRESSION
    utilities/noises/.*
)

source_group(
    "src\\utilities\\rng" REGULAR_EXPRESSION
    utilities/rng/.*
)

source_group(
    "src\\utilities\\system" REGULAR_EXPRESSION
    utilities/system/.*
)

source_group(
    "src\\utilities\\system\\_dll" REGULAR_EXPRESSION
    utilities/system/_dll/.*
)
