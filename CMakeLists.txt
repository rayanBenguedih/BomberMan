cmake_minimum_required(VERSION 3.17)
project(bomberman)
set(CMAKE_CXX_STANDARD 17)

set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake)
set(GAME_INCLUDE "${CMAKE_SOURCE_DIR}/gamecore/includes")
file(GLOB_RECURSE GAME_SRCS "game/src/*.cpp")
file(GLOB_RECURSE GAME_CORE "gamecore/src/*.cpp")

add_subdirectory(engine)
add_executable(${PROJECT_NAME} ${GAME_SRCS} ${GAME_CORE})
target_include_directories(${PROJECT_NAME} PUBLIC ${GAME_INCLUDE})
target_link_libraries(${PROJECT_NAME} PUBLIC engine)