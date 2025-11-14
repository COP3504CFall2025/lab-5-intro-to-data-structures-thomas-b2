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
	Node<T>::Node* getHead() {
		return head;
	}
	const Node<T>::Node* getHead() const {
		return head;
	}
	Node<T>::Node* getTail() {
		return tail;
	}
	const Node<T>::Node* getTail() const {
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
		head->prev = nullptr;
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
		for (Node<T>* node = head; node != nullptr; node = node->next) {
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
	Node<T>::Node* head;
	Node<T>::Node* tail;
	unsigned int count{};

};

/*template<typename T>
void LinkedList<T>::addHead(const T &data) {
	Node<T>* newNode = new Node<T>(data);
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

template<typename T>
void LinkedList<T>::addTail(const T &data) {
	Node<T>* newNode = new Node<T>(data);
	newNode->next = nullptr;
	newNode->prev = tail;
	if (tail != nullptr) {
		tail->next = newNode;
	}
	else {
		head = newNode;
	}
	tail = newNode;
	count++;
}

template<typename T>
bool LinkedList<T>::removeHead() {
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
	head->prev = nullptr;
	delete temp;
	count--;
	return true;
}

template<typename T>
bool LinkedList<T>::removeTail() {
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

template<typename T>
void LinkedList<T>::Clear() {
	for (Node<T>* node = head; node != nullptr; node = node->next) {
		delete node;
	}
	head = nullptr;
	tail = nullptr;
	count = 0;
}

template<typename T>
unsigned int LinkedList<T>::getCount() const {
	return count;
}

template<typename T>
Node<T>* LinkedList<T>::getHead() const{
	return head;
}

template<typename T>
const Node<T>::Node* LinkedList<T>::getHead() const {
	return head;
}

template<typename T>
Node<T>::Node* LinkedList<T>::getTail() {
	return tail;
}

template<typename T>
const Node<T>::Node* LinkedList<T>::getTail() const {
	return tail;
}

template<typename T>
void LinkedList<T>::printForward() const {
	for (Node<T>* node = head; node != nullptr; node = node->next) {
		std::cout << node->data << " ";
	}
}

template<typename T>
void LinkedList<T>::printReverse() const {
	for (Node<T>* node = tail; node != nullptr; node = node->prev) {
		std::cout << node->data << " ";
	}
}

template<typename T>
LinkedList<T>::LinkedList() {
	head = nullptr;
	tail = nullptr;
	count = 0;
}

template<typename T>
LinkedList<T>::LinkedList(const LinkedList<T>& list) { //copy
	Clear();
	for (Node<T>* node = list.head; node != nullptr; node = node->next) {
		addTail(node->data);
	}
}

template<typename T>
LinkedList<T>& LinkedList<T>::operator=(const LinkedList<T> &rhs) { //copy assignment
	if (this == &rhs) {
		return *this;
	}
	Clear();
	for (Node<T>* node = head; node != nullptr; node = node->next) {
		addTail(node->data);
	}
	return *this;
}

template<typename T>
LinkedList<T>::LinkedList(LinkedList<T>&& other) noexcept { //move
	head = other.head;
	tail = other.tail;
	count = other.count;

	other.head = nullptr;
	other.tail = nullptr;
	other.count = 0;
}

template<typename T>
LinkedList<T>& LinkedList<T>::operator=(LinkedList<T>&& other) noexcept {
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

template<typename T>
LinkedList<T>::~LinkedList() {
	Clear();
}*/







