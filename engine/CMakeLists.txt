cmake_minimum_required(VERSION 3.17)

# Adding our source files
file(GLOB_RECURSE PROJECT_SOURCES "src/*.cpp")
file(GLOB_RECURSE LIB_SOURCES "libs/Raylib/src/*.cpp")
set(THREADS_PREFER_PTHREAD_FLAG ON)

find_package(raylib REQUIRED)
find_package(Threads REQUIRED)

add_library(engine STATIC ${PROJECT_SOURCES})
target_sources(engine PUBLIC ${LIB_SOURCES})
target_include_directories(engine PUBLIC "includes")
target_link_libraries(engine PUBLIC ${CMAKE_DL_LIBS} raylib Threads::Threads)