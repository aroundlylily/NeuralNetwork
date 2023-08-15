#include "include/NetworkStructure.hpp"
#include "include/NetworkVisuals.hpp"
#include "include/NetworkTrainingStrategies.hpp"
#include "include/ColorGrid.hpp"

#include <iostream>

int main() {
        //std::string fontFile = "/usr/share/fonts/TTF/Hack-Regular.ttf";
	std::string fontFile = "/usr/share/fonts/truetype/dejavu/DejaVuSansMono.ttf";

	VisualizationSettings settings(800, 600, 40, fontFile, 20);
        NetworkVisualization visualization(&settings);

        NeuralNetwork network;

        network.addNeuronLayer(2); // input layer
        network.addNeuronLayer(6); // hidden layer
        //network.addNeuronLayer(4); // hidden layer
        //network.addNeuronLayer(8); // hidden layer
        network.addNeuronLayer(1); // output layer

	LayerIterator iterator(network.getNeuronLayers());

        visualization.renderNeuralNetwork(&network);

        NetworkTraining strategy(0.1, 100000);

	visualization.renderError(&strategy);

        int gridWidth = 20;
        int gridHeight = 20;
        ColorGrid grid(gridWidth, gridHeight, 20);
	grid.draw();

	while (grid.isTakingUserInput() && visualization.isOpen() && grid.isOpen()) {
		grid.getUserInput();
		grid.draw();
		visualization.draw();
	}

	strategy.setInputs(grid.getInputs());
	strategy.setOutputs(grid.getOutputs());
	
        while (visualization.isOpen() && grid.isOpen()) {
		if (strategy.isTraining())
                	strategy.train(&iterator);
                visualization.draw();
                for (float x = 0; x < gridWidth; x++) {
                        for (float y = 0; y < gridHeight; y++) {
                                float output = strategy.test(&iterator, { x / gridWidth, y / gridHeight })[0];
                                grid.setPixelColor(x, y, output);
                        }
                }
                grid.draw();
        }

        return 0;
}
