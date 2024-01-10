set(___PATH_MODULES_DIR___ ${CMAKE_CURRENT_LIST_DIR})

function(add_shader_target TARGET_NAME SOURCE_DIR OUTPUT_DIR)
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

    get_filename_component(SOURCE_ABS_DIR ${SOURCE_DIR} ABSOLUTE)
    get_filename_component(OUTPUT_ABS_DIR ${OUTPUT_DIR} ABSOLUTE)

    add_custom_target(
            ${TARGET_NAME}
            WORKING_DIRECTORY ${___PATH_MODULES_DIR___}/../../
            COMMAND Python3::Interpreter -m scripts.compile_shader -s ${SOURCE_ABS_DIR} -o ${OUTPUT_ABS_DIR} -c $<TARGET_FILE:Vulkan::glslc>
    )
endfunction()