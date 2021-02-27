# vim: set filetype=cmake tabstop=4 shiftwidth=4 expandtab :
CMAKE_MINIMUM_REQUIRED(VERSION 3.7 FATAL_ERROR)

if (BUILD_TESTS)
    message(DEBUG "Building tests as part of sxelog")

else (BUILD_TESTS)
    message(DEBUG "Building standalone tests against installed sxelog")

    project(sxelog_tests
        LANGUAGES CXX)

    find_package(sxelog REQUIRED)
    add_library(sxelog ALIAS SxE::sxelog)

endif (BUILD_TESTS)

add_executable(stdout stdout.cpp)
target_link_libraries(stdout sxelog)

add_executable(file file.cpp)
target_link_libraries(file sxelog)

add_executable(rate rate.cpp)
target_link_libraries(rate sxelog)

add_executable(customsink customsink.cpp)
target_link_libraries(customsink sxelog)

add_executable(squelch squelch.cpp)
target_link_libraries(squelch sxelog)

add_executable(spam spam.cpp)
target_link_libraries(spam sxelog)
