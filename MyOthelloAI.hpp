#ifndef MYOTHELLOAI_HPP
#define MYOTHELLOAI_HPP

#include "OthelloAI.hpp"

namespace dsthomp1
{


    class MyOthelloAI:public OthelloAI
    {
        public:
            std::pair<int, int> chooseMove(const OthelloGameState& state);
            int search(OthelloGameState& s, int depth); //searches for the best move
            int evalPosition(OthelloGameState& state); //evaluates the games position
            int getDifferenceWhite(OthelloGameState &s);  //returns white tiles - black ones
            int getDifferenceBlack(OthelloGameState &s); //returns black tiles - white tiles
            int positionalAdvantage(const OthelloBoard & b); //returns positional advantage
            int hasCorners(const OthelloBoard & b);//returns an int based on the number of corners owned
            int hasSides(const OthelloBoard & b); //retunrs an int based on the number of vital edge tiles
        private:
            int maxDepth = 4;
            int isWhitePlayer;
            int boardHeight;
            int boardWidth;
            int bestX = 0;  //holds value for best move x  position
            int bestY = 0;  //holds vlaue for best move y  position
    };




}

#endif
