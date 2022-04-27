#include "ChessKingPiece.h"

ChessKingPiece::ChessKingPiece(position data, char player) : ChessPiece(data, player) {}; // Ctor

void ChessKingPiece::operator=(const ChessKingPiece& other) {
	if (this != &other) //Making sure no self copy is done
	{
		ChessPiece::operator=(other); // Copy father
	}
}

ChessKingPiece::ChessKingPiece(const ChessKingPiece& other) // Copy ctor
{
	*this = other;
}

void ChessKingPiece::setLegalMoves(GamePiece*** board) {

	position move, saver;

	saver = data;

	for (int i = -1; i <= 1; i++)
		for (int j = -1; j <= 1; j++)
		{
			if (i != 0 || j != 0)
			{
				move.x = saver.x + i; // Creating a "dummy" move
				move.y = saver.y + j;
				board[saver.x - 1][saver.y - 1] = nullptr;

				if (inRange(move) && (board[move.x - 1][move.y - 1] == nullptr || !isSamePlayer(move, board))) { //Nullptr for empty cell, Is not same player for eating.
					data = move;

					setThreatMoves(board);

					if (_threatMoves.isEmpty()) // Making sure the move is not threatening the king
					{
						add<PositionList*, position, positionNode, positionNode*>(&_legalMoves, move, nullptr);
					}

					_threatMoves.free();
				}
			}
		}
	data = saver;
	board[data.x - 1][data.y - 1] = this; // Moving King to old position
}