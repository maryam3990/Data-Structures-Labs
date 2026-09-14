#include<iostream>
using namespace std;

template<class T>
class DoublyLinkedList
{
private:
    class Node;
    Node* head;
    Node* tail;
    int size;

public:
    DoublyLinkedList()
    {
        head = tail = nullptr;
        size = 0;
    }
    void InsertAtStart(T val) //o(1)
    {
        ++size;
        Node* newNode = new Node(val);
        if (head == nullptr)
        {
            head = tail = newNode;

            return;
        }

        newNode->next = head;
        head->prev = newNode;
        head = newNode;

    }
    void InsertAtEnd(T val) //o(1)
    {
        ++size;
        Node* newNode = new Node(val);
        if (head == nullptr)
        {
            head = tail = newNode;
            return;

        }
        newNode->prev = tail;
        tail->next = newNode;
        tail = newNode;

    }
    void InsertAtPosition(T val, int pos) //o(n)
    {
        if (pos < 1)
            return;
        if (pos == 1)
        {
            InsertAtStart(val);
            return;
        }
        Node* temp = head;
        for (int i = 0; i < pos - 2; i++)
        {
            temp = temp->next;
            if (temp == nullptr) return;
        }
        if (temp == tail)
        {
            InsertAtEnd(val);
            return;
        }
        Node* newNode = new Node(val);
        newNode->next = temp->next;
        temp->next->prev = newNode;
        temp->next = newNode;
        newNode->prev = temp;
        ++size;
    }

    void print() //o(n)
    {
        Node* temp = head;
        while (temp != nullptr)
        {
            cout << temp->val << "->";
            temp = temp->next;
        }
        cout << "nullptr" << endl;
    }
    void removeFromHead() //o(1)
    {
        if (head == nullptr) return;
        if (head == tail)
        {
            delete head;
            head = tail = nullptr;
            --size;
            return;
        }
        Node* temp = head->next;
        delete head;
        head = temp;
        head->prev = nullptr;
        --size;
    }
    void removeFromTail() //o(1)
    {
        if (head == nullptr) return;
        if (head == tail)
        {
            delete head;
            head = tail = nullptr;
            --size;
            return;
        }
        Node* temp = tail->prev;
        delete tail;
        tail = temp;
        tail->next = nullptr;
        --size;
    }
    void removeSpecifiedId(T val) //o(n)
    {
        Node* temp = head;
        while (temp != nullptr)
        {
            if (temp->val == val && temp == head)
            {
                removeFromHead();
                return;
            }
            if (temp->val == val && temp == tail)
            {
                removeFromTail();
                return;
            }
            if (temp->val == val)
            {
                temp->prev->next = temp->next;
                temp->next->prev = temp->prev;
                delete temp;
                --size;
                return;
            }
            temp = temp->next;
        }
    }
    void transverseForward() //o(n)
    {
        Node* temp = head;
        while (temp != nullptr)
        {
            cout << temp->val << "->";
            temp = temp->next;
        }
        cout << "nullptr" << endl;
    }

    void transverseBackward() //o(n)
    {
        Node* temp = tail;
        while (temp != nullptr)
        {
            cout << temp->val << "->";
            temp = temp->prev;
        }
        cout << "nullptr" << endl;
    }

    int posOfAnElement(T val) //o(n)
    {
        Node* temp = head;
        int i = 1;
        while (temp != nullptr)
        {
            if (temp->val == val) return i;
            temp = temp->next;
            ++i;
        }
        return -1;
    }
    int totalNodes() //o(1)
    {
        return size;
    }

    void displayCurrent(T val) //o(n)
    {
        Node* temp = head;
        while (temp != nullptr)
        {
            if (temp->val == val)
            {
                cout << "current->val: " << temp->val << endl;
                if (temp->next != nullptr)
                {
                    temp = temp->next;
                    cout << "current->next: " << temp->val << endl;
                }
                else
                {
                    cout << "current->next: nullptr" << endl;
                }
                if (temp->prev->prev != nullptr)
                {
                    temp = temp->prev->prev;
                    cout << "current->prev: " << temp->val << endl;
                    temp = temp->next;
                }
                else
                {
                    cout << "current->prev: nullptr" << endl;
                }
                return;
            }
            temp = temp->next;
        }
        cout << "Not Found" << endl;
    }

