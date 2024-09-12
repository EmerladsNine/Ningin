#include "ForceComputation.h"

// DefaultForceComputation definitions
DefaultForceComputation::DefaultForceComputation(DefaultForceDynamics dynamics)
    : get_magnitude_func(dynamics.get_magnitude_func), arg(dynamics.arg) {}

DefaultForceComputation DefaultForceComputation::create_default_force(DefaultForceDynamics dynamics) {
    return DefaultForceComputation(dynamics);
}

float DefaultForceComputation::getMagnitude() {
    return get_magnitude_func(arg);
}

// AppliedForceComputation definitions
AppliedForceComputation::AppliedForceComputation(AppliedForceDynamics dynamics)
    : magnitude(dynamics.force_magnitude) {}

AppliedForceComputation AppliedForceComputation::create_applied_force(AppliedForceDynamics dynamics) {
    return AppliedForceComputation(dynamics);
}

float AppliedForceComputation::getMagnitude() {
    return magnitude;
}
