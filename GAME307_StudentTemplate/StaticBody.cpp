#include "StaticBody.h"
#include "VMath.h"

void StaticBody::Update(float deltaTime, KinematicSteeringOutput* steering_)
{
	// can do this at beginning or end
	Body::Update(deltaTime);
	newOrientation();

	// set the values based on the steering input
	if (steering_ == NULL)
	{
		vel = Vec3();
		rotation = 0.0f;
		return;
	}

	vel = steering_->velocity;
	rotation = steering_->rotation;

	// clip to max
	if (VMath::mag(vel) > maxSpeed)
		vel = VMath::normalize(vel) * maxSpeed;

	rotation = (rotation > maxRotation ? maxRotation : rotation);
}

void StaticBody::newOrientation()
{
	if (VMath::mag(vel) > FLT_EPSILON)
	{
		orientation = atan2(-vel.y, vel.x);
	}
}
void StaticBody::MoveTowards(Vec3 targetPos, float deltaTime) {
	Vec3 direction = targetPos - pos;

	// Normalize and scale with maxSpeed and deltaTime for frame independence
	if (VMath::mag(direction) > maxSpeed * deltaTime) {
		direction = VMath::normalize(direction);
		pos += direction * maxSpeed * deltaTime;  // Adjusted for deltaTime
	}
	else {
		pos = targetPos;  // Snap to target if within step size
	}
}

bool StaticBody::HasReached(Vec3 targetPos, float threshold) const {
	return VMath::distance(pos, targetPos) < threshold;  // Using custom threshold
}
