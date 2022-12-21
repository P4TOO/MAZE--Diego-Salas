#include <iostream>
#include <stack>
using namespace std;

class CustomMaze
{
public:
	CustomMaze()
	{
		name = "MAZE";
	}

private:
	int  width;
	int  height;
	int *maze;

	enum
	{
		N_PATH = 0x01,
		E_PATH = 0x02,
		S_PATH = 0x04,
		W_PATH = 0x08,
		VISITED = 0x10,
	};

	int  visited;
	stack<pair<int, int>> m_stack;	// (x, y) coordinate pairs
	int  pathWidth;


protected:
	virtual bool OnUserCreate()
	{
		// Maze parameters
		width = 40;
		height = 25;
		maze = new int[width * height];
		memset(maze, 0x00, width * height * sizeof(int));
		pathWidth = 3;

		// Choose a starting cell
		int x = rand() % width;
		int y = rand() % height;
		m_stack.push(make_pair(x, y));
		maze[y * width + x] = VISITED;
		visited = 1;

		return true;
	}

	virtual bool OnUserUpdate(float fElapsedTime)
	{
		// Slow down
		this_thread::sleep_for(10ms);

		auto offset = [&](int x, int y)
		{
			return (m_stack.top().second + y) * width + (m_stack.top().first + x);
		};

		// Do Maze Algorithm
		if (visited < width * height)
		{
			// unvisted neighbours
			vector<int> neighbours;

			// Northr
			if (m_stack.top().second > 0 && (maze[offset(0, -1)] & VISITED) == 0)
				neighbours.push_back(0);
			// East
			if (m_stack.top().first < width - 1 && (maze[offset(1, 0)] & VISITED) == 0)
				neighbours.push_back(1);
			// South
			if (m_stack.top().second < height - 1 && (maze[offset(0, 1)] & VISITED) == 0)
				neighbours.push_back(2);
			// West
			if (m_stack.top().first > 0 && (maze[offset(-1, 0)] & VISITED) == 0)
				neighbours.push_back(3);

			// Are there any neighbours available?
			if (!neighbours.empty())
			{
				// Choose one available neighbour at random
				int next_cell_dir = neighbours[rand() % neighbours.size()];

				// Create a path between the neighbour and the current cell
				switch (next_cell_dir)
				{
				case 0: // North
					maze[offset(0, -1)] |= VISITED | S_PATH;
					maze[offset(0,  0)] |= N_PATH;
					m_stack.push(make_pair((m_stack.top().first + 0), (m_stack.top().second - 1)));
					break;

				case 1: // East
					maze[offset(+1, 0)] |= VISITED | W_PATH;
					maze[offset( 0, 0)] |= E_PATH;
					m_stack.push(make_pair((m_stack.top().first + 1), (m_stack.top().second + 0)));
					break;

				case 2: // South
					maze[offset(0, +1)] |= VISITED | N_PATH;
					maze[offset(0,  0)] |= S_PATH;
					m_stack.push(make_pair((m_stack.top().first + 0), (m_stack.top().second + 1)));
					break;

				case 3: // West
					maze[offset(-1, 0)] |= VISITED | E_PATH;
					maze[offset( 0, 0)] |= W_PATH;
					m_stack.push(make_pair((m_stack.top().first - 1), (m_stack.top().second + 0)));
					break;

				}

				visited++;
			}
			else
			{
				// backtrack
				m_stack.pop();
			}
		}

		// drawing spaces
		Fill(0, 0, ScreenWidth(), ScreenHeight(), L' ');

		// Generate
		for (int x = 0; x < width; x++)
		{
			for (int y = 0; y < height; y++)
			{
				for (int py = 0; py < pathWidth; py++)
					for (int px = 0; px < pathWidth; px++)
					{
						if (maze[y * width + x] & VISITED)
							Draw(x * (pathWidth + 1) + px, y * (pathWidth + 1) + py, PIXEL_SOLID, FG_WHITE); // Draw Cell
						else
							Draw(x * (pathWidth + 1) + px, y * (pathWidth + 1) + py, PIXEL_SOLID, FG_BLUE); // Draw Cell
					}

				// Generate passways
				for (int p = 0; p < pathWidth; p++)
				{
					if (maze[y * width + x] & S_PATH)
						Draw(x * (pathWidth + 1) + p, y * (pathWidth + 1) + pathWidth); // Draw South Passage

					if (maze[y * width + x] & E_PATH)
						Draw(x * (pathWidth + 1) + pathWidth, y * (pathWidth + 1) + p); // Draw East Passage
				}
			}
		}

		// top of stack
		for (int py = 0; py < pathWidth; py++)
			for (int px = 0; px < pathWidth; px++)
				Draw(m_stack.top().first * (pathWidth + 1) + px, m_stack.top().second * (pathWidth + 1) + py, 0x2588, FG_GREEN); // Draw Cell


		return true;
	}
};


int main()
{
	// Seed random number generator
	srand(clock());

	CustomMaze game;
	game.ConstructConsole(160, 100, 8, 8);
	game.Start();

	return 0;
}
