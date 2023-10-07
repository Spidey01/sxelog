# vim: set filetype=cmake tabstop=4 shiftwidth=4 expandtab :
CMAKE_MINIMUM_REQUIRED(VERSION 3.7 FATAL_ERROR)

project(libsxelog
    VERSION 2.0.0
    LANGUAGES CXX)

add_subdirectory(include)
add_subdirectory(source)

option(BUILD_TESTS "Build test programs" ON)
if (BUILD_TESTS)
    add_subdirectory(test)
endif (BUILD_TESTS)



set(CPACK_PACKAGE_VERSION_MAJOR ${PROJECT_VERSION_MAJOR})
set(CPACK_PACKAGE_VERSION_MINOR ${PROJECT_VERSION_MINOR})
set(CPACK_PACKAGE_VERSION_PATCH ${PROJECT_VERSION_PATCH})
set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_CURRENT_SOURCE_DIR}/COPYING")
set(CPACK_RESOURCE_FILE_README "${CMAKE_CURRENT_SOURCE_DIR}/README.md")
set(CPACK_GENERATOR "ZIP;TGZ")
find_program(HAVE_DEB dpkg)
if (HAVE_DEB)
    list(APPEND CPACK_GENERATOR "DEB")
set(CPACK_DEBIAN_PACKAGE_DEPENDS "")
endif()
find_program(HAVE_RPM rpmbuild)
if (HAVE_RPM)
    list(APPEND CPACK_GENERATOR "RPM")
set(CPACK_RPM_PACKAGE_DEPENDS "")
endif()
include(CPack)

# Allow us to be find_package()'d.
include(CMakePackageConfigHelpers)

configure_package_config_file(sxelogConfig.cmake.in
    ${CMAKE_CURRENT_BINARY_DIR}/sxelogConfig.cmake
    INSTALL_DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/sxelog
)
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/sxelogConfig.cmake
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/sxelog)

write_basic_package_version_file(
    sxelogConfigVersion.cmake
    VERSION ${PACKAGE_VERSION}
    COMPATIBILITY SameMajorVersion
    )
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/sxelogConfigVersion.cmake
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/sxelog)
