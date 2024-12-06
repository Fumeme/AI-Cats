#ifndef NODE_H
#define NODE_H

#include <Vector.h>
#include <vector>
#include <cmath>  // For abs function
#include <Vector.h>

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
    Node(int label_) : label{ label_ } {
        x = label_ / 25;  // Assuming grid size is 25x25
        y = label_ % 25;
        
    }

    // Destructor
    ~Node() {}

    int getLabel() {

        if (this != nullptr && label != NULL) {
            return label;
        } else
        return NULL;
    }

    // Calculate total cost (fCost = gCost + hCost)
    float fCost() const
    {
        return gCost + hCost;
    }
     MATH::Vec2 getPos2() {
        MATH::Vec2 Result;
        Result.x = x;
        Result.y = y;
        return Result;
    }
     MATH::Vec3 getPos3() {
        MATH::Vec3 Result;
        if (this == nullptr) {
            std::cerr << "node is null" << std::endl;
            return Result;;
        }
        Result.x = x;
        Result.y = y;
        Result.z = 0;
        return Result;
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
        MATH::Vec2 pos;
        pos.x = x;
        pos.y = y;
        return pos;
    }
};

#endif
