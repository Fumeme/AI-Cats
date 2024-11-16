//#include "AStarPathfinder.h"
//#include <algorithm>
//#include <cmath>
//#include <limits>
//#include <queue>
//#include <unordered_map>
//
//// Constructor for NodeCost
//NodeCost::NodeCost(Node* node)
//    : node(node), gCost(FLT_MAX), hCost(0.0f), fCost(FLT_MAX), parent(nullptr) {}
//
//// Comparison operator for priority queue (using fCost)
//bool NodeCost::operator>(const NodeCost& other) const {
//    return fCost > other.fCost;
//}
//
//// Constructor for AStarPathfinder
//AStarPathfinder::AStarPathfinder(Graph* graph, float tileWidth, float tileHeight)
//    : graph(graph), tileWidth(tileWidth), tileHeight(tileHeight) {}
//
//// Main pathfinding function using A* algorithm
//std::vector<Node*> AStarPathfinder::findPath(Node* start, Node* goal, const std::vector<Tile*>& blockedTiles) {
//    std::priority_queue<NodeCost, std::vector<NodeCost>, std::greater<NodeCost>> openList;
//    std::unordered_map<Node*, NodeCost> allNodes;
//
//    NodeCost startCost(start);
//    startCost.gCost = 0.0f;
//    startCost.hCost = heuristic(start, goal);
//    startCost.fCost = startCost.gCost + startCost.hCost;
//    allNodes[start] = startCost;
//    openList.push(startCost);
//
//    while (!openList.empty()) {
//        NodeCost currentCost = openList.top();
//        openList.pop();
//
//        Node* currentNode = currentCost.node;
//
//        // If we reached the goal, reconstruct and return the path
//        if (currentNode == goal) {
//            return reconstructPath(currentNode);
//        }
//
//        // Iterate through neighbors of the current node
//        for (Node* neighbor : getNeighbors(currentNode)) {
//            if (isBlocked(neighbor, blockedTiles)) {
//                continue;  // Skip blocked neighbors
//            }
//
//            float tentativeGCost = currentCost.gCost + distance(currentNode, neighbor);
//            if (allNodes.find(neighbor) == allNodes.end() || tentativeGCost < allNodes[neighbor].gCost) {
//                NodeCost neighborCost(neighbor);
//                neighborCost.gCost = tentativeGCost;
//                neighborCost.hCost = heuristic(neighbor, goal);
//                neighborCost.fCost = neighborCost.gCost + neighborCost.hCost;
//                neighborCost.parent = currentNode;
//
//                allNodes[neighbor] = neighborCost;
//                openList.push(neighborCost);
//            }
//        }
//    }
//
//    return {}; // If no path is found, return an empty vector
//}
//
//// Reconstruct the path by backtracking from the goal node
//std::vector<Node*> AStarPathfinder::reconstructPath(Node* goal) {
//    std::vector<Node*> path;
//    Node* currentNode = goal;
//    while (currentNode != nullptr) {
//        path.push_back(currentNode);
//        currentNode = currentNode->getParent();  // Assuming Node has a getParent method
//    }
//    std::reverse(path.begin(), path.end());  // Reverse to get the path from start to goal
//    return path;
//}
//
//// Heuristic function (Manhattan distance for grid-based pathfinding)
//float AStarPathfinder::heuristic(Node* a, Node* b) {
//    return std::abs(a->getRow() - b->getRow()) + std::abs(a->getCol() - b->getCol());
//}
//
//// Distance function (uniform cost for all edges)
//float AStarPathfinder::distance(Node* a, Node* b) {
//    return 1.0f;  // Assuming uniform cost between adjacent nodes
//}
//
//// Check if the node is blocked (by its corresponding Tile object)
//bool AStarPathfinder::isBlocked(Node* node, const std::vector<Tile*>& blockedTiles) {
//    for (Tile* tile : blockedTiles) {
//        if (tile->getNode() == node && !tile->isPassable()) {
//            return true;  // Node is blocked
//        }
//    }
//    return false;  // Node is not blocked
//}
//
//// Get the neighbors of a node (based on the grid structure)
//std::vector<Node*> AStarPathfinder::getNeighbors(Node* node) {
//    std::vector<Node*> neighbors;
//
//    // Assuming your Node has methods `getRow()` and `getCol()` to determine the position
//    int row = node->getRow();
//    int col = node->getCol();
//
//    // Check the neighbors in the grid (up, down, left, right)
//    if (row > 0) neighbors.push_back(graph->getNode(row - 1, col));  // Up
//    if (row < graph->getHeight() - 1) neighbors.push_back(graph->getNode(row + 1, col));  // Down
//    if (col > 0) neighbors.push_back(graph->getNode(row, col - 1));  // Left
//    if (col < graph->getWidth() - 1) neighbors.push_back(graph->getNode(row, col + 1));  // Right
//
//    return neighbors;
//}
