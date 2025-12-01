#include "AdjacencyMatrix.hpp"
#include <iostream>
using namespace std;

int main(){
    Graph* myGraph = new MyGraph();
    char op, v, u;
    int e;

    do{
        cout << "Op: ";
        cin >> op;
        switch(op){
            case 'v':
                cin >> v;
                myGraph->insertVertex(v);
                break;
            case 'e':
                cin >> v >> u >> e;
                try{
                    myGraph->insertEdge(v, u, e);
                }catch(exception &e){
                    cout << e.what() << endl;
                }
                break;
            case 'p':
                myGraph->print();
                break;
            case 'r':
                cin >> v;
                myGraph->removeVertex(v);
                break;
            case 'x':
                cout << "Exiting...." << endl;
                break;
            default:
                cout << "Invalid operation" << endl;
        }      
    }while(op != 'x');
}