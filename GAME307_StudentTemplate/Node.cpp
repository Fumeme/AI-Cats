
#include "Node.h"  // Include the header file

// Constructor definition
Node::Node(int label_) : label{ label_ } {
    x = label_ / 25;  // Assuming grid size is 25x25
    y = label_ % 25;
}

// Destructor definition
Node::~Node() {}

// fCost definition (total cost = gCost + hCost)
float Node::fCost() const {
    return gCost + hCost;
}

// Comparison operator for priority queue (min-heap)
bool Node::operator>(const Node& other) const {
    return fCost() > other.fCost();
}

// Heuristic function (Manhattan distance)
float Node::Heuristic(Node* targetNode) const {
    return std::abs(targetNode->x - this->x) + std::abs(targetNode->y - this->y);  // Manhattan Distance
}

// Function to convert label to grid position
MATH::Vec2 Node::NodeToGrid(int label_) {
    int x = label_ / 25;
    int y = label_ % 25;
    return MATH::Vec2(x, y);
}

// Placeholder FindPath function (A* algorithm will be here)
std::vector<Node*> Node::FindPath(Node* startnode_, Node* targetnode_) {
    // This function will eventually contain the A* pathfinding logic
    std::vector<Node*> path;
    return path;
}
