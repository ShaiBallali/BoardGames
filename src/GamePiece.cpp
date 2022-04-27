#include "GamePiece.h"


GamePiece::GamePiece(position posi, char player) : player(player), data(posi) {
}


void GamePiece::setPos(position currPos)
{
	data = currPos;
}

void GamePiece::setPlayer(char curPlayer)
{
	player = curPlayer;
}

const position GamePiece::getPos() const
{
	return data;
}

const char GamePiece::getPlayer() const
{
	return player;
}

GamePiece::GamePiece(const GamePiece& other) {

	*this = other;
}

void GamePiece::operator=(const GamePiece& other) {
	data = other.getPos();
	player = other.getPlayer();
}

