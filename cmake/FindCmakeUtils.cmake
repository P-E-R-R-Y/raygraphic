set(name cmakeutils)
set(tag main)#1.0.0)

include(FetchContent)
FetchContent_GetProperties(${name})
if (NOT ${name}_POPULATED)
	FetchContent_Declare(
		${name}
		GIT_REPOSITORY https://github.com/P-E-R-R-Y/cmake-utils
		GIT_TAG ${tag}
	)
	FetchContent_MakeAvailable(${name})
endif()
