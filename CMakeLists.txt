cmake_minimum_required(VERSION 3.2 FATAL_ERROR)
include(CMakePrintHelpers)
project( XML_PARSER )

set( LIBRARY_NAME XML_PARSER )


file(GLOB SRC_FILES
    "${CMAKE_CURRENT_LIST_DIR}/src/*"
)

# cmake_print_variables(SRC_FILES)

add_executable(
    ${LIBRARY_NAME}
    ${SRC_FILES}
)

set_target_properties(
    ${LIBRARY_NAME}
    PROPERTIES
    CXX_STANDARD 17
    # RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
    VS_CONFIGURATION_TYPE "Application"
    CMAKE_CONFIGURATION_TYPES "RelWithDebInfo"
    )

add_compile_definitions(NOMINMAX)
