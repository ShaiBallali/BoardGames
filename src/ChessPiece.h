#pragma once
#include "GamePiece.h"
//#include "ChessGame.h"

const int ROW_CHESS = 8;
const int COL_CHESS = 8;
const int NUM_OF_INPUTS_FOR_CHESS_MOVE = 2;

class ChessPiece : public GamePiece
{
protected:
	PositionList _threatMoves;
	PositionList _legalMoves;


public:
	ChessPiece(position data, char player);
	ChessPiece() = default;
	ChessPiece(const ChessPiece& other);
	void operator=(const ChessPiece& other);

	bool isSamePlayer(position other, GamePiece*** board);

	virtual void setLegalMoves(GamePiece*** board) = 0;
	virtual const PositionList& getLegalMoves() const;
	virtual PositionList& getLegalMoves();
	virtual void  printLegalMoves() const;

	virtual void setThreatMoves(GamePiece*** board);
	virtual const PositionList& getThreatMoves() const;
	virtual PositionList& getThreatMoves();
	virtual const char getColor() const;
	void  printThreatMoves() const;

	bool inRange(position move);
	void findKingPosition(GamePiece*** board, position* kingPos, char king);

	bool isKingThreatened(position kingPos, position currPos, position move, GamePiece*** board, ChessPiece* This);

};

