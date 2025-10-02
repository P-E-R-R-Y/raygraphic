#----------- general -----------

cmake_minimum_required(VERSION 3.24)
project(raygraphic)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

#----------- project -----------

list(PREPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)
find_package(CMakeUtils REQUIRED)
include(${cmakeutils_SOURCE_DIR}/ToolBSL.cmake)

bsl_store()

find_package(System REQUIRED)
find_package(IGraphic REQUIRED)
find_package(Maths REQUIRED)
find_package(Raylib REQUIRED)

bsl_restore()

set(SOURCE_FILES sources/raylib.cpp)

add_library(${PROJECT_NAME} SHARED ${SOURCE_FILES})

#----------- dependencies -----------

target_link_libraries(${PROJECT_NAME} PRIVATE maths)
target_link_libraries(${PROJECT_NAME} PUBLIC system igraphic raylib)

# Checks if OSX and links appropriate frameworks (Only required on MacOS)
if (APPLE)
  # macOS frameworks
  target_link_libraries(${PROJECT_NAME} PRIVATE 
    "-framework IOKit"
    "-framework Cocoa"
    "-framework OpenGL"
  )
elseif(UNIX)
    # Linux (Ubuntu, Debian, etc.)
    find_package(X11 REQUIRED)

    target_link_libraries(${PROJECT_NAME} PRIVATE
        ${X11_LIBRARIES}
        m
        pthread
        dl
        GL
    )

    target_include_directories(${PROJECT_NAME} PRIVATE
        ${X11_INCLUDE_DIR}
    )

    set_target_properties(${PROJECT_NAME} PROPERTIES POSITION_INDEPENDENT_CODE ON)
endif()

#----------- includes -----------

target_include_directories(${PROJECT_NAME} PUBLIC
  ${CMAKE_CURRENT_SOURCE_DIR}/includes/window
  ${CMAKE_CURRENT_SOURCE_DIR}/includes/graphic
  ${CMAKE_CURRENT_SOURCE_DIR}/includes/event
  ${CMAKE_CURRENT_SOURCE_DIR}/includes/audio
  ${CMAKE_CURRENT_SOURCE_DIR}/includes
)

#----------- tests -----------

find_package(GoogleTest REQUIRED)

enable_testing()

file(GLOB TEST_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/tests/*.cpp)

add_executable(${PROJECT_NAME}_tests ${TEST_SOURCES})

target_link_libraries(${PROJECT_NAME}_tests 
	gtest_main
  igraphic
)

include(GoogleTest)
gtest_discover_tests(${PROJECT_NAME}_tests
  WORKING_DIRECTORY ${PROJECT_BINARY_DIR}
)

#set_tests_properties(${PROJECT_NAME}_tests PROPERTIES
#    WORKING_DIRECTORY "${CMAKE_BINARY_DIR}"
#
# use to define path to help dlopen finding libs.
#
#    ENVIRONMENT "LD_LIBRARY_PATH=${CMAKE_BINARY_DIR}/shared:$ENV{LD_LIBRARY_PATH}; #Unix
#                 DYLD_LIBRARY_PATH=${CMAKE_BINARY_DIR}/shared:$ENV{DYLD_LIBRARY_PATH}" #Apple
#)
