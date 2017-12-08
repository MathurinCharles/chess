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

KingCastling::KingCastling(Color color) : color_(color) {}

void KingCastling::perform(Board *b) const {
    if (color_ == WHITE){
      Piece *K;
      Piece *R;
      b->getPiece({0,4}, &K);
      b->setPiece({0,6},K);
      K->setPosition({0,6});
      b->removePiece({0,4});
      b->getPiece({0,7}, &R);
      b->setPiece({0,5}, R);
      R->setPosition({0,5});
      b->removePiece({0,7});
    } else {
      Piece *K;
      Piece *R;
      b->getPiece({7,4}, &K);
      b->setPiece({7,6},K);
      K->setPosition({7,6});
      b->removePiece({7,4});
      b->getPiece({7,7}, &R);
      b->setPiece({7,5}, R);
      R->setPosition({7,5});
      b->removePiece({7,7});
    }
}

void KingCastling::unPerform(Board *b) const {
    if (color_ == WHITE){
      Piece *K;
      Piece *R;
      b->getPiece({0,6}, &K);
      b->setPiece({0,4},K);
      K->setPosition({0,4});
      b->removePiece({0,6});
      b->getPiece({0,5}, &R);
      b->setPiece({0,7}, R);
      R->setPosition({0,7});
      b->removePiece({0,5});
    } else {
      Piece *K;
      Piece *R;
      b->getPiece({7,6}, &K);
      b->setPiece({7,4},K);
      K->setPosition({7,4});
      b->removePiece({7,6});
      b->getPiece({7,5}, &R);
      b->setPiece({7,7}, R);
      R->setPosition({7,7});
      b->removePiece({7,5});
    }
}

bool KingCastling::doesCapture(Piece*) const {
    return false;
}

std::string KingCastling::toAlgebraicNotation(int i) const {
    return "0-0";
}

std::string KingCastling::toBasicNotation() const {
     return "0-0";
}

QueenCastling::QueenCastling(Color color) : color_(color) {}

void QueenCastling::perform(Board *b) const {
    if (color_ == WHITE){
      Piece *K;
      Piece *R;
      b->getPiece({0,4}, &K);
      b->setPiece({0,2},K);
      K->setPosition({0,2});
      b->removePiece({0,4});
      b->getPiece({0,0}, &R);
      b->setPiece({0,3}, R);
      K->setPosition({0,3});
      b->removePiece({0,0});
    } else {
      Piece *K;
      Piece *R;
      b->getPiece({7,4}, &K);
      b->setPiece({7,2},K);
      K->setPosition({7,2});
      b->removePiece({7,4});
      b->getPiece({7,0}, &R);
      b->setPiece({7,3}, R);
      R->setPosition({7,3});
      b->removePiece({7,0});
    }
}

void QueenCastling::unPerform(Board *b) const {
    if (color_ == WHITE){
      Piece *K;
      Piece *R;
      b->getPiece({0,2}, &K);
      b->setPiece({0,4},K);
      K->setPosition({0,4});
      b->removePiece({0,2});
      b->getPiece({0,3}, &R);
      b->setPiece({0,0}, R);
      R->setPosition({0,0});
      b->removePiece({0,3});
    } else {
      Piece *K;
      Piece *R;
      b->getPiece({7,2}, &K);
      b->setPiece({7,4},K);
      K->setPosition({7,4});
      b->removePiece({7,2});
      b->getPiece({7,3}, &R);
      b->setPiece({7,0}, R);
      R->setPosition({7,0});
      b->removePiece({7,3});
    }
}

bool QueenCastling::doesCapture(Piece*) const {
    return false;
}

std::string QueenCastling::toAlgebraicNotation(int i) const {
    return "0-0-0";
}

std::string QueenCastling::toBasicNotation() const {
     return "0-0-0";
}


std::string BasicMove::toAlgebraicNotation(int i) const {
    std::string notation = "";
    Piece *currentPiece = this->moved_;
    notation += currentPiece->notation();
    if (i==0) notation += getFileRank(from_);
    if (i==1) notation += getRank(from_);
    if (i==2) notation += getFileLetter(from_);
    if (doesCapture(NULL)) notation += "x";
    notation += getFileRank(to_);
    return notation;
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


 //////////////////////////////////////////////////////////////////////////////////
BasicPromotion::BasicPromotion(Position from, Position to, Piece *moved, Piece *npiece) : from_(from),
                     to_(to), moved_(moved), npiece_(npiece) {
   assert(moved);
}
//Nouveau constructeur à partir de par exemple "a4a5"

void BasicPromotion::perform(Board *b) const {
    //////
    b->setPiece(to_, moved_);
    moved_->setPosition(to_);
    b->removePiece(from_);
}

void BasicPromotion::unPerform(Board *b) const {
    b->setPiece(from_, moved_);
    moved_->setPosition(from_);
    b->removePiece(to_);
}

bool BasicPromotion::doesCapture(Piece*) const {
    return false;
}

std::string BasicPromotion::toAlgebraicNotation(int i) const {
    std::string notation = "";
    Piece *currentPiece = this->moved_;
    notation += currentPiece->notation();
    if (i==0) notation += getFileRank(from_);
    if (i==1) notation += getRank(from_);
    if (i==2) notation += getFileLetter(from_);
    if (doesCapture(NULL)) notation += "x";
    notation += getFileRank(to_);
    return notation;
}

std::string BasicPromotion::toBasicNotation() const {
     return getFileRank(from_) + getFileRank(to_);
}

bool BasicPromotionWithCapture::doesCapture(Piece *p) const {
    return (p == NULL) || (p == captured_);
}

BasicPromotionWithCapture::BasicPromotionWithCapture(Position from, Position to,
                                           Piece *moved, Piece *npiece, Piece *captured) :
   BasicPromotion(from, to, moved, npiece), captured_(captured) {
   assert(captured);
}

void BasicPromotionWithCapture::perform(Board *b) const {
    BasicPromotion::perform(b);
    captured_->setCaptured(true);
}

void BasicPromotionWithCapture::unPerform(Board *b) const {
    BasicPromotion::unPerform(b);
    b->setPiece(captured_->getPosition(), captured_);
    captured_->setCaptured(false);
}
