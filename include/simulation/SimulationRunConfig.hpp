#pragma once
#include <cmath>
#include "app/ExceptionHandler.hpp"

struct SimulationRunConfig
{
    SimulationRunConfig(double timeStepInSeconds, unsigned int numberOfSteps)
        : timeStep{ timeStepInSeconds }, stepCount{ numberOfSteps }
    {
        ExceptionHandler::ensure(std::isfinite(timeStep) && timeStep > 0.0, ExceptionHandler::ExceptionType::Argument, "Time step must be positive and finite");
        ExceptionHandler::ensure(numberOfSteps > 0u,                        ExceptionHandler::ExceptionType::Argument, "Step count must be positive");
    }

	double timeStep;
	unsigned int stepCount;
};
