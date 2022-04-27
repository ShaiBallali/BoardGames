#include "CheckersGame.h"


#include "CheckersGame.h"


CheckersGame::CheckersGame() : Game(ROW_CHECKERS, COL_CHECKERS, NUM_OF_INPUTS_FOR_CHECKERS_MOVE) { // Ctor, getting row, col and num of inputs (2 for checkers)
	board = new GamePiece * *[ROW_CHECKERS];
	for (int i = 0; i < ROW_CHECKERS; i++)
	{
		board[i] = new GamePiece * [COL_CHECKERS]; // Polymorphism
	}

	for (int i = 0; i < ROW_CHECKERS; i++)
		for (int j = 0; j < COL_CHECKERS; j++)
		{
			position data;
			data.x = i + 1;
			data.y = j + 1;

			if (((i + 1) + (j + 1)) % 2 == 1 && (i < 3 || i > 4))
				board[i][j] = new CheckersPiece(data, i < 3 ? 'X' : 'O', false); // Upper pieces are O, bottom are X
			else
				board[i][j] = nullptr;
		}

	_playerX.setNumOfPieces(12);
	_playerO.setNumOfPieces(12);

	updateBoard();
}

CheckersGame::~CheckersGame() { // Dtor
	int i, j;
	for (i = 0; i < ROW_CHECKERS; i++)
		for (j = 0; j < COL_CHECKERS; j++) // Freeing each cell (GamePiece*)
		{
			delete(board[i][j]);
		}
	for (int i = 0; i < COL_CHECKERS; i++)
	{
		delete[](board[i]); // Freeing each col
	}
	delete[](board); // Freeing entire board
}


void CheckersGame::updateBoard()
{
	int i, j;
	for (i = 0; i < ROW_CHECKERS; i++)
		for (j = 0; j < COL_CHECKERS; j++)
		{
			if (board[i][j] != nullptr)
			{
				board[i][j]->setLegalMoves(board);
				board[i][j]->setThreatMoves(board);
			}
		}

	_playerX.initPieces(board, ROW_CHECKERS);
	_playerO.initPieces(board, ROW_CHECKERS);
}

GamePiece& CheckersGame::getGamePiece(const position data)
{
	return *(board[data.x - 1][data.y - 1]);
}

GamePiece& CheckersGame::getGamePiece(const position data) const
{
	return *(board[data.x - 1][data.y - 1]);
}

void CheckersGame::operator=(const CheckersGame& other)
{
	if (this != &other) // Checking for self assigning
	{
		Game::operator=(other); // Father copy
		position data;
		for (int i = 0; i < ROW_CHECKERS; i++)
		{
			for (int j = 0; j < COL_CHECKERS; j++)
			{
				if (board[i][j] != nullptr) // Copying non-empty cells
				{
					data.x = i;
					data.y = j;

					board[i][j] = &(other.getGamePiece(data));
				}
			}
		}
	}
}
CheckersGame::CheckersGame(const CheckersGame& other) // Copy ctor
{
	*this = other;
}

CheckersGame::CheckersGame(const CheckersGame&& other) // Move ctor
{
	position data;

	for (int i = 0; i < ROW_CHECKERS; i++)
		for (int j = 0; j < COL_CHECKERS; j++)
		{
			data.x = i + 1;
			data.y = j + 1;

			board[i][j] = &(other.getGamePiece(data)); // Copying address

			other.getBoard()[i][j] = nullptr; // Old cells will point to null

			int i;
			for (i = 0; i < ROW_CHECKERS; i++) // Free old board
			{
				delete[](board[i]);
			}
			delete[](board);
		}
}

const bool CheckersGame::isEmptyCell(const position& data) const
{
	if (board[data.x - 1][data.y - 1] == nullptr)
		return true;
	return false;
}

GamePiece*** CheckersGame::getBoard() const {
	return board;
}

