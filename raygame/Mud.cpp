#include "Mud.h"
#include "Maze.h"

Mud::Mud(float x, float y) 
	: Actor(x, y, Maze::TILE_SIZE / 2.0f, 0, 0x7C5BCCFF)
{
	setStatic(true);
}
