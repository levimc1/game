cmake_minimum_required(VERSION 3.16)
project(Game C CXX)

set(CMAKE_C_STANDARD 17)
set(CMAKE_CXX_STANDARD 23) # Ez windowson nem jó

include_directories(${PROJECT_SOURCE_DIR}/src)

find_package(OpenGL REQUIRED)
find_package(PkgConfig REQUIRED)
pkg_check_modules(GLFW REQUIRED glfw3)

include_directories(${GLFW_INCLUDE_DIRS})

file(GLOB_RECURSE SOURCES 
  "src/*.c"
  "src/*.cpp"
)

add_executable(${PROJECT_NAME} ${SOURCES})

target_compile_options(Game PRIVATE
  $<IF:$<CONFIG:Release>,-O2,-g -O0>
)

target_link_options(Game PRIVATE
  $<$<CONFIG:Release>:-static>
)

target_link_libraries(${PROJECT_NAME} ${GLFW_LIBRARIES} ${OPENGL_LIBRARIES})