    bool middle(T& result) //o(n)
    {
        if (head == nullptr) return false;
        if (head == tail)
        {
            result = head->val;
            return true;
        }
        Node* slow = head;
        Node* fast = head;
        while (fast != nullptr && fast->next != nullptr)
        {
            slow = slow->next;
            fast = fast->next->next;
        }
        if (fast == nullptr) slow = slow->prev;
        result = slow->val;
        return true;
    }
    void insertInSortedOrder(T val) //o(n)
    {
        if (head == nullptr)
        {
            InsertAtStart(val);
            return;
        }
        Node* temp = head;
        while (temp != nullptr)
        {
            if (val < temp->val && temp == head)
            {
                InsertAtStart(val);
                return;
            }
            if (val < temp->val)
            {
                Node* newNode = new Node(val);
                newNode->next = temp;
                newNode->prev = temp->prev;
                temp->prev->next = newNode;
                temp->prev = newNode;
                ++size;
                return;
            }
            temp = temp->next;
        }
        InsertAtEnd(val);
    }
    void reverseList() //o(n)
    {
        if (head == nullptr || head == tail) return;

        Node* current = head;
        Node* prev_ptr = nullptr;
        Node* next_ptr = nullptr;
        while (current != nullptr)
        {
            next_ptr = current->next;
            current->next = prev_ptr;
            current->prev = next_ptr;
            prev_ptr = current;
            current = next_ptr;
        }
        tail = head ;
        head = prev_ptr;
    }

    void removeDuplicates() //o(n)
    {
        if (head == nullptr || head->next == nullptr) return;
        Node* temp = head;
        while (temp->next != nullptr)
        {
            if (temp->next->val == temp->val)
            {
                Node* x = temp->next;
                temp->next = x->next;
                if (temp->next != nullptr)
                {
                    x->next->prev = temp;
                }
                if (x == tail)
                {
                    tail = tail->prev;
                }
                delete x;
                --size;
            }
            else { temp = temp->next; }
        }
    }


    int merge(DoublyLinkedList* l1) //o(n+m)
    { 
        if (l1 == nullptr || l1->head == nullptr) return size;
        if (head == nullptr)
        {
            size = l1->size;
            head = l1->head;
            tail = l1->tail;
            return l1->size;
        }

        Node* h1 = l1->head;
        int x = 0;
        Node* t1 = head;
        Node* t2 = h1;

        Node* start = nullptr;
        Node* temp = start;
        if (t1->val < t2->val)
        {
            start = t1;
            t1 = t1->next;
            ++x;
        }
        else
        {
            start = t2;
            t2 = t2->next;
            ++x;
        }
        temp = start;

        while (t1 != nullptr || t2 != nullptr)
        {
            if ((t1 != nullptr && t2 != nullptr && t1->val < t2->val) || (t2 == nullptr && t1 != nullptr))
            {
                temp->next = t1;
                t1->prev = temp;
                temp = t1;
                t1 = t1->next;
                ++x;
            }
            else if ((t1 != nullptr && t2 != nullptr && t1->val >= t2->val) || (t1 == nullptr && t2 != nullptr))
            {
                temp->next = t2;
                t2->prev = temp;
                temp = t2;
                t2 = t2->next;
                ++x;
            }
        }
        tail = temp;
        tail->next = nullptr;
        head = start;
        l1->size = 0;
        l1->head = l1->tail = nullptr;
        return x;
    }
    void unionOfLists(DoublyLinkedList* l1) //o(n+m)
    {
        if (l1 == nullptr) return;
        size = merge(l1); 
        removeDuplicates(); 
    }
    int lastOccurence(T val) //o(n)
    {
        Node* temp = tail;
        int pos = 0;
        while (temp != nullptr)
        {
            if (temp->val == val)
            {
                return size - pos;
            }
            temp = temp->prev;
            ++pos;
        }
        return -1;
    }
    void swap(T& a, T& b) //o(1)
    {
        T temp = a;
        a = b;
        b = temp;
    }
    void selectionSort() //o(n*n)
    {
        if (head == nullptr) return;
        if (head->next == nullptr) return;
        Node* temp1 = head;
        while (temp1 != nullptr)
        {
            Node* temp2 = temp1->next;
            Node* Min = temp1;
            while (temp2 != nullptr)
            {
                if (temp2->val < Min->val)
                {
                    Min = temp2;
                }
                temp2 = temp2->next;
            }
            swap(temp1->val, Min->val);
            temp1 = temp1->next;
        }
    }
    ~DoublyLinkedList() //o(n)
    {
        Node* temp = head;
        while (temp != nullptr)
        {
            Node* nextNode = temp->next;
            delete temp;
            temp = nextNode;
        }
        head = tail = nullptr;
        size = 0;
    }
};
template<class T>
class DoublyLinkedList<T>::Node
{
public:
    T val;
    Node* next;
    Node* prev;
    Node(T data, Node* next = nullptr, Node* prev = nullptr)
        :val(data), next(next), prev(prev)
    {
    }
};

