#ifndef OPENINGTREE_H_
#define OPENINGTREE_H_

#include <vector>
#include "move.h"

class Node {
public:

    Node(Move *m, std::vector<Node *> f);

    Move * getLabel() const;

    std::vector<Node *> getFollowers() const;

private:

    Move *label;
    std::vector<Node *> followers;

};

class Librarytree {
public:

    Tree(/*A trouver*/);
    

private:

    Node *root;
    Node *record;

};

#endif // OPENINGTREE_H_