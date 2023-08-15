#ifndef LAYERITERATOR_HPP
#define LAYERITERATOR_HPP

#include <vector>

class NeuronLayer;

class LayerIterator {
private:
	std::vector<NeuronLayer *> layers_;
	int layerIndex_;

public:
	LayerIterator(std::vector<NeuronLayer *> layers);
	LayerIterator * startAtInputLayer();
	LayerIterator * startAtOutputLayer();
	LayerIterator * next();
	LayerIterator * previous();
	NeuronLayer * viewInputLayer();
	NeuronLayer * viewOutputLayer();
	NeuronLayer * viewNextLayer();
	NeuronLayer * viewCurrentLayer();
	NeuronLayer * viewPreviousLayer();
};

#endif
