#include "ForceComputation.h"

// Default Force Computation
DefaultForceComputation::DefaultForceComputation(DefaultForceDynamics dynamics)
    : getMagnitudeFunc(dynamics.getMagnitudeFunc), _arg(dynamics.arg) {}

DefaultForceComputation DefaultForceComputation::create_default_force(DefaultForceDynamics dynamics)
{
    return DefaultForceComputation(dynamics);
}

float DefaultForceComputation::getMagnitude()
{
    return getMagnitudeFunc(_arg);
}

// Applied Force Computation
AppliedForceComputation::AppliedForceComputation(AppliedForceDynamics dynamics)
    : _magnitude(dynamics.forceMagnitude) {}

AppliedForceComputation AppliedForceComputation::create_applied_force(AppliedForceDynamics dynamics)
{
    return AppliedForceComputation(dynamics);
}

float AppliedForceComputation::getMagnitude()
{
    return _magnitude;
}
