# vim: set filetype=cmake tabstop=4 shiftwidth=4 expandtab :
CMAKE_MINIMUM_REQUIRED(VERSION 3.7 FATAL_ERROR)

# For all examples here.
if(MSVC)
    add_compile_options(/wd4251 /wd4275)
    add_compile_definitions(_CRT_SECURE_NO_WARNINGS)
endif(MSVC)

# Surely there's a better way of doing this? set(somevar the thingy) doesn't
# work, and I'd like to keep the namespace when installed.

if (BUILD_TESTS)
    message(DEBUG "Building tests as part of sxelog")

    add_executable(stdout stdout.cpp)
    target_link_libraries(stdout sxelog)

    add_executable(file file.cpp)
    target_link_libraries(file sxelog)

else (BUILD_TESTS)
    message(DEBUG "Building standalone tests against installed sxelog")
    project(sxelog_tests
        LANGUAGES CXX)

    find_package(sxelog REQUIRED)

    add_executable(stdout stdout.cpp)
    target_link_libraries(stdout SxE::sxelog)

    add_executable(file file.cpp)
    target_link_libraries(file SxE::sxelog)

endif (BUILD_TESTS)