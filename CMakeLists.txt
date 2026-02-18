cmake_minimum_required(VERSION 3.16)
project(Game C CXX)

# C17 - Nem tudom mi lehet benne :/
set(CMAKE_C_STANDARD 17)
set(CMAKE_CXX_STANDARD 23)

# inc feldolgozása
include_directories(${PROJECT_SOURCE_DIR}/inc)

# OpenGL, glfw feldolgozása
find_package(OpenGL REQUIRED)
find_package(PkgConfig REQUIRED)
pkg_check_modules(GLFW REQUIRED glfw3)

include_directories(${GLFW_INCLUDE_DIRS})
link_libraries(${GLFW_LIBRARIES} ${OPENGL_LIBRARIES})

# src feldolgozása
file(GLOB_RECURSE SOURCES 
  "src/*.c"
  "src/*.cpp"
)

# futtatható
add_executable(${PROJECT_NAME} ${SOURCES})

# OpenGL/GLFW link feldolgozása
target_link_libraries(${PROJECT_NAME} ${GLFW_LIBRARIES} ${OPENGL_LIBRARIES})

