#include "../../include/structure/LayerIterator.hpp"

LayerIterator::LayerIterator(std::vector<NeuronLayer *> layers)
	: layerIndex_(0), layers_(layers) {}

LayerIterator * LayerIterator::startAtInputLayer() {
	layerIndex_ = 0;
	return this;
}

LayerIterator * LayerIterator::startAtOutputLayer() {
	layerIndex_ = layers_.size() - 1;
	return this;
}

LayerIterator * LayerIterator::next() {
	++layerIndex_;
	return this;
}

LayerIterator * LayerIterator::previous() {
	--layerIndex_;
	return this;
}

NeuronLayer * LayerIterator::viewInputLayer() {
	return layers_[0];
}

NeuronLayer * LayerIterator::viewOutputLayer() {
	return layers_[layers_.size() - 1];
}

NeuronLayer * LayerIterator::viewCurrentLayer() {
	if (layerIndex_ < 0 || layerIndex_ >= layers_.size())
		return nullptr;
	return layers_[layerIndex_];
}

NeuronLayer * LayerIterator::viewNextLayer() {
	if (layerIndex_ + 1 < 0 || layerIndex_ + 1 >= layers_.size())
		return nullptr;
	return layers_[layerIndex_ + 1];
}

NeuronLayer * LayerIterator::viewPreviousLayer() {
	if (layerIndex_ - 1 < 0 || layerIndex_ - 1 >= layers_.size())
		return nullptr;
	return layers_[layerIndex_ - 1];
}
