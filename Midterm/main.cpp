#include <iostream>
#include "Stack.hpp"
#include "CircularLL.hpp"
#include <stack>
// #include "Sll.hpp"
// #include "LinkedListDll.hpp"
using namespace std;

// int main(){
//     DLinkedList* d1 = new DLinkedList();
//     DLinkedList* d2 = new DLinkedList();

//     for(int i = 1; i<=6; i++){
//         d1->add(i);
//     }
    
//     for(int i = 1; i<=10; i++){
//         d1->add(i);
//     }


//     d1->combine(*d2);
//     d2->print();
// }

int main(){
    CircularLL* cll = new CircularLL();

    cll->addLast(1);
    cll->addLast(2);
    cll->addLast(3);
    cout << cll->removeNode(1) << endl;
    cll->rotates();
    cll->print();
    cll->insert(3, 10);
    cll->addLast(5);
    cll->print();
    cout << cll->removeNode(2) << endl;
    cll->print();
    cout << cll->removeNode(5) << endl;
    cll->print();

}

// int main(){
//     stack<string> s;
//     string str;
//     cout << "Enter string: ";
//     cin >> str;

//     int len = str.length();
//     int mid = str.length() / 2;

//     for(int i = 0; i<mid; i++){
//         s.push(string(1, str[i]));
//     }

//     if(len % 2 != 0) mid++;

//     for(int i = mid; i<len; i++){
//         string temp = string(1, str[i]);
//         if(s.top() == temp) s.pop();
//     }
    
//     if(s.empty()){
//         cout << "pali";
//     }else{
//         cout << "NAh boi";
//     }
// }

// int main(){
//     SLinkedList* sll = new SLinkedList();

//     for(int i = 0; i<5; i++){
//         sll->addTail(i + 1);
//     }

//     sll->print();
//     sll->flip();
//     sll->print();
// }

// int main(){
//     Stack* s = new Stack();
//     string str;
//     cout << "Enter string: ";
//     cin >> str;

//     for(char c : str){
//         if(isdigit(c)){
//             s->push(c - '0');
//         }else {
//             int v2 = s->pop();
//             int v1 = s->pop();

//             switch(c)
//         }
//     }
// }