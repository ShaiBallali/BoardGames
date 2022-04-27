#pragma once

#include "Game.h"
#include "generic.h"

class GamePiece {

protected:
	position data;
	char player;

public:

	GamePiece(position data, char player);
	GamePiece() = default;
	GamePiece(const GamePiece& other);
	void operator=(const GamePiece& other);

	virtual void setLegalMoves(GamePiece*** board) = 0; 
	virtual const PositionList& getLegalMoves() const = 0;
	virtual PositionList& getLegalMoves() = 0;
	virtual void  printLegalMoves() const = 0;

	virtual const PositionList& getThreatMoves() const = 0;
	virtual  PositionList& getThreatMoves()  = 0;
	virtual void setThreatMoves(GamePiece*** board) {};

	void              setPos(position currPos);
	void			  setPlayer(char curPlayer);

	const  position       getPos() const;
	const char		  getPlayer() const;
	virtual const char getColor() const = 0;
};

