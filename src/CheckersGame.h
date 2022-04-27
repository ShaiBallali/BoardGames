#pragma once
#include "Game.h"
#include "CheckersPiece.h"

const int ROW_CHECKERS = 8;
const int COL_CHECKERS = 8;
const int NUM_OF_INPUTS_FOR_CHECKERS_MOVE = 2;

class CheckersGame : public Game {
private:
	GamePiece*** board;

public:
	                          CheckersGame();
    virtual                   ~CheckersGame();
	                          CheckersGame(const CheckersGame&);
							  CheckersGame(const CheckersGame&&);
	                          void operator=(const CheckersGame& other);

	virtual  GamePiece***     getBoard() const;
	virtual void              updateBoard();
	GamePiece&                getGamePiece(const position data);
	GamePiece&                getGamePiece(const position data) const;

	void			          updateLegalAndThreatMoves(const position& from, const position& to);
	void                      didCapture(position& data, const position& from, const position& to);
	const bool                validInputToPrintLegal(const position& data) const;
	void                      lookForWinner();
	bool	                  isPlayerLoser(Player* player);

	virtual const bool		  isEmptyCell(const position& data) const;
	virtual const bool        validInputToPrintThreat(const position& data) const;
	virtual void              playMove(position* movePositions);
	virtual const bool		  isLegalMove(const position& from, const position& to);
	virtual const bool		  isBelongToCurrTurn(const position& from);
};

