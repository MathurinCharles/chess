#include <vector>
#include <stack>
#include <algorithm>
#include <iostream>
#include <cassert>
#include "game.h"
#include "board.h"
#include "global.h"
#include "piece.h"
#include "concretepieces.h"
#include "move.h"

Game::Game() {
    haveOpeningLibrary = false;
 }

void Game::importLibrary(std::string filename){
    if(!(haveOpeningLibrary)) haveOpeningLibrary=true;
    openingLibrary.readFile(filename);
}

void Game::play(Move *m) {
    assert(m != NULL);
    plays_.push(m);
    lenPlays_ += 1;
    if (haveOpeningLibrary){
        haveOpeningLibrary = false;
        if (!openingLibrary.emptyTree()){
            std::vector<std::string> libMoves = openingLibrary.allMoves();
            for (auto x : libMoves) {
                std::string s = m->toBasicNotation();
                if(s == x){
                    libPlays_.push(openingLibrary);
                    lenLibPlays_ += 1;
                    openingLibrary = *(openingLibrary.playMove(s));
                    haveOpeningLibrary = true;
                    continue;
                }
            }
        }
    }
    m->perform(&board_);
    board_.switch_player();
}

bool Game::undo() {
    if (plays_.empty()) {
        std::cout << "No move to undo" << std::endl;
        return false;
    }
    Move *m;
    m = plays_.top();
    m->unPerform(&board_);
    plays_.pop();
    lenPlays_ -= 1;
    if (haveOpeningLibrary){
        openingLibrary = libPlays_.top();
        libPlays_.pop();
        lenLibPlays_ -= 1;
    } else if (lenPlays_ == lenLibPlays_){
        haveOpeningLibrary = true;
    }
    board_.switch_player();
    return true;
}

void Game::display() {
    board_.display();
}

void Game::displayHeuristic() {
    int score = board_.heuristic();
    std::cout << score << std::endl;
}

void Game::displayCaptured() {
    board_.displayCaptured();
}

std::vector<Move *> Game::getAllLegalMoves() {
    return board_.getAllLegalMoves();
}


Move *Game::computerSuggestion(int strength,bool uselib) {
    srand(time(NULL));
    std::vector<Move *> moves = board_.getAllLegalMoves();

    if (haveOpeningLibrary && uselib && !(openingLibrary.emptyTree())){
        std::vector<std::string> libMoves = openingLibrary.allMoves();
        for (auto x:libMoves){
            std::cout << "library moves___________________" << x << std::endl;
        }
    }

    if (haveOpeningLibrary && uselib && !(openingLibrary.emptyTree())){
        if (plays_.empty()) {
            std::vector<std::string> libMoves = openingLibrary.allMoves();
            int nm = rand()%libMoves.size();
            for (auto x : moves) {
                std::string s = x->toBasicNotation();
                if(s == libMoves[nm]){
                    return x;
                }
            }
        } else {
            std::vector<std::string> libMoves = openingLibrary.allMoves();
            int nm = rand()%libMoves.size();
            for (auto x : moves) {
                std::string s = x->toBasicNotation();
                if(s == libMoves[nm]){
                    return x;
                }
            }
        }
    }
    if (moves.size() == 0) {
        return NULL;
    }
    if (strength == 0) {
        int nm = rand()%moves.size();
        return moves[nm];
    }
    if (strength == 1) {
        std::vector<int> values(moves.size());
        for (unsigned int i = 0; i<moves.size(); i++){
            play(moves[i]);
            values[i] = board_.heuristic();
            undo();
        }
        int nm = 0;
        if (board_.getPlayer() == WHITE){
            for (unsigned int i = 1; i<moves.size(); i++){
                if (values[i] > values[nm]) {
                    nm = i;
                }
            }
        } else {
            for (unsigned int i = 1; i<moves.size(); i++){
                if (values[i] < values[nm]) {
                    nm = i;
                }
            }
        }
        if (values[nm] == 0){
            nm = rand()%moves.size();
        }
        return moves[nm];
    }

    return NULL;
}
