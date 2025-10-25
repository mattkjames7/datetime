cmake_minimum_required(VERSION 3.5)
project(DateTime LANGUAGES C CXX)

set(CMAKE_C_STANDARD 23)
set(CMAKE_CXX_STANDARD 23)

option(BUILD_TESTING "Build unit tests" OFF)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -O3 -Wextra -fPIC")

add_subdirectory(src)

if(BUILD_TESTING)
  enable_testing()
  add_subdirectory(tests)
endif()

# Add a manual uninstall target
configure_file(
  ${CMAKE_SOURCE_DIR}/cmake/cmake_uninstall.cmake.in
  ${CMAKE_BINARY_DIR}/cmake_uninstall.cmake
  IMMEDIATE @ONLY
)

add_custom_target(uninstall
  COMMAND ${CMAKE_COMMAND} -P ${CMAKE_BINARY_DIR}/cmake_uninstall.cmake
)