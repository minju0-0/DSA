#include <iostream>
using namespace std;

// ------------------- NODE ADT -------------------
struct node {
    int elem;
    struct node* next;
};

// ------------------- LIST ADT -------------------
class list {
public:
    virtual void enqueue(int num) = 0;
    virtual int dequeue() = 0;
    virtual int first() = 0;
    virtual void print() = 0;
};

// ------------------- QUEUE IMPLEMENTATION -------------------
class Queue : public list {
private:
    struct node* head;
    int size;

public:
    Queue() {
        head = nullptr;
        size = 0;
    }

    void enqueue(int num) override {
        struct node* n = new node();
        n->elem = num;

        if (!head) {
            head = n;
            head->next = nullptr;
        } else {
            struct node* curr = head;
            while (curr->next) {
                curr = curr->next;
            }
            curr->next = n;
            n->next = nullptr;
        }
        size++;
    }

    int dequeue() override {
        if (!head) {
            cout << "Queue Underflow!" << endl;
            return -1;
        }
        int val = head->elem;
        struct node* temp = head;
        head = head->next;
        delete temp;
        size--;
        return val;
    }

    int first() override {
        if (!head) {
            cout << "Queue is empty!" << endl;
            return -1;
        }
        return head->elem;
    }

    void print() override {
        cout << "Queue: ";
        struct node* curr = head;
        for (int i = 0; i < size; i++) {
            cout << curr->elem << " -> ";
            curr = curr->next;
        }
        cout << "NULL" << endl;
    }
};

// ------------------- MAIN PROGRAM -------------------
int main() {
    Queue q;
    int choice, val;

    do {
        cout << "\n--- Queue Menu ---\n";
        cout << "1. Enqueue\n";
        cout << "2. Dequeue\n";
        cout << "3. First element\n";
        cout << "4. Display Queue\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter value: ";
                cin >> val;
                q.enqueue(val);
                break;
            case 2:
                val = q.dequeue();
                if (val != -1) cout << "Dequeued: " << val << endl;
                break;
            case 3:
                val = q.first();
                if (val != -1) cout << "First element: " << val << endl;
                break;
            case 4:
                q.print();
                break;
            case 5:
                cout << "Exiting program..." << endl;
                break;
            default:
                cout << "Invalid choice! Try again.\n";
        }
    } while (choice != 5);

    return 0;
}