void CheckersGame::playMove(position* movePositions)
{
	position from, to;

	from = movePositions[0];

	to = movePositions[1];

	board[to.x - 1][to.y - 1] = board[from.x - 1][from.y - 1]; // Moving the piece (old position's piece moves to the new position)
	board[from.x - 1][from.y - 1] = nullptr; // Old position is now empty
	board[to.x - 1][to.y - 1]->setPos(to);

	if (_currTurn == 'X') {
		_playerX.getPieces().updateNodePos(from, to); // Updating piece list
	}
	else {
		_playerO.getPieces().updateNodePos(from, to);
	}

	if (to.x == 1 || to.x == 8)
	{
		CheckersPiece* t = dynamic_cast <CheckersPiece*>(board[to.x - 1][to.y - 1]); // Checking if a pawn got to last line (then make him a king)
		if (t != nullptr)
		{
			t->setIsKing(true);
		}
	}

	updateLegalAndThreatMoves(from, to);

	lookForWinner();

	setCurrTurn();
}

const bool CheckersGame::isBelongToCurrTurn(const position& from)
{
	return !isEmptyCell(from) && board[from.x - 1][from.y - 1]->getPlayer() == _currTurn;
}

const bool CheckersGame::isLegalMove(const position& from, const position& to)
{
	return  board[from.x - 1][from.y - 1]->getLegalMoves().isPosFound(to);
}

void CheckersGame::updateLegalAndThreatMoves(const position& from, const position& to)
{
	int i, j;
	Player* currEnemy;
	position data;
	data.x = 0;
	data.y = 0;
	if (_currTurn == 'X') {
		currEnemy = &_playerO;
	}
	else {
		currEnemy = &_playerX;
	}
	didCapture(data, from, to);

	if (data.x != 0) // If there is a capture
	{
		delete board[data.x - 1][data.y - 1];
		board[data.x - 1][data.y - 1] = nullptr;

		currEnemy->setNumOfPieces(currEnemy->getNumOfPieces() - 1); //Updating num of pieces
		currEnemy->getPieces().deleteNode(data); //Removing captured piece
	}

	for (i = 0; i < ROW_CHECKERS; i++)
		for (j = 0; j < COL_CHECKERS; j++)
		{
			if (board[i][j] != nullptr)
			{
				board[i][j]->getLegalMoves().free();
				board[i][j]->setLegalMoves(board);

				board[i][j]->getThreatMoves().free();
				board[i][j]->setThreatMoves(board);
			}
		}
}

void CheckersGame::didCapture(position& data, const position& from, const position& to) {
	position potentialCaptured;

	potentialCaptured.x = to.x + (from.x < to.x ? -1 : 1);
	potentialCaptured.y = to.y + (from.y < to.y ? -1 : 1);

	if (board[potentialCaptured.x - 1][potentialCaptured.y - 1] != nullptr)
	{
		data = potentialCaptured;
	}
}

bool CheckersGame::isPlayerLoser(Player* player) {
	bool isLoser = true;

	PositionList pieces = player->getPieces();
	if (player->getNumOfPieces() != 0) // If there are some piecs left
	{
		positionNode* curr = pieces.getHead();
		while (curr != nullptr && isLoser) {
			if (!(board[curr->data.x - 1][curr->data.y - 1]->getLegalMoves().isEmpty())) // If there are no legal moves left
				isLoser = false;
			curr = curr->next;
		}
	}
	return isLoser;
}

void CheckersGame::lookForWinner()
{
	Player* potentialLoser;

	if (_currTurn == 'X')
		potentialLoser = &_playerO;
	else
		potentialLoser = &_playerX;

	if (isPlayerLoser(potentialLoser))
	{
		setIsGameOver(true);
		setWinner(_currTurn);
		potentialLoser->setIsLoser(true);
	}
}

const bool  CheckersGame::validInputToPrintThreat(const position& data) const {
	if (!isEmptyCell(data))
		return true;
	return false;
}

const bool CheckersGame::validInputToPrintLegal(const position& data) const {
	return validInputToPrintThreat(data);
}