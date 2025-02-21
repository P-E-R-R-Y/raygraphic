include(FetchContent)
FetchContent_GetProperties(igraphic) 
if (NOT igraphic_POPULATED)
  # If not, fetch it
  FetchContent_Declare(
    igraphic
    GIT_REPOSITORY https://github.com/P-E-R-R-Y/igraphic.git
    GIT_TAG main #v0.1.0  # You can replace "main" with a specific version tag or commit hash
  )
  FetchContent_MakeAvailable(igraphic)
endif()
