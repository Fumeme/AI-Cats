#ifndef STATIC_BODY_H
#define STATIC_BODY_H

#include "Body.h"
#include "KinematicSteeringOutput.h"

class StaticBody :
    public Body
{
private:

public:
    StaticBody() : Body{}
    {}

    StaticBody(Vec3 pos_, float orientation_, float maxSpeed_, float maxRotation_) :
        Body
    {
        pos_,
        Vec3(),
        Vec3(),
        1.0f,
        1.0f,
        orientation_,
        0.0f,
        0.0f,
        maxSpeed_,
        0.0f,
        maxRotation_,
        0.0f
    }
    {}

    void Update(float deltaTime, KinematicSteeringOutput* steering_);
    void newOrientation();
<<<<<<< Updated upstream
    // Add MoveTowards and HasReached declarations
    void MoveTowards(Vec3 targetPos, float deltaTime); // Moves towards a specified target position
    bool HasReached(Vec3 targetPos, float threshold) const;// Checks if it has reached the target position
=======
    void MoveTowards(Vec3 targetPos, float deltaTime);
    bool HasReached(Vec3 targetPos, float threshold) const;
>>>>>>> Stashed changes
};

#endif
