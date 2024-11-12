#ifndef NODE_H
#define NODE_H

#include <Vector.h>
#include <vector>
#include <cmath>  

class Node
{
private:
    int label;

public:
    int x, y;
    float gCost = INFINITY;  // Cost from the start node
    float hCost = 0.0f;      // Heuristic 
    Node* parent = nullptr;  // Parent node to reconstruct the path
    bool walkable = true;    // If the node is walkable

    // Constructor
    Node(int label_) : label{ label_ } {
        x = label_ / 25;  // Assuming grid size is 25x25
        y = label_ % 25;
    }

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
    MATH::Vec2 NodeToGrid(int label_)
    {
        int x = label_ / 25;  
        int y = label_ % 25;  
        return MATH::Vec2(x, y);
    }

    // Placeholder for FindPath (A* algorithm will be here)
    std::vector<Node*> FindPath(Node* startnode_, Node* targetnode_);
};

#endif
