/*******************************************************************************************
*
*   raylib [core] example - basic window
*
*   This example has been created using raylib 1.0 (www.raylib.com)
*   raylib is licensed under an unmodified zlib/libpng license (View raylib.h for details)
*
*   raylib Copyright (c) 2013-2016 Ramon Santamaria (@raysan5)
*
********************************************************************************************/

/*******************************************************************************************
* 
*	Required modifications
*		Implement NodeGraph::findPath.
*		Create one or more decision-making behaviors using Behavior as the base class.
*		Create one or more behaviors using PathfindBehavior as the base class.
*	Recommended modifications
*		Create any additional classes needed using Agent as a base.
*		Add additional items to Maze::TileKey as needed for your plan.
*		Add those items to Maze::createTile so that they can be created at map generation.
* 
********************************************************************************************/

#include "raylib.h"
#include "Game.h"
#include "Maze.h"
#include <Vector2.h>

int main()
{
	Game game = Game();

	//Define tile costs
	Maze::TileKey _ = Maze::TileKey::OPEN;
	Maze::TileKey w = Maze::TileKey::WALL;
	Maze::TileKey s = Maze::TileKey::MUD;
	Maze::TileKey g = Maze::TileKey::GHOST;

	// Create the maps
	Maze::TileKey emptyMap[Maze::HEIGHT][Maze::WIDTH] = {
		{ w, w, w, w, w, w, w, w, w, w, w, w, w, w, w, w, w, w, w, w, w, w, w, w, w, w, w, w },
		{ w, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, w },
		{ w, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, w },
		{ w, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, w },
		{ w, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, w },
		{ w, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, w },
		{ w, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, w },
		{ w, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, w },
		{ w, _, _, _, _, _, _, g, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, w },
		{ w, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, w },
		{ w, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, w },
		{ w, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, w },
		{ w, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, w },
		{ w, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, w },
		{ w, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, w },
		{ w, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, w },
		{ w, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, w },
		{ w, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, w },
		{ w, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, w },
		{ w, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, w },
		{ w, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, w },
		{ w, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, w },
		{ w, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, w },
		{ w, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, w },
		{ w, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, w },
		{ w, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, w },
		{ w, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, w },
		{ w, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, w },
		{ w, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, w },
		{ w, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, w },
		{ w, w, w, w, w, w, w, w, w, w, w, w, w, w, w, w, w, w, w, w, w, w, w, w, w, w, w, w },
	};
	Maze::TileKey pacMap[Maze::HEIGHT][Maze::WIDTH] = {
		{ w, w, w, w, w, w, w, w, w, w, w, w, w, w, w, w, w, w, w, w, w, w, w, w, w, w, w, w },
		{ w, _, _, _, _, _, _, _, _, _, _, _, _, w, w, _, _, _, _, _, _, _, _, _, _, _, _, w },
		{ w, _, w, w, w, w, _, w, w, w, w, w, _, w, w, _, w, w, w, w, w, _, w, w, w, w, _, w },
		{ w, _, w, w, w, w, _, w, w, w, w, w, _, w, w, _, w, w, w, w, w, _, w, w, w, w, _, w },
		{ w, _, w, w, w, w, _, w, w, w, w, w, _, w, w, _, w, w, w, w, w, _, w, w, w, w, _, w },
		{ w, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, w },
		{ w, _, w, w, w, w, _, w, w, _, w, w, w, w, w, w, w, w, _, w, w, _, w, w, w, w, _, w },
		{ w, _, w, w, w, w, _, w, w, _, w, w, w, w, w, w, w, w, _, w, w, _, w, w, w, w, _, w },
		{ w, _, _, _, _, _, _, w, w, _, _, _, _, w, w, _, _, _, _, w, w, _, _, _, _, _, _, w },
		{ w, w, w, w, w, w, _, w, w, w, w, w, _, w, w, _, w, w, w, w, w, _, w, w, w, w, w, w },
		{ w, w, w, w, w, w, _, w, w, w, w, w, _, w, w, _, w, w, w, w, w, _, w, w, w, w, w, w },
		{ w, w, w, w, w, w, _, w, w, _, _, _, _, _, _, _, _, _, _, w, w, _, w, w, w, w, w, w },
		{ w, w, w, w, w, w, _, w, w, _, _, _, _, g, _, _, _, _, _, w, w, _, w, w, w, w, w, w },
		{ w, w, w, w, w, w, _, w, w, _, _, _, _, _, _, _, _, _, _, w, w, _, w, w, w, w, w, w },
		{ _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _ },
		{ w, w, w, w, w, w, _, w, w, _, _, _, _, _, _, _, _, _, _, w, w, _, w, w, w, w, w, w },
		{ w, w, w, w, w, w, _, w, w, _, _, _, _, _, _, _, _, _, _, w, w, _, w, w, w, w, w, w },
		{ w, w, w, w, w, w, _, w, w, _, _, _, _, _, _, _, _, _, _, w, w, _, w, w, w, w, w, w },
		{ w, w, w, w, w, w, _, w, w, _, w, w, w, w, w, w, w, w, _, w, w, _, w, w, w, w, w, w },
		{ w, w, w, w, w, w, _, w, w, _, w, w, w, w, w, w, w, w, _, w, w, _, w, w, w, w, w, w },
		{ w, _, _, _, _, _, _, _, _, _, _, _, _, w, w, _, _, _, _, _, _, _, _, _, _, _, _, w },
		{ w, _, w, w, w, w, _, w, w, w, w, w, _, w, w, _, w, w, w, w, w, _, w, w, w, w, _, w },
		{ w, _, w, w, w, w, _, w, w, w, w, w, _, w, w, _, w, w, w, w, w, _, w, w, w, w, _, w },
		{ w, _, _, _, w, w, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, w },
		{ w, w, w, _, w, w, _, w, w, _, w, w, w, w, w, w, w, w, _, w, w, _, w, w, _, w, w, w },
		{ w, w, w, _, w, w, _, w, w, _, w, w, w, w, w, w, w, w, _, w, w, _, w, w, _, w, w, w },
		{ w, _, _, _, _, _, _, w, w, _, _, _, _, w, w, _, _, _, _, w, w, _, _, _, _, _, _, w },
		{ w, _, w, w, w, w, w, w, w, w, w, w, _, w, w, _, w, w, w, w, w, w, w, w, w, w, _, w },
		{ w, _, w, w, w, w, w, w, w, w, w, w, _, w, w, _, w, w, w, w, w, w, w, w, w, w, _, w },
		{ w, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, w },
		{ w, w, w, w, w, w, w, w, w, w, w, w, w, w, w, w, w, w, w, w, w, w, w, w, w, w, w, w },
	};

	Maze::TileKey newMap[Maze::HEIGHT][Maze::WIDTH] = {
		{ w, w, w, w, w, w, w, w, w, w, w, w, w, w, w, w, w, w, w, w, w, w, w, w, w, w, w, w },
		{ w, w, w, w, w, w, w, w, w, w, w, w, w, w, w, w, w, w, w, w, w, w, w, w, w, w, w, w },
		{ w, w, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, w, w },
		{ w, w, _, g, _, w, w, w, w, w, w, w, w, _, _, w, w, w, w, w, w, w, w, _, g, _, w, w },
		{ w, w, _, _, _, _, _, _, _, _, _, _, _, g, _, _, _, _, _, _, _, _, _, _, _, _, w, w },
		{ w, w, _, w, _, w, w, _, _, w, _, w, _, _, _, _, w, _, w, _, _, w, w, _, w, _, w, w },
		{ w, w, _, w, _, w, _, _, _, w, _, _, w, _, _, w, _, _, w, _, _, _, w, _, w, _, w, w },
		{ w, w, _, w, _, _, _, w, _, w, _, _, _, w, w, _, _, _, w, _, w, _, _, _, w, _, w, w },
		{ w, w, _, w, _, _, _, _, _, w, _, _, w, _, _, w, _, _, w, _, _, _, _, _, w, _, w, w },
		{ w, w, _, w, _, w, w, w, w, w, _, w, _, _, _, _, w, _, w, w, w, w, w, _, w, _, w, w },
		{ w, w, _, w, _, g, g, g, g, g, g, g, g, g, g, g, g, g, g, g, g, g, g, _, w, _, w, w },
		{ w, w, _, w, _, g, g, g, w, g, g, g, g, g, g, g, g, g, g, w, g, g, g, _, w, _, w, w },
		{ w, w, _, w, _, g, g, w, g, g, g, g, _, _, _, _, _, g, g, g, w, g, g, _, w, _, w, w },
		{ w, w, _, w, _, w, g, g, g, g, g, _, _, _, _, _, _, g, g, g, g, g, w, _, w, _, w, w },
		{ w, w, _, w, _, g, w, g, g, g, g, _, _, _, _, _, _, g, g, g, g, w, g, _, w, _, w, w },
		{ w, w, _, _, _, g, g, g, g, g, g, _, _, _, _, _, _, g, g, g, g, g, g, _, _, _, w, w },
		{ w, w, _, w, _, _, w, g, g, g, g, _, _, _, _, _, _, g, g, g, g, w, g, _, w, _, w, w },
		{ w, w, _, w, _, w, g, g, g, g, g, _, _, _, _, _, _, g, g, g, g, g, w, _, w, _, w, w },
		{ w, w, _, w, _, _, g, w, g, g, g, _, _, _, _, _, _, g, g, g, w, _, g, _, w, _, w, w },
		{ w, w, _, w, _, _, g, g, w, g, g, _, _, _, _, _, _, g, g, w, g, g, g, _, w, _, w, w },
		{ w, w, _, w, _, _, g, g, g, g, g, w, _, _, _, _, w, g, g, g, g, g, g, _, w, _, w, w },
		{ w, w, _, w, _, w, w, w, w, w, _, _, _, _, _, _, _, _, w, w, w, w, w, _, w, _, w, w },
		{ w, w, _, w, _, _, _, _, _, w, _, _, w, _, _, w, _, _, w, _, _, _, _, _, w, _, w, w },
		{ w, w, _, w, _, _, _, w, _, w, _, _, w, _, _, w, _, _, w, _, w, _, _, _, w, _, w, w },
		{ w, w, _, w, _, w, _, _, _, w, _, _, w, _, _, w, _, _, w, _, _, _, w, _, w, _, w, w },
		{ w, w, _, w, _, w, w, _, _, w, _, _, w, _, g, w, _, _, w, _, _, w, w, _, w, _, w, w },
		{ w, w, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, w, w },
		{ w, w, _, g, _, w, w, w, w, w, w, w, w, _, _, w, w, w, w, w, w, w, w, _, g, _, w, w },
		{ w, w, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, w, w },
		{ w, w, w, w, w, w, w, w, w, w, w, w, w, w, w, w, w, w, w, w, w, w, w, w, w, w, w, w },
		{ w, w, w, w, w, w, w, w, w, w, w, w, w, w, w, w, w, w, w, w, w, w, w, w, w, w, w, w },
	};

	// Create a maze, add it to the scene, and set it as the current scene
	game.setCurrentScene(game.addScene(new Maze(newMap)));

	game.run();

	return 0;

}