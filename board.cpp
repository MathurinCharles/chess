#include "board.h"
#include "piece.h"
#include "concretepieces.h"
#include <vector>
#include <algorithm>
#include <iostream>
#include <cassert>
#include <cstring>

int Board::heuristic() const {
    int score = 0;
    for (int i = 0 ; i < 16;i++){
        if ((pieces_[1][i])->isCaptured()){
            score -= pieces_[1][i]->heuristic();
        }
    }
    for (int i = 0 ; i < 16;i++){
        if ((pieces_[0][i])->isCaptured()){
            score += pieces_[0][i]->heuristic();
        }
    }
    return score;
}

bool Board::isInside(int i, int j) const {
    return i >= 0 && i < 8 && j >= 0 && j < 8;
}

void Board::reachablePositionsAlongStraightLine(Position start, int di, int dj, 
    int max, Color pl, bool canCapture, std::vector<Position> &res) const {
    int step = 0;
    int si = start.first; 
    int sj = start.second;
    while (true) { 
        step++;
        si += di;
        sj += dj;
        if (!isInside(si, sj) || 
            step > max) {
            break;
        } 
        if (board_[si][sj] != NULL && 
            (board_[si][sj]->getColor() == pl || !canCapture)) {
            break;
        }
        res.push_back({si, sj});
        if (board_[si][sj] != NULL) {
            break;
        }
    }
}

void Board::filter(Position start, const std::vector<Position> &rel, Color pl, 
    bool onlyIfCapture, std::vector<Position> &res) const {
    int si = start.first; 
    int sj = start.second;
    for (auto d : rel) {
        int nsi = si + d.first;
        int nsj = sj + d.second;
        if (!isInside(nsi, nsj)) {
            continue;
        }
        Piece *p = board_[nsi][nsj];
        if ((p != NULL) && p->getColor() == pl) {
            continue;
        }
        if (onlyIfCapture && p == NULL) {
            continue;
        }
        res.push_back({nsi,nsj});
    }
}

Board::Board() {
    memset(board_, (int) NULL, 64 * sizeof(Piece *));
    for (int i = 0; i < 8; i++) {
        board_[6][i] = addPiece(new Pawn({6,i}, BLACK)); 
        board_[1][i] = addPiece(new Pawn({1,i}, WHITE)); 
    }

    board_[7][0] = addPiece(new Rook({7,0}, BLACK));
    board_[7][1] = addPiece(new Knight({7,1}, BLACK));
    board_[7][2] = addPiece(new Bishop({7,2}, BLACK));
    board_[7][3] = addPiece(new Queen({7,3}, BLACK));
    board_[7][4] = king_[BLACK] = addPiece(new King({7,4}, BLACK));
    board_[7][5] = addPiece(new Bishop({7,5}, BLACK));
    board_[7][6] = addPiece(new Knight({7,6}, BLACK));
    board_[7][7] = addPiece(new Rook({7,7}, BLACK));

    board_[0][0] = addPiece(new Rook({0,0}, WHITE));
    board_[0][1] = addPiece(new Knight({0,1}, WHITE));
    board_[0][2] = addPiece(new Bishop({0,2}, WHITE));
    board_[0][3] = addPiece(new Queen({0,3}, WHITE));
    board_[0][4] = king_[WHITE] = addPiece(new King({0,4}, WHITE));
    board_[0][5] = addPiece(new Bishop({0,5}, WHITE));
    board_[0][6] = addPiece(new Knight({0,6}, WHITE));
    board_[0][7] = addPiece(new Rook({0,7}, WHITE));
}

Piece * Board::addPiece(Piece *p) {
  pieces_[p->getColor()].push_back(p);
  return p;
}

Color Board::getPlayer() const { 
    return current_player_;
}

void Board::switch_player() {
    current_player_ = current_player_?BLACK:WHITE;
}

void Board::display() {
    std::string player = current_player_?"White":"Black";
    std::cout << " Current player " << player << std::endl;
    std::cout << "  ABCDEFGH " << std::endl;
    for (int i = 7; i >= 0; i--) {
        std::cout << i+1 << " ";
        for (int j = 0; j < 8; j++) {
            if (board_[i][j]) {
                std::cout << board_[i][j]->toChar();
            } else {
                std::cout << ' ';
            }
        }
        std::cout << " " << i+1 << std::endl;
    }
    std::cout << "  ABCDEFGH" << std::endl;
    if (isInCheck(WHITE)) {
        std::cout << "White is checked" << std::endl;
    }
    if (isInCheck(BLACK)) {
        std::cout << "Black is checked" << std::endl;
    }
    if (getAllLegalMoves().size() == 0) {
        std::cout << "Game over" << std::endl;
    }

}

void Board::displayCaptured() {
    std::cout << "White captured pieces : ";
    for (int i = 0 ; i < 16;i++){
        if ((pieces_[0][i])->isCaptured()){
            std::cout << (pieces_[0][i])->toChar() << " ";
        }
    }
    std::cout << std::endl << "Black captured pieces : ";
    for (int i = 0 ; i < 16;i++){
        if ((pieces_[1][i])->isCaptured()){
            std::cout << (pieces_[1][i])->toChar() << " ";
        }
    }
    std::cout << std::endl;
}

std::vector<Move *> Board::getAllMoves(Color player) const {
        std::vector<Move *> moves;
        for (auto p : pieces_[player]) {
            if (p->isCaptured()) {
                continue;
            }
            p->getMoves(*this, moves);
        }
        return moves;
}

std::vector<Move *> Board::getAllMoves() const {
        return getAllMoves(current_player_);
}

std::vector<Move *> Board::getAllLegalMoves() {
        std::vector<Move *> moves = getAllMoves();
        std::vector<Move *> res;
        for (auto x : moves) {
            if (isLegal(x)) {
                res.push_back(x);
           }
        }
        return res;
}

bool Board::isLegal(Move *m) {
    bool res = false;
    m->perform(this);
    res = !isInCheck(current_player_);
    m->unPerform(this);
    return res;
}

bool Board::getPiece(Position pos, Piece **p) const {
    *p = board_[pos.first][pos.second];
    return *p != NULL;
}

void Board::setPiece(Position pos, Piece *p) {
    assert(p);
    board_[pos.first][pos.second] = p;
}

void Board::removePiece(Position pos) {
    board_[pos.first][pos.second] = NULL;
}

bool Board::isInCheck(Color p) const {
    Color other = p?BLACK:WHITE;
    std::vector<Move *> moves = getAllMoves(other);
    Piece *k = king_[p];
    for (auto m : moves) {
        if (m->doesCapture(k)) {
            return true;
        }  
    }
    return false;
}

