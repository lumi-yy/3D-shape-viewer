# 3D Shape Viewer

A terminal-based 3D shape viewer written in C++17 using raylib and ncurses.

The project allows users to select geometric shapes and colors through an interactive terminal interface. It includes custom geometry generation, 3D rotations, and perspective projection.

## Features

- **5 geometric shapes:** Cube, Pyramid, Sphere, Cylinder, and Cone.
- **Procedural geometry generation** using mathematical operations and trigonometry.
- **3D rotations** around coordinate axes.
- **Perspective projection** to transform 3D coordinates into 2D screen coordinates.
- **Interactive terminal interface** built with ncurses.
- **Shape and color selection.**
- **Command-based scene configuration.**
- **CMake build system.**

## Demo

### Interface

![Terminal Interface](docs/gifs/interface.gif)

### 3D Shapes

| Cube | Sphere |
|:---:|:---:|
| ![Cube](docs/gifs/cube.gif) | ![Sphere](docs/gifs/sphere.gif) |

| Pyramid | Cylinder | Cone |
|:---:|:---:|:---:|
| ![Pyramid](docs/gifs/pyramid.gif) | ![Cylinder](docs/gifs/cylinder.gif) | ![Cone](docs/gifs/cone.gif) |

## Technologies

- C++17
- CMake
- raylib
- ncurses

## Requirements

Before building the project, make sure you have installed:

- A C++17-compatible compiler
- CMake
- raylib
- ncurses development libraries

## Build

Clone the repository:

```bash
git clone https://github.com/lumi-yy/3D-shape-viewer.git
cd 3D-shape-viewer
```

Configure the project:

```bash
cmake -S . -B build
```

Build the project:

```bash
cmake --build build
```

Run the generated executable from the build directory. The exact executable path depends on your build configuration.

## Usage

- Enter a command or press `Enter` to proceed to shape selection.
- Use `W` / `S` to select a shape and press `Enter`.
- Use `W` / `A` / `S` / `D` to select a color and press `Enter`.

**Note:** A sufficiently large terminal window is required.

## Project Structure

```text
3D-shape-viewer/
├── docs/
├── include/        # Header files
├── src/            # Source files
├── CMakeLists.txt  # CMake build configuration
└── README.md
```
