#include "Menu.h"

Menu::Menu() : _isValidInput(false), _currGame(nullptr), _userChoice(0) {}

void Menu::gamePlay() {
	while (_userChoice != 8)                           // Initialized to 0
	{
		bool validInput = false;
		while (!validInput)
		{
			validInput = true;
			printMenu();
			if (!getUserChoiceFromUser())
			{
				validInput = false;
				cout << "ENTER VALID INPUT" << endl;
			}
		}
		switch (_userChoice)
		{
		case 1:
			addGame();
			break;
		case 2:
			next();
			break;
		case 3:
			deleteGame();
			break;
		case 4:
			printGameDetails();
			break;
		case 5:
			printLegalMoves();
			break;
		case 6:
			printThreatMoves();
			break;
		case 7:
			playMove();
			break;
		case 8:
			exitGame();
			break;
		}
	}
}

void Menu::printMenu() {
	cout << "MENU:" << "\n" << "1.Add a new game\n" << "2.Go to next game\n" << "3.Delete current game\n" << "4.Show game details\n" << "5.Show piece's legal moves (enter row then col)\n" << "6.Show cell's threat moves (enter row then col)\n" << "7.Make a move\n" << "8.Exit\n";
}

bool Menu::getUserChoiceFromUser() {
	int userChoice;
	cin >> userChoice;
	return checkInputMenu(userChoice);
}

void Menu::setUserChoice(int userChoice)
{
	_userChoice = userChoice;
}

bool Menu::checkInputMenu(int userChoice) {
	bool isValidInput = true;

	if (userChoice <= 0 || userChoice >= 9)
	{
		isValidInput = false;
		cout << "Please enter a number between 1 to 8." << endl;
	}
	else if (_gameList.isEmpty() && (userChoice != 1 && userChoice != 8))
	{
		isValidInput = false;
		cout << "You have no game yet" << endl;
	}
	else {
		setUserChoice(userChoice);
	}

	return isValidInput;
}

void Menu::addGame() {
	int numOfGame = 0;
	bool valid = false;
	cout << "Choose game: \n1 - Checkers.\n2 - Amazons.\n3 - Chess." << endl;
	while (!valid)
	{
		cin >> numOfGame;
		if (numOfGame >= 1 && numOfGame <= 3)
		{
			valid = true;
		}
		else {
			cout << "Please enter a correct number: (between 1 to 3):" << endl;
		}
	}
	if (numOfGame == 1)
	{
		_currGame = new CheckersGame;
	}
	else if (numOfGame == 2)
	{
		_currGame = new AmazonsGame;
	}
	else {
		_currGame = new ChessGame;

	}
	_gameList + _currGame;                   // operator+  gameList+game = add new game

}

bool Menu::getIsValidInput() const
{
	return _isValidInput;
}

int	Menu::getUserChoice() const
{
	return _userChoice;
}

const GameList& Menu::getGameList() const
{
	return _gameList;
}

GameList& Menu::getGameList()
{
	return _gameList;
}

Game* Menu::getCurrGame() const
{
	return _currGame;
}

Menu::Menu(const Menu& other)
{
	*this = other;
}

void Menu::operator=(const Menu& other)
{
	if (this != &other)
	{
		_userChoice = other.getUserChoice();
		_gameList = other.getGameList();
		_isValidInput = other.getIsValidInput();
		_currGame = _gameList.getCurr()->data;
	}
}

void Menu::next() {
	_gameList.next();
	_currGame = _gameList.getCurr()->data;
}

void Menu::deleteGame() {
	_gameList.deleteCurrGame();
	_currGame = _gameList.getCurr()->data;
}

void Menu::printGameDetails() {
	cout << *_currGame;

	if (_currGame->getIsGameOver())
	{
		cout << "Game over" << endl;
		cout << "Player: " << _currGame->getWinner() << " won" << endl;
	}
	else
	{
		cout << "Game is not over" << endl;
		cout << "Player: " << _currGame->getCurrTurn() << " is playing" << endl;
	}
}

ostream& operator<<(ostream& os, const Game& game) {
	int i, j;
	int row = game.getNumCols();
	int col = game.getNumRows();
	os << "  ";
	for (i = 1; i <= col; i++)
		os << " " << i;

	os << "\n" << " ";

	int numOfHyphen = row * 2 + 2;
	for (i = 0; i < numOfHyphen; i++)
		os << "-";
	os << "\n";

	for (i = 0; i < row; i++)
	{
		os << i + 1;
		if (i < 9) {
			os << " ";
		}
		for (j = 0; j < col; j++)
		{
			os << "|";
			position data;
			data.x = i + 1;
			data.y = j + 1;

			if (game.isEmptyCell(data))
				os << " ";
			else
			{
				char temp = game.getBoard()[i][j]->getPlayer();
				os << temp;
			}

		}
		os << "|" << endl;
	}

	os << " ";
	for (i = 0; i < numOfHyphen; i++)
		os << "-";
	os << "\n";

	return os;
}


void Menu::printLegalMoves() {
	position data;
	getPositionToLegalMoves(data);
	_currGame->getBoard()[data.x - 1][data.y - 1]->getLegalMoves().print();
}

void Menu::getPositionToLegalMoves(position& data) {
	bool valid = false;

	while (!valid)
	{
		cout << "enter row then col: " << endl;
		cin >> data.x;
		cin >> data.y;
		if (!(_currGame->checkIfPosInRange(data) && _currGame->validInputToPrintLegal(data)))
		{
			cout << "please enter a correct position" << endl;
		}
		else
			valid = true;
	}
}

void Menu::printThreatMoves() {
	position data;
	getPositionToThreatMoves(data);
	_currGame->getBoard()[data.x - 1][data.y - 1]->getThreatMoves().print();
}

void Menu::getPositionToThreatMoves(position& data)
{
	bool valid = false;

	while (!valid)
	{
		cout << "enter row then col: " << endl;
		cin >> data.x;
		cin >> data.y;
		if (!(_currGame->checkIfPosInRange(data) && _currGame->validInputToPrintThreat(data)))
		{
			cout << "please enter a correct position" << endl;
		}
		else
			valid = true;
	}
}

void Menu::playMove() {
	int size = _currGame->getNumOfInputForMove();        // Each  game needs a diffrent number of input in order to play a move.
	bool validMove = false;
	position* movePositions = new position[size];

	while (!validMove)
	{
		validMove = true;
		cout << "Enter " << size << " positions for move (row then col):" << endl;
		for (int i = 0; i < size; i++) {
			cin >> movePositions[i].x;
			cin >> movePositions[i].y;
		}
		if (!(_currGame->checkValidMoveFrom(movePositions[0]) && _currGame->checkValidMoveTo(movePositions[0], movePositions[1]))) // cheking moveFrom and moveTo
		{
			cout << "Invalid moves! Please enter valid moves." << endl;
			validMove = false;
		}
		else {
			_currGame->playMove(movePositions);           // play a move
		}
	}
	delete[](movePositions);
}

void Menu::exitGame() {
	cout << "Bye";
	exit(0);
}
