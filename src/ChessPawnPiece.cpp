#include "ChessPawnPiece.h"

ChessPawnPiece::ChessPawnPiece(position data, char player) : ChessPiece(data, player) {};

void ChessPawnPiece::operator=(const ChessPawnPiece& other) {
	if (this != &other)
	{
		ChessPiece::operator=(other);
	}
}

ChessPawnPiece::ChessPawnPiece(const ChessPawnPiece& other)
{
	*this = other;
}

void ChessPawnPiece::setLegalMoves(GamePiece*** board) {
	int direction, start;
	bool validDirection = false;
	position move, kingPosition;

	findKingPosition(board, &kingPosition, player <= 'Z' ? 'K' : 'k');  // Checking where the king is

	if (player < 'Z')
	{
		direction = 1;  // direction of Pawn traffic 
		start = 2;
	}
	else
	{
		direction = -1;
		start = 7;
	}

	move.x = data.x + direction;
	move.y = data.y;

	if (inRange(move) && board[move.x - 1][move.y - 1] == nullptr)          // in range && empty place
	{

		if (!isKingThreatened(kingPosition, data, move, board, this))       // if king not Threatened because this move
		{
			add<PositionList*, position, positionNode, positionNode*>(&_legalMoves, move, nullptr);
			validDirection = true;
		}

		if (validDirection && data.x == start) {                          // firstMove, Pawn can forward 2 steps
			move.x = move.x + direction;
			move.y = move.y;
			if (inRange(move) && board[move.x - 1][move.y - 1] == nullptr)
				add<PositionList*, position, positionNode, positionNode*>(&_legalMoves, move, nullptr);
		}
	}

	int leftOrRight = -1;                                                  
	for (int i = 0; i < 2; i++, leftOrRight = 1)                       // check if pawn can eat someone else
	{
		move.x = data.x + direction;
		move.y = data.y + leftOrRight;

		if (inRange(move) && board[move.x - 1][move.y - 1] != nullptr && !isSamePlayer(move, board))
		{
			if (!(isKingThreatened(kingPosition, data, move, board, this)))
			{
				add<PositionList*, position, positionNode, positionNode*>(&_legalMoves, move, nullptr);
				validDirection = true;
			}
		}
	}
}