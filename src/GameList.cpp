#include "GameList.h"


GameList::GameList() {
	makeEmpty();
}

GameList::~GameList() {
	free();
}

ListNode* GameList::createNewListNode(Game* currGame, ListNode* next)
{
	ListNode* res;
	res = new ListNode();
	res->data = currGame;
	res->next = next;
	return res;
}

void GameList::free()
{
	ListNode* curr1, * curr2;
	curr1 = curr2 = _head;
	while (curr2 != nullptr)
	{
		curr2 = curr2->next;
		delete (curr1->data);
		delete curr1;
		curr1 = curr2;
	}
}

void GameList::makeEmpty()
{
	_head = _tail = _curr = nullptr;
}

void GameList::operator+(Game* other)
{
	add<GameList*, Game*, ListNode, ListNode*>(this, other, nullptr);
}

const bool GameList::isEmpty() const
{
	if (_head == nullptr)
		return true;
	return false;
}

ListNode* GameList::getHead() const
{
	return _head;
}

void GameList::deleteCurrGame()
{
	// Store _head node
	delete (_curr->data);
	ListNode* temp = _curr;

	if (_head == _tail)
	{
		delete (temp);
		_head = _tail = _curr = nullptr;
	}

	else
	{
		next();
		// If _head node itself holds the key to be deleted
		if (_head == temp)
		{
			_head = temp->next; // Changed _head
			delete temp; // free old _head
		}
		else
		{
			ListNode* prev = _head;

			while (prev->next != temp)
				prev = prev->next;

			if (_tail == temp)
			{
				_tail = prev;
				_tail->next = nullptr;
				delete temp;
			}
			else
			{
				prev->next = temp->next;
				delete temp;
			}
		}
	}

}

void GameList::next()
{
	if (_curr->next != nullptr)
		_curr = _curr->next;
	else
		_curr = _head;
}

ListNode* GameList::getCurr() const
{
	return _curr;
}

ListNode* GameList::getTail() const
{
	return _tail;
}


GameList::GameList(const GameList& other) {   //העתקה
	*this = other;
}

void GameList:: operator=(const GameList& other) { //אופרטור השמה 
	if (this != &other)
	{
		this->free();
		ListNode* curr;
		ListNode* curr2 = other.getHead();
		while (curr2)
		{
			curr = createNewListNode(other.getHead()->data);
			addNodeToTail(this, curr);
			curr2 = curr2->next;
		}
	}
}

void GameList::setCurr(ListNode* ptr) {
	_curr = ptr;
}

void GameList::setHead(ListNode* ptr) {
	_head = ptr;
}

void GameList::setTail(ListNode* ptr) {
	_tail = ptr;
}

GameList::GameList(GameList&& other) {
	_head = other.getHead();
	_tail = other.getTail();
	_curr = other.getCurr();

	other.setCurr(nullptr);
	other.setTail(nullptr);
	other.setHead(nullptr);
}
