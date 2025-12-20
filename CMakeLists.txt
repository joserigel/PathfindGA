cmake_minimum_required(VERSION 3.28)

set(CMAKE_CXX_STANDARD 17)
project(PathfindRL VERSION 1.0)
set(PathfindRL VERSION 1.0)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_BUILD_TYPE Debug)

include(FetchContent)
FetchContent_Declare(
  SDL3
  GIT_REPOSITORY https://github.com/libsdl-org/SDL.git
  GIT_TAG release-3.2.28
  GIT_SHALLOW ON
  EXCLUDE_FROM_ALL
  SYSTEM
)
FetchContent_MakeAvailable(SDL3)

FetchContent_Declare(
    Eigen3
    GIT_REPOSITORY https://gitlab.com/libeigen/eigen.git
    GIT_TAG 3.4.1
    GIT_SHALLOW ON
    EXCLUDE_FROM_ALL
    SYSTEM
)
FetchContent_MakeAvailable(Eigen3)

file(GLOB_RECURSE PATHFIND_RL_SOURCES "src/*.hpp" "src/*.cpp")

add_executable(PathfindRL ${PATHFIND_RL_SOURCES})

target_link_libraries(PathfindRL PRIVATE SDL3::SDL3)
target_link_libraries(PathfindRL PRIVATE Eigen3::Eigen)
