#pragma once
#include "ChessPiece.h"
class ChessRookPiece : public ChessPiece
{
public:
	ChessRookPiece(position data, char player);
	void			operator=(const ChessRookPiece& other);
	ChessRookPiece(const ChessRookPiece& other);
	virtual void    setLegalMoves(GamePiece*** board);
};

