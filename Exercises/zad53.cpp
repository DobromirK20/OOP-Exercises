#include <iostream>
#include <cstring>
using namespace std;

class LinkedList
{
private:
    class Node
    {
    public:
        int data;
        Node* next;

        Node(int value) {
            data = value;
            next = nullptr;
        }
    };

    Node* first;
    Node* last;
public:
    class Iterator
    {
    private:
        Node* cur;
    public:
        Iterator(Node* c = nullptr) {
            cur = c;
        }

        int& operator*() {
            return cur->data;
        }

        Iterator& operator++() {
            cur = cur->next;
            return *this;
        }

        bool operator!=(const Iterator& other) const {
            return cur != other.cur;
        }
    };
    
    LinkedList() {
        first = nullptr;
        last = nullptr;
    }

    ~LinkedList() {
        Node* current = first;

        while (current != nullptr) {
            Node* next = current->next;
            delete current;
            current = next;
        }
    }

    void push_back(int value) {
        Node* newNode = new Node(value);

        if (first == nullptr) {
            first = newNode;
            last = newNode;
        } else {
            last->next = newNode;
            last = newNode;
        }
    }
    
    Iterator begin() {
        return Iterator(first);
    }

    Iterator end() {
        return Iterator(nullptr);

    }
};

int main() {
    LinkedList list;

    list.push_back(1);
    list.push_back(2);
    list.push_back(3);

    for (int val : list) {
        cout << val << " ";
    }

    return 0;
}