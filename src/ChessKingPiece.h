#pragma once
#include "ChessPiece.h"
class ChessKingPiece : public ChessPiece
{
public:
	                      ChessKingPiece(position data, char player);
	                      ChessKingPiece(const ChessKingPiece& other);

	void	              operator=(const ChessKingPiece& other);

	virtual void          setLegalMoves(GamePiece*** board);
};

