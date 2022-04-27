#pragma once
#include "ChessPiece.h"

class ChessBishopPiece : public ChessPiece
{
public:
	                 ChessBishopPiece(position data, char player);
					 ChessBishopPiece(const ChessBishopPiece& other);

	void	         operator=(const ChessBishopPiece& other);

	virtual void	 setLegalMoves(GamePiece*** board);
};