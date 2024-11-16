//#ifndef ASTARPATHFINDER_H
//#define ASTARPATHFINDER_H
//
//#include <vector>
//#include <unordered_map>
//#include <queue>
//#include "Node.h"  
//#include "Graph.h" 
//#include "Tile.h" 
//
//
//struct NodeCost {
//    Node* node;
//    float gCost;  // Cost from start node
//    float hCost;  // Heuristic to goal node
//    float fCost;  // Total cost (gCost + hCost)
//    Node* parent;
//
//    NodeCost(Node* node);
//    bool operator>(const NodeCost& other) const;
//};
//
//class AStarPathfinder {
//private:
//    Graph* graph;
//    float tileWidth;
//    float tileHeight;
//
//public:
//    AStarPathfinder(Graph* graph, float tileWidth, float tileHeight);
//
//    // Main function to find the shortest path from start to goal, considering blocked tiles
//    std::vector<Node*> findPath(Node* start, Node* goal, const std::vector<Tile*>& blockedTiles);
//
//private:
//    // Helper functions
//    std::vector<Node*> reconstructPath(const NodeCost& goalCost);
//    float heuristic(Node* a, Node* b);
//    float distance(Node* a, Node* b);
//    bool isBlocked(Node* node, const std::vector<Tile*>& blockedTiles);
//    std::vector<Node*> getNeighbors(Node* node);
//};
//
//#endif // ASTARPATHFINDER_H
