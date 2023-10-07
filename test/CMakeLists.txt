CMAKE_MINIMUM_REQUIRED(VERSION 3.13 FATAL_ERROR)

if (BUILD_TESTS)
    message(DEBUG "Building tests as part of sxelog")

else (BUILD_TESTS)
    message(DEBUG "Building standalone tests against installed sxelog")

    project(sxelog_tests
        LANGUAGES CXX)

    find_package(sxelog REQUIRED)
    add_library(sxelog ALIAS SxE::sxelog)

endif (BUILD_TESTS)

# Tests need to compile with the same standard as sxelog.
# For standalone mode you may need to -DCXX_STANDARD=14.
get_property(sxelog_cxxstd TARGET sxelog PROPERTY CXX_STANDARD)

foreach(testprog stdout file rate customsink squelch spam)
    add_executable(${testprog} ${testprog}.cpp)
    target_link_libraries(${testprog} sxelog)
    set_property(TARGET ${testprog} PROPERTY CXX_STANDARD ${sxelog_cxxstd})
endforeach(testprog)
