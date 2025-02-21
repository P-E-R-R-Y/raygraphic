cmake_minimum_required(VERSION 3.24)
project(raygraphic)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
#set(CMAKE_OBJC_STANDARD_REQUIRED OFF)

# Dependencies
#include(cmake/FindRaylib.cmake)
set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake ${CMAKE_MODULE_PATH})

find_package(igraphic REQUIRED)
find_package(maths REQUIRED)
find_package(raylib REQUIRED)

set(SOURCE_FILES raylib.cpp)

add_library(${PROJECT_NAME} SHARED ${SOURCE_FILES})

target_include_directories(${PROJECT_NAME} PUBLIC
  ${CMAKE_CURRENT_SOURCE_DIR}/window
  ${CMAKE_CURRENT_SOURCE_DIR}/graphic
  ${CMAKE_CURRENT_SOURCE_DIR}/event
  ${CMAKE_CURRENT_SOURCE_DIR}/audio
  ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(${PROJECT_NAME} PUBLIC maths igraphic raylib)

# Checks if OSX and links appropriate frameworks (Only required on MacOS)
if (APPLE)
  target_link_libraries(${PROJECT_NAME} PRIVATE "-framework IOKit")
  target_link_libraries(${PROJECT_NAME} PRIVATE "-framework Cocoa")
  target_link_libraries(${PROJECT_NAME} PRIVATE "-framework OpenGL")
endif()