cmake_minimum_required(VERSION 3.15)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")
include(downloadP4api)

project(
    p4t
    LANGUAGES CXX
    VERSION 1.0
    DESCRIPTION "P4 Tool"
)

# Generate compile_commands.json, will be used by lsp_server
set(CMAKE_EXPORT_COMPILE_COMMANDS 1)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(NOT P4API_ROOT_DIR)
    set(P4API_VENDOR_DIR "${CMAKE_SOURCE_DIR}/vendor/p4api")
    set(P4API_VERSION "2025.1.2761706")
    set(P4API_ROOT_DIR "${P4API_VENDOR_DIR}/p4api-${P4API_VERSION}")
endif()

message(STATUS "P4API_ROOT_DIR:" ${P4API_ROOT_DIR})

if(NOT EXISTS "${P4API_ROOT_DIR}")
    download_and_extract_p4api()
endif()

file(GLOB_RECURSE INCLUDES include/**.h)
file(GLOB_RECURSE SOURCES source/**.cpp)
add_executable(${PROJECT_NAME} ${SOURCES} ${INCLUDES})

add_subdirectory(vendor)

target_include_directories(${PROJECT_NAME} PRIVATE
    include/p4t
    include/p4t/commands
    include/p4t/utils
)

if (MSVC)
    # NOTE: I'm not sure if these lines below are the same, so better to keep all
    # add_compile_options("/MT$<$<CONFIG:Debug>:d>")
    # set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
    # Compile with /MT flag for release and /MTd for debug.
    # Do not use /MD or /MDd
    set_property(TARGET ${PROJECT_NAME} PROPERTY MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")

    # WARN: Not sure what does this do, just saw it some where, known to cause build error
    # target_link_options(${PROJECT_NAME} PUBLIC /NODEFAULTLIB:libcmt.lib)
    # target_compile_definitions(${PROJECT_NAME} PUBLIC OS_NT CASE_INSENSITIVE)

    # https://help.perforce.com/helix-core/apis/p4api/current/Content/P4API/client.programming.compiling.html#Compiling_and_linking_P4_Server_applications
    # Although the  document instructs us to link with these lib, but it seems to work just fine without them.
    # target_link_libraries(${PROJECT_NAME} PRIVATE libcmt oldnames kernel32 ws2_32 advapi32)
endif()

target_link_libraries(${PROJECT_NAME} PRIVATE P4API::client CLI11::CLI11 dbg_macro)
