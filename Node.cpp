#include "Node.h"

Node::Node(SharedTile tile, std::shared_ptr<Node> next) {
    this->tile = tile;
    this->next = next;
}

SharedTile &Node::getTile() {
    return tile;
}

std::shared_ptr<Node> &Node::getNext() {
    return next;
}

void Node::setNext(const std::shared_ptr<Node> &next) {
    Node::next = next;
}
