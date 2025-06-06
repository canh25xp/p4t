cmake_minimum_required(VERSION 3.15)

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

# Find openssl on the system
if (NOT OPENSSL_ROOT_DIR)
    if (UNIX)
        set(OPENSSL_ROOT_DIR "/usr/local")
    elseif (MSVC)
        set(OPENSSL_ROOT_DIR "C:/Program Files/FireDaemon OpenSSL 3")
    elseif (WIN32)
        set(OPENSSL_ROOT_DIR "C:/msys64/mingw64")
    endif()
    message("OPENSSL_ROOT_DIR: ${OPENSSL_ROOT_DIR}")
endif()
set(OPENSSL_USE_STATIC_LIBS TRUE)
find_package(OpenSSL REQUIRED)

message("OPENSSL_FOUND: ${OPENSSL_FOUND}")
message("OPENSSL_VERSION: ${OPENSSL_VERSION}")
message("OPENSSL_INCLUDE_DIR: ${OPENSSL_INCLUDE_DIR}")
message("OPENSSL_LIBRARIES: ${OPENSSL_LIBRARIES}")

if (NOT P4API_ROOT_DIR )
    set(P4API_ROOT_DIR "./vendor/p4api/p4api-2024.1.2724731")
    message("P4API_ROOT_DIR:" ${P4API_ROOT_DIR})
endif()

file(GLOB_RECURSE INCLUDES include/**.h)
file(GLOB_RECURSE SOURCES source/**.cpp)
add_executable(p4t ${SOURCES})

add_subdirectory(vendor)

target_include_directories(p4t PRIVATE
    ${P4API_ROOT_DIR}/include
    include
)

target_link_directories(p4t PRIVATE ${P4API_ROOT_DIR}/lib)

if (MSVC)
    # NOTE: I'm not sure if these lines below are the same, so better to keep all
    # add_compile_options("/MT$<$<CONFIG:Debug>:d>")
    # set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
    # Compile with /MT flag for release and /MTd for debug.
    # Do not use /MD or /MDd
    set_property(TARGET p4t PROPERTY MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")

    # WARN: Not sure what does this do, just saw it some where, known to cause build error
    # target_link_options(p4t PUBLIC /NODEFAULTLIB:libcmt.lib)
    # target_compile_definitions(p4t PUBLIC OS_NT CASE_INSENSITIVE)
    target_link_libraries(p4t PRIVATE libclient librpc libsupp libp4api libp4script libp4script_c libp4script_cstub libp4script_curl libp4script_sqlite)

    # https://help.perforce.com/helix-core/apis/p4api/current/Content/P4API/client.programming.compiling.html#Compiling_and_linking_P4_Server_applications
    # Although the  document instructs us to link with these lib, but it seems to work just fine without them.
    # target_link_libraries(p4t PRIVATE libcmt oldnames kernel32 ws2_32 advapi32)
else()
    target_link_libraries(p4t PRIVATE client rpc supp)
endif()

target_link_libraries(p4t PRIVATE OpenSSL::Crypto OpenSSL::SSL CLI11::CLI11 dbg_macro)
