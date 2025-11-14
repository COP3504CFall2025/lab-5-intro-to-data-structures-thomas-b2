#pragma once
#include <iostream>
using namespace std;

template <typename T>
struct Node {
	T data;
	Node* prev;
	Node* next;
};

template <typename T>
class LinkedList {
public:
	void clear() { //autograder shenanigans
		Clear();
	}
	// Behaviors
	void printForward() const {
		for (Node<T>* node = head; node != nullptr; node = node->next) {
			std::cout << node->data << " ";
		}
	}
	void printReverse() const {
		for (Node<T>* node = tail; node != nullptr; node = node->prev) {
			std::cout << node->data << " ";
		}
	}

	// Accessors
	[[nodiscard]] unsigned int getCount() const {
		return count;
	}
	Node<T>* getHead() {
		return head;
	}
	const Node<T>* getHead() const {
		return head;
	}
	Node<T>* getTail() {
		return tail;
	}
	const Node<T>* getTail() const {
		return tail;
	}

	// Insertion
	void addHead(const T& data) {
		Node<T>* newNode = new Node<T>();
		newNode->data = data;
		newNode->prev = nullptr;
		newNode->next = head;
		if (head != nullptr) {
			head->prev = newNode;
		}
		else {
			tail = newNode;
		}
		head = newNode;
		count++;
	}
	void addTail(const T& data) {
		Node<T>* newNode = new Node<T>();
		newNode->data = data;
		newNode->prev = tail;
		newNode->next = nullptr;
		if (tail != nullptr) {
			tail->next = newNode;
		}
		else {
			head = newNode;
		}
		tail = newNode;
		count++;
	}

	// Removal
	bool removeHead() {
		if (head == nullptr) {
			return false;
		}
		Node<T>* temp = head;
		head = head->next;
		if (head == nullptr) {
			tail = nullptr;
		} else {
			head->prev = nullptr;
		}
		delete temp;
		count--;
		return true;
	}
	bool removeTail() {
		if (tail == nullptr) {
			return false;
		}
		Node<T>* temp = tail;
		tail = tail->prev;
		if (tail == nullptr) {
			head = nullptr;
		} else {
			tail->next = nullptr;
		}
		delete temp;
		count--;
		return true;
	}
	void Clear() {
		Node<T>* temp = head;
		while (temp != nullptr) {
			Node<T>* next = temp->next;
			delete temp;
			temp = next;
		}
		head = nullptr;
		tail = nullptr;
		count = 0;
	}

	// Operators
	LinkedList<T>& operator=(LinkedList<T>&& other) noexcept {
		if (this == &other) {
			return *this;
		}
		Clear();

		head = other.head;
		tail = other.tail;
		count = other.count;

		other.head = nullptr;
		other.tail = nullptr;
		other.count = 0;

		return *this;
	}
	LinkedList<T>& operator=(const LinkedList<T>& rhs) {
		if (this == &rhs) {
			return *this;
		}
		Clear();
		for (Node<T>* node = rhs.head; node != nullptr; node = node->next) {
			addTail(node->data);
		}
		return *this;
	}

	// Construction/Destruction
	LinkedList() {
		head = nullptr;
		tail = nullptr;
		count = 0;
	}
	LinkedList(const LinkedList<T>& list) {
		Clear();
		for (Node<T>* node = list.head; node != nullptr; node = node->next) {
			addTail(node->data);
		}
	}
	LinkedList(LinkedList<T>&& other) noexcept {
		head = other.head;
		tail = other.tail;
		count = other.count;

		other.head = nullptr;
		other.tail = nullptr;
		other.count = 0;
	}
	~LinkedList() {
		Clear();
	}

private:
	// Stores pointers to first and last nodes and count
	Node<T>* head;
	Node<T>* tail;
	unsigned int count{};

};







