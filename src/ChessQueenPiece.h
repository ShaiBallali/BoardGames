#pragma once
#include "ChessPiece.h"
class ChessQueenPiece : public ChessPiece
{
public:
	ChessQueenPiece(position data, char player);
	void			operator=(const ChessQueenPiece& other);
	ChessQueenPiece(const ChessQueenPiece& other);

	virtual void    setLegalMoves(GamePiece*** board);
};

