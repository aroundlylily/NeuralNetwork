#ifndef TRAININGSTRATEGY_HPP
#define TRAININGSTRATEGY_HPP

class ErrorRender;

class TrainingStrategy {
public:
	virtual void setRender(ErrorRender *render) = 0;
};

#endif
