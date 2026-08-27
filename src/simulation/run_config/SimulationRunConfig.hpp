#pragma once
#include <cmath>

#include "common/runtime_checks/RuntimeChecks.hpp"

struct SimulationRunConfig
{
    SimulationRunConfig(double timeStepInSeconds, unsigned int numberOfSteps)
        : timeStep{ timeStepInSeconds }, stepCount{ numberOfSteps }
    {
        runtime_checks::ensure(std::isfinite(timeStep) && timeStep > 0.0,    runtime_checks::Type::Argument, "Time step must be positive and finite");
        runtime_checks::ensure(numberOfSteps > 0u,                           runtime_checks::Type::Argument, "Step count must be positive");
    }

	double timeStep;
	unsigned int stepCount;
};
