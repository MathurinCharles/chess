#include <cassert>
#include "concretepieces.h"
#include "global.h"
#include "board.h"
#include "move.h"

void Pawn::getMoves(const Board &g, std::vector<Move *> &res) const {
    std::vector<Position> poss;
    Color color = getColor();
    Position pos = getPosition(); 
    int di = 0;
    int dj = 0;
    int max = 0;

    if (color == WHITE) {
        std::vector<Position> rel = {{1,1},{1,-1}};
        g.filter(pos, rel, color, true, poss);
        di = 1;
        max = (pos.first == 1)?2:1;
    } else {
        std::vector<Position> rel = {{-1,1},{-1,-1}};
        g.filter(pos, rel, color, true, poss);
        di = -1;
        max = (pos.first == 6)?2:1;
    }
    g.reachablePositionsAlongStraightLine(pos, di, dj, max, color, false, poss);
    positionsToMoves(g, pos, poss, res);
}

char Pawn::notation() const {
    return ' ';
}

char Pawn::toChar() const {
    return getColor()?'P':'p';
}

int Pawn::heuristic() const{
    return 1;
}

Pawn::Pawn(Position pos, Color color) : Piece(pos,color) {}

Bishop::Bishop(Position pos, Color color) : Piece(pos, color) {}

void Bishop::getMoves(const Board &g, std::vector<Move *> &res) const {
    std::vector<Position> poss;
    Position pos = getPosition(); 
    int di[] = {-1, 1, 1, -1};
    int dj[] = {-1, 1, -1, 1}; 
    int max = 8;
    for (int i = 0; i < 4; i++) {
        g.reachablePositionsAlongStraightLine(pos, di[i], dj[i], max, getColor(), true, poss);
    }
    positionsToMoves(g, pos, poss, res);
}

char Bishop::toChar() const {
    return (getColor())?'B':'b';
}

int Bishop::heuristic() const{
    return 3;
}

char Bishop::notation() const {
    return 'B';
}

King::King(Position pos, Color color) : Piece(pos,color) {}

void King::getMoves(const Board &g, std::vector<Move *> &res) const {
    std::vector<Position> poss;
    Position pos = getPosition(); 
    int di[] = {-1, 1, 1, -1,-1,0,1,0};
    int dj[] = {-1, 1, -1, 1,0,-1,0,1}; 
    int max = 1;
    for (int i = 0; i < 8; i++) {
        g.reachablePositionsAlongStraightLine(pos, di[i], dj[i], max,  getColor(), true, poss);
    }
    positionsToMoves(g, pos, poss, res);
}

char King::toChar() const {
    return (getColor())?'K':'k';
}

int King::heuristic() const{
    return 1000;
}

char King::notation() const {
    return 'K';
}

Queen::Queen(Position pos, Color color) : Piece(pos,color) {}

void Queen::getMoves(const Board &g, std::vector<Move *> &res) const {
    std::vector<Position> poss;
    Position pos = getPosition(); 
    int di[] = {-1, 1, 1, -1,-1,0,1,0};
    int dj[] = {-1, 1, -1, 1,0,-1,0,1}; 
    int max = 8;
    for (int i = 0; i < 8; i++) {
        g.reachablePositionsAlongStraightLine(pos, di[i], dj[i], max,  getColor(), true, poss);
    }
    positionsToMoves(g, pos, poss, res);
}

char Queen::toChar() const {
    return (getColor())?'Q':'q';
}

int Queen::heuristic() const{
    return 10;
}

char Queen::notation() const {
    return 'Q';
}

Rook::Rook(Position pos, Color color) : Piece(pos,color) {}

void Rook::getMoves(const Board &g, std::vector<Move *> &res) const {
    std::vector<Position> poss;
    Position pos = getPosition(); 
    int di[] = {-1,0,1,0};
    int dj[] = {0,-1,0,1}; 
    int max = 8;
    for (int i = 0; i < 4; i++) {
        g.reachablePositionsAlongStraightLine(pos, di[i], dj[i], max,  getColor(), true, poss);
    }
    positionsToMoves(g, pos, poss, res);
}

char Rook::toChar() const {
    return (getColor())?'R':'r';
}

int Rook::heuristic() const{
    return 5;
}

char Rook::notation() const {
    return 'R';
}

Knight::Knight(Position pos, Color color) : Piece(pos,color) {}

void Knight::getMoves(const Board &g, std::vector<Move *> &res) const {
    std::vector<Position> poss;
    Color color = getColor();
    Position pos = getPosition();
    std::vector<Position> rel = {{2,1}, {-2,1}, {2,-1}, {-2,-1}, {1,2}, {1,-2}, {-1,2}, {-1,-2}};
    g.filter(pos, rel, color, false, poss);
    positionsToMoves(g, pos, poss, res);
}

char Knight::toChar() const {
    return (getColor())?'N':'n';
}

int Knight::heuristic() const{
    return 3;
}

char Knight::notation() const {
    return 'N';
}

