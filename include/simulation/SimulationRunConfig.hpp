#pragma once
#include <cmath>
#include <stdexcept>

struct SimulationRunConfig
{
    SimulationRunConfig(double timeStepInSeconds, unsigned int numberOfSteps)
        : timeStep{ timeStepInSeconds }, stepCount{ numberOfSteps }
    {
        if (!std::isfinite(timeStep) || timeStep <= 0.0) {
            throw std::invalid_argument{ "Time step must be positive and finite." };
        }

        if (numberOfSteps == 0u) {
            throw std::invalid_argument{ "Step count must be positive." };
        }
    }

	double timeStep;
	unsigned int stepCount;
};
