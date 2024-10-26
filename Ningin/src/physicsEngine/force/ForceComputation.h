#pragma once

#include <functional>
#include "ForceDynamics.h"

struct ForceComputation {
    virtual ~ForceComputation() = default; // Virtual destructor for proper cleanup

    virtual float getMagnitude() {
        return 0.0f;
    }
};

struct DefaultForceComputation : ForceComputation {
    private:
        float _arg;
        std::function<float(float)> getMagnitudeFunc;

        DefaultForceComputation(DefaultForceDynamics dynamics);

    public:
        static DefaultForceComputation create_default_force(DefaultForceDynamics dynamics);

        virtual ~DefaultForceComputation() = default; // Virtual destructor for proper cleanup

        virtual float getMagnitude() override;
};

struct AppliedForceComputation : ForceComputation {
    private:
        float _magnitude;

        AppliedForceComputation(AppliedForceDynamics dynamics);

    public:
        static AppliedForceComputation create_applied_force(AppliedForceDynamics dynamics);

        virtual ~AppliedForceComputation() = default; // Virtual destructor for proper cleanup

        virtual float getMagnitude() override;
};
