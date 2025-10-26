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
  URL https://github.com/google/googletest/releases/download/v1.17.0/googletest-1.17.0.tar.gz
  DOWNLOAD_EXTRACT_TIMESTAMP TRUE
)

# Prevent GoogleTest from being installed
set(INSTALL_GTEST OFF CACHE BOOL "Disable installation of GoogleTest" FORCE)
set(BUILD_GMOCK OFF CACHE BOOL "Disable GoogleMock" FORCE)

# tests/CMakeLists.txt, before FetchContent_MakeAvailable(googletest)
# Temporarily force static libs while googletest configures
set(_OLD_BSL "${BUILD_SHARED_LIBS}")
set(BUILD_SHARED_LIBS OFF CACHE BOOL "" FORCE)

FetchContent_MakeAvailable(googletest)

# Restore parent setting
set(BUILD_SHARED_LIBS "${_OLD_BSL}" CACHE BOOL "" FORCE)

link_directories(${CMAKE_SOURCE_DIR}/lib)

add_executable(test_datetime test_datetime.cc)


# Determine which datetime library to link against
set(DATETIME_LIB_TARGET "")
if(WIN32)
    set(DATETIME_LIB_TARGET datetime)
elseif(TARGET datetime_shared)
    set(DATETIME_LIB_TARGET datetime_shared)
elseif(TARGET datetime_static)
    set(DATETIME_LIB_TARGET datetime_static)
else()
    message(FATAL_ERROR "No datetime library target found")
endif()

target_link_libraries(test_datetime
    gtest_main
    ${DATETIME_LIB_TARGET}
    m
)

# Include headers
target_include_directories(test_datetime PRIVATE ${CMAKE_SOURCE_DIR}/include)

# So test executable can find the shared lib at runtime (only needed for shared libs)
if(BUILD_SHARED_LIBS)
    set_target_properties(test_datetime PROPERTIES
        BUILD_RPATH ${CMAKE_SOURCE_DIR}/lib
        INSTALL_RPATH ${CMAKE_SOURCE_DIR}/lib
    )
endif()

include(GoogleTest)
gtest_discover_tests(test_datetime)

# On Windows the test executable won't find DLLs located in other directories
# (RPATH doesn't apply). If we built shared libs, copy the datetime DLL
# next to the test executable so it can be loaded at runtime in CI.
if(BUILD_SHARED_LIBS AND WIN32)
    # Copy the datetime DLL to the test exe dir
    add_custom_command(TARGET test_datetime POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
            $<TARGET_FILE:datetime>
            $<TARGET_FILE_DIR:test_datetime>
    )
    # Copy GoogleTest DLLs to the test exe dir (they're in bin/)
    add_custom_command(TARGET test_datetime POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
            $<TARGET_FILE:gtest>
            $<TARGET_FILE_DIR:test_datetime>
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
            $<TARGET_FILE:gtest_main>
            $<TARGET_FILE_DIR:test_datetime>
    )
endif()

# Only build C tests if check library is available
if(CHECK_FOUND OR Check_FOUND)
    add_executable(test_c test_c.c)

    target_include_directories(test_c PRIVATE ${CMAKE_SOURCE_DIR}/include)

    # Link libraries based on which method found check
    if(TARGET PkgConfig::CHECK)
        target_link_libraries(test_c
            PkgConfig::CHECK
            ${DATETIME_LIB_TARGET}
            m
        )
    elseif(TARGET Check::check)
        target_link_libraries(test_c
            Check::check
            ${DATETIME_LIB_TARGET}
            m
        )
    else()
        # Fallback to manual linking
        target_link_libraries(test_c
            check
            ${DATETIME_LIB_TARGET}
            m
        )
    endif()

    # So test executable can find the shared lib at runtime (only needed for shared libs)
    if(BUILD_SHARED_LIBS)
        set_target_properties(test_c PROPERTIES
            BUILD_RPATH ${CMAKE_SOURCE_DIR}/lib
            INSTALL_RPATH ${CMAKE_SOURCE_DIR}/lib
        )
    endif()
else()
    message(WARNING "Check library not found. C tests will not be built. Install libcheck-dev or check package.")
endif()
