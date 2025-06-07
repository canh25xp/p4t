cmake_minimum_required(VERSION 3.15)

project(P4API)

set(OPENSSL_USE_STATIC_LIBS TRUE)
find_package(OpenSSL REQUIRED)

# Find openssl on the system
if (NOT OPENSSL_ROOT_DIR)
    if (UNIX)
        set(OPENSSL_ROOT_DIR "/usr/local")
    elseif (MSVC)
        set(OPENSSL_ROOT_DIR "C:/Program Files/FireDaemon OpenSSL 3")
    elseif (WIN32)
        set(OPENSSL_ROOT_DIR "C:/msys64/mingw64")
    endif()
    message(STATUS "OPENSSL_ROOT_DIR: ${OPENSSL_ROOT_DIR}")
endif()

message(STATUS "OPENSSL_FOUND: ${OPENSSL_FOUND}")
message(STATUS "OPENSSL_VERSION: ${OPENSSL_VERSION}")
message(STATUS "OPENSSL_INCLUDE_DIR: ${OPENSSL_INCLUDE_DIR}")
message(STATUS "OPENSSL_LIBRARIES: ${OPENSSL_LIBRARIES}")

add_library(p4api_client INTERFACE)

if(MSVC)
    message(FATAL_ERROR "TODO...")
else()
    set(P4API_BASE_DIR "${CMAKE_CURRENT_LIST_DIR}/p4api-2025.1.2761706")
    set(P4API_INCLUDE_DIR "${P4API_BASE_DIR}/include")
    set(P4API_LIBRARY_DIR "${P4API_BASE_DIR}/lib")

    file(GLOB P4API_LIBS
        "${P4API_LIBRARY_DIR}/libclient.a"
        "${P4API_LIBRARY_DIR}/librpc.a"
        "${P4API_LIBRARY_DIR}/libsupp.a"
        "${P4API_LIBRARY_DIR}/p4script_cstub.a"
    )

    target_link_libraries(p4api_client INTERFACE ${P4API_LIBS})
endif()

target_include_directories(p4api_client INTERFACE "${P4API_INCLUDE_DIR}")

target_link_libraries(p4api_client INTERFACE OpenSSL::SSL OpenSSL::Crypto)

add_library(P4API::client ALIAS p4api_client)
