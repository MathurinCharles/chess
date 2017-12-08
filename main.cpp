// This module defines the entry point for the program. It
// instanciate a Game object and then runs a simple REPL
// (read-eval-print-loop). Most commands are evaluted by calling a
// corresponding method on the Game object.

#include <iostream>
#include <fstream>
#include <sstream>
#include <cassert>
#include <map>
#include "game.h"
#include "move.h"
#include "piece.h"

bool isFinished(Game &g) {
    return g.getAllLegalMoves().size() == 0;
}

// We need to parse a line, construct a Move, and make sure
// the move is valid in the current Game.
// What we do instead is to get all the valid moves, and see
// if line is equal to the string representation of one of these moves.
Move *parseAndValidate(Game &g, const std::string &line) {
    bool algebricNot = true;
    bool same3, same2, same1 = false;
    std::string s="";
    std::vector<Move *> moves = g.getAllLegalMoves();
    if (algebricNot){
        for (auto x : moves) {
            for (auto y : moves) {
                if((x->toAlgebraicNotation(0) != y->toAlgebraicNotation(0))&&(x->toAlgebraicNotation(3) == y->toAlgebraicNotation(3))){
                    same3 = true;
                }
            }
            if (same3){
                for (auto y : moves) {
                    if((x->toAlgebraicNotation(0) != y->toAlgebraicNotation(0))&& (x->toAlgebraicNotation(2) == y->toAlgebraicNotation(2))){
                        same2 = true;
                    }
                }
                if (same2){
                    for (auto y : moves) {
                        if((x->toAlgebraicNotation(0) != y->toAlgebraicNotation(0))&& (x->toAlgebraicNotation(1) == y->toAlgebraicNotation(1))){
                            same1 = true;
                        }
                    }
                    if (same1){
                        s = x->toAlgebraicNotation(0);
                        if (line == s) return x;
                    } else {
                        s = x->toAlgebraicNotation(1);
                        if (line == s) return x;
                        s = x->toAlgebraicNotation(0);
                        if (line == s) return x;

                    }
                } else {
                    s = x->toAlgebraicNotation(2);
                    if (line == s) return x;
                    s = x->toAlgebraicNotation(1);
                    if (line == s) return x;
                    s = x->toAlgebraicNotation(0);
                    if (line == s) return x;
                }
            } else {
                s = x->toAlgebraicNotation(3);
                if (line == s) return x;
                s = x->toAlgebraicNotation(2);
                if (line == s) return x;
                s = x->toAlgebraicNotation(1);
                if (line == s) return x;
                s = x->toAlgebraicNotation(0);
                if (line == s) return x;
            }
        }
    }
    for (auto x : moves) {
        std::string s = x->toBasicNotation();
        if (line == s) return x;
    }
    return NULL;
}

// Transforms a string s into a vector of words (substrings not containing
// spaces)
void tokenize(const std::string &s, std::vector<std::string> &tokens) {
    std::istringstream f(s);
    std::string word;
    while (f >> word) {
        tokens.push_back(word);
    }
}

// Asks the computer what next move to play.
void computerPlay(Game &g, int strength) {
    if (isFinished(g)) {
       std::cout << "Nothing to play !" << std::endl;
       return;
    }
    Move *m = g.computerSuggestion(strength,true);
    // should not be null as there is always something to play if the game is not
    // finished
    assert(m != NULL);
    g.play(m);
    std::cout << "Computer played " << m->toBasicNotation() << std::endl;
    g.display();
}

void evaluateCommand(Game &g, const std::string &line) {
        std::vector<std::string> commands;
        tokenize(line, commands);
        if (commands.size() == 0) {
            return;
        }
        std::string &command = commands[0];
        if (command == "d") {
            g.display();
        } else if (command == "dc") {
            g.displayCaptured();
        } else if (command == "?") {
            std::vector<Move *> moves = g.getAllLegalMoves();
            for (auto x : moves) {
                std::cout << x->toBasicNotation() << " ";
            }
            std::cout << std::endl;
        } else if (command == "help" || command == "h") {
            std::cout << "*move*: play *move* (type '?' for list of possible moves)" << std::endl;
            std::cout << "play s, p s, p: computer plays next move, s = strength" << std::endl;
            std::cout << "display, d: display current state of the game" << std::endl;
            std::cout << "dc: display the list of pieces captured by both players" << std::endl;
            std::cout << "undo, u: cancel last move" << std::endl;
            std::cout << "?: print all possible moves" << std::endl;
            std::cout << "quit, q: quit game" << std::endl;
            std::cout << "help, h: this message" << std::endl;
        } else if (command == "quit" || command == "q") {
            std::cout << "bye bye" << std::endl;
            exit(0);
        } else if (command == "undo" || command == "u") {
            std::cout << "undo last move" << std::endl;
            g.undo();
        } else if (command == "play" || command == "p") {
            computerPlay(g, 1);
            return;
        } else if (command == "heuristic" || command == "heu") {
            g.displayHeuristic();
        } else {
            Move *m = parseAndValidate(g, line);
            if (m == NULL) {
               std::cout << "I didn't understand your move, try '?' for list of moves or 'help'" << std::endl;
            } else {
               g.play(m);
               std::cout << m->toBasicNotation() << std::endl;
               g.display();
            }
        }
    }

int main() {
    Game g;
    g.importLibrary("lib1");
    g.importLibrary("lib2");
    g.importLibraryPgn("openingtest.pgn");
    // g.importLibraryPgn("openings.pgn");
    std::string line;
    while(true) {
        std::cout << "> ";
        getline(std::cin, line);
        evaluateCommand(g, line);
    }
    return 0;
}
