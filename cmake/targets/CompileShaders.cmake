cmake_minimum_required(VERSION 3.24)

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

add_custom_target(
        CompileShaders
        WORKING_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/../..
        COMMAND Python3::Interpreter -m scripts.compile_shader -s assets/shaders -o build/shaders -c $<TARGET_FILE:Vulkan::glslc>
        COMMAND Python3::Interpreter -m scripts.generate_shader_headers -c -b build/shaders -o src/generated/shaders -t assets/generator_templates/shader_encoded.h.jinja
)