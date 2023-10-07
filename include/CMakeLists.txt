include(GNUInstallDirs)

# This file just makes sure install and package related targets work.
# For build related interface see source/CMakeLists.txt.

# package sxe/logging/*.hpp -> sxe/logging/*.hpp
install(DIRECTORY sxe/logging
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/sxe FILES_MATCHING PATTERN "*.hpp")
