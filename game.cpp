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

Game::Game() { }

void Game::play(Move *m) {
    assert(m != NULL);
    plays_.push(m);
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


Move *Game::computerSuggestion(int strength) {
    srand(time(NULL));
    std::vector<Move *> moves = board_.getAllLegalMoves();
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
            std::cout << values[i] << std::endl;
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