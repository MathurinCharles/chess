#include <vector>
#include "openingtree.h"
#include "move.h"

Node::Node(Move *m, std::vector<Node *> f){
    label = m;
    followers = f;
}

Move * Node::getLabel() const {
    return label;
}

std::vector<Node *> Node::getFollowers() const{
    return followers;
}