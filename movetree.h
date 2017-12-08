
#include <iostream>
#include <cassert>
#include <map>
#include <vector>
#include <string>


class Tree {
    public:

    //Read the file "filename" and build the Tree
    void readFile(std::string filename);

    void readFilePgn(std::string filename);

    // add the opening given in `opening` vector starting from index i
    // ...exercise to the reader: use an iterator instead
    void addOpening(const std::vector<std::string> &opening, int i);

    // print all possible moves from current node/tree
    std::vector<std::string> allMoves();

    // return node/tree after playing move s
    // from current node/tree
    Tree *playMove(const std::string &s);

    bool emptyTree();

private:
    // a tree is a map from string (ie. move) to trees
    std::map<std::string, Tree *> children_;
};
