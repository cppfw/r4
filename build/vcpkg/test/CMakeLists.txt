cmake_minimum_required(VERSION 3.10)

set(CMAKE_TOOLCHAIN_FILE $ENV{VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake)

project(test)

find_package(myci CONFIG REQUIRED)
find_package(tst CONFIG REQUIRED)
find_package(r4 CONFIG REQUIRED)

include(../../cmake/unit_tests.cmake)
