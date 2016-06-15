#include <ics46/factory/DynamicFactory.hpp>
#include "MyOthelloAI.hpp"
#include "OthelloGameState.hpp"
#include "OthelloBoard.hpp"
#include <iostream>
#include "OthelloCell.hpp"

ICS46_DYNAMIC_FACTORY_REGISTER(OthelloAI,dsthomp1::MyOthelloAI, "Dan's OthelloAI(Required)");

std::pair<int,int> dsthomp1::MyOthelloAI::chooseMove(const OthelloGameState& state)
{

    //save dimensions of the board
    const OthelloBoard& board = state.board();
    boardHeight = board.height();
    boardWidth = board.width();

    //get whose turn it is
   if(state.isWhiteTurn())
    isWhitePlayer = 1;
   else
    isWhitePlayer = 0;

    //search for a move
    int d = maxDepth;
   std::unique_ptr<OthelloGameState> gs = state.clone(); 
    search(*gs, d);
 
   return std::make_pair(bestX,bestY); //best x and y are stored in the class
}



int dsthomp1::MyOthelloAI::search(OthelloGameState& s, int depth)
{
    int max = -10000;
    int min = 10000;
    int rtrValue;
    if(depth == 0)
        return evalPosition(s);
    if(s.isGameOver())
        return evalPosition(s);
    else if((isWhitePlayer && s.isWhiteTurn()) || (!isWhitePlayer && s.isBlackTurn()))//if its ai's turn
        {
            for(int i = 0; i < boardHeight; ++i)
            {
                for(int j = 0; j < boardWidth; ++j)
                {
                    if(s.isValidMove(j,i))//check all valid moves
                    {
                       std::unique_ptr<OthelloGameState> gameSt = s.clone();
                       gameSt->makeMove(j,i);//make the move
                       rtrValue = search(*gameSt,depth - 1);
                       if(rtrValue > max)
                       {
                        max = rtrValue;
                        if(depth == maxDepth)
                        {///update bestX and bestY with the best place to move.
                        bestX = j;
                        bestY = i;
                        }
                    
                       }
                    }  
                }
            }
            return max;
        }
    else
        {
            for(int i = 0; i < boardHeight; ++i)
            {
                for(int j = 0; j < boardWidth; ++ j)
                {
                    if(s.isValidMove(j,i))//check all valid moves
                    {
                        std::unique_ptr<OthelloGameState> gameSt = s.clone();
                        gameSt->makeMove(j,i);//make the move
                        rtrValue = search(*gameSt,depth -1);
                        if(rtrValue < min)
                        {
                           min = rtrValue;
                        }
                    }
                }

            }
            return min;
        }

}



int dsthomp1::MyOthelloAI::evalPosition(OthelloGameState& state)
{
  const OthelloBoard& board = state.board();
  if(isWhitePlayer)
  {
      
    if(state.isGameOver() && (state.whiteScore() > state.blackScore()))
    return 1000;
    return getDifferenceWhite(state) + positionalAdvantage(board);
  }
  else
  {
    if(state.isGameOver() && (state.blackScore() > state.whiteScore()))
    return 1000;
    return getDifferenceBlack(state) + positionalAdvantage(board);
  }
}



int dsthomp1::MyOthelloAI::getDifferenceWhite(OthelloGameState& s)
{
   return s.whiteScore() - s.blackScore();
}



int dsthomp1::MyOthelloAI::getDifferenceBlack(OthelloGameState& s)
{
    return s.blackScore() - s.whiteScore();
}


int dsthomp1::MyOthelloAI::hasCorners(const OthelloBoard & b)
{
    int toReturn = 0;
    if(isWhitePlayer)
    {
    if(b.cellAt(0,0) == OthelloCell::white)
    toReturn += 10;
    if(b.cellAt(7,7) == OthelloCell::white)
    toReturn += 10;
    if(b.cellAt(0,7) == OthelloCell::white)
    toReturn += 10;
    if(b.cellAt(7,0) == OthelloCell::white)
    toReturn += 10;
    if(b.cellAt(0,0) == OthelloCell::black)
    toReturn -= 10;
    if(b.cellAt(7,7) == OthelloCell::black)
    toReturn -= 10;
    if(b.cellAt(0,7) == OthelloCell::black)
    toReturn -= 10;
    if(b.cellAt(7,0) == OthelloCell::black)
    toReturn -= 10;
   
    }
    else
    {
    if(b.cellAt(0,0) == OthelloCell::black)
    toReturn += 10;
    if(b.cellAt(7,7) == OthelloCell::black)
    toReturn += 10;
    if(b.cellAt(0,7) == OthelloCell::black)
    toReturn += 10;
    if(b.cellAt(7,0) == OthelloCell::black)
    toReturn += 10;
    if(b.cellAt(0,0) == OthelloCell::white)
    toReturn -= 10;
    if(b.cellAt(7,7) == OthelloCell::white)
    toReturn -= 10;
    if(b.cellAt(0,7) == OthelloCell::white)
    toReturn -= 10;
    if(b.cellAt(7,0) == OthelloCell::white)
    toReturn -= 10;
   }

    return toReturn;
}


int dsthomp1::MyOthelloAI::positionalAdvantage(const OthelloBoard & b)
{
    return hasCorners(b);
}


