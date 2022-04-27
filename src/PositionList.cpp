#define _CRT_SECURE_NO_WARNINGS
#include "PositionList.h"
#include <iostream>

using namespace std;

PositionList::PositionList() {
	makeEmpty();
};

PositionList::~PositionList() {
	free();
}

PositionList::PositionList(const PositionList& other) {   //העתקה
	*this = other;
}

void PositionList:: operator=(const PositionList& other) {      //השמה
	if (this != &other)
	{
		this->free();
		positionNode* curr = other.getHead();
		position currPos;

		while (curr != nullptr)
		{
			currPos = curr->data;

			add<PositionList*, position, positionNode, positionNode*>(this, currPos, nullptr);
			curr = curr->next;
		}
		_head = getHead();
		_tail = getTail();
		_curr = getCurr();
	}
}


PositionList::PositionList(PositionList&& other) {
	_head = other.getHead();
	_tail = other.getTail();
	_curr = other.getCurr();

	other.setCurr(nullptr);
	other.setTail(nullptr);
	other.setHead(nullptr);
}


void PositionList::free()
{
	positionNode* curr2;
	if (!isEmpty())
	{
		_curr = curr2 = _head;
		while (_curr->next != nullptr)
		{
			_curr = _curr->next;
			delete curr2;
			curr2 = _curr;
		}
		delete _curr;
	}
	makeEmpty();
}

void PositionList::print() const {
	positionNode* curr = _head;
	if (!isEmpty())
	{
		while (curr != nullptr)
		{
			cout << curr->data.x << ", " << curr->data.y << endl;
			curr = curr->next;
		}
	}
}

const bool PositionList::isEmpty() const
{
	if (_head != nullptr)
		return false;
	return true;
}

void PositionList::makeEmpty()
{
	_head = _tail = _curr = nullptr;
}

const bool PositionList::isPosFound(const position data) const
{
	bool IsFound = false;

	positionNode* curr = _head;
	if (!isEmpty())
	{
		while (curr != nullptr && !IsFound)
		{
			if (curr->data == data)
				IsFound = true;
			curr = curr->next;
		}
	}
	return IsFound;
}

positionNode* PositionList::getHead() const {
	return _head;
}

positionNode* PositionList::getTail() const {
	return _tail;
}

positionNode* PositionList::getCurr() const {
	return _curr;
}

void PositionList::setCurr(positionNode* ptr) {
	_curr = ptr;
}

void PositionList::setTail(positionNode* ptr) {
	_tail = ptr;
}

void PositionList::setHead(positionNode* ptr) {
	_head = ptr;
}

void PositionList::deleteNode(const position posToDelete)
{
	// Store _head node
	positionNode* temp = _head, * prev = _head;

	if (isPosFound(posToDelete) == false)
		return;

	// If _head node itself holds the key to be deleted
	if (temp != nullptr && temp->data == posToDelete) {
		_head = _head->next; // Changed _head
		delete temp; // free old _head
		return;
	}

	// Search for the key to be deleted, keep track of the
	// previous node as we need to change 'prev->next'
	while (temp != nullptr && !(temp->data == posToDelete)) {
		prev = temp;
		temp = temp->next;
	}

	// If key was not present in linked list
	if (temp == nullptr)
		return;

	// Unlink the node from linked list
	else
	{
		prev->next = temp->next;
		if (prev->next == nullptr)
			_tail = prev;
	}

	delete temp; // Free memory
}

void PositionList::updateNodePos(position oldPos, position newPos)
{
	positionNode* curr = _head;
	while (!(curr->data == oldPos))
	{
		curr = curr->next;
	}
	curr->data = newPos;
}




