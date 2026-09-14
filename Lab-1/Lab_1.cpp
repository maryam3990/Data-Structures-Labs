#include<iostream>
using namespace std;

template<class T>
class List
{
private:
	class Node;
	Node* head;

public:
	List() : head(nullptr) {}
	void insertAtStart(T const& data)
	{
		Node* newNode = new Node(data);
		Node* temp = head;
		newNode->next = temp;
		head = newNode;
	}
	Node* getHead()
	{
		return head;
	}
	void insertAtEnd(T const& data)
	{
		Node* newNode = new Node(data);
		Node* temp = head;
		if (head == nullptr)
		{
			head = newNode;
			return;
		}

		while (temp->next != nullptr)
		{
			temp = temp->next;
		}
		temp->next = newNode;
	}

	void print()

	{
		Node* temp = head;
		while (temp != nullptr)
		{
			cout << temp->val << "->";
			temp = temp->next;
		}
		cout << "nullptr\n";
	}
	bool search(T const& element) const
	{
		Node* temp = head;
		while (temp != nullptr)
		{
			if (temp->val == element) return true;
			temp = temp->next;
		}
		return false;
	}

	bool isEmpty()
	{
		return head == nullptr;
	}

	bool insertBefore(T const& v1, T const& v2)
	{
		if (head == nullptr) return false;
		if (head->val == v2)
		{
			insertAtStart(v1);
			return true;
		}
		Node* temp = head;
		while (temp != nullptr)
		{
			if (temp->next->val == v2)
			{
				Node* newNode = new Node(v1);
				newNode->next = temp->next;
				temp->next = newNode;
				return true;
			}
			temp = temp->next;
		}
		return false;
	}
	~List()
	{
		Node* temp = head;
		while (temp != nullptr)
		{
			head = temp->next;
			delete temp;
			temp = head;
		}
	}

	void deleteDupliates()
	{
		Node* temp = head;
		while (temp != nullptr)
		{
			Node* temp2 = temp;
			while (temp2->next != nullptr)
			{
				if (temp2->next->val == temp->val)
				{
					Node* toBeDeleted = temp2->next;
					temp2->next = toBeDeleted->next;
					delete toBeDeleted;
				}
				else
					temp2 = temp2->next;
			}
			temp = temp->next;

		}
	}

	bool deleteInRange(const T& a, const T& b)
	{
		while (head != nullptr && head->val >= a && head->val < b)
		{
			Node* TBD = head;
			head = head->next;
			delete TBD;
		}
		if (head == nullptr) return true;
		Node* temp = head;
		while (temp->next != nullptr)
		{
			if (temp->next->next == nullptr) return true;
			if (temp->next->val >= a && temp->next->val < b)
			{
				Node* TBD = temp->next;
				temp->next = TBD->next;
				delete TBD;
			}
			else temp = temp->next;
		}
		return true;

	}


	void merge(List* l2)
	{
		if (l2 == nullptr || l2->head == nullptr) return;

		if (head == nullptr) {
			head = l2->head;
			l2->head = nullptr;
			return;
		}

		Node* l1 = head;
		Node* start = nullptr;
		Node* t1 = l1;
		Node* t2 = l2->head;

		if (t1->val < t2->val)
		{
			start = t1;
			t1 = t1->next;
		}
		else
		{
			start = t2;
			t2 = t2->next;
		}
		Node* temp = start;
		{
			while (t1 != nullptr || t2 != nullptr)
			{

				if ((t1 != nullptr && t2 != nullptr && t1->val < t2->val) || (t2 == nullptr && t1 != nullptr))
				{
					temp->next = t1;
					t1 = t1->next;
					temp = temp->next;
				}
				else if ((t1 != nullptr && t2 != nullptr && t2->val <= t1->val) || (t1 == nullptr && t2 != nullptr))
				{
					temp->next = t2;
					t2 = t2->next;
					temp = temp->next;
				}
			}

			l2->head = nullptr;
			head = start;
		}

	}
};
template<class T>
class List<T>::Node
{
public:
	T val;
	Node* next;
	Node(T data, Node* ptr = 0)
	{
		val = data;
		next = ptr;
	}
	T getData()
	{
		return val;
	}
};

int main()
{
	List<int> l1;
	l1.insertAtEnd(13);
	l1.insertAtEnd(15);
	l1.insertBefore(15, 15);
	l1.insertAtStart(10);
	l1.insertBefore(13, 10);
	l1.insertAtEnd(10);
	l1.print();
	l1.deleteDupliates();
	l1.print();

	List<int> l2;
	l2.insertAtEnd(1001);
	l2.insertAtEnd(1005);
	l2.insertAtEnd(1007);
	l2.insertAtEnd(1010);
	l2.insertAtEnd(1013);
	l2.insertAtEnd(1017);
	l2.insertAtEnd(1013);
	l2.print();
	l2.deleteInRange(1005, 1017);
	l2.print();

	List<int> l3;
	l3.insertAtEnd(1);
	l3.insertAtEnd(5);
	l3.insertAtEnd(6);

	List<int> l5;
	l5.insertAtEnd(3);
	l5.insertAtEnd(4);
	l5.insertAtEnd(8);

	List<int>* l4 = &l5;

	l3.merge(l4);
	l3.print();
}