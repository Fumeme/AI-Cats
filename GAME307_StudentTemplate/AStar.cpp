#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <cmath>
#include <functional>
#include <algorithm>
#include "Node.h"



class AStar {
private:
    std::vector<std::vector<Node>> grid;
    std::priority_queue<Node*, std::vector<Node*>, std::greater<Node*>> frontier;
    std::unordered_map<Node*, float> costSoFar;
    std::unordered_map<Node*, Node*> cameFrom;

    // Define the neighbors (8 directions)
    int dx[8] = { -1, 1, 0, 0, -1, 1, -1, 1 };
    int dy[8] = { 0, 0, -1, 1, -1, -1, 1, 1 };

    // Get the neighbors of the current node
    std::vector<Node*> getNeighbors(Node* current) {
        std::vector<Node*> neighbors;
        for (int i = 0; i < 8; ++i) {
            int nx = current->x + dx[i];
            int ny = current->y + dy[i];
            if (nx >= 0 && nx < grid.size() && ny >= 0 && ny < grid[0].size() && grid[nx][ny].walkable) {
                neighbors.push_back(&grid[nx][ny]);
            }
        }
        return neighbors;
    }

    // Heuristic function: Manhattan distance
    float heuristic(Node* a, Node* b) {
        return std::abs(a->x - b->x) + std::abs(a->y - b->y);
    }

public:
    AStar(std::vector<std::vector<Node>>& grid_) : grid(grid_) {}

    // Main A* algorithm
    void findPath(Node* start, Node* goal) {
        frontier.push(start);
        costSoFar[start] = 0;
        start->hCost = heuristic(start, goal);

        while (!frontier.empty()) {
            Node* current = frontier.top();
            frontier.pop();

            // If we reached the goal, stop
            if (current == goal) {
                std::cout << "Goal reached!" << std::endl;
                return;
            }

            // Process neighbors
            for (Node* next : getNeighbors(current)) {
                float newCost = costSoFar[current] + 1;  // Assuming cost between neighbors is 1

                // If we haven't visited this node or found a better path to it
                if (costSoFar.find(next) == costSoFar.end() || newCost < costSoFar[next]) {
                    costSoFar[next] = newCost;
                    next->parent = current;
                    next->hCost = heuristic(next, goal);

                    float priority = newCost + next->hCost;
                    frontier.push(next);

                    cameFrom[next] = current;
                }
            }
        }

        std::cout << "No path found!" << std::endl;
    }

    // Reconstruct the path from start to goal
    std::vector<Node*> getPath(Node* goal) {
        std::vector<Node*> path;
        Node* current = goal;
        while (current != nullptr) {
            path.push_back(current);
            current = cameFrom[current];
        }
        std::reverse(path.begin(), path.end());  // Reverse to get the path from start to goal
        return path;
    }
};
