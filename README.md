# SFML-project

This repository contains two projects developed using the SFML library, a cross-platform software development library designed to provide a simple application programming interface (API) for multimedia programming.
## Super simple particle physics

To run this project, compile and execute the main.cpp file. This project features simple particle physics and allows the user to interact by spawning and deleting particles. Additionally, the user can switch between four particle types by pressing the following keys:

    w: water
    a: sand
    s: smoke
    p: wood

Controls:

    Left-click: spawns particles
    Right-click: deletes particles

## Quick sort visualization

To run this project, compile and execute the QuickSortVis.cpp file. This project features a visualization of the quick sort algorithm, where the user can watch the sorting process in real-time. The visualization is accompanied by a sound effect that plays with each comparison and swap during the sorting process.

Controls:

    None


## Compiling

Build using CMake with the commmands 
```bash
cmake -B build
cmake --build build 
```
The binaries are then in ./build/bin/