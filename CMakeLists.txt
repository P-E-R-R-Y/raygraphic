#----------- general -----------

cmake_minimum_required(VERSION 3.24)
project(raygraphic)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

#----------- dependencies -----------

list(PREPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)
find_package(CMakeUtils REQUIRED)
include(${cmakeutils_SOURCE_DIR}/ToolBSL.cmake)

bsl_store()

find_package(System REQUIRED)
find_package(IGraphic REQUIRED)
find_package(Maths REQUIRED)
find_package(Raylib REQUIRED)

bsl_restore()

#----------- test -----------

set(SOURCE_FILES sources/raylib.cpp)

add_library(${PROJECT_NAME} SHARED ${SOURCE_FILES})

target_include_directories(${PROJECT_NAME} PUBLIC
  ${CMAKE_CURRENT_SOURCE_DIR}/includes/window
  ${CMAKE_CURRENT_SOURCE_DIR}/includes/graphic
  ${CMAKE_CURRENT_SOURCE_DIR}/includes/event
  ${CMAKE_CURRENT_SOURCE_DIR}/includes/audio
  ${CMAKE_CURRENT_SOURCE_DIR}/includes
)

target_link_libraries(${PROJECT_NAME} PRIVATE maths)
target_link_libraries(${PROJECT_NAME} PUBLIC system igraphic raylib)

# Checks if OSX and links appropriate frameworks (Only required on MacOS)
if (APPLE)
  target_link_libraries(${PROJECT_NAME} PRIVATE "-framework IOKit")
  target_link_libraries(${PROJECT_NAME} PRIVATE "-framework Cocoa")
  target_link_libraries(${PROJECT_NAME} PRIVATE "-framework OpenGL")
endif()