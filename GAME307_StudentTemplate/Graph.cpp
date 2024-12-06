#include "Graph.h"
#include <queue>

Graph::Graph()
{
}

Graph::~Graph()
{
}

bool Graph::OnCreate(std::vector<Node*> nodes_)
{
    // given a list of nodes, initialize a matrix of costs with 0.0

    int numNodes = nodes_.size();

    cost.resize(numNodes);

    for (int i = 0; i < numNodes; i++)
    {
        // populate the internal map
        if (i != nodes_[i]->getLabel())
        {
            std::cerr << "node with label 'i' not in the 'i' position for " << i << "\n";
            return false;
        }
        node[i] = nodes_[i];

        // set up connections
        cost[i].resize(numNodes);

        for (int j = 0; j < numNodes; j++)
        {


            //ClearConnections();
            //clearAllConnections();
            cost[i][j] = 0.0f;
            
        }
    }

    return true;
}
void Graph::clearAllConnections() {
    // Step 1: Clear the connection costs (set all to -1.0f or another default value)
    for (auto& row : cost) {
        std::fill(row.begin(), row.end(), 0.0f); // Reset all weights (assuming -1.0f means no connection)
    }

    // Step 2: Optionally, clear per-node connection information (like neighbors, visited flag, etc.)
    for (auto& pair : node) {
        if (pair.second != nullptr) {
        Node* currentNode = pair.second;
        currentNode->walkable = true;

    }

    }
}
void Graph::ClearConnections(Node* fromNode, Node* toNode) {
    addWeightedConnection(fromNode, toNode, 0.0f);
}

int Graph::numNodes()
{
    return node.size();
}

void Graph::addWeightedConnection(Node* fromNode, Node* toNode, float weight)
{
    cost[fromNode->getLabel()][toNode->getLabel()] = weight;
}

std::vector<Node*> Graph::neighbours(Node* fromNode) {
    std::vector<Node*> result = {};
    int from = fromNode->getLabel();

    // Debug print to check if the cost matrix is properly set
  //  std::cout << "Checking neighbors for node " << fromNode->getLabel() << std::endl;

    cost.resize(numNodes());
    for (int j = 0; j < numNodes(); j++) {
        cost[j].resize(numNodes());  // Initialize each row with a size of numNodes() and default value 0.0f
        if (cost
            [from]
            [j] > 
            0.0f) 
        { // there is a valid connection
            result.push_back(getNode(j));
        }
    }

    // Debug print to check the number of neighbors
   // std::cout << "Number of neighbors: " << result.size() << std::endl;

    return result;
}


struct NodeAndPriority
{
    Node* node;
    float priority;

    bool operator()(NodeAndPriority const& lhs, NodeAndPriority const& rhs)
    {
        return lhs.priority > rhs.priority;
    }


};



std::vector<Node*> Graph::findPath(Node* startNode, Node* goalNode)
{
    std::vector<Node*> result;

    //declarations
    float new_cost;
    float priority;
    Node* currentNode = startNode;

    //frontier
    std::priority_queue<NodeAndPriority, std::deque<NodeAndPriority>, NodeAndPriority> frontier;
    frontier.push(NodeAndPriority{ currentNode, 0.0f });

    // track solution path (came_from)
    std::vector<int> came_from;
    // intialize to -1, a value that cannot be label of a node
    came_from.resize(numNodes(), -1);

    //cost so far storage
    //use std::map, not vector, to allow detecting if a node has an entry
    int start = startNode->getLabel();
    int goal = goalNode->getLabel();

    std::map<int, float> cost_so_far;
    cost_so_far[start] = 0.0f;

    //TODO 

    // loop through the frontier, while it is not empty
    while (!frontier.empty())
    {
        //get the top node, save it in currentNode
        currentNode = frontier.top().node;
        //pop the top node
        frontier.pop();
        // if its the goal, then break out
        if (currentNode->getLabel() == goal)
        {
            break;
        }

        //for the neighbours of current node
        for (Node* next : neighbours(currentNode))
        {
            int nextLabel = next->getLabel();
            if (nextLabel >= numNodes())
            {
                std::cerr << "Error: nextLabel out of range: " << nextLabel << "\n";
                continue;
            }


            //calculate new cost
            new_cost = cost_so_far[currentNode->getLabel()] + cost[currentNode->getLabel()][nextLabel];
            //if neighbour is not an index in cost_so_far or new_cost is lower
            if (cost_so_far.find(nextLabel) == cost_so_far.end() || new_cost < cost_so_far[nextLabel])
            {
                // found a better path, so update data structures
                cost_so_far[nextLabel] = new_cost;
                priority = new_cost; // Assuming heuristic is zero for simplicity
                frontier.push(NodeAndPriority{ next, priority });
                came_from[nextLabel] = currentNode->getLabel();
            }
        }
    }

    // TODO
    // follow the breadcrumbs in came from to rebuild the path, store in result
    int current = goal;
    while (current != start) {
        if (current >= numNodes() || current < 0) {
            std::cerr << "Error: current out of range: " << current << std::endl;
            break;
        }

        Node* node = getNode(current);
        if (node == nullptr) {
            std::cerr << "Error: getNode returned nullptr for label " << current << std::endl;
            break;
        }

        result.push_back(node);
        current = came_from[current];
    }


    result.push_back(getNode(start));
    std::reverse(result.begin(), result.end());



    return result;
}
