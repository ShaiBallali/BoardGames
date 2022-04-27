#include "ChessGame.h"

ChessGame::ChessGame() : Game(ROW_CHESS, COL_CHESS, NUM_OF_INPUTS_FOR_CHESS_MOVE) { //Ctor, getting Col, Row, num of inputs (2 in this case)
	board = new GamePiece * *[ROW_CHESS];
	for (int i = 0; i < ROW_CHESS; i++)
	{
		board[i] = new GamePiece * [COL_CHESS];
	}

	for (int i = 0; i < ROW_CHESS; i++)
		for (int j = 0; j < COL_CHESS; j++)
		{
			position data;
			data.x = i + 1;
			data.y = j + 1;

			if (i == 1 || i == 6)
			{
				board[i][j] = new ChessPawnPiece(data, i == 6 ? 'p' : 'P'); //Initializing pawns
			}
			else if ((i == 0 || i == 7))
			{
				if (j == 0 || j == 7)
					board[i][j] = new ChessRookPiece(data, i == 7 ? 'r' : 'R'); // Initializing pieces
				else if (j == 1 || j == 6)
					board[i][j] = new ChessKnightPiece(data, i == 7 ? 'n' : 'N');
				else if (j == 2 || j == 5)
					board[i][j] = new ChessBishopPiece(data, i == 7 ? 'b' : 'B');
				else if (j == 3)
					board[i][j] = new ChessQueenPiece(data, i == 7 ? 'q' : 'Q');
				else if (j == 4)
					board[i][j] = new  ChessKingPiece(data, i == 7 ? 'k' : 'K');
			}
			else
			{
				board[i][j] = nullptr;
			}
		}

	_playerX.setNumOfPieces(16);
	_playerO.setNumOfPieces(16);

	_kingPositionW.x = 8; // Initializing king position in a special field (we need to know where the king is every move)
	_kingPositionW.y = 5;
	_kingPositionB.x = 1;
	_kingPositionB.y = 5;

	updateBoard();
}

ChessGame::~ChessGame() { // Freeing each cell, then cols then entire board
	int i, j;

	for (i = 0; i < 10; i++)
		for (j = 0; j < 10; j++)
		{
			delete(board[i][j]);
		}
	for (int i = 0; i < 10; i++)
	{
		delete[](board[i]);
	}
	delete[](board);
}

void ChessGame::updateBoard()
{
	int i, j;
	for (i = 0; i < ROW_CHESS; i++)
		for (j = 0; j < COL_CHESS; j++)
		{
			if (board[i][j] != nullptr)
				board[i][j]->setLegalMoves(board);
		}

	for (i = 0; i < ROW_CHESS; i++)
		for (j = 0; j < COL_CHESS; j++)
		{
			if (board[i][j] != nullptr)
				board[i][j]->setThreatMoves(board);
		}

	_playerX.initPieces(board, ROW_CHESS);
	_playerO.initPieces(board, ROW_CHESS);
}

GamePiece& ChessGame::getGamePiece(const position data)
{
	return *(board[data.x - 1][data.y - 1]);
}

GamePiece& ChessGame::getGamePiece(const position data) const
{
	return *(board[data.x - 1][data.y - 1]);
}

void ChessGame::operator=(const ChessGame& other)
{
	if (this != &other)
	{
		_kingPositionW = other.getKingPositionW();
		_kingPositionB = other.getKingPositionB();
		position data;
		for (int i = 0; i < ROW_CHESS; i++)
		{
			for (int j = 0; j < COL_CHESS; j++)
			{
				if (board[i][j] != nullptr)
				{
					data.x = i;
					data.y = j;

					board[i][j] = &other.getGamePiece(data);
				}
			}
		}
	}
}

ChessGame::ChessGame(const ChessGame& other)
{
	*this = other;
}

ChessGame::ChessGame(const ChessGame&& other)
{
	_kingPositionW = other.getKingPositionW();
	_kingPositionB = other.getKingPositionB(); // Shallow copy for "position" type

	position data;

	for (int i = 0; i < ROW_CHESS; i++)
		for (int j = 0; j < COL_CHESS; j++)
		{
			data.x = i + 1;
			data.y = j + 1;

			board[i][j] = &(other.getGamePiece(data)); //Assigning addresses

			other.getBoard()[i][j] = nullptr; //Assigning old board to null

			int i;
			for (i = 0; i < ROW_CHESS; i++) //Freeing old board
			{
				delete[](board[i]);
			}
			delete[](board);
		}
}

const bool ChessGame::isEmptyCell(const position& data) const
{
	if (board[data.x - 1][data.y - 1] == nullptr)
		return true;
	return false;
}

GamePiece*** ChessGame::getBoard() const {
	return board;
}

