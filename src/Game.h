#define _CRT_SECURE_NO_WARNINGS
#pragma once

#include <iostream>
#include "Player.h"
#include "generic.h"

using namespace std;

class Player;

class Game 
{
protected:
	Player			  _playerX;
	Player		  	  _playerO;
	char			  _winner;
	bool			  _isGameOver;
	char			  _currTurn;
	int               _numRows, _numCols;
	int               _numOfInputForMove;

public:
	Game(int numRows, int numCols, int numOfInputForMove);
	Game() = default;            //////////////////////////////////////////////////////////////
	Game(const Game&);
	void operator=(const Game&);

	const char        getWinner() const;
	const bool        getIsGameOver() const;
	const char        getCurrTurn() const;
	const int         getNumRows() const;
	const int         getNumCols() const;
	const int         getNumOfInputForMove() const;

	const Player&     getPlayerX() const;
	const Player&	  getPlayerO() const;

	void			  setWinner(char winner);
	void              setIsGameOver(bool isOver);
	void              setCurrTurn();                        ///void changeCurrTurn();
	const bool		  checkIfPosInRange(const position& data) const;


	virtual void playMove (position* movePositions) = 0; ///////////////////
	
	virtual const bool        validInputToPrintThreat(const position& data) const = 0;
	virtual const bool        validInputToPrintLegal(const position& data)const = 0;
	virtual const bool		  isEmptyCell(const position& data) const = 0;
	virtual  GamePiece***     getBoard() const = 0;
	virtual const bool        isBelongToCurrTurn(const position& from) = 0;
	virtual const bool        isLegalMove(const position& from, const position& to) = 0;

	const bool checkValidMoveFrom(const position& data);
	const bool checkValidMoveTo(const position& from, const position& to);
};



