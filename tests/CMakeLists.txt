include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/heads/main.zip
)
FetchContent_MakeAvailable(googletest)

link_directories(${CMAKE_SOURCE_DIR}/lib)

add_executable(test_datetime test_datetime.cc)

# Link to Google Test + your datetime shared lib
target_link_libraries(test_datetime
    gtest_main
    datetime
    m
)

# Include headers
target_include_directories(test_datetime PRIVATE ${CMAKE_SOURCE_DIR}/include)

# So test executable can find the shared lib at runtime
set_target_properties(test_datetime PROPERTIES
    BUILD_RPATH ${CMAKE_SOURCE_DIR}/lib
    INSTALL_RPATH ${CMAKE_SOURCE_DIR}/lib
)

include(GoogleTest)
gtest_discover_tests(test_datetime)
