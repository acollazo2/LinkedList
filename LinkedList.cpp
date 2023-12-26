#include <iostream>
#include <string>
#include <sstream>


template<typename T>
class LinkedList
{
private:
	class Node
	{
		public:
			T element;
			Node* next = nullptr;

			Node(T element) : element(element){}
	};

	Node* head = nullptr;
	Node* tail = nullptr;
	size_t m_size = 0;

public:

	LinkedList(){}

	LinkedList(std::initializer_list<T> initList)
	{
		for (auto element: initList)
			this->append(element);
	}

	LinkedList(const LinkedList& other) // Copy contructor
	{
		Node* current = other.head;
		for (size_t i = 0; i < other.size(); i++)
		{
			this->append(current->element);
			current = current->next;
		}

	}

	LinkedList(LinkedList&& other) noexcept // rvalue move
	{
		this->head = other.head;
		this->tail = other.tail;

		other.head = nullptr;
		other.tail = nullptr;
		other.size = 0;
	}
	
	void append(T element)
	{
		Node* newNode = new Node(element);

		if (tail == nullptr) // If linkedlist is empty
			head = tail = newNode;
		else
		{
			tail->next = newNode;
			tail = newNode;
		}

		m_size++;
	}

	void addFirst(T element)
	{
		Node* newNode = new Node(element); // Create new node somewhere in space
		newNode->next = head; // Bascially "copy" our existing linked structure into newNode
		head = newNode; // Make newNode the new head;
		m_size++;

		if (tail == nullptr) // newNode is only node in list, happens if an emtpy list was made and insert(T, 0) or addFirst() was called
			tail = head; // tail and head now point to this only node

	}

	void insert(T element, const int index)
	{
		if (index == 0)
			addFirst(element);
		else if (index >= m_size)
			append(element);
		else
		{
			Node* current = head;

			for (int i = 0; i < index-1; i++)
				current = current->next;

			Node* temp = current->next;
			current->next = new Node(element);
			(current->next)->next = temp;

			m_size++;
		}

	}

	void pop()
	{
		if (head == tail) // If there is only one node or no nodes. We could also check if m_size==0 or m_size==1
		{
			deleteFirst();
			return;
		}

		Node* current = head;

		for (size_t i = 0; i < m_size-2; i++)
			current = current->next;

		delete current->next;
		current->next = nullptr;
		tail = current;
		m_size--;
	}

	void deleteFirst()
	{
		if (m_size == 0 || m_size == 1)
		{
			delete head;
			head = nullptr;
			tail = nullptr;
			m_size = 0;
			return;
		}
		Node* temp = head->next;
		delete head; // We delete the object head pointed to. head however still exists and now points to a freed piece of memory
		head = temp;
		m_size--;
	}

	void deleteAt(const int index)
	{
		if (index == 0)
			deleteFirst();
		else if (index >= (m_size-1))
			pop();
		else
		{
			Node* current = head;
			for (int i = 0; i < index-1; i++)
			{
				current = current->next;
			}

			Node* temp = (current->next)->next;
			delete current->next;
			current->next = temp;
			m_size--;


		}
	}

	void clear()
	{
		while (this->size() != 0)
		{
			this->pop();
		}
	}

	T& get(const size_t& index)
	{
		Node* current = head;

		for (int i = 0; i < index; i++)
			current = current->next;

		return current->element;
	}

	void print()
	{
		std::stringstream ss;
		ss << "[";

		Node* current = head;
		if (current == nullptr)
		{
			std::cout << "[]" << std::endl;
			return;
		}

		for (int i = 0; i < m_size; i++)
		{
			ss << current->element;
			current = current->next;

			if (current != nullptr)
				ss << ", ";
			else
				//ss << "]";
				break;

		}
		ss << "]"; //

		std::string result = ss.str();
		std::cout << result << std::endl;
	}

	size_t size() const
	{
		return m_size;
	}

	T& operator[](size_t index) // Return a reference so we can have it on the left side of an assignment
	{
		return get(index);
	}
	const T& operator[](size_t index) const // For if we have a const instance of the class
	{
		return get(index);
	}

	~LinkedList()
	{
		clear();
	}
};