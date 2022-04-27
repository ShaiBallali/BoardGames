#pragma once
#include "Game.h"
#include "ChessPawnPiece.h"
#include "ChessKingPiece.h"
#include "ChessBishopPiece.h"
#include "ChessKnightPiece.h"
#include "ChessQueenPiece.h"
#include "ChessRookPiece.h"


class ChessGame : public Game
{
private:
	GamePiece*** board;
public:
	position _kingPositionW, _kingPositionB;

public:
	                                         ChessGame();
	virtual                                  ~ChessGame();
	                                         ChessGame(const ChessGame&);
											 ChessGame(const ChessGame&&);
	void                                     operator=(const ChessGame& other);
	
	virtual void                             updateBoard();
	GamePiece&                               getGamePiece(const position data);
	 GamePiece&                              getGamePiece(const position data) const;
	void			                         updateLegalAndThreatMoves(position& capturePos, const position& from, const position& to);
	void                                     didCapture(position& data, const position& from, const position& to);
	const bool                               validInputToPrintLegal(const position& data) const;
	void                                     lookForWinner();
	bool	                                 isPlayerLoser(Player* player);
	const position&                          getKingPositionW() const;
	const position&                          getKingPositionB() const;

	virtual  GamePiece***                    getBoard() const;
	virtual void                             playMove(position* movePositions);
	virtual const bool		                 isEmptyCell(const position& data) const;
	virtual const bool                       validInputToPrintThreat(const position& data) const;
	virtual const bool		                 isLegalMove(const position& from, const position& to);
	virtual const bool		                 isBelongToCurrTurn(const position& from);
};

