# Fetch igraphic (only if not already provided)
include(FetchContent)
# Check if it's already fetched
FetchContent_GetProperties(maths) 
if (NOT maths_POPULATED)
  # If not, fetch it
  FetchContent_Declare(
    maths
    GIT_REPOSITORY https://github.com/P-E-R-R-Y/maths.git
    GIT_TAG main #v0.1.0  # You can replace "main" with a specific version tag or commit hash
  )
  FetchContent_MakeAvailable(maths)
endif()