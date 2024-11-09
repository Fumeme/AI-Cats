#include "Node.h"
#include <queue>


MATH::Vec2 Node::NodeToGrid(int label_)
{
    int x = label_ / 25;
    int y = label_ % 25;
    return MATH::Vec2(x, y);
}

float Node::Heuristic(Node* node_, Node* TargetNode_)
{
    int i = node_->getLabel() / 25;
    int i = node_->getLabel() % 25;

    float dx = std::abs(NodeToGrid(node_->getLabel()).x - NodeToGrid(TargetNode_->getLabel()).x);
    float dy = std::abs(NodeToGrid(node_->getLabel()).y - NodeToGrid(TargetNode_->getLabel()).y);

    return dx + dy;

}

std::vector<Node*> Node::FindPath(Node* startnode_, Node* targetnode_)
{
    std::vector<Node*> result;
    result.clear();
    Node* currentNode = startnode_;



    return result;
}
