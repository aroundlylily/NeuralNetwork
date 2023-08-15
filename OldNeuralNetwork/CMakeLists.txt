cmake_minimum_required(VERSION 3.0)
project(YourProjectName)

# Set the C++ standard (optional)
set(CMAKE_CXX_STANDARD 11)

# Find the SFML libraries
find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)

# Add your source files
add_executable(
	Program 
	main.cpp 

	source/structure/Neuron.cpp 
	source/structure/NeuronLayer.cpp 
	source/structure/Weight.cpp 
	source/structure/LayerIterator.cpp 
	source/structure/NeuralNetwork.cpp 

	source/render/NeuronRender.cpp 
	source/render/WeightRender.cpp 
	source/render/ErrorRender.cpp 
	source/render/NetworkVisualization.cpp 
	
	source/training/NetworkTraining.cpp
	
	source/ColorGrid.cpp)


# Link the SFML libraries
target_link_libraries(Program sfml-graphics sfml-window sfml-system)

