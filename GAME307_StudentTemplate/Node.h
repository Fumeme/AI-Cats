#ifndef NODE_H
#define NODE_H

#include <Vector.h>
#include <vector>

class Node
{
private:
	int label;

public:
    int x, y;
    //float gCost;  // Cost from the start node
    //float hCost;  // Heuristic (estimated cost to the goal)
    //Node* parent; // Parent node to reconstruct the path
    //bool walkable; // If the node is walkable

	Node(int label_) : label{ label_ } {};
    //Node(int x_, int y_) : x(x_), y(y_), gCost(INFINITY), hCost(0), parent(nullptr), walkable(true) {}

	~Node() {}

	int getLabel() { return label; };
    // Get total cost
    //float fCost() const { return gCost + hCost; }

    // Compare nodes for the priority queue (min-heap)
    //bool operator>(const Node& other) const {
    //    return fCost() > other.fCost();
    //}

    MATH::Vec2 NodeToGrid(int label_);
    float Heuristic(Node* node_, Node* TargetNode_);
    std::vector<Node*> FindPath(Node* startnode_, Node* targetnode_);


};

#endif