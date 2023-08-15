#include "include/NetworkStructure.hpp"
#include "include/NetworkTraining.hpp"
#include "include/NetworkVisuals.hpp"

int main() {
	NeuralNetwork network({ 2, 8, 8, 1 });
	SigmoidFunction sigmoid;
	RectifiedLinearUnit ReLU;
	LeakyRectifiedLinearUnit leakyReLU(0.05);

	TrainingStrategy trainingStrategy(0.025, leakyReLU, 1e9, 1e-9);
	trainingStrategy.setScalingFunction(&sigmoid);

        network.setTrainingStrategy(&trainingStrategy);

	ColorGrid grid(20, 20, 20);
	grid.initialize();

	// Arch: "/usr/share/fonts/TTF/Hack-Regular.ttf"
	// Ubuntu: "/usr/share/fonts/truetype/hack/Hack-Bold.ttf"
	NetworkVisualization visualization(VisualizationSettings(800, 600, 40, "/usr/share/fonts/truetype/hack/Hack-Bold.ttf", 20));
	visualization.visualize(&network);

	while (visualization.isOpen() && grid.isOpen()) {
		visualization.draw();
		grid.draw();
		if (!network.hasCompletedTraining()) {
			network.train(grid.getInputs(), grid.getOutputs());
			grid.applyNetwork(trainingStrategy, &network);
			visualization.update();
		}
	}

	return 0;
}
