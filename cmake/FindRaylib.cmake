include(FetchContent)

set (RAYLIB_VERSION 5.0)

if (NOT raylib_FOUND) # If there's none, fetch and build raylib
    include(FetchContent)
    FetchContent_Declare(
        raylib #package name
        URL https://github.com/raysan5/raylib/archive/refs/tags/${RAYLIB_VERSION}.tar.gz #where
    )
    #prefer to use FetchContent_MakeAvailable instead of lowerLever customLogic like this FetchContent_GetProperties+FetchContent_Populate
    set(BUILD_EXAMPLES OFF CACHE INTERNAL "")
    FetchContent_MakeAvailable(raylib)
endif()