int main()
{
    DoublyLinkedList<int> list;
    cout << "1. insert at start" << endl;
    cout << "inserting id: 30" << endl;
    list.InsertAtStart(30);
    cout << "list: "; list.print();
    cout << endl;
    cout << "inserting id: 20" << endl;
    list.InsertAtStart(20);
    cout << "list: "; list.print();
    cout << endl;
    cout << "inserting id: 10" << endl;
    list.InsertAtStart(10);
    cout << "list: "; list.print();
    cout << endl;
    cout << "2. insert at end" << endl;
    cout << "inserting id: 40" << endl;
    list.InsertAtEnd(40);
    cout << "list: "; list.print();
    cout << endl;
    cout << "inserting id: 50" << endl;
    list.InsertAtEnd(50);
    cout << "list: "; list.print();
    cout << endl;
    cout << "3. insert at specific position" << endl;
    cout << "inserting id: 25 at position 3" << endl << endl;
    list.InsertAtPosition(25, 3);
    cout << "list:" << endl;
    list.print();
    cout << endl;
    cout << "4. remove from head" << endl;
    cout << "removed id: 10" << endl << endl;
    list.removeFromHead();
    cout << "list:" << endl;
    list.print();
    cout << endl;
    cout << "5. remove from tail" << endl;
    cout << "removed id: 50" << endl << endl;
    list.removeFromTail();
    cout << "list:" << endl;
    list.print();
    cout << endl;
    cout << "6. remove a specific id" << endl;
    cout << "enter id to remove: 25" << endl << endl;
    cout << "id 25 found and removed." << endl << endl;
    list.removeSpecifiedId(25);
    cout << "list:" << endl;
    list.print();
    cout << endl;
    cout << "7. traverse list forward" << endl;
    list.transverseForward();
    cout << endl;
    cout << "8. traverse list backward" << endl;
    list.transverseBackward();
    cout << endl;
    cout << "9. search specific id" << endl;
    cout << "enter id to search: 40" << endl << endl;
    cout << "id 40 found at position: " << list.posOfAnElement(40) << endl;
    cout << "10. count total number of nodes" << endl;
    cout << "total number of nodes: " << list.totalNodes() << endl;
    cout << "11. currently selected id" << endl;
    list.displayCurrent(20);
    cout << endl;
    cout << "12. return middle of the list" << endl;
    cout << "list:" << endl;
    list.print();
    int midVal;
    if (list.middle(midVal))
    {
        cout << "middle node id: " << midVal << endl << endl;
    }
    cout << "13. sort the list" << endl;
    DoublyLinkedList<int> l1;
    l1.InsertAtEnd(40);
    l1.InsertAtEnd(10);
    l1.InsertAtEnd(30);
    l1.InsertAtEnd(20);
    l1.InsertAtEnd(50);

    cout << "before sorting:" << endl;
    l1.print();
    cout << endl;
    l1.selectionSort();
    cout << "after selection sort:" << endl;
    l1.print();
    cout << endl;
    cout << "14. insert in sorted order" << endl;
    DoublyLinkedList<int> l2;
    l2.InsertAtEnd(10);
    l2.InsertAtEnd(20);
    l2.InsertAtEnd(30);
    l2.InsertAtEnd(40);
    cout << "sorted list:" << endl;
    l2.print();
    cout << endl;
    cout << "inserting id: 25" << endl << endl;
    l2.insertInSortedOrder(25);
    cout << "after sorted insertion:" << endl;
    l2.print();
    cout << endl;
    cout << "15. reverse the list" << endl;
    cout << "before reversing:" << endl;
    l2.print();
    cout << endl;
    l2.reverseList();
    cout << "after reversing:" << endl;
    l2.print();
    cout << endl;
    cout << "16. union of two lists" << endl;
    DoublyLinkedList<int> l3;
    l3.InsertAtEnd(10);
    l3.InsertAtEnd(20);
    l3.InsertAtEnd(30);
    l3.InsertAtEnd(40);
    DoublyLinkedList<int> l4;
    l4.InsertAtEnd(30);
    l4.InsertAtEnd(40);
    l4.InsertAtEnd(50);
    l4.InsertAtEnd(60);
    cout << "list 1:" << endl;
    l3.print();
    cout << endl;
    cout << "list 2:" << endl;
    l4.print();
    cout << endl;
    cout << "union of list 1 and list 2:" << endl;
    l3.unionOfLists(&l4);
    l3.print();
    cout << endl;
    cout << "duplicate ids removed." << endl << endl;
    cout << "17. print list" << endl;
    cout << "current doubly linked list:" << endl;
    l1.print();
    cout << endl;
    cout << "18. find last occurence" << endl;
    cout << "list:" << endl;
    list.print();
    cout << endl;
    cout << "enter id: 20" << endl << endl;
    cout << "last occurrence of id 20 is at position: " << list.lastOccurence(20) << endl;
}