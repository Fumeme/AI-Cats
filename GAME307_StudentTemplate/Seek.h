#ifndef SEEK_H
#define SEEK_H

#include "SteeringBehaviour.h"
class Seek :
    public SteeringBehaviour
{
protected:
    const Body* target;

public:
    Vec3 Target_pos;
    Seek(const Body* npc_, const Body* target_);
    Seek(const Body* npc_, const Vec3 target_pos);
    virtual ~Seek();
    SteeringOutput* getSteering();
};

#endif
