#include "SteeringBehavior.h"

void SteeringBehavior::update(Agent* owner, float deltaTime)
{
	owner->applyForce(calculateForce(owner));
}