#pragma once

#include "Game.h"
#include "AmazonsPiece.h"
#include "generic.h"

const int ROW_AMAZONS = 10;
const int COL_AMAZONS = 10;
const int NUM_OF_INPUTS_FOR_AMAZONS_MOVE = 3;

class  AmazonsGame : public Game
{
private:
	GamePiece*** board;
  
public:
	                       AmazonsGame(); 
    virtual                ~AmazonsGame();
	                       AmazonsGame(const AmazonsGame&);
	                       AmazonsGame(const AmazonsGame&&);

	void                   operator=(const AmazonsGame& other);

	virtual  GamePiece***  getBoard() const;
	virtual void           updateBoard();
	GamePiece&             getGamePiece(const position data);
	GamePiece&             getGamePiece(const position data) const;
	void			       updateLegalMoves(const position& from, const position& to);
	void                   lookForWinner();
	bool	               isPlayerLoser(Player* player);
	void                   freeBoard();

	virtual const bool     isLegalMove(const position& from, const position& to);
	virtual const bool	   isBelongToCurrTurn(const position& from);
	virtual void		   playMove (position* movePositions);
	virtual const bool	   isEmptyCell(const position& data) const;
	virtual const bool     validInputToPrintThreat(const position& data) const;
	virtual const bool     validInputToPrintLegal(const position& data) const;

};



