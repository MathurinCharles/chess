// This is a simple implementation of a "prefix tree" 
// https://en.wikipedia.org/wiki/Trie
// used to represent and play openings in chess.
//
// An *opening* is a sequence of move. For instance, the following openings
// 1. a, f  
// 2. a, b
// 3. a, b, h
// 4. a, c
// 5. e, f, g
// correspond the tree
//                   
//   --a--*-f--*
//   |    |--b-*-h-*
// *-|    |--c-----*
//   |   
//    -e--*-f-*-g--*

#include <iostream>
#include <cassert>
#include <map>
#include <vector>
#include <string>

class Tree {
    public:

    // add the opening given in `opening` vector starting from index i
    // ...exercise to the reader: use an iterator instead
    void addOpening(const std::vector<std::string> &opening, int i) {
        if ((size_t)i == opening.size()) {
            return;
        }
        std::string move = opening[i];
        Tree *t = NULL;
        if (children_.find(move) == children_.end()) {
            t = new Tree();
            children_[move] = t;
        } else {
            t = children_[move];
        }
        t->addOpening(opening, i+1);
    }

    // print all possible moves from current node/tree
    std::vector<std::string> allMoves() {
        std::vector<std::string> res;
        // kv goes over all pairs in map children_
        // kv = (kv.first, kv.second)
        for (const auto &kv : children_) {
            res.push_back(kv.first);
        }
        return res;
    } 

    // return node/tree after playing move s
    // from current node/tree
    Tree *playMove(const std::string &s) {
        assert(children_.find(s) != children_.end());
        return children_[s];
    }

private:
    // a tree is a map from string (ie. move) to trees
    std::map<std::string, Tree *> children_;
};

// print a vector of string on one line
void print_vector(const std::vector<std::string> &v) {
    std::cout << "vector: ";
    for (auto &s : v) {
        std::cout << s << " "; 
    }
    std::cout << std::endl;
}

int main() { 
    Tree *t = new Tree();

    // add all the openings to the initially empty tree
    t->addOpening({"a", "f"}, 0);
    t->addOpening({"a", "b"}, 0);
    t->addOpening({"a", "b", "h"}, 0);
    t->addOpening({"a", "c"}, 0);
    t->addOpening({"e", "f", "g"}, 0);

    // initially, moves a and e are possible
    print_vector(t->allMoves());
    // if we play a
    t = t->playMove("a");
    // moves b, c and f become possible
    print_vector(t->allMoves());
    t = t->playMove("b");
    print_vector(t->allMoves());
}