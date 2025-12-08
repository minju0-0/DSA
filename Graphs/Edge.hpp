#include <cstdlib>
#include <iostream>
using namespace std;

class Edge {
    private:
    int name;
    char origin;
    char destination;

    public:
    Edge(char o, char d, int n) : name(n), origin(o), destination(d) {}
    
    char getOrigin(){ return (this->origin) ? this->origin : '\0'; }
    void setOrigin(char o) { origin = o;}
    
    char getDestination(){ return (this->destination)? this->destination : '\0'; }
    void setDestination(char d){ destination = d; }
        
    int getName(){ return (this->name)? this->name : -1; }
    void setName(int n){ name = n; }
       

    void toString() {
        cout << name << " | (" << origin << " -> " << destination << ")";
    }
};