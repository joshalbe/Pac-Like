#include "EvadePathBehavior.h"
#include "Agent.h"

EvadePathBehavior::EvadePathBehavior(Character* target, float forceScale)
{
	setForceScale(forceScale);

}

MathLibrary::Vector2 EvadePathBehavior::calculateForce(Agent* agent)
{
    Agent* owner = agent;

    //If target is too close
    if ((owner->getTarget()->getWorldPosition() - owner->getWorldPosition()).getMagnitude() <= getForceScale())
    {
        //Get the target's position and velocity
        MathLibrary::Vector2 targetPosition = owner->getTarget()->getWorldPosition();
        MathLibrary::Vector2 targetVelocity = owner->getTarget()->getVelocity();
        //Subtract the new variables from the owner's position to get a Vector facing away from the target
        MathLibrary::Vector2 direction = owner->getWorldPosition() - targetPosition + targetVelocity;
        //Return the direction Vector scaled by the owner's max speed
        return direction * owner->getMaxSpeed();
    }
    return MathLibrary::Vector2();
}
