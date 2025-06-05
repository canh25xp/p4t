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

target_include_directories(p4t PRIVATE ${OPENSSL_INCLUDE_DIR} ${P4API_ROOT_DIR}/include/p4)
target_link_directories(p4t PRIVATE ${P4API_ROOT_DIR}/lib)

if (MSVC)
    target_link_options(p4t PUBLIC /NODEFAULTLIB:libcmt.lib)
    target_link_libraries(p4t PRIVATE libclient librpc libsupp libp4api libp4script libp4script_c libp4script_cstub libp4script_curl libp4script_sqlite)
else()
    target_link_libraries(p4t PRIVATE client rpc supp)
endif()
target_link_libraries(p4t PRIVATE OpenSSL::Crypto OpenSSL::SSL)
