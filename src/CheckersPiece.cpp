#include "CheckersPiece.h"

const int LEFT = -1;
const int RIGHT = 1;


CheckersPiece::CheckersPiece(position data, char player, bool isKing) : GamePiece(data, player), _isKing(isKing) {}; // Ctor

CheckersPiece::CheckersPiece(const CheckersPiece& other) { // Copy ctor
	*this = other;
}

void CheckersPiece::operator=(const CheckersPiece& other) {
	if (this != &other) // Checking for self assigning
	{
		GamePiece::operator=(other); // Father copy
		_legalMoves = other.getLegalMoves(); // "Operator =" for lists
		_threatMoves = other.getThreatMoves();
		_isKing = other.getIsKing(); // Shallow copy
	}
}

void CheckersPiece::setLegalMoves(GamePiece*** board) {
	int direction;
	if (player == 'X')
		direction = 1;
	else
		direction = -1;

	_legalMoves.makeEmpty();

	if (_isKing == false)
		legalPawnMoves(board, direction);
	else
		legalKingMoves(board);
}

void CheckersPiece::setIsKing(bool isKing) {
	_isKing = isKing;
}

void CheckersPiece::legalPawnMoves(GamePiece*** board, int direction) {

	position move;
	int leftOrRight = LEFT;

	for (int i = 0; i < 2; i++, leftOrRight = RIGHT) // Checking for each side
	{
		move.x = data.x + direction; // Per color
		move.y = data.y + leftOrRight; // Per side

		if (inRange(move))
		{
			if (board[move.x - 1][move.y - 1] == nullptr) // No capture
				add<PositionList*, position, positionNode, positionNode*>(&_legalMoves, move, nullptr);

			else
			{
				if (board[move.x - 1][move.y - 1]->getPlayer() != this->getPlayer())  // Capture
				{
					move.x = move.x + direction;
					move.y = move.y + leftOrRight;

					if (inRange(move) && board[move.x - 1][move.y - 1] == nullptr)
					{
						add<PositionList*, position, positionNode, positionNode*>(&_legalMoves, move, nullptr);
					}
				}
			}
		}
	}
}

void CheckersPiece::legalKingMoves(GamePiece*** board) {
	int direction, leftOrRight;
	direction = 1;
	leftOrRight = RIGHT;
	position move;

	for (int i = 0; i < 4; i++) // Can move in 4 diagonal directions
	{
		move.x = data.x + direction;
		move.y = data.y + leftOrRight;

		while ((inRange(move)) && board[move.x - 1][move.y - 1] == nullptr) // No capture
		{
			add<PositionList*, position, positionNode, positionNode*>(&_legalMoves, move, nullptr);
			move.x = move.x + direction;
			move.y = move.y + leftOrRight;
		}
		if (inRange(move) && board[move.x - 1][move.y - 1]->getPlayer() != this->getPlayer()) // Capture
		{
			move.x = move.x + direction;
			move.y = move.y + leftOrRight;
			if (inRange(move) && board[move.x - 1][move.y - 1] == nullptr)
				add<PositionList*, position, positionNode, positionNode*>(&_legalMoves, move, nullptr);
		}

		if (leftOrRight == RIGHT)
			leftOrRight = LEFT;
		else
		{
			direction = -1;
			leftOrRight = RIGHT;
		}
	}
}

void CheckersPiece::setThreatMoves(GamePiece*** board)
{
	_threatMoves.makeEmpty();

	pawnThreats(board);
	kingsThreats(board);
}

void CheckersPiece::pawnThreats(GamePiece*** board)
{
	int direction, leftOrRight;

	if (player == 'X')
		direction = 1;
	else
		direction = -1;

	leftOrRight = RIGHT;

	for (int i = 0; i < 2; i++, leftOrRight = LEFT)
	{
		position move;

		move.x = data.x + -1 * direction;
		move.y = data.y + leftOrRight;

		if (inRange(move) && board[move.x - 1][move.y - 1] == nullptr)
		{
			move.x = data.x + direction;
			move.y = data.y + -1 * leftOrRight;

			if (inRange(move) && board[move.x - 1][move.y - 1] != nullptr && board[move.x - 1][move.y - 1]->getPlayer() != this->getPlayer())
				add<PositionList*, position, positionNode, positionNode*>(&_threatMoves, move, nullptr);
		}
	}
}

void CheckersPiece::kingsThreats(GamePiece*** board)
{
	int direction = 1, leftOrRight = RIGHT;
	position move;

	for (int i = 0; i < 4; i++)
	{
		move.x = data.x + -1 * direction;
		move.y = data.y + leftOrRight;

		if (inRange(move) && board[move.x - 1][move.y - 1] == nullptr)
		{
			move.x = data.x + direction;
			move.y = data.y + -1 * leftOrRight;
			while (inRange(move) && board[move.x - 1][move.y - 1] == nullptr)
			{
				move.x = move.x + direction;
				move.y = move.y + -1 * leftOrRight;
			}
			if (inRange(move))
			{
				CheckersPiece* t = dynamic_cast <CheckersPiece*>(board[move.x - 1][move.x - 1]);
				if (t != nullptr)
					if (inRange(move) && t->getPlayer() != this->getPlayer() && t->getIsKing() == true)
						add<PositionList*, position, positionNode, positionNode*>(&_threatMoves, move, nullptr);
			}
		}
		if (leftOrRight == RIGHT)
			leftOrRight = LEFT;
		else
		{
			direction = -1;
			leftOrRight = RIGHT;
		}
	}
}

const bool CheckersPiece::getIsKing() const {
	return _isKing;
}



bool CheckersPiece::inRange(position move)
{
	if (move.x > 0 && move.x <= 8 && move.y > 0 && move.y <= 8)
		return true;
	return false;
}

void CheckersPiece::printLegalMoves() const
{
	_legalMoves.print();
}

void CheckersPiece::printThreatMoves() const {
	_threatMoves.print();
}

const PositionList& CheckersPiece::getLegalMoves() const
{
	return _legalMoves;
}

PositionList& CheckersPiece::getLegalMoves()
{
	return _legalMoves;
}

const PositionList& CheckersPiece::getThreatMoves() const
{
	return _threatMoves;
}

PositionList& CheckersPiece::getThreatMoves()
{
	return _threatMoves;
}

const char CheckersPiece::getColor() const {
	return player;
}