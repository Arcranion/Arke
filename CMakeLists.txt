cmake_minimum_required(VERSION 3.24)

project(Arke)

set(CMAKE_CXX_STANDARD 20)

include(cmake/Shaders.cmake)

find_package(
        Python3
        REQUIRED
        COMPONENTS Interpreter
)

find_package(
        Vulkan
        REQUIRED
        COMPONENTS glslc
)

set(SOURCES
        src/glad/gl.c
        src/arke/engine/graphics/VertexAttribute.h
        src/arke/engine/graphics/VertexAttribute.cpp
        src/arke/engine/graphics/VertexAttributes.h
        src/arke/engine/graphics/VertexAttributes.cpp
        src/arke/engine/graphics/backends/vulkan/GraphicsVulkan.h
        src/arke/engine/graphics/backends/vulkan/GraphicsVulkan.cpp
        src/arke/engine/Consts.h
        src/arke/util/Version.h
        src/arke/util/Logging.h
        src/arke/engine/graphics/Window.h
        src/arke/util/String.h
        src/arke/engine/application/Application.h
        src/arke/engine/graphics/Graphics.h
        src/arke/util/Disposable.h
        src/arke/engine/application/Application.cpp
        src/arke/engine/application/Module.h
        src/arke/engine/application/ModuleMain.h
        src/arke/util/Error.h
        src/arke/engine/graphics/backends/opengl/GraphicsGL.h
        src/arke/engine/graphics/backends/opengl/GraphicsGL.cpp
        src/arke/engine/math/unit/Size.h
        src/arke/engine/graphics/Looper.h
        src/arke/engine/graphics/backends/sdl2/WindowSDL2.h
        src/arke/engine/graphics/backends/sdl2/WindowSDL2.cpp
        src/arke/engine/graphics/backends/glfw/WindowGLFW.cpp
        src/arke/engine/graphics/backends/glfw/WindowGLFW.h
        src/arke/engine/graphics/ShaderProgram.h
        src/arke/engine/graphics/backends/opengl/ShaderProgramGL.h
        src/arke/engine/application/Core.h
        src/arke/engine/application/Core.cpp
        src/arke/engine/graphics/backends/opengl/ShaderProgramGL.cpp
        src/arke/engine/graphics/backends/opengl/DrawGL.h
        src/arke/engine/graphics/backends/opengl/DrawGL.cpp
        src/arke/engine/graphics/Draw.h
        src/arke/engine/resources/Resources.h
        src/arke/engine/resources/ResourceLoader.h
        src/arke/engine/resources/Resources.cpp
        src/arke/engine/resources/loaders/TextLoader.h
        src/arke/engine/resources/loaders/TextLoader.cpp
        src/arke/engine/resources/ResourceType.h
        src/arke/engine/resources/loaders/BinaryLoader.h
        src/arke/engine/resources/loaders/BinaryLoader.cpp
        src/arke/engine/graphics/Factory.h
        src/arke/engine/graphics/backends/opengl/FactoryGL.h
        src/arke/engine/graphics/backends/opengl/FactoryGL.cpp
        src/arke/engine/ui/Container.h
        src/arke/engine/ui/Drawable.h
        src/arke/engine/ui/Container.cpp
        src/arke/engine/ui/VerticalContainer.h
        src/arke/engine/ui/HorizontalContainer.h
        src/arke/util/TypeCheck.h
        src/arke/engine/ui/Element.h
        src/arke/engine/ui/unit/Dp.h
        src/arke/engine/ui/unit/Dp.cpp
        src/arke/engine/ui/unit/DpSize.h
        src/arke/engine/math/Vector2.h
        src/arke/engine/math/Vector2.cpp
        src/arke/engine/ui/unit/Dp2.h
        src/arke/engine/ui/HorizontalContainer.cpp
        src/arke/engine/ui/VerticalContainer.cpp
        src/arke/engine/graphics/UIRenderer.h
        src/arke/engine/graphics/backends/opengl/UIRendererGL.h
        src/arke/engine/graphics/backends/opengl/UIRendererGL.cpp
        src/arke/engine/ui/DrawContext.h
        src/arke/engine/ui/DrawCall.h
        src/arke/engine/ui/DrawContext.cpp
        src/arke/engine/graphics/Texture.h
        src/arke/engine/graphics/Texture.cpp
        src/arke/engine/graphics/backends/opengl/TextureGL.h
        src/arke/engine/graphics/backends/opengl/TextureGL.cpp
        src/arke/engine/resources/loaders/TextureLoader.cpp
        src/arke/engine/resources/loaders/TextureLoader.h
)

file(GLOB_RECURSE PREDEFINED_SHADER_SOURCES assets/shaders/src/*)

add_library(Arke STATIC ${SOURCES})


#add_custom_command(
#        TARGET Arke
#        PRE_BUILD
#        DEPENDS ${PREDEFINED_SHADER_SOURCES}
#        WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
#        COMMAND Python3::Interpreter -m "scripts.generate_shader_headers"
#        --compiler $<TARGET_FILE:Vulkan::glslc>
#        --source "${PROJECT_SOURCE_DIR}/assets/shaders/src"
#        --binary "${PROJECT_SOURCE_DIR}/assets/shaders/bin"
#        --generated-output "${PROJECT_SOURCE_DIR}/src/generated/header"
#)

include(cmake/Targets.cmake)

file(GLOB_RECURSE GENERATED_SHADER_HEADERS src/generated/*)

target_sources(Arke PUBLIC ${GENERATED_SHADER_HEADERS})

add_compile_options(/std:c++20)

set_target_properties(Arke PROPERTIES LINKER_LANGUAGE CXX)

target_include_directories(Arke
        PUBLIC include
        PUBLIC src
)
target_link_directories(Arke PUBLIC library)
target_link_libraries(Arke
        PUBLIC vulkan-1
        PUBLIC spdlogd
        PUBLIC glfw3
        PUBLIC SDL2_test
        PUBLIC SDL2main
        PUBLIC SDL2
)