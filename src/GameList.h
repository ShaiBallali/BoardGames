#pragma once

#include "game.h"
#include "generic.h"

struct ListNode
{
	Game* data;
	ListNode* next;
};

class GameList
{
private:

	ListNode* _head;
	ListNode* _tail;
	ListNode* _curr;

	ListNode* createNewListNode(Game* currGame, ListNode* next = nullptr);

public:

	GameList();
	~GameList();

	GameList(const GameList& other);
	GameList(GameList&& other);

	void			  operator=(const GameList& other);
	void			  operator+(Game* other);

	void			  makeEmpty();
	const bool		  isEmpty() const;
	void			  next();
	void			  deleteCurrGame();
	void			  free();

	ListNode* getHead() const;
	ListNode* getTail() const;
	ListNode* getCurr() const;

	void			  setCurr(ListNode* ptr);
	void			  setTail(ListNode* ptr);
	void			  setHead(ListNode* ptr);

};

