# Create a shared library from all .cc files in this directory
file(GLOB DATETIME_SRC CONFIGURE_DEPENDS "*.cc")

set(TARGETS_TO_INSTALL)


# On Windows, always build a shared library named 'datetime' for compatibility
if(WIN32)
    add_library(datetime SHARED ${DATETIME_SRC})
    target_compile_features(datetime PRIVATE cxx_std_23)
    target_compile_options(datetime PRIVATE -O3 -g -Wextra -fPIC)
    target_link_libraries(datetime PRIVATE m)
    target_include_directories(datetime PUBLIC ${CMAKE_SOURCE_DIR}/include)
    list(APPEND TARGETS_TO_INSTALL datetime)
else()
    # Build shared library if requested (non-Windows)
    if(BUILD_SHARED_LIBS)
        add_library(datetime_shared SHARED ${DATETIME_SRC})
        target_compile_features(datetime_shared PRIVATE cxx_std_23)
        target_compile_options(datetime_shared PRIVATE -O3 -g -Wextra -fPIC)
        target_link_libraries(datetime_shared PRIVATE m)
        target_include_directories(datetime_shared PUBLIC ${CMAKE_SOURCE_DIR}/include)
        set_target_properties(datetime_shared PROPERTIES OUTPUT_NAME datetime)
        list(APPEND TARGETS_TO_INSTALL datetime_shared)
    endif()
endif()

# Build static library if requested (but not on Windows - keep it simple there)
if(BUILD_STATIC_LIBS AND NOT WIN32)
    add_library(datetime_static STATIC ${DATETIME_SRC})
    
    # Use C++23, enable warnings and optimizations
    target_compile_features(datetime_static PRIVATE cxx_std_23)
    target_compile_options(datetime_static PRIVATE -O3 -g -Wextra -fPIC)
    
    # Link math lib
    target_link_libraries(datetime_static PRIVATE m)
    
    # Public include path
    target_include_directories(datetime_static PUBLIC ${CMAKE_SOURCE_DIR}/include)
    
    # Set output name to remove the _static suffix
    set_target_properties(datetime_static PROPERTIES OUTPUT_NAME datetime)
    
    # Add to install list
    list(APPEND TARGETS_TO_INSTALL datetime_static)
endif()


# Only create alias for non-Windows
if(NOT WIN32)
    if(BUILD_SHARED_LIBS)
        add_library(datetime ALIAS datetime_shared)
    elseif(BUILD_STATIC_LIBS)
        add_library(datetime ALIAS datetime_static)
    endif()
endif()

# Output library to lib/
foreach(target ${TARGETS_TO_INSTALL})
    set_target_properties(${target} PROPERTIES
        LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib
        ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib
        RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib
    )
endforeach()

# Install targets
if(TARGETS_TO_INSTALL)
    install(TARGETS ${TARGETS_TO_INSTALL}
        LIBRARY DESTINATION lib
        RUNTIME DESTINATION bin        # For Windows .dll
        ARCHIVE DESTINATION lib        # For static libs
    )
endif()

install(DIRECTORY ${CMAKE_SOURCE_DIR}/include/ DESTINATION include)
