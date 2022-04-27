#include "Game.h"

Game::Game(int numRows, int numCols, int numOfInputForMove) : _isGameOver(false), _currTurn('O'), _numCols(numRows), _numRows(numCols), _numOfInputForMove(numOfInputForMove), _playerO(true, 'O'), _playerX(false, 'X') {}

Game::Game(const Game& other)
{
	*this = other;
}


void Game::operator=(const Game& other)
{
	_playerX = other.getPlayerX();
	_playerO = other.getPlayerO();
	_winner = other.getWinner();
	_isGameOver = other.getIsGameOver();
	_currTurn = other.getCurrTurn();
	_numRows = other.getNumRows();
	_numCols = other.getNumCols();
	_numOfInputForMove = other.getNumOfInputForMove();
}


void Game::setCurrTurn()      // change currTurn
{
	if (_currTurn == 'X')
	{
		_currTurn = 'O';
		_playerX.setIsPlaying(false);
		_playerO.setIsPlaying(true);
	}
	else
	{
		_currTurn = 'X';
		_playerX.setIsPlaying(true);
		_playerO.setIsPlaying(false);
	}
}


void Game::setWinner(char winner) {
	_winner = winner;
}

const char Game::getWinner() const
{
	return _winner;
}

const bool Game::getIsGameOver() const {
	return _isGameOver;
}

const char Game::getCurrTurn() const {
	return _currTurn;
}

const Player& Game::getPlayerX() const
{
	return _playerX;
}


const Player& Game::getPlayerO() const
{
	return _playerO;
}

void Game::setIsGameOver(bool isOver) {
	_isGameOver = isOver;
}

const int Game::getNumRows() const {
	return _numRows;
}

const int Game::getNumCols() const {
	return _numCols;
}

const int Game::getNumOfInputForMove() const {
	return _numOfInputForMove;
}

const bool Game::checkIfPosInRange(const position& data) const {           // check if position is in range of the board
	if (data.x < 1 || data.x > _numRows || data.y < 1 || data.y > _numCols)
		return false;
	return true;
}

const bool Game::checkValidMoveFrom(const position& data)                  
{
	if (checkIfPosInRange(data) && isBelongToCurrTurn(data))
		return true;
	return false;
}

const bool Game::checkValidMoveTo(const position& from, const position& to)
{
	if (checkIfPosInRange(to) && isLegalMove(from, to))
		return true;
	return false;
}