void ChessGame::playMove(position* movePositions)
{
	position from, to;
	position capturePos = { 0,0 };
	Player* currEnemy;

	from = movePositions[0]; // Old pos
	to = movePositions[1];   // Wanted pos

	if (_currTurn == 'X') {
		currEnemy = &_playerO;
	}
	else {
		currEnemy = &_playerX;
	}

	didCapture(capturePos, from, to);

	if (capturePos.x != 0) // If there was a capture
	{
		delete board[capturePos.x - 1][capturePos.y - 1];
		board[capturePos.x - 1][capturePos.y - 1] = nullptr;

		currEnemy->setNumOfPieces(currEnemy->getNumOfPieces() - 1); // Num of enemy pieces -1
		currEnemy->getPieces().deleteNode(capturePos); // Delete caputred piece
	}

	board[to.x - 1][to.y - 1] = board[from.x - 1][from.y - 1]; // Moving the piece
	board[from.x - 1][from.y - 1] = nullptr; // Assinging null to old position
	board[to.x - 1][to.y - 1]->setPos(to);

	if (board[to.x - 1][to.y - 1]->getPlayer() == 'k') // If we moved a King, update KingPosition
	{
		_kingPositionW = to;

	}
	else if (board[to.x - 1][to.y - 1]->getPlayer() == 'K')
	{
		_kingPositionB = to;
	}

	if (_currTurn == 'X') {
		_playerX.getPieces().updateNodePos(from, to); // Update piece list
	}
	else {
		_playerO.getPieces().updateNodePos(from, to);
	}

	if (to.x == 1 || to.x == 8) // If we moved a pawn to the last line, make it a Queen (chess rules)
	{
		char pieceType = board[to.x - 1][to.y - 1]->getPlayer();
		if (pieceType == 'P' || pieceType == 'p')
		{
			free(board[to.x - 1][to.y - 1]);
			board[to.x - 1][to.y - 1] = new ChessQueenPiece(to, _currTurn == 'X' ? 'Q' : 'q');
		}
	}

	updateLegalAndThreatMoves(capturePos, from, to);

	lookForWinner();

	setCurrTurn();


}

const bool ChessGame::isBelongToCurrTurn(const position& from)
{

	return !isEmptyCell(from) && board[from.x - 1][from.y - 1]->getColor() == _currTurn;
}

const bool ChessGame::isLegalMove(const position& from, const position& to)
{
	return  board[from.x - 1][from.y - 1]->getLegalMoves().isPosFound(to);
}

void ChessGame::updateLegalAndThreatMoves(position& capturePos, const position& from, const position& to)
{
	int i, j;

	for (i = 0; i < ROW_CHESS; i++)
		for (j = 0; j < COL_CHESS; j++)
		{
			if (board[i][j] != nullptr)
			{
				board[i][j]->getThreatMoves().free();
				board[i][j]->getLegalMoves().free();

				board[i][j]->setLegalMoves(board);
				board[i][j]->setThreatMoves(board);
			}
		}
	board[_kingPositionW.x - 1][_kingPositionW.y - 1]->setThreatMoves(board);
	board[_kingPositionB.x - 1][_kingPositionB.y - 1]->setThreatMoves(board);
}

void ChessGame::didCapture(position& data, const position& from, const position& to) {

	if (board[to.x - 1][to.y - 1] != nullptr)
	{
		data.x = to.x;
		data.y = to.y;
	}
}

bool ChessGame::isPlayerLoser(Player* player) {
	bool isLoser = true;
	position kingPos;

	if (_currTurn == 'O')
	{
		kingPos = _kingPositionB;
	}
	else
	{
		kingPos = _kingPositionW;
	}

	if (!(board[kingPos.x - 1][kingPos.y - 1]->getThreatMoves().isEmpty())) // If a king's threat exists
	{
		PositionList pieces = player->getPieces();
		positionNode* curr = pieces.getHead();
		while (curr != nullptr && isLoser) {
			if (!(board[curr->data.x - 1][curr->data.y - 1]->getLegalMoves().isEmpty())) // And the king has no legal moves (which take him out of any other threats)
				isLoser = false;
			curr = curr->next;
		}
	}
	else
	{
		isLoser = false;
	}
	return isLoser;
}

void ChessGame::lookForWinner()
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

const bool  ChessGame::validInputToPrintThreat(const position& data) const {
	if (!isEmptyCell(data))
		return true;
	return false;
}

const bool ChessGame::validInputToPrintLegal(const position& data) const {
	return validInputToPrintThreat(data);
}

const position& ChessGame::getKingPositionW() const {
	return _kingPositionW;
}

const position& ChessGame::getKingPositionB() const {
	return _kingPositionB;
}