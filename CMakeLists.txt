cmake_minimum_required(VERSION 3.0)
project(OptimizedNeuralNetwork)

# Set the C++ standard (optional)
set(CMAKE_CXX_STANDARD 11)
# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3")

# Find the SFML libraries
find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)

# Add your source files
add_executable(
	Program 
	main.cpp 

	source/structure/NeuronLayer.cpp 
	source/structure/NeuralNetwork.cpp

	source/render/NeuronRender.cpp
	source/render/WeightRender.cpp
	source/render/TextRender.cpp
	source/render/NetworkVisualization.cpp
	source/render/ColorGrid.cpp

	source/training/TrainingStrategy.cpp
	source/training/ActivationFunction.cpp
)

# Link the SFML libraries
target_link_libraries(Program sfml-graphics sfml-window sfml-system)

