cmake_minimum_required(VERSION 3.0)
project(NeuralNetwork)

set(CMAKE_CXX_STANDARD 11)

# Find the SFML libraries
find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)

add_executable(
        NeuralNetwork
	src/main.cpp 

	src/structure/NeuralNetwork.cpp
        src/structure/NeuronLayer.cpp

	src/render/ColorGrid.cpp

	src/render/NetworkVisualization.cpp
	src/render/NeuronRender.cpp
	src/render/WeightRender.cpp
	src/render/TextRender.cpp

	src/training/TrainingStrategy.cpp
	src/training/ActivationFunction.cpp
)

target_link_libraries(NeuralNetwork PUBLIC sfml-graphics sfml-window sfml-system)

target_include_directories(NeuralNetwork PUBLIC ${CMAKE_SOURCE_DIR}/src)
