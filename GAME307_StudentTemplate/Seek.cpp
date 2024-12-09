#include "Seek.h"

Seek::Seek(const Body* npc_, const Body* target_)
{
	npc = npc_;
	target = target_;
	Target_pos = target->getPos();
}
Seek::Seek(const Body* npc_, const Vec3 targetpos)
{
	npc = npc_;
	Target_pos = targetpos;
}

Seek::~Seek()
{
}

SteeringOutput* Seek::getSteering()
{
	//Get direction to target

	result->linear = Target_pos - npc->getPos();

	// accellerate in that direction
	result->linear = VMath::normalize(result->linear) * npc->getMaxAcceleration();
	result->angular = 0.0f;
	

	return result;
}
