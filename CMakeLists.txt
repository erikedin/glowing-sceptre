cmake_minimum_required (VERSION 2.6)
project (GlowingSceptre)

 add_compile_options(-std=c++11)

add_subdirectory(./googletest-release-1.8.0/googlemock
                 ${CMAKE_BINARY_DIR}/googletest-build)

include_directories ("${PROJECT_SOURCE_DIR}/include")

add_library(glowingsceptre src/base64.cpp src/hex.cpp)
add_executable(acceptance_glowingsceptre test/set1.cpp)
target_link_libraries(acceptance_glowingsceptre glowingsceptre gtest_main)

enable_testing()
add_test(NAME acceptance COMMAND acceptance_glowingsceptre)