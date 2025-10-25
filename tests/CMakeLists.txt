# Try to find check library via pkg-config first, then fallback to find_package
find_package(PkgConfig QUIET)
if(PkgConfig_FOUND)
    pkg_check_modules(CHECK QUIET IMPORTED_TARGET check)
endif()

# If pkg-config didn't find check, try find_package
if(NOT CHECK_FOUND)
    find_package(Check QUIET)
endif()

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/heads/main.zip
)

# Prevent GoogleTest from being installed
set(INSTALL_GTEST OFF CACHE BOOL "Disable installation of GoogleTest" FORCE)
set(BUILD_GMOCK OFF CACHE BOOL "Disable GoogleMock" FORCE)

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

# Only build C tests if check library is available
if(CHECK_FOUND OR Check_FOUND)
    add_executable(test_c test_c.c)

    target_include_directories(test_c PRIVATE ${CMAKE_SOURCE_DIR}/include)

    # Link libraries based on which method found check
    if(TARGET PkgConfig::CHECK)
        target_link_libraries(test_c
            PkgConfig::CHECK
            datetime
            m
        )
    elseif(TARGET Check::check)
        target_link_libraries(test_c
            Check::check
            datetime
            m
        )
    else()
        # Fallback to manual linking
        target_link_libraries(test_c
            check
            datetime
            m
        )
    endif()

    set_target_properties(test_c PROPERTIES
        BUILD_RPATH ${CMAKE_SOURCE_DIR}/lib
        INSTALL_RPATH ${CMAKE_SOURCE_DIR}/lib
    )
else()
    message(WARNING "Check library not found. C tests will not be built. Install libcheck-dev or check package.")
endif()
