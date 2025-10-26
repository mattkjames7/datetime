# Create a shared library from all .cc files in this directory
file(GLOB DATETIME_SRC CONFIGURE_DEPENDS "*.cc")

set(TARGETS_TO_INSTALL)


# On Windows, always build a shared library named 'datetime' for compatibility
if(WIN32)
    add_library(datetime SHARED ${DATETIME_SRC})
    target_compile_features(datetime PRIVATE cxx_std_11)
    target_include_directories(datetime PUBLIC 
        $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
    )
    target_link_libraries(datetime PRIVATE m)
    # Define macro for Windows DLL exports
    target_compile_definitions(datetime PRIVATE BUILDING_DATETIME)
    list(APPEND TARGETS_TO_INSTALL datetime)
else()
    # Build shared library if requested (non-Windows)
    if(BUILD_SHARED_LIBS)
        add_library(datetime_shared SHARED ${DATETIME_SRC})
        target_compile_features(datetime_shared PRIVATE cxx_std_11)
        target_include_directories(datetime_shared PUBLIC 
            $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/include>
            $<INSTALL_INTERFACE:include>
        )
        target_link_libraries(datetime_shared PRIVATE m)
        set_target_properties(datetime_shared PROPERTIES 
            OUTPUT_NAME datetime
            VERSION ${PROJECT_VERSION}
            SOVERSION ${PROJECT_VERSION_MAJOR}
        )
        list(APPEND TARGETS_TO_INSTALL datetime_shared)
    endif()
endif()

# Build static library if requested (but not on Windows - keep it simple there)
if(BUILD_STATIC_LIBS AND NOT WIN32)
    add_library(datetime_static STATIC ${DATETIME_SRC})
    
    # Use C++11, enable warnings and optimizations
    target_compile_features(datetime_static PRIVATE cxx_std_11)
    
    # Link math lib
    target_link_libraries(datetime_static PRIVATE m)
    
    # Public include path with proper generator expressions
    target_include_directories(datetime_static PUBLIC 
        $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
    )
    
    # Set output name and version
    set_target_properties(datetime_static PROPERTIES 
        OUTPUT_NAME datetime
        VERSION ${PROJECT_VERSION}
    )
    
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

# Install targets with proper config
if(TARGETS_TO_INSTALL)
    install(TARGETS ${TARGETS_TO_INSTALL}
        EXPORT DateTimeTargets
        LIBRARY DESTINATION lib
        RUNTIME DESTINATION bin        # For Windows .dll
        ARCHIVE DESTINATION lib        # For static libs
        INCLUDES DESTINATION include   # For imported targets
    )
    
    # Install export targets
    install(EXPORT DateTimeTargets
        FILE DateTimeTargets.cmake
        DESTINATION lib/cmake/DateTime
    )
endif()

# Install headers
install(DIRECTORY ${CMAKE_SOURCE_DIR}/include/ 
    DESTINATION include
    FILES_MATCHING PATTERN "*.h"
)
