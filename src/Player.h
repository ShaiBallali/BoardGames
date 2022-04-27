#pragma once

#include "PositionList.h"
#include "generic.h"

class GamePiece;
class PositionList;

class Player {
private:
	bool				   _isPlaying;
	bool				   _isLoser;
	char				   _whichPlayer;
	int					   _numOfPieces;
	int					   _sizeBoard;
	PositionList		   pieces;

public:

	                       Player(const bool isPlaying, const char whichPlayer);
	                       Player() = default;
	                       Player(const Player&);

	void				   operator=(const Player&);

	void				   setIsPlaying(bool isPlaying);
	void				   setIsLoser(bool isWinner);
	void				   setWhichPlayer(char whichPlayer);

	void				   initPieces(GamePiece*** board, int sizeBoard);
	void				   setNumOfPieces(int numOfPieces);

	const int			   getNumOfPieces() const;
	const int			   getSizeBoard() const;
	const bool			   getIsPlaying() const;
	const bool			   getIsLoser() const;
	const int			   getWhichPlayer() const;
	PositionList&          getPieces();
	const PositionList&    getPieces() const;
};

