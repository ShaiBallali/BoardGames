#pragma once

#include "AmazonsGame.h"
#include "CheckersGame.h"
#include "ChessGame.h"

#include "GameList.h"
#include "GamePiece.h"
#include "generic.h"
#include "Player.h"
#include "PositionList.h"

#include <iostream>
using namespace std;

ostream& operator<<(ostream& os, const Game& game);

class Menu
{
private:
	int				_userChoice;
	GameList		_gameList;
	bool			_isValidInput;
	Game* _currGame;

public:
	Menu();
	Menu(const Menu& other);

	void			operator=(const Menu& other);

	void			gamePlay();

private:

	void			printMenu();
	bool			getUserChoiceFromUser();
	bool			getIsValidInput() const;
	int				getUserChoice() const;
	const GameList& getGameList() const;
	GameList&       getGameList();
	Game*           getCurrGame() const;

	void			setUserChoice(int userChoice);
	bool			checkInputMenu(int userChoice);

	void			addGame();
	void			deleteGame();
	void			next();
	void			printGameDetails();
	void			printLegalMoves();
	void			getPositionToLegalMoves(position& data);
	void			printThreatMoves();
	void			getPositionToThreatMoves(position& data);
	void			playMove();
	void			exitGame();
};