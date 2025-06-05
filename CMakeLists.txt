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
    elseif (WIN32)
        set(OPENSSL_ROOT_DIR "C:/msys64/mingw64")
    elseif (MSVC)
        set(OPENSSL_ROOT_DIR "C:/Program Files/FireDaemon OpenSSL 3")
    endif()
endif()
message("OPENSSL_ROOT_DIR: ${OPENSSL_FOUND}")
set(OPENSSL_USE_STATIC_LIBS TRUE)
find_package(OpenSSL REQUIRED)

message("OPENSSL_FOUND: ${OPENSSL_FOUND}")
message("OPENSSL_VERSION: ${OPENSSL_VERSION}")
message("OPENSSL_INCLUDE_DIR: ${OPENSSL_INCLUDE_DIR}")
message("OPENSSL_LIBRARIES: ${OPENSSL_LIBRARIES}")

set(P4API vendor/p4api)

file(GLOB_RECURSE INCLUDES include/**.h)
file(GLOB_RECURSE SOURCES source/**.cpp)
add_executable(p4t ${SOURCES})

target_include_directories(p4t PRIVATE ${OPENSSL_INCLUDE_DIR} ${P4API}/include/p4)
target_link_directories(p4t PRIVATE ${P4API}/lib)
target_link_libraries(p4t PRIVATE client rpc supp OpenSSL::Crypto OpenSSL::SSL)
