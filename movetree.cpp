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

void Tree::readFilePgn(std::string filename){
    std::ifstream file(filename, std::ios::in);
    std::string s="";
    std::vector<std::string> opening(0);
    if(file){
        std::string move;
        while(file){
            file >> move;
            s = "";
            s.append(move,1,1);
            while((s==".")){
                std::cout << "test in loop while" << std::endl;
                file >> move; // move of first player
                if (move.size()==2) move = " "+move;
                std::cout << "move1: " << move << std::endl;
                opening.push_back(move);
                if (file){
                    move = "";
                    file >> move; // move of second player
                    std::cout << "move2: " << move << std::endl;
                    s = "";
                    s.append(move,0,1);
                    if (s !="["){
                        if (move.size()==2) move = " "+move;
                        opening.push_back(move);
                    } else {
                        s = "";
                        s.append(move,move.length()-1,1);
                        while(s!="]"){
                            file >> move;
                            s = "";
                            s.append(move,move.length()-1,1);
                            std::cout << "move3: " << move << std::endl;
                        }
                        if (opening.size()>0){
                            std::cout << "inside opening.size(): " << opening.size() << std::endl;
                            this->addOpening(opening, 0);
                            opening.clear();
                        }
                    }
                }
                if (file){
                    file >> move;
                    s ="";
                    s.append(move,1,1);
                }
            }
            if (opening.size()>0){
                std::cout << "opening.size(): " << opening.size() << std::endl;
                this->addOpening(opening, 0);
                opening.clear();
            }
        }
    }
    file.close();
}


void Tree::addOpening(const std::vector<std::string> &opening, int i) {
    if ((size_t)i == opening.size()) {
        return;
    }
    std::string move = opening[i];

    std::cout << " in addopening " <<  opening[i] << std::endl;
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
