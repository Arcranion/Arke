find_package(
        Vulkan
        REQUIRED
        COMPONENTS glslc
)

function(compile_shaders_recursive SOURCE_PATH OUTPUT_PATH COMPILED_LIST_VARIABLE)
    message("${SOURCE_PATH}")
    file(GLOB SOURCE_FILES "${SOURCE_PATH}/*.vert" "${SOURCE_PATH}/*.frag" "${SOURCE_PATH}/*.tesc" "${SOURCE_PATH}/*.tese" "${SOURCE_PATH}/*.geom" "${SOURCE_PATH}/*.comp")

    foreach (INPUT_PATH ${SOURCE_FILES})
        file(RELATIVE_PATH RELATIVE_INPUT_PATH ${SOURCE_PATH} ${INPUT_PATH})
        set(COMPILED_OUTPUT_PATH "${OUTPUT_PATH}/${RELATIVE_INPUT_PATH}")
        get_filename_component(COMPILED_OUTPUT_PATH ${COMPILED_OUTPUT_PATH} NAME)
        set(COMPILED_OUTPUT_PATH ${COMPILED_OUTPUT_PATH}.spv)

        set(GENERATED_OUTPUT_PATH "${OUTPUT_PATH}/${RELATIVE_INPUT_PATH}.generated.h")

        add_custom_command(
                OUTPUT ${COMPILED_OUTPUT_PATH}
                COMMAND ${CMAKE_COMMAND} -E cmake_echo_color --green "[Compiling] ${RELATIVE_INPUT_PATH} --> ${COMPILED_OUTPUT_PATH}"
                COMMAND Vulkan::glslc --target-env=opengl ${INPUT_PATH} -o ${COMPILED_OUTPUT_PATH}
                COMMAND Python3::Interpreter -m scripts.generate_shader_header --binary ${COMPILED_OUTPUT_PATH} --output ${GENERATED_OUTPUT_PATH} --template assets/generator_templates/shader_encoded.h.jinja
                WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
#                DEPENDS ${INPUT_PATH}
        )

        list(APPEND ${COMPILED_LIST_VARIABLE} ${COMPILED_OUTPUT_PATH})
    endforeach()
endfunction()