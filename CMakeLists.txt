cmake_minimum_required(VERSION 3.24)
project(raygraphic)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Dependencies
list(PREPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

find_package(cmakeutils REQUIRED)
include(${cmakeutils_SOURCE_DIR}/ToolBSL.cmake)

bsl_store()

find_package(igraphic REQUIRED)
find_package(maths REQUIRED)
find_package(raylib REQUIRED)

bsl_restore()

set(SOURCE_FILES raylib.cpp)

add_library(${PROJECT_NAME} ${SOURCE_FILES})

target_include_directories(${PROJECT_NAME} PUBLIC
  ${CMAKE_CURRENT_SOURCE_DIR}/window
  ${CMAKE_CURRENT_SOURCE_DIR}/graphic
  ${CMAKE_CURRENT_SOURCE_DIR}/event
  ${CMAKE_CURRENT_SOURCE_DIR}/audio
  ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(${PROJECT_NAME} PUBLIC maths system igraphic raylib)

# Checks if OSX and links appropriate frameworks (Only required on MacOS)
if (APPLE)
  target_link_libraries(${PROJECT_NAME} PRIVATE "-framework IOKit")
  target_link_libraries(${PROJECT_NAME} PRIVATE "-framework Cocoa")
  target_link_libraries(${PROJECT_NAME} PRIVATE "-framework OpenGL")
endif()