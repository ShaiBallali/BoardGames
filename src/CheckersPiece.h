#pragma once
#include "GamePiece.h"

class CheckersPiece : public GamePiece {
private:
	PositionList _legalMoves;
	PositionList _threatMoves;
	bool _isKing;

public:
	                                 CheckersPiece(position data, char player, bool isKing);
					                 CheckersPiece(const CheckersPiece& other);

	void	                         operator=(const CheckersPiece& other);

	void                             printThreatMoves() const;
	void	                         legalPawnMoves(GamePiece*** board, int direction);
	void	                         legalKingMoves(GamePiece*** board);
	void	                         pawnThreats(GamePiece*** board);
	void                             kingsThreats(GamePiece*** board);
	bool                             inRange(position move);
	void                             setIsKing(bool isKing);
	const bool                       getIsKing() const;

	virtual void		             setLegalMoves(GamePiece*** board);
	virtual const PositionList&      getLegalMoves() const;
	virtual PositionList&            getLegalMoves();
	virtual void			         printLegalMoves() const;
	virtual const PositionList&      getThreatMoves() const;
	virtual void                     setThreatMoves(GamePiece*** board);
	virtual PositionList&            getThreatMoves();
	virtual const char               getColor() const;
};



