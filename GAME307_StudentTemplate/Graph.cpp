#include "Graph.h"
#include "Node.h"
#include <map>
#include <vector>
#include <iostream>
#include <algorithm> 

Graph::Graph()
{
}

Graph::~Graph()
{
}

bool Graph::OnCreate(std::vector<Node*> nodes_)
{
<<<<<<< Updated upstream

    // given a list of nodes, initialize a matrix of costs with 0.0
    int numNodes = nodes_.size();
=======
	int numNodes = nodes_.size();
>>>>>>> Stashed changes

	// Resize cost matrix to match the number of nodes
	cost.resize(numNodes);

	for (int i = 0; i < numNodes; ++i)
	{
		// Insert node into the map using the node's label as the key
		if (nodes_[i])
		{
			node[nodes_[i]->getLabel()] = nodes_[i];
		}
		else {
			std::cerr << "Invalid graph!" << std::endl;
			return false;
		}

		// Resize the cost matrix row to match the number of nodes
		cost[i].resize(numNodes, INFINITY); // Initialize all connections with infinity (no path)
	}

	return true;
}


int Graph::numNodes()
{
	return node.size();
}

void Graph::addWeightedConnection(Node* fromNode, Node* toNode, float weight)
{
<<<<<<< Updated upstream
    // Add weight to the connection from 'fromNode' to 'toNode'
    cost[fromNode->getLabel()][toNode->getLabel()] = weight;
=======
	// Add weight to the connection from 'fromNode' to 'toNode'
	cost[fromNode->getLabel()][toNode->getLabel()] = weight;
>>>>>>> Stashed changes
}

std::vector<Node*> Graph::neighbours(Node* fromNode)
{
<<<<<<< Updated upstream
    std::vector<Node*> result;
    int from = fromNode->getLabel();

    // Check all possible neighbors
    for (int j = 0; j < numNodes(); j++)
    {
        if (cost[from][j] > 0.0f)  // Only add if there is a connection
        {
            result.push_back(getNode(j));
        }
    }

    return result;
=======
	std::vector<Node*> result;
	int from = fromNode->getLabel();

	// Check all possible neighbors
	for (int j = 0; j < numNodes(); j++)
	{
		if (cost[from][j] > 0.0f)  // Only add if there is a connection
		{
			if (j)  // Ensure it's a valid pointer
			{
				result.push_back(getNode(j));
			}
		}
	}

	return result;
>>>>>>> Stashed changes
}

std::vector<Node*> Graph::findPath(Node* startNode, Node* goalNode)
{
<<<<<<< Updated upstream
    std::vector<Node*> openList;
    std::vector<Node*> closedList;

    startNode->gCost = 0.0f;
    startNode->hCost = startNode->Heuristic(goalNode);
    openList.push_back(startNode);

    while (!openList.empty())
    {
        // Find node with lowest fCost
        Node* currentNode = nullptr;
        for (Node* node : openList)
        {
            if (currentNode == nullptr || node->fCost() < currentNode->fCost())
            {
                currentNode = node;
            }
        }

        if (currentNode == goalNode)
        {
            std::vector<Node*> path;
            while (currentNode != nullptr)
            {
                path.push_back(currentNode);
                currentNode = currentNode->parent;
            }
            std::reverse(path.begin(), path.end());
            return path;
        }

        openList.erase(std::remove(openList.begin(), openList.end(), currentNode), openList.end());
        closedList.push_back(currentNode);

        for (Node* neighbor : neighbours(currentNode))
        {
            if (std::find(closedList.begin(), closedList.end(), neighbor) != closedList.end())
                continue;

            float tentativeGCost = currentNode->gCost + cost[currentNode->getLabel()][neighbor->getLabel()];

            if (tentativeGCost < neighbor->gCost)
            {
                neighbor->parent = currentNode;
                neighbor->gCost = tentativeGCost;
                neighbor->hCost = neighbor->Heuristic(goalNode);

                if (std::find(openList.begin(), openList.end(), neighbor) == openList.end())
                {
                    openList.push_back(neighbor);
                }
            }
        }
    }

    std::cerr << "No path found!" << std::endl;
    return std::vector<Node*>(); // Return empty path if no path is found
=======
	std::vector<Node*> openList;
	std::vector<Node*> closedList;

	// Ensure startNode and goalNode are valid
	if (!startNode) {
		std::cerr << "Invalid start node!" << std::endl;
		return {};
	}
	else if (!goalNode) {
		std::cerr << "Invalid goal node!" << std::endl;
		return {};
	}

	startNode->gCost = 0.0f;
	startNode->hCost = startNode->Heuristic(goalNode);
	openList.push_back(startNode);

	while (!openList.empty())
	{
		// Find node with lowest fCost
		Node* currentNode = nullptr;
		for (Node* node : openList)
		{
			if (!node) {
				std::cerr << "Encountered a nullptr in openList!" << std::endl;
				continue;  // Skip invalid nodes
			}

			if (currentNode == nullptr || node->fCost() < currentNode->fCost())
			{
				currentNode = node;
			}
		}

		// If currentNode is nullptr, we are in a bad state, should break
		if (!currentNode) {
			std::cerr << "No valid node found in openList!" << std::endl;
			break;
		}

		// If we reached the goal node, reconstruct the path
		if (currentNode == goalNode)
		{
			std::vector<Node*> path;
			while (currentNode != nullptr)
			{
				path.push_back(currentNode);
				currentNode = currentNode->parent;
			}
			std::reverse(path.begin(), path.end());
			return path;
		}

		// Move currentNode from openList to closedList
		openList.erase(std::remove(openList.begin(), openList.end(), currentNode), openList.end());
		closedList.push_back(currentNode);

		// Explore neighbors
		for (Node* neighbor : neighbours(currentNode))
		{
			if (std::find(closedList.begin(), closedList.end(), neighbor) != closedList.end())
				continue;  // Skip already processed neighbors

			if (!neighbor) {
				std::cerr << "Encountered a nullptr in neighbors!" << std::endl;
				continue;  // Skip invalid neighbors
			}

			float tentativeGCost = currentNode->gCost + cost[currentNode->getLabel()][neighbor->getLabel()];

			// If the tentative GCost is better, update neighbor
			if (tentativeGCost < neighbor->gCost)
			{
				neighbor->parent = currentNode;
				neighbor->gCost = tentativeGCost;
				neighbor->hCost = neighbor->Heuristic(goalNode);

				// If the neighbor is not in openList, add it
				if (std::find(openList.begin(), openList.end(), neighbor) == openList.end())
				{
					openList.push_back(neighbor);
				}
			}
		}
	}

	std::cerr << "No path found!" << std::endl;
	return {};  // Return empty path if no path is found
>>>>>>> Stashed changes
}
