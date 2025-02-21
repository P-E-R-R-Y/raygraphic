include(FetchContent)
FetchContent_GetProperties(system) 
if (NOT system_POPULATED)
  # If not, fetch it
  FetchContent_Declare(
    system
    GIT_REPOSITORY https://github.com/P-E-R-R-Y/system.git
    GIT_TAG main #v0.1.0  # You can replace "main" with a specific version tag or commit hash
  )
  FetchContent_MakeAvailable(system)
endif()
