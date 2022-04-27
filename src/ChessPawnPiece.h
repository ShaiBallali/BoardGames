#pragma once
#include "ChessPiece.h"
class ChessPawnPiece : public ChessPiece
{
public:
	                  ChessPawnPiece(position data, char player);
					  ChessPawnPiece(const ChessPawnPiece& other);

	void	          operator=(const ChessPawnPiece& other);

	virtual void      setLegalMoves(GamePiece*** board);
};

