#include "KinematicBody.h"

void KinematicBody::Update(float deltaTime, SteeringOutput* steering)
{
    // Update position and velocity using the base class method
    Body::Update(deltaTime);

    // If there is steering input, adjust velocity and rotation accordingly
    if (steering)
    {
        accel = steering->linear;  // Update linear acceleration
        angular = steering->angular;  // Update angular acceleration
    }

    // Limit acceleration to max speed
    if (VMath::mag(accel) > maxAcceleration)
    {
        accel = VMath::normalize(accel) * maxAcceleration;
    }

    // Clip angular acceleration to the max allowed
    if (angular > maxAngular)
    {
        angular = maxAngular;
    }
}

