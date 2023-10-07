CMAKE_MINIMUM_REQUIRED(VERSION 3.13 FATAL_ERROR)

# It's documentation sucks but it's more universal than SxE's own versions for this.
include(GenerateExportHeader)

option(BUILD_SHARED_LIBS "Build shared libraries" ON)

add_library(sxelog
    Log.cpp
    LogSink.cpp
    LogSquelch.cpp
    RateCounter.cpp
    TextLogSink.cpp
)

# Features used.
target_compile_features(sxelog INTERFACE
    cxx_nullptr
    cxx_auto_type
    cxx_override
    cxx_range_for
)

# Generates a header with SXELOG_EXPORT for the usual dllimport/export usage
# based on sxelog_EXPORTS.
#
set(sxelog_export_hpp ${CMAKE_CURRENT_BINARY_DIR}/include/sxe/logging/sxelog_export.hpp)
generate_export_header(sxelog
    EXPORT_FILE_NAME ${sxelog_export_hpp})

# Make sure -std= is set.
set_property(TARGET sxelog PROPERTY CXX_REQUIRED 14)
if(${CMAKE_VERSION} VERSION_LESS "3.8.0")
    # - cmake 3.7 limited this to 14.
    set_property(TARGET sxelog PROPERTY CXX_STANDARD 14)
elseif(${CMAKE_VERSION} VERSION_LESS "3.12.0")
    # - cmake 3.8 limited this to 17.
    set_property(TARGET sxelog PROPERTY CXX_STANDARD 17)
elseif(${CMAKE_VERSION} VERSION_LESS "3.20")
    # - cmake 3.12 limited this to 20.
    set_property(TARGET sxelog PROPERTY CXX_STANDARD 20)
else()
    # - cmake 3.20 limited this to 23.
    set_property(TARGET sxelog PROPERTY CXX_STANDARD 23)
endif()

# honor visiblity even when building static libs.
cmake_policy(SET CMP0063 NEW)
# Commenting out because gcc/clang and msvc disagree on the result.
# set_property(TARGET sxelog PROPERTY CXX_VISIBILITY_PRESET hidden)

target_include_directories(sxelog PUBLIC
    # allow #include <sxe/logging/foo.hpp> for include/
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../include>

    # api.hpp below.
    $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/include>

    # for users via find_package()
    $<INSTALL_INTERFACE:include>
)


# Various things to deal with becoming a library cmake can link to.

install(TARGETS sxelog
    EXPORT sxelogTargets
    RUNTIME DESTINATION "${CMAKE_INSTALL_BINDIR}"
    ARCHIVE DESTINATION "${CMAKE_INSTALL_LIBDIR}"
    LIBRARY DESTINATION "${CMAKE_INSTALL_LIBDIR}"
    INCLUDES DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}"
    PUBLIC_HEADER DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}")

install(FILES ${sxelog_export_hpp} DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/sxe/logging)

install(EXPORT sxelogTargets
        FILE sxelogTargets.cmake
        NAMESPACE SxE::
        DESTINATION lib/cmake/sxelog)
