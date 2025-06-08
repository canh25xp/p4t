# https://help.perforce.com/helix-core/apis/p4api/current/Content/P4API/client.programming.compiling.html
cmake_minimum_required(VERSION 3.15)

project(P4API)

set(OPENSSL_USE_STATIC_LIBS TRUE)

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

find_package(OpenSSL REQUIRED)

message(STATUS "OPENSSL_FOUND: ${OPENSSL_FOUND}")
message(STATUS "OPENSSL_VERSION: ${OPENSSL_VERSION}")
message(STATUS "OPENSSL_INCLUDE_DIR: ${OPENSSL_INCLUDE_DIR}")
message(STATUS "OPENSSL_LIBRARIES: ${OPENSSL_LIBRARIES}")


add_library(p4api_client INTERFACE)

set(P4API_VERSION "2025.1.2761706")

if(MSVC)
    if (CMAKE_GENERATOR MATCHES "Visual Studio 17 2022")
        set(P4API_BASE_DIR "${CMAKE_CURRENT_LIST_DIR}/p4api-${P4API_VERSION}-vs2022_static")
        set(P4API_RELEASE_DIR "${CMAKE_CURRENT_LIST_DIR}/p4api-${P4API_VERSION}-vs2022_static")
        set(P4API_DEBUG_DIR   "${CMAKE_CURRENT_LIST_DIR}/p4api-${P4API_VERSION}-vs2022_static_vsdebug")
    elseif(CMAKE_GENERATOR MATCHES "Visual Studio 15 2017")
        set(P4API_BASE_DIR "${CMAKE_CURRENT_LIST_DIR}/p4api-${P4API_VERSION}-vs2017_static")
        set(P4API_RELEASE_DIR "${CMAKE_CURRENT_LIST_DIR}/p4api-${P4API_VERSION}-vs2017_static")
        set(P4API_DEBUG_DIR   "${CMAKE_CURRENT_LIST_DIR}/p4api-${P4API_VERSION}-vs2017_static_vsdebug")
    endif()

    set(P4API_INCLUDE_DIR "${P4API_BASE_DIR}/include")
    set(P4API_LIBRARY_RELEASE_DIR "${P4API_RELEASE_DIR}/lib")
    set(P4API_LIBRARY_DEBUG_DIR "${P4API_DEBUG_DIR}/lib")

    target_link_libraries(p4api_client INTERFACE
        $<$<CONFIG:Release>:${P4API_LIBRARY_RELEASE_DIR}/libclient.lib>
        $<$<CONFIG:Release>:${P4API_LIBRARY_RELEASE_DIR}/librpc.lib>
        $<$<CONFIG:Release>:${P4API_LIBRARY_RELEASE_DIR}/libsupp.lib>
        $<$<CONFIG:Release>:${P4API_LIBRARY_RELEASE_DIR}/libp4script_cstub.lib>

        $<$<CONFIG:Debug>:${P4API_LIBRARY_DEBUG_DIR}/libclient.lib>
        $<$<CONFIG:Debug>:${P4API_LIBRARY_DEBUG_DIR}/librpc.lib>
        $<$<CONFIG:Debug>:${P4API_LIBRARY_DEBUG_DIR}/libsupp.lib>
        $<$<CONFIG:Debug>:${P4API_LIBRARY_DEBUG_DIR}/libp4script_cstub.lib>
    )

    target_link_libraries(p4api_client INTERFACE
        $<$<CONFIG:Release>:libcmt>
        $<$<CONFIG:Debug>:libcmtd>
        oldnames
        kernel32
        ws2_32
        advapi32
    )
else()
    set(P4API_BASE_DIR "${CMAKE_CURRENT_LIST_DIR}/p4api-${P4API_VERSION}")
    set(P4API_INCLUDE_DIR "${P4API_BASE_DIR}/include")
    set(P4API_LIBRARY_DIR "${P4API_BASE_DIR}/lib")

    file(GLOB P4API_LIBS
        "${P4API_LIBRARY_DIR}/libclient.a"
        "${P4API_LIBRARY_DIR}/librpc.a"
        "${P4API_LIBRARY_DIR}/libsupp.a"
    )

    target_link_libraries(p4api_client INTERFACE ${P4API_LIBS})
endif()

target_include_directories(p4api_client INTERFACE "${P4API_INCLUDE_DIR}")

target_link_libraries(p4api_client INTERFACE OpenSSL::SSL OpenSSL::Crypto)

add_library(P4API::client ALIAS p4api_client)
