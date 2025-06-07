function(download_and_extract_p4api)
    cmake_minimum_required(VERSION 3.18)  # Required for ARCHIVE_EXTRACT
    message("P4API downloading")

    set(P4API_VENDOR_DIR "${CMAKE_SOURCE_DIR}/vendor/p4api")
    set(P4API_VERSION "2025.1.2761706")

    if(UNIX)
        set(P4API_ARCHIVE_URLS
            "https://filehost.perforce.com/perforce/r25.1/bin.linux26x86_64/p4api-glibc2.3-openssl3.tgz"
        )
        set(P4API_ROOT_DIR "${P4API_VENDOR_DIR}/p4api-${P4API_VERSION}")
    elseif (MSVC)
        if (CMAKE_GENERATOR MATCHES "Visual Studio 17 2022")
            set(P4API_ARCHIVE_URLS
              "https://filehost.perforce.com/perforce/r25.1/bin.ntx64/p4api_vs2022_static_openssl3.zip"
              "https://filehost.perforce.com/perforce/r25.1/bin.ntx64/p4api_vs2022_static_vsdebug_openssl3.zip"
            )
            set(P4API_RELEASE_DIR "${P4API_VENDOR_DIR}/p4api-${P4API_VERSION}-vs2022_static")
            set(P4API_DEBUG_DIR   "${P4API_VENDOR_DIR}/p4api-${P4API_VERSION}-vs2022_static_vsdebug")
        elseif(CMAKE_GENERATOR MATCHES "Visual Studio 15 2017")
            set(P4API_ARCHIVE_URLS
              "https://filehost.perforce.com/perforce/r25.1/bin.ntx64/p4api_vs2017_static_openssl3.zip"
              "https://filehost.perforce.com/perforce/r25.1/bin.ntx64/p4api_vs2017_static_vsdebug_openssl3.zip"
            )
            set(P4API_RELEASE_DIR "${P4API_VENDOR_DIR}/p4api-${P4API_VERSION}-vs2017_static")
            set(P4API_DEBUG_DIR   "${P4API_VENDOR_DIR}/p4api-${P4API_VERSION}-vs2017_static_vsdebug")
        endif()
    elseif(WIN32)
        set(P4API_ARCHIVE_URLS
          "https://filehost.perforce.com/perforce/r25.1/bin.mingw64x64/p4api-openssl3_gcc8_win32_seh.zip"
        )
        set(P4API_ROOT_DIR "${P4API_VENDOR_DIR}/p4api-${P4API_VERSION}")
    else()
        message(FATAL_ERROR "Unsupported platform")
    endif()

    file(MAKE_DIRECTORY "${P4API_VENDOR_DIR}")

    foreach(url IN LISTS P4API_ARCHIVE_URLS)
        get_filename_component(archive_name "${url}" NAME)
        set(archive_path "${P4API_VENDOR_DIR}/${archive_name}")

        if(NOT EXISTS "${archive_path}")
            message(STATUS "Download url ${url}...")
            file(DOWNLOAD "${url}" "${archive_path}" SHOW_PROGRESS)
        endif()

        if(MSVC)
            if(archive_name MATCHES "vsdebug")
                set(extract_dir "${P4API_DEBUG_DIR}")
            else()
                set(extract_dir "${P4API_RELEASE_DIR}")
            endif()
        else()
            set(extract_dir "${P4API_ROOT_DIR}")
        endif()

        if(NOT EXISTS "${extract_dir}")
            message(STATUS "Extracting ${archive_name} to ${P4API_VENDOR_DIR}...")
            file(ARCHIVE_EXTRACT INPUT "${archive_path}" DESTINATION "${P4API_VENDOR_DIR}")
        endif()
    endforeach()

    message(STATUS "P4API downloaded to: ${P4API_ROOT_DIR}")
endfunction()
