#include <cstdlib>
#include <iostream>
#include "graph.hpp"
#include "Edge.hpp"
using namespace std;

class EdgeList : public Graph {
    Edge** s_edges;
    int num_edge;
    char s_vertices[10];
    int num_vert;
    
    int getVertex(char v){
        for(int i = 0; i<num_vert; i++){
            if(s_vertices[i] == v) return i;
        }
        return -1;
    }
    
    int getEdgeIn(char u, char v){
        for(int i = 0; i<num_edge; i++){
            if(s_edges[i]->getOrigin() == u && s_edges[i]->getDestination() == v) return i;
        }
        return -1;
    }

    int getEdgeByName(int e) {
        for (int i = 0; i < num_edge; i++){
            if (s_edges[i]->getName() == e) return i;
        } 
        return -1;
    }

    public:
    EdgeList() {
        s_edges = new Edge*[100]; 
        num_vert = 0;
        num_edge = 0;
    }

    int numVertices() { return num_vert; }

    char* vertices() {
        char* vert = new char[num_vert];
        for(int i = 0; i<num_vert; i++){
            vert[i] = s_vertices[i]; 
        }
        return vert;
    }

    int numEdges() { return num_edge; }

    int* edges() {
        int* e = new int[num_edge];
        for(int i = 0; i<num_edge; i++){
            e[i] = s_edges[i]->getName(); 
        }
        
        return e;
    }

    int getEdge(char u, char v)  {
        int i = getEdgeIn(u, v);
        if (i == -1) return 0;
        return s_edges[i]->getName();
    }

    char* endVertices(int e)  {
        char* endV = new char[2];
        endV[0] = endV[1] = '-';
        int i = getEdgeByName(e);
        if(i != -1){
            endV[0] = s_edges[i]->getOrigin();
            endV[1] = s_edges[i]->getDestination();
        }
        return endV;
    }

    char opposite(char v, int e)  {
        int i = getEdgeByName(e);
        if (i != -1){
            Edge* ed = s_edges[i];
            if (ed->getOrigin() == v) return ed->getDestination();
            if (ed->getDestination() == v) return ed->getOrigin();
        }
        return '-';
    }

    int outDegree(char v)  {
        int count = 0;
        for(int i = 0; i<num_edge; i++){
            if(s_edges[i]->getOrigin() == v) count++;
        }
        return count;
    }

    int inDegree(char v)  {
        int count = 0;
        for(int i = 0; i<num_edge; i++){
            if(s_edges[i]->getDestination() == v) count++;
        }
        return count;
    }

    int* outgoingEdges(char v) {
        int* out = new int[outDegree(v)];
        int count = 0;
        for(int i = 0; i<num_edge; i++){
            if(s_edges[i]->getOrigin() == v) out[count++] = s_edges[i]->getName();
        }
        return out;
    }

    int* incomingEdges(char v) {
        int* in = new int[inDegree(v)];
        int count = 0;
        for(int i = 0; i<num_edge; i++){
            if(s_edges[i]->getDestination() == v) in[count++] = s_edges[i]->getName();
        }
        return in;
    }

    bool insertVertex(char x)  {
        if (getVertex(x) != -1) return false; 
        s_vertices[num_vert++] = x;
        return true;
    }

    bool insertEdge(char u, char v, int x)  {
        if (getEdgeIn(u, v) != -1) throw logic_error("Not Null");
        s_edges[num_edge++] = new Edge(u, v, x);
        return true;
    }

    int removeVertex(char v) {
        int index = getVertex(v);
        int removed = 0;
        if (index != -1){
            for (int i = 0; i < num_edge; i++) {
                if (s_edges[i]->getOrigin() == v || s_edges[i]->getDestination() == v) {
                    removeEdge(s_edges[i]->getName());
                    removed++;
                    i--;
                }
            }
            for(int j = index; j < num_vert - 1; j++){
                s_vertices[j] = s_vertices[j + 1];
            }
            num_vert--;
        }
        return removed;
    }

    bool removeEdge(int e)  {
        int index = getEdgeByName(e);
        if (index == -1) return false;

        delete s_edges[index];
        for (int i = index; i < num_edge - 1; i++)
            s_edges[i] = s_edges[i + 1];

        num_edge--;
        return true;
    }


    void print() {
        cout << "Vertices: ";
        for (int i = 0; i < num_vert; i++) {
            cout << s_vertices[i] << " ";
        }
        cout << endl << "Edges: " << endl;
        for (int i = 0; i < num_edge; i++) {
            s_edges[i]->toString();
            cout << endl;
        }
    }
};