#include "SeekPathBehavior.h"
#include "Maze.h"
#include "raylib.h"

MathLibrary::Vector2 SeekPathBehavior::findDestination(Agent* owner)
{
	return getTarget()->getWorldPosition();
}