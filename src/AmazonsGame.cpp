#include "AmazonsGame.h"

AmazonsGame::AmazonsGame() : Game(ROW_AMAZONS, COL_AMAZONS, NUM_OF_INPUTS_FOR_AMAZONS_MOVE) { //Each game needs row, col, num of inputs (amazons needs 3, chess and checkers need 2)
	board = new GamePiece * *[ROW_AMAZONS]; // Creating suitable board
	for (int i = 0; i < ROW_AMAZONS; i++)
	{
		board[i] = new GamePiece * [COL_AMAZONS];
	}

	for (int i = 0; i < ROW_AMAZONS; i++)
		for (int j = 0; j < COL_AMAZONS; j++)
		{
			position data;
			data.x = i + 1;
			data.y = j + 1;

			board[i][j] = new AmazonsPiece(data, '0'); // Polymorphism
		}

	board[6][0]->setPlayer('O'); // Initializing pieces
	board[9][3]->setPlayer('O');
	board[9][6]->setPlayer('O');
	board[6][9]->setPlayer('O');

	board[3][0]->setPlayer('X');
	board[0][3]->setPlayer('X');
	board[0][6]->setPlayer('X');
	board[3][9]->setPlayer('X');

	_playerX.setNumOfPieces(4);
	_playerO.setNumOfPieces(4);

	updateBoard(); // Initialize board
}

AmazonsGame::~AmazonsGame() {
	freeBoard();
}

void AmazonsGame::freeBoard() // Freeing each cell, then each col, then whole board
{
	int i, j;
	for (i = 0; i < ROW_AMAZONS; i++)
		for (j = 0; j < COL_AMAZONS; j++)
		{
			delete(board[i][j]);
		}
	for (i = 0; i < ROW_AMAZONS; i++)
	{
		delete[](board[i]);
	}
	delete[](board);
}


void AmazonsGame::updateBoard()
{
	int i, j;
	for (i = 0; i < ROW_AMAZONS; i++)
		for (j = 0; j < COL_AMAZONS; j++)
			board[i][j]->setLegalMoves(board);

	_playerX.initPieces(board, ROW_AMAZONS);
	_playerO.initPieces(board, ROW_AMAZONS);
}

GamePiece& AmazonsGame::getGamePiece(const position data)
{
	return *(board[data.x - 1][data.y - 1]);
}

GamePiece& AmazonsGame::getGamePiece(const position data) const
{
	return *(board[data.x - 1][data.y - 1]);
}

void AmazonsGame::operator=(const AmazonsGame& other)
{
	if (this != &other) // Making sure no self copy is made
	{
		Game::operator=(other); // Father copy first

		position data;

		for (int i = 0; i < ROW_AMAZONS; i++) // Copying fields
			for (int j = 0; j < COL_AMAZONS; j++)
			{
				data.x = i + 1;
				data.y = j + 1;

				*board[i][j] = other.getGamePiece(data); // Copying value, not address
			}
	}
}

AmazonsGame::AmazonsGame(const AmazonsGame& other) // Copy ctor
{
	*this = other;
}

AmazonsGame::AmazonsGame(const AmazonsGame&& other) // Move ctor
{
	position data;

	for (int i = 0; i < ROW_AMAZONS; i++)
		for (int j = 0; j < COL_AMAZONS; j++)
		{
			data.x = i + 1;
			data.y = j + 1;

			board[i][j] = &(other.getGamePiece(data)); // Assigning address

			other.getBoard()[i][j] = nullptr; // Pointing old addresses to null

			int i;
			for (i = 0; i < ROW_AMAZONS; i++)
			{
				delete[](board[i]);
			}
			delete[](board);
		}
}

const bool AmazonsGame::isEmptyCell(const position& data) const
{
	if (board[data.x - 1][data.y - 1]->getPlayer() == '0')
		return true;
	return false;
}

GamePiece*** AmazonsGame::getBoard() const {
	return board;
}

void AmazonsGame::playMove(position* movePositions) // Getting an array for the inputs (Amazons has 3 inputs)
{
	position from, to, arrow;
	from = movePositions[0]; // Initial position
	to = movePositions[1]; // Wanted position
	arrow = movePositions[2]; // Arrow position

	board[to.x - 1][to.y - 1]->setPlayer(_currTurn); // Assigning new position with current piece
	board[from.x - 1][from.y - 1]->setPlayer('0');   // Assigning old position with "empty" (0)
	board[to.x - 1][to.y - 1]->setLegalMoves(board);

	if (_currTurn == 'X') {
		_playerX.getPieces().updateNodePos(from, to); // Updating piece list (replacing old with new)
	}
	else {
		_playerO.getPieces().updateNodePos(from, to);
	}

	bool validArrow = checkValidMoveTo(to, arrow);

	while (!validArrow)
	{
		cout << "Arrow coordinates invalid. Please enter a new coordinate (enter row then col):" << endl;
		cin >> arrow.x;
		cin >> arrow.y;

		validArrow = checkValidMoveTo(to, arrow);
	}

	board[arrow.x - 1][arrow.y - 1]->setPlayer('A');
	board[arrow.x - 1][arrow.y - 1]->getLegalMoves().free();

	updateLegalMoves(from, to); // After each move, LegalMoves should be updated

	lookForWinner();            // After each move, a player may win

	setCurrTurn();              // Change turns
}

const bool AmazonsGame::isBelongToCurrTurn(const position& from)
{
	return !isEmptyCell(from) && board[from.x - 1][from.y - 1]->getPlayer() == _currTurn;
}

const bool AmazonsGame::isLegalMove(const position& from, const position& to)
{
	return  board[from.x - 1][from.y - 1]->getLegalMoves().isPosFound(to);
}


void AmazonsGame::updateLegalMoves(const position& from, const position& to)
{
	int i, j;

	for (i = 0; i < ROW_AMAZONS; i++)
		for (j = 0; j < COL_AMAZONS; j++)
		{
			if (board[i][j]->getPlayer() != 'A')
			{
				board[i][j]->getLegalMoves().free();
				board[i][j]->setLegalMoves(board);
			}
		}
}

bool AmazonsGame::isPlayerLoser(Player* player) {

	bool isLoser = true;
	PositionList pieces = player->getPieces();
	positionNode* curr = pieces.getHead();
	while (curr != nullptr && isLoser) { // Iterating through piece list
		if (!(board[curr->data.x - 1][curr->data.x - 1]->getLegalMoves().isEmpty()))  // A player lost if he has no legal moves with every piece   
			isLoser = false;
		curr = curr->next;
	}
	return isLoser;
}

void AmazonsGame::lookForWinner() // Setting winner if necessary
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


const bool AmazonsGame::validInputToPrintThreat(const position& data) const { // In Amazons, option 6 is only for empty cells
	if (board[data.x - 1][data.y - 1]->getPlayer() == '0')
		return true;
	return false;
}

const bool AmazonsGame::validInputToPrintLegal(const position& data) const { // Print legal moves only if there's a player in the cell
	if (board[data.x - 1][data.y - 1]->getPlayer() == 'X' || board[data.x - 1][data.y - 1]->getPlayer() == 'O')
		return true;
	return false;
}