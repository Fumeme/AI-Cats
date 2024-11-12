#ifndef NODE_H
#define NODE_H

#include <Vector.h>
#include <vector>
#include <cmath>  // For abs function

class Node
{
private:
    int label;

public:
    int x, y;
    float gCost = INFINITY;  // Cost from the start node
    float hCost = 0.0f;      // Heuristic (estimated cost to the goal)
    Node* parent = nullptr;  // Parent node to reconstruct the path
    bool walkable = true;    // If the node is walkable

    // Constructor
<<<<<<< Updated upstream
    Node(int label_) : label{ label_ }, x(0), y(0) {}

    // Destructor
    ~Node() {}

    int getLabel() { return label; }

    // Calculate total cost (fCost = gCost + hCost)
    float fCost() const
    {
        return gCost + hCost;
    }

    // Compare nodes for the priority queue (min-heap)
    bool operator>(const Node& other) const
    {
        return fCost() > other.fCost();
    }

    // Function to calculate heuristic (Manhattan distance)
    float Heuristic(Node* targetNode) const
    {
        return std::abs(targetNode->x - this->x) + std::abs(targetNode->y - this->y);  // Manhattan Distance
    }

    // Optional: Function to convert label to grid position, if needed
    MATH::Vec2 NodeToGrid(int label_);

};

#endif
=======
    Node(int label_);

    // Destructor
    ~Node();

    // Getter for label
    int getLabel() const { return label; }

    // Calculate total cost (fCost = gCost + hCost)
    float fCost() const;

    // Compare nodes for the priority queue (min-heap)
    bool operator>(const Node& other) const;

    // Function to calculate heuristic (Manhattan distance)
    float Heuristic(Node* targetNode) const;

    // Optional: Function to convert label to grid position
    MATH::Vec2 NodeToGrid(int label_);

    // Placeholder for FindPath (A* algorithm will be here)
    std::vector<Node*> FindPath(Node* startnode_, Node* targetnode_);
};

#endif // NODE_H
>>>>>>> Stashed changes
