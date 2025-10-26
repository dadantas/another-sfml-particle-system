cmake_minimum_required(VERSION 3.28)
project(SFMLParticles LANGUAGES CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 3.0.2
    GIT_SHALLOW ON
    EXCLUDE_FROM_ALL
    SYSTEM)
FetchContent_MakeAvailable(SFML)

# First executable: main program
add_executable(Particles
    src/main.cpp
)
target_include_directories(Particles PRIVATE ${CMAKE_SOURCE_DIR}/include)
target_compile_features(Particles PRIVATE cxx_std_17)
target_link_libraries(Particles PRIVATE SFML::Graphics)
target_compile_definitions(Particles PRIVATE ASSETS_DIR="${CMAKE_SOURCE_DIR}/assets")

# Second executable: QuickSort visualizer
add_executable(QuickSortVis
    src/QuickSortVis.cpp
)
target_include_directories(QuickSortVis PRIVATE ${CMAKE_SOURCE_DIR}/include)
target_compile_features(QuickSortVis PRIVATE cxx_std_17)
target_link_libraries(QuickSortVis PRIVATE SFML::Graphics)
target_compile_definitions(QuickSortVis PRIVATE ASSETS_DIR="${CMAKE_SOURCE_DIR}/assets")
