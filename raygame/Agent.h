#pragma once
#include "Actor.h"
#include "SeekBehavior.h"
#include <Vector2.h>
#include <vector>

class Behavior;

class Agent : public Actor
{
public:
	Agent();
	/// <param name="x">Position on the x axis</param>
	/// <param name="y">Position on the y axis</param>
	/// <param name="collisionRadius">The size of the circle surrounding the actor that will be used to detect collisions</param>
	/// <param name="icon">The symbol that will appear when drawn</param>
	/// <param name="maxSpeed">The largest the magnitude of the actors velocity can be</param>
	Agent(float x, float y, float collisionRadius, float maxSpeed, float maxForce, char icon);
	/// <param name="x">Position on the x axis</param>
	/// <param name="y">Position on the y axis</param>
	/// <param name="collisionRadius">The size of the circle surrounding the actor that will be used to detect collisions</param>
	/// <param name="icon">The symbol that will appear when drawn</param>
	/// <param name="maxSpeed">The largest the magnitude of the actors velocity can be</param>
	Agent(float x, float y, float collisionRadius, float maxSpeed, float maxForce, int color);
	/// <param name="x">Position on the x axis</param>
	/// <param name="y">Position on the y axis</param>
	/// <param name="collisionRadius">The size of the circle surrounding the actor that will be used to detect collisions</param>
	/// <param name="sprite">That sprite that will be drawn in this actors drawGraph function</param>
	/// <param name="maxSpeed">The largest the magnitude of the actors velocity can be</param>
	Agent(float x, float y, float collisionRadius, float maxSpeed, float maxForce, Sprite* sprite);
	/// <param name="x">Position on the x axis</param>
	/// <param name="y">Position on the y axis</param>
	/// <param name="collisionRadius">The size of the circle surrounding the actor that will be used to detect collisions</param>
	/// <param name="sprite">That path for the sprite that will be drawn in this actors drawGraph function</param>
	/// <param name="maxSpeed">The largest the magnitude of the actors velocity can be</param>
	Agent(float x, float y, float collisionRadius, float maxSpeed, float maxForce, const char* spriteFilePath);

	/// <summary>
	/// Update the agent and its behaviours.
	/// </summary>
	/// <param name="deltaTime"></param>
	virtual void update(float deltaTime) override;

	/// <returns>The maximum force that can be applied in a single update.</returns>
	float getMaxForce() { return m_maxForce; }
	/// <summary>
    /// Changes the maximum force that can be applied in a single update.
	/// </summary>
	/// <param name="value">The new maximum force.</param>
	void setMaxForce(float value) { m_maxForce = value; }

	/// <summary>
	/// Apply a force to the agent, affect its velocity.
	/// </summary>
	/// <param name="force"></param>
	void applyForce(MathLibrary::Vector2 force);

	/// <summary>
	/// Add a behaviour to the agent.
	/// </summary>
	/// <param name="behavior"></param>
	void addBehavior(Behavior* behavior);


	void setTarget(Agent* target) { m_target = target; }
	Agent* getTarget() { return m_target; }

private:
	std::vector<Behavior*> m_behaviorList;

	MathLibrary::Vector2 m_force = { 0, 0 };
	float m_maxForce;
	Agent* m_target = nullptr;
};

