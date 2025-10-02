set(name raylib)
set (RAYLIB_VERSION 5.5)

include(FetchContent)
if (NOT ${name}_FOUND) # If there's none, fetch and build raylib
    FetchContent_Declare(
        ${name} #package name
        URL https://github.com/raysan5/raylib/archive/refs/tags/${RAYLIB_VERSION}.tar.gz #where
    )
    enable_language(OBJC)

    #prefer to use FetchContent_MakeAvailable instead of lowerLever customLogic like this FetchContent_GetProperties+FetchContent_Populate
        # Force static library + position independent code
    set(BUILD_SHARED_LIBS OFF CACHE BOOL "Build static libs" FORCE)
    set(CMAKE_POSITION_INDEPENDENT_CODE ON CACHE BOOL "Enable PIC for static libs" FORCE)

    # Disable examples/tests
    set(BUILD_EXAMPLES OFF CACHE INTERNAL "")
    set(BUILD_GAMES OFF CACHE INTERNAL "")
    FetchContent_MakeAvailable(${name})
endif()
