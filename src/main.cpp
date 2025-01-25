#include "structure/NeuralNetwork.hpp"

#include "training/TrainingStrategy.hpp"
#include "training/ActivationFunction.hpp"

#include "render/ColorGrid.hpp"
#include "render/NetworkVisualization.hpp"

int main() {
	NeuralNetwork network({ 2, 8, 8, 1 });
	SigmoidFunction sigmoid;
	RectifiedLinearUnit ReLU;
	LeakyRectifiedLinearUnit leakyReLU(0.05);

	TrainingStrategy trainingStrategy(0.025, leakyReLU, 1e9, 1e-9);

	ColorGrid grid(20, 20, 20);

        VisualizationSettings settings(800, 600, 40, "../assets/Hack-Bold.ttf", 20);
        NetworkVisualization visualization(settings);

	trainingStrategy.setScalingFunction(&sigmoid);
        network.setTrainingStrategy(&trainingStrategy);

	grid.initialize();
	visualization.visualize(&network);

	while (visualization.isOpen() && grid.isOpen()) {
		visualization.draw();
		grid.draw();
		if (!grid.getInputs().empty() && !network.hasCompletedTraining()) {
			network.train(grid.getInputs(), grid.getOutputs());
			grid.applyNetwork(trainingStrategy, &network);
			visualization.update();
		}
	}

	return 0;
}
