#ifndef ACTIVATIONFUNCTION_HPP
#define ACTIVATIONFUNCTION_HPP

#include <math.h>

class ActivationFunction {
public:
	virtual double apply(double value) const = 0;
	virtual double applyDerivative(double value) const = 0;
};

class SigmoidFunction : public ActivationFunction {
public:
	double apply(double value) const override;
	double applyDerivative(double value) const override;
};

class RectifiedLinearUnit : public ActivationFunction {
public:
	double apply(double value) const override;
	double applyDerivative(double value) const override;
};

class LeakyRectifiedLinearUnit : public ActivationFunction {
private:
	double slope_;

public:
	LeakyRectifiedLinearUnit(double slope);
	double apply(double value) const override;
	double applyDerivative(double value) const override;
};

#endif
