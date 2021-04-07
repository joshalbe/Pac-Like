#pragma once
#include "PathfindBehavior.h"

class SeekPathBehavior : public PathfindBehavior
{
public:
	SeekPathBehavior(Maze* maze) : PathfindBehavior(maze) {}

	virtual MathLibrary::Vector2 findDestination(Agent* owner) override;
};

