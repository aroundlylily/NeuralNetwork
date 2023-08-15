#include "../../include/training/ActivationFunction.hpp"

double SigmoidFunction::apply(double value) const {
	return 1.f / (1.f + std::exp(-value));
}

double SigmoidFunction::applyDerivative(double value) const {
	return value * (1 - value);
}

double RectifiedLinearUnit::apply(double value) const {
	if (value > 0)
		return value;
	return 0;
}

double RectifiedLinearUnit::applyDerivative(double value) const {
	if (value > 0)
		return 1;
	return 0;
}

LeakyRectifiedLinearUnit::LeakyRectifiedLinearUnit(double slope)
	: slope_(slope) {}

double LeakyRectifiedLinearUnit::apply(double value) const {
	if (value >= 0)
		return value;
	return slope_ * value;
}

double LeakyRectifiedLinearUnit::applyDerivative(double value) const {
	if (value >= 0)
		return 1.f;
	return slope_;
}
