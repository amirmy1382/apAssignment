#include <iostream>
#include <string>

using namespace std;

template <typename T>
class LinkedList {
private:
    class Node {
    public:
        T data;
        Node* next;

        Node(const T& data, Node* next = nullptr)
                : data(data), next(next) {}
    };

    Node* head;

    void copy_from(const LinkedList<T>& other) {
        clear();
        if (!other.head) return;

        head = new Node(other.head->data);
        Node* current = head;
        Node* other_current = other.head->next;

        while (other_current) {
            current->next = new Node(other_current->data);
            current = current->next;
            other_current = other_current->next;
        }
    }

public:
    LinkedList() : head(nullptr) {}

    ~LinkedList() {
        clear();
    }

    void push_front(const T& value) {
        head = new Node(value, head);
    }

    void push_back(const T& value) {
        if (!head) {
            head = new Node(value);
            return;
        }
        Node* current = head;
        while (current->next) {
            current = current->next;
        }
        current->next = new Node(value);
    }

    void pop_front() {
        if (!head) return;
        Node* temp = head;
        head = head->next;
        delete temp;
    }

    void pop_back() {
        if (!head) return;
        if (!head->next) {
            delete head;
            head = nullptr;
            return;
        }
        Node* current = head;
        while (current->next && current->next->next) {
            current = current->next;
        }
        delete current->next;
        current->next = nullptr;
    }

    bool is_empty() const {
        return head == nullptr;
    }

    void clear() {
        while (head) {
            pop_front();
        }
    }

    void print() const {
        Node* current = head;
        while (current) {
            std::cout << current->data << " ";
            current = current->next;
        }
        std::cout << std::endl;
    }

    bool remove(const T& value) {
        if (!head) return false;
        if (head->data == value) {
            pop_front();
            return true;
        }

        Node* current = head;
        while (current->next && current->next->data != value) {
            current = current->next;
        }

        if (current->next) {
            Node* temp = current->next;
            current->next = temp->next;
            delete temp;
            return true;
        }

        return false;
    }

    int size() const {
        int count = 0;
        Node* current = head;
        while (current) {
            ++count;
            current = current->next;
        }
        return count;
    }

    bool contains(const T& value) const {
        Node* current = head;
        while (current) {
            if (current->data == value)
                return true;
            current = current->next;
        }
        return false;
    }

    T& front() const {
        if (!head) throw std::runtime_error("Empty list");
        return head->data;
    }

    T& back() const {
        if (!head) throw std::runtime_error("Empty list");
        Node* current = head;
        while (current->next) {
            current = current->next;
        }
        return current->data;
    }
};

// -------------------- Stack --------------------

template <typename T>
class Stack {
private:
    LinkedList<T> list;

public:
    void push(const T& value) {
        list.push_front(value);
    }

    void pop() {
        if (list.is_empty()) throw std::runtime_error("Stack underflow");
        list.pop_front();
    }

    T& top() const {
        if (list.is_empty()) throw std::runtime_error("Stack is empty");
        return list.front(); // یا دسترسی به front مستقیماً
    }

    bool is_empty() const {
        return list.is_empty();
    }

    int size() const {
        return list.size();
    }

    void print() const {
        list.print();
    }
};

// -------------------- Queue --------------------

template <typename T>
class Queue {
private:
    LinkedList<T> list;

public:
    void enqueue(const T& value) {
        list.push_back(value);
    }

    void dequeue() {
        if (list.is_empty()) throw std::runtime_error("Queue underflow");
        list.pop_front();
    }

    T& front() const {
        if (list.is_empty()) throw std::runtime_error("Queue is empty");
        return list.front();
    }

    bool is_empty() const {
        return list.is_empty();
    }

    int size() const {
        return list.size();
    }

    void print() const {
        list.print();
    }
};

int main() {
    cout << "===== LinkedList Test =====\n";
    LinkedList<string> names;
    names.push_back("Ali");
    names.push_front("Zahra");
    names.push_back("Reza");
    names.print(); // Zahra Ali Reza
    cout << "Size: " << names.size() << endl; 

    cout << "Contains 'Ali'? " << (names.contains("Ali") ? "Yes" : "No") << endl;

    cout << "===== Stack Test =====\n";
    Stack<int> stack;
    stack.push(10);
    stack.push(20);
    stack.push(30);
    stack.print(); // 30 20 10
    cout << "Top: " << stack.top() << endl;
    stack.pop();
    stack.print();

    cout << "===== Queue Test =====\n";
    Queue<std::string> queue;
    queue.enqueue("first");
    queue.enqueue("second");
    queue.enqueue("third");
    queue.print();
    cout << "Front: " << queue.front() << endl;
    queue.dequeue();
    queue.print();

    return 0;
}
