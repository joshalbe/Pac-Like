#include "EvadePathBehavior.h"
#include "Agent.h"

EvadePathBehavior::EvadePathBehavior(Character* target, float forceScale)
{
	setForceScale(forceScale);

}

MathLibrary::Vector2 EvadePathBehavior::calculateForce(Agent* agent)
{
    Agent* agent = dynamic_cast<Agent*>(agent);

    //If target is too close
    if ((agent->getTarget()->getWorldPosition() - agent->getWorldPosition()).getMagnitude() <= getForceScale())
    {
        //Get the target's position and velocity
        MathLibrary::Vector2 targetPosition = agent->getTarget()->getWorldPosition();
        MathLibrary::Vector2 targetVelocity = agent->getTarget()->getVelocity();
        //Subtract the new variables from the owner's position to get a Vector facing away from the target
        MathLibrary::Vector2 direction = agent->getWorldPosition() - targetPosition + targetVelocity;
        //Return the direction Vector scaled by the owner's max speed
        return direction * agent->getMaxSpeed();
    }
    return MathLibrary::Vector2();
}
