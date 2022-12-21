#include <bits/stdc++.h>
#include "CustomMaze.h"
using namespace std;
#define N 4

bool solveMazeUtil(int maze[N][N], int x, int y,int sol[N][N]);

void printSolution(int sol[N][N])
{
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++)
            cout<<" "<<sol[i][j]<<" ";
        cout<<endl;
    }
}

bool isSafe(int maze[N][N], int x, int y)
{
    // if (x, y outside maze) return false
    if (x >= 0 && x < N && y >= 0 && y < N && maze[x][y] == 1)
        return true;
    return false;
}

// Uses backtracking and translate physical maze into an array to simplify
// solving
bool solveMaze(CustomMaze maze)
{
	int arrayMaze[N][N] = translateArray(maze);
    int sol[N][N] = { { 0, 0, 0, 0 },
                      { 0, 0, 0, 0 },
                      { 0, 0, 0, 0 },
                      { 0, 0, 0, 0 } };
    if (solveMazeUtil(arrayMaze, 0, 0, sol) == false) {
        cout<<"Solution doesn't exist";
        return false;
    }
    printSolution(sol);
    return true;
}

bool solveMazeUtil(int maze[N][N], int x, int y, int sol[N][N])
{
    if (x == N - 1 && y == N - 1 && maze[x][y] == 1) {
        sol[x][y] = 1;
        return true;
    }
    // Check if maze is valid
    if (isSafe(maze, x, y) == true) {
        // Check if the current block is already part of sol[][]
        if (sol[x][y] == 1)
            return false;
        // mark x
        sol[x][y] = 1;
        if (solveMazeUtil(maze, x + 1, y, sol) == true)
            return true;
        // Determine to move horizontally or vertically
        if (solveMazeUtil(maze, x, y + 1, sol) == true)
            return true;
        // If none of the above movements work then backtrack unmark x
        sol[x][y] = 0;
        return false;
    }
    return false;
}

vector<int> translateArray (CustomMaze maze)
{
	vector<int> ans;

	return ans;
}
