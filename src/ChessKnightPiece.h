#pragma once
#include "ChessPiece.h"
class ChessKnightPiece : public ChessPiece
{
public:
	                  ChessKnightPiece(position data, char player);
	                  ChessKnightPiece(const ChessKnightPiece& other);

	void	          operator=(const ChessKnightPiece& other);

	virtual void      setLegalMoves(GamePiece*** board);
};

