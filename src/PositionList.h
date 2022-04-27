#pragma once

#include "generic.h"

class Game;

struct positionNode
{
	position data;                          // THE_GAME* / POSITION
	positionNode* next;
};

class PositionList
{
public:

	PositionList();
	~PositionList();

	PositionList(const PositionList& other);
	PositionList(PositionList&& other);

	void			  operator=(const PositionList& other);

	//void			  add(position data, positionNode* next = nullptr);
	void			  free();
	void			  print() const;
	const bool		  isEmpty() const;
	void			  makeEmpty();
	const bool		  isPosFound(const position data) const;
	void              deleteNode(const position dataToDelete);
	void              updateNodePos(position oldData, position newData);

	positionNode*     getHead() const;
	positionNode*     getTail() const;
	positionNode*     getCurr() const;

	void			  setCurr(positionNode* ptr);
	void			  setTail(positionNode* ptr);
	void			  setHead(positionNode* ptr);

private:

	positionNode* _head;
	positionNode* _tail;
	positionNode* _curr;
};


