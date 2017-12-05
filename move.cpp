#include "global.h"
#include "move.h"
#include <iostream>
#include <cassert>

BasicMove::BasicMove(Position from, Position to, Piece *moved) : from_(from), 
                     to_(to), moved_(moved) {
   assert(moved);
}
//Nouveau constructeur à partir de par exemple "a4a5"

void BasicMove::perform(Board *b) const {
    b->setPiece(to_, moved_);
    moved_->setPosition(to_);
    b->removePiece(from_);
}

void BasicMove::unPerform(Board *b) const {
    b->setPiece(from_, moved_);
    moved_->setPosition(from_);
    b->removePiece(to_);
}

bool BasicMove::doesCapture(Piece*) const {
    return false;
}

std::string BasicMove::toAlgebraicNotation(int i) const {
     // FILL THIS
     return "";
}

std::string BasicMove::toBasicNotation() const {
     return getFileRank(from_) + getFileRank(to_);
}

bool BasicMoveWithCapture::doesCapture(Piece *p) const {
    return (p == NULL) || (p == captured_);
}

BasicMoveWithCapture::BasicMoveWithCapture(Position from, Position to, 
                                           Piece *moved, Piece *captured) :
   BasicMove(from, to, moved), captured_(captured) {
   assert(captured);
}

void BasicMoveWithCapture::perform(Board *b) const {
    BasicMove::perform(b);
    captured_->setCaptured(true);
}

void BasicMoveWithCapture::unPerform(Board *b) const {
    BasicMove::unPerform(b);
    b->setPiece(captured_->getPosition(), captured_);
    captured_->setCaptured(false);
}

