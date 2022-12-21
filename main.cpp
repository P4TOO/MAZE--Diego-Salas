#include "CustomMaze.h"
#include "SolveMaze.h"

int main()
{
	// Seed random number generator
	srand(clock());

	CustomMaze game;
	game.ConstructConsole(160, 100, 8, 8);
	game.Start();

	return 0;
}
