#pragma once
#include "Agent.h"

class Behavior
{
public:
	Behavior() {}

	/// <summary>
	/// Update the Behavior, affecting its owning Agent where necessary.
	/// </summary>
	/// <param name="owner">The Agent to which this Behavior belongs</param>
	/// <param name="deltaTime"></param>
	virtual void update(Agent* owner, float deltaTime) = 0;

	/// <summary>
	/// Draw the Behavior, primarily for debugging purposes. Agent calls
	/// this by default.
	/// </summary>
	/// <param name="owner">The Agent to which this Behavior belongs</param>
	virtual void draw(Agent* owner) {}

	bool getEnabled() { return m_enabled; }
	void setEnabled(bool enabled) { m_enabled = true; }

private:
	bool m_enabled = true;
};
