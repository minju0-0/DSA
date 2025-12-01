#include <iostream>
#include "SllList.hpp"
#include "Sllnode.hpp"
using namespace std;

class SLinkedList : public List {
    int size;
    Node* head, *tail;

    public:
    SLinkedList(){
        size = 0; 
        head = nullptr;
        tail = nullptr;
    }

    void print(){
        Node* curr = head;
        while(curr){
            cout << curr->data << " -> ";
            curr = curr->next;
        }
        cout << endl;
    }


    void addTail(int n){
        Node* newNode = new Node{n, nullptr};
        if(!head) head = tail = newNode;
        else tail = tail->next = newNode;
        size++;
    }

    void addHead(int n){
        Node* prev = nullptr; 
        Node* newNode = new Node{n, nullptr};
        if(!head) head = tail = newNode;
        else {
            newNode->next = head;
            head = newNode;
        }
        size++;
    }

    int getPosition(int n){
        Node* curr = head;
        for(int i = 0; curr != nullptr && i<size; i++){
            if(curr->data == n){
                return i + 1;
            }
            curr = curr->next;
        }

        return -1;
    }

        int remove(int n){
            if(!head) return 0;

            Node* prev = nullptr;
            Node* curr = head;

            while(curr){
                if(curr->data == n){
                    Node* toDelete = curr;
                    if(curr == head) head = head->next;
                    else{
                        prev->next = curr->next;
                        if(curr == tail) tail = prev;
                    }
                    delete(toDelete);
                    size--;
                    return 1;
                }
                prev = curr;
                curr = curr->next;
            }

            return 0;
        }

    


};  