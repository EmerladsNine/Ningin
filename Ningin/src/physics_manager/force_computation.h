#pragma once

#include <functional>
#include "force_dynamics.h"

struct ForceComputation {
    virtual ~ForceComputation() = default; // Virtual destructor for proper cleanup

    virtual float getMagnitude() {
        return 0.0f;
    }
};


struct DefaultForceComputatuon: ForceComputation {
    private:
        float arg;
        
        std::function<float(float)> get_magnitude_func;
       
        DefaultForceComputatuon(DefaultForceDynamics dynamics): get_magnitude_func(dynamics.get_magnitude_func), arg(dynamics.arg) {}
    
    public:
        static DefaultForceComputatuon create_default_force(DefaultForceDynamics dynamics) {
            return DefaultForceComputatuon(dynamics);
        }

        virtual ~DefaultForceComputatuon() = default; // Virtual destructor for proper cleanup

        virtual float getMagnitude() override {
            return get_magnitude_func(arg);
        }
};

struct AppliedForceComputation : ForceComputation {
    private:
        float magnitude;

        AppliedForceComputation(AppliedForceDynamics dynamics) : magnitude(dynamics.force_magnitude) {}

    public:
        static AppliedForceComputation create_applied_force(AppliedForceDynamics dynamics) {
            return AppliedForceComputation(dynamics);
        }

        virtual ~AppliedForceComputation() = default; // Virtual destructor for proper cleanup

        virtual float getMagnitude() override {
            return magnitude;
        }
};
