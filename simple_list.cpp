#include <iostream>


class Node {
public:
	Node();
	Node(int x);

	int data;
	Node* next;
};

Node::Node()	
	: data(0),
	  next(nullptr)
{}

Node::Node(int x)
	: data(x),
	  next(nullptr)
{}

class SimpleList {
public:
	SimpleList();
	~SimpleList();

	void push_front(int x);
	void push_back(int x);

	void pop_back();
	void pop_front();

	void delete_at(Node* n);
	void insert_at(Node* n, Node* newNode);

	Node* find(int x);

private:
	Node* head;
};

SimpleList::SimpleList()
	: head(nullptr)
{}

SimpleList::~SimpleList()
{
	Node* curr = head;
	while (curr) {
		Node* temp = curr->next;
		delete curr;
		curr = temp;
	}
}

void SimpleList::push_front(int x)
{
	Node* newNode = new Node(x);

	if (head == nullptr){
		head = newNode;
		return;
	}

	Node* temp = head;
	head = newNode;
	head->next = temp;
}

void SimpleList::push_back(int x)
{
	Node* newNode = new Node(x);
	if (head == nullptr){
		head = newNode;
		return;
	}

	Node* curr = head;
	while (curr->next) {
		curr = curr->next;
	}

	curr->next = newNode;
}

void SimpleList::pop_back()
{
	if (head == nullptr)
		return;

	Node* curr = head;
	Node* prev = nullptr;
	while (curr->next){
		prev = curr;
		curr = curr->next;
	}

	delete curr;
	//if prev is null then it means there was only one node in the list
	//and we just deleted the head so null out appropriately.
	if (prev)
		prev->next = nullptr;
	else
		head = nullptr;
}

void SimpleList::pop_front()
{
	if (head == nullptr)
		return;

	Node* temp = head->next;
	delete head;
	head = temp;
}

void SimpleList::delete_at(Node* n)
{
	if (!n || !head)
		return;

	/*** Assume n is always in the list, don't need to search for it ***/
	/*
	Node* curr = head;
	while (curr && curr != n) {
		curr = curr->next;
	}

	//n is not in the list
	if (!curr)
		return;

	//if it's the last node in the list, just delete
	if (!curr->next){
		delete curr;
		curr = nullptr;
		return;
	}
	*/

	//copy the next node into current and update the next pointer to point to
	//next->next and then delete the next.  Essentially overwrite the current
	//when next and delete next which is essentially deleting the current node
	//without using a prev pointer.
	Node* nextNode = n->next;

	//At the tail so just delete and return
	if (!nextNode){
		delete n;
		n = nullptr;
		return;
	}

	n->next = nextNode->next;
	n->data = nextNode->data;

	delete nextNode;
	nextNode = nullptr;
}

//Inserts at newNode after position n
void SimpleList::insert_at(Node* n, Node* newNode)
{
	if (!n || !newNode)
		return;

	//at the tail
	if (!n->next){
		n->next = newNode;
		newNode->next = nullptr;
		return;
	}

	Node* temp = n->next;
	n->next = newNode;
	newNode->next = temp;
}
	
Node* SimpleList::find(int x) {
	if (!head)
		return nullptr;
	Node* curr = head;
	while (curr->data != x){
		curr = curr->next;
	}

	return curr;
}

int main() {
	
	SimpleList s;
	s.push_front(1);	// 1
	s.push_front(2);	// 2 -> 1
	s.push_back(5);		// 2 -> 1 -> 5
	s.pop_back();		// 2-> 1
	s.pop_front();		// 1
	s.pop_back();		// <empty>

	s.push_back(1);		// 1
	s.push_back(2);		// 1 -> 2
	s.push_back(3);		// 1 -> 2 -> 3
	s.push_back(4);		// 1 -> 2 -> 3 -> 4

	Node* n = s.find(2);
	s.delete_at(n);		// 1 -> 3 -> 4

	//Will be delete by the list's destructor
	Node* newNode1 = new Node(5);
	Node* newNode2 = new Node(6);
	
	n = s.find(3);
	s.insert_at(n, newNode1);	// 1 -> 3 -> 5 -> 4

	n = s.find(4);
	s.insert_at(n, newNode2);	// 1 -> 5 -> 3 -> 4 -> 6

	return 0;
}