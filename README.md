# NeuralNetwork

This project implements a neural network from scratch in C++ to modulate background color values to fit user-defined target points.

![Demo](https://github.com/aroundlylily/NeuralNetwork/blob/main/assets/images/NeuralNetwork.gif?raw=true)

## Features

- Custom Neural Network Implementation: No external machine learning frameworks are used; the neural network is built entirely from scratch.

- Flexible input: Accepts 2D target points using the mouse.

- Interactive Training Data: Users may supply additional points dynamically while the model trains

## Requirements

### Dependencies

- C++17 or later
- [SFML](https://www.sfml-dev.org/download/sfml/3.0.0/) (to create the visualization)
- CMake (for building the project)

### Installation

1. Clone the repository:
```
git clone https://github.com/aroundlylily/NeuralNetwork.git
cd NeuralNetwork
```
2. Create a build directory and compile:
```
mkdir build
cd build
cmake ..
make
```
3. Run the executable
```
./NeuralNetwork
```

## Usage

1. After running the application, two windows will appear. One window accepts user-input while the other visualizes the network.
2. Click anywhere on the grid to apply a target point. Left click applies a white target point while right click applies a black target point.
3. Watch as the neural network trains and adjusts background color values to match the given input.
4. Pressing the Escape key over the input grid resets the target inputs. Pressing the Escape key over the network visualization resets the network.

## Future Enhancements

- Implement GPU acceleration with CUDA or OpenCL
- Expand functionality for RBG values
