#include <iostream>
#include <cassert>
#include <map>
#include <vector>
#include <string>
#include "movetree.h"
#include <fstream>




void Tree::readFile(std::string filename){
    std::ifstream file(filename, std::ios::in);
    int n, m;
    file >> n;
    for (int l=0;l<n;l++){
        file >> m;
        std::vector<std::string> opening(m);
        for (int i=0;i<m;i++){
            file >> opening[i];            
        }
        this->addOpening(opening, 0);
    }
    file.close();
}

void Tree::addOpening(const std::vector<std::string> &opening, int i) {
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

std::vector<std::string> Tree::allMoves() {
    std::vector<std::string> res;
    // kv goes over all pairs in map children_
    // kv = (kv.first, kv.second)
    for (const auto &kv : children_) {
        res.push_back(kv.first);
    }
    return res;
} 

Tree *Tree::playMove(const std::string &s) {
    assert(children_.find(s) != children_.end());
    return children_[s];
}

bool Tree::emptyTree(){
    return (children_.empty());
}




