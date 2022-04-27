#pragma once
// This file contains:
// 1. struct the presented position in the board.
// 2. two template


struct position {
	int x;
	int y;
	
	void operator=(const position& other)
	{
		x = other.x;
		y = other.y;
	}

	bool operator==(const position& other)
	{
		return x == other.x && y == other.y;
	}
};

template <class List, class Data, class Node, class Next>
void add(List list, Data data, Next next)
{
	Node* node = new Node;
	node->data = data; 
	node->next = next;
	addNodeToTail(list, node);
	list->setCurr(node);
}

template <class List, class Node>
void addNodeToTail(List list ,Node node)
{
	if (list->getHead() == nullptr)
	{
		list->setHead(node);
		list->setTail(node);
	}
	else
	{
		list->getTail()->next = node;
		list->setTail(node);
	}
	list->getTail()->next = nullptr;
}
