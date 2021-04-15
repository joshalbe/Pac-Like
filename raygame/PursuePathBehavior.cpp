#include "PursuePathBehavior.h"

MathLibrary::Vector2 PursuePathBehavior::findDestination(Agent* owner)
{
    MathLibrary::Vector2 targetPosition = getTarget()->getWorldPosition();
    return targetPosition;
}