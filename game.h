#ifndef GAME_H_
#define GAME_H_

#include <vector>
#include <stack>
#include "piece.h"
#include "move.h"
#include "board.h"
#include "movetree.h"

// This class defines a game as seen by the 'main' module. It has the following
// roles:
// 1. It is a wrapper to a Board object
// 2. It maintains the history of the game
// 3. It implements a computer opponent

class Game {
public:
    Game();

    void display();

    void displayHeuristic();

    void displayCaptured();

    bool undo();
//
    void importLibrary(std::string filename);
//
    std::vector<Move *> getAllLegalMoves();

    Move *computerSuggestion(int strength, bool uselib);

    void play(Move *);

private:

    Board board_;
    std::stack<Move *> plays_;
//
    std::stack<Tree > libPlays_;
    unsigned int lenPlays_, lenLibPlays_ = 0;
    Tree openingLibrary;
    bool haveOpeningLibrary;
//
};

#endif // GAME_H_
