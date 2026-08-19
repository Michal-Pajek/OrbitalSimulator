#pragma once
#include <cmath>
#include "common/RuntimeChecks.hpp"

struct SimulationRunConfig
{
    SimulationRunConfig(double timeStepInSeconds, unsigned int numberOfSteps)
        : timeStep{ timeStepInSeconds }, stepCount{ numberOfSteps }
    {
        RuntimeChecks::ensure(std::isfinite(timeStep) && timeStep > 0.0,    RuntimeChecks::Type::Argument, "Time step must be positive and finite");
        RuntimeChecks::ensure(numberOfSteps > 0u,                           RuntimeChecks::Type::Argument, "Step count must be positive");
    }

	double timeStep;
	unsigned int stepCount;
};
