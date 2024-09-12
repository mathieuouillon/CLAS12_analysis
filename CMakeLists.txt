cmake_minimum_required(VERSION 3.19)
if (${CMAKE_VERSION} VERSION_LESS 3.19)
    cmake_policy(VERSION ${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION})
endif ()

project(project_name
        VERSION 1.0
        DESCRIPTION ""
        LANGUAGES CXX)

add_executable(project_name source/main.cpp)

target_include_directories(project_name PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/hipo/install/include)
target_compile_features(project_name PRIVATE cxx_std_20)
