// Class definition for AStar pathfinding
// Contains static methods for AIcontroller to call, probably should just move this code in there idk

#include <vector>
#include <iostream>

// Size of the wall map
const int ROW = 10;
const int COL = 10;

typedef std::pair<int, int> Pair; // Pair of ints used for map coordinates

#ifndef ASTAR
#define ASTAR

class AStar {
private:

	
	// Structure to store data for a node in a path
	struct PathfindingNode {

		Pair pos{ -1,-1 };
		Pair parentPos{ -1,-1 };

		float cost = FLT_MAX;
		float heuristicCost = FLT_MAX;
		float total = FLT_MAX;
	};



	// Function to find if a position is within range
	static bool isValid(Pair& p) {
		if ((p.first < ROW) && (p.second < COL))
			if ((p.first >= 0) && (p.second >= 0))
				return true;
		return false;
	}
	// Function to find if a position is blocked by a wall
	static bool isUnblocked(std::vector<std::vector<int>> walls, Pair& p) {
		return (walls[p.first][p.second] == 0);
	}
	// Function to find if a position matches Goal
	static bool pairMatches(Pair& p, Pair& p2) {
		return ((p.first == p2.first) && (p.second == p2.second));
	}


public:
	// Method to perform AStar search
	static Pair AStarSearch(int startX, int startY, int goalX, int goalY, std::vector<std::vector<int>> walls) {

		Pair startPos{ startX, startY };
		Pair goalPos{ goalX, goalY };

		

		// TODO Handle invalid inputs

		//Initialize nodes
		PathfindingNode nodes[ROW][COL]; // Map size must be constant

		for (int i = 0; i < ROW; i++)
			for (int j = 0; j < COL; j++)
				nodes[i][j].pos = Pair{ i,j };


		nodes[startPos.first][startPos.second].cost = 0;
		nodes[startPos.first][startPos.second].heuristicCost = 0;
		nodes[startPos.first][startPos.second].parentPos = startPos;


		// Create the open and closed Lists
		std::vector<PathfindingNode> openList;
		std::vector<PathfindingNode> closedList;
		openList.push_back(nodes[startPos.first][startPos.second]);
		bool goalFound = false;



		while (!openList.size() == 0) {
			PathfindingNode current = openList[0];
			openList.erase(openList.begin());

			int i = current.pos.first;
			int j = current.pos.second;
			// Create an array of pairs to check
			Pair checkArr[4] = { Pair{i + 1, j}, Pair{ i - 1,j }, Pair{ i,j + 1 }, Pair{ i,j - 1 } };

			// Iterate over successors
			for (Pair successorPos : checkArr) {
				if (isValid(successorPos) && isUnblocked(walls, successorPos)) {
					// Check if the goal is found
					if (pairMatches(successorPos, goalPos)) {
						goalFound = true;
						nodes[successorPos.first][successorPos.second].parentPos = current.pos;
					}
					// Else try to add successor to the openList	
					else {
						// Calculate cost of this successor
						double successorCost = current.cost + 1;
						double successorHeuristic = (abs(goalPos.first - successorPos.first) + abs(goalPos.second - successorPos.second)); //Hueristic is Manhattan distance to goal
						double successorTotal = successorCost + successorHeuristic;

						// Check if this node already has a better cost
						bool addToList = true;
						for (PathfindingNode n : openList)
							if (pairMatches(n.pos, successorPos))
								if (n.cost <= successorTotal)
									addToList = false;

						for (PathfindingNode n : closedList)
							if (pairMatches(n.pos, successorPos))
								if (n.cost <= successorTotal)
									addToList = false;
						// If not, set its vars add it to list
						if (addToList) {
							nodes[successorPos.first][successorPos.second].cost = successorCost;
							nodes[successorPos.first][successorPos.second].heuristicCost = successorHeuristic;
							nodes[successorPos.first][successorPos.second].total = successorTotal;
							nodes[successorPos.first][successorPos.second].parentPos = current.pos;
							openList.push_back(nodes[successorPos.first][successorPos.second]);
						}
					}
				}
			}

			closedList.push_back(current);

			// Stop the search if the goal is found
			if (goalFound)
				openList.clear();

		}

		Pair currentPos = goalPos;
		Pair previousPos;
		while (currentPos != startPos) {
			previousPos = currentPos;
			currentPos = nodes[currentPos.first][currentPos.second].parentPos;
		}

		// Return the next position in the path, 
		return previousPos;
	}

};



#endif