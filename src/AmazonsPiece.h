#pragma once
#include "GamePiece.h"
#include "PositionList.h"
#include "generic.h"


class AmazonsPiece : public GamePiece {

private:
	PositionList legalMoves;
	PositionList threatMoves;

public:
	                                 AmazonsPiece (position data, char player);
	                                 AmazonsPiece (const AmazonsPiece& other);

	void	                         operator=(const AmazonsPiece& other);

	bool                             inRange(position move);
	const char                       getColor() const;

	virtual void		             setLegalMoves(GamePiece*** board);
	virtual const PositionList&      getLegalMoves() const;
	virtual PositionList&            getLegalMoves();
	virtual void			         printLegalMoves() const;

	virtual const PositionList&      getThreatMoves() const;
	virtual  PositionList&           getThreatMoves();
};

