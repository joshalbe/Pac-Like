#pragma once
#include "Behavior.h"
#include <Vector2.h>

class Character;

class SteeringBehavior : public Behavior
{
public:
	virtual void update(Agent* owner, float deltaTime) override;
	virtual MathLibrary::Vector2 calculateForce(Agent* agent) = 0;
	float getForceScale() { return m_forceScale; }
	void setForceScale(float forceScale) { m_forceScale = forceScale; }
private:
	float m_forceScale = 1;
};