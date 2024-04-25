cmake_minimum_required(VERSION 3.14.0 FATAL_ERROR)
include(FetchContent)
project(Example)

enable_testing()

find_package(Enzyme REQUIRED CONFIG)


message("found dir ${Enzyme_DIR}")
message("found ${Enzyme_FOUND}")
get_property(importTargetsAfter DIRECTORY "${CMAKE_SOURCE_DIR}" PROPERTY IMPORTED_TARGETS)
message("imported targets ${importTargetsAfter}")

list(APPEND CMAKE_MODULE_PATH ${catch2_SOURCE_DIR}/extras)


add_subdirectory(src)
