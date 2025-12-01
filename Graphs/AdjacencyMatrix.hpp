#include "Graph.hpp"
#include <iostream>
#include <stdexcept>
using namespace std;

class MyGraph : public Graph{
    char* vertex;
    int* edge;
    int** adjMatrix;
    int numOfVertices;
    int numOfEdges;

    int getIndex(char vert){
        for(int i = 0; i < numOfVertices; i++){
            if(vertex[i] == vert) return i;
        }
        return -1;
    }

    bool checkEdge(char source, char desti){
        int i = getIndex(source);
        int j = getIndex(desti);
        if(adjMatrix[i][j] != 0 ) return false;
        return true;
    }

    void printHeader(){
        cout << "\t";
        for(int i = 0; i<numOfVertices; i++){
            cout << vertex[i] << "\t";
        }
        cout << endl;
    }

    public:
    MyGraph(){
        vertex = new char[10];
        edge = new int[90];
        adjMatrix = (int**)calloc(10, sizeof(int*));
        for(int i = 0; i<10; i++){
            adjMatrix[i] = (int*)calloc(10, sizeof(int));
        }
        numOfVertices = 0;
        numOfEdges = 0;
    }

    void insertVertex(char vert){
        if(getIndex(vert) == -1){
            vertex[numOfVertices++] = vert;
        }
    }

    void insertEdge(char source, char desti, int e){
        int i = getIndex(source);
        int j = getIndex(desti);
        if(i == -1 || j == -1 || i == j) return;
        if(adjMatrix[i][j] != 0)  throw logic_error("Not Null");
        adjMatrix[i][j] = e;
        edge[numOfEdges++] = e;
    }

    int numVertices(){
        return numOfVertices;
    }

    char* vertices(){
        return vertex;
    }

    int numEdges(){
        return numOfEdges;
    }

    int* edges(){
        return edge;
    }

    int getEdge(char source, char desti){
        int i = getIndex(source);
        int j = getIndex(desti);
        if(i != -1 && j != -1){
            return adjMatrix[i][j];
        }
        return 0;
    }

    char* endVertices(int e){
        char* endVert = new char[2];

        for(int i = 0; i<numOfVertices; i++){
            for(int j = 0; j<numOfVertices; j++){
                if(adjMatrix[i][j] == e){
                    endVert[0] = vertex[i];
                    endVert[1] = vertex[j];
                    return endVert;
                }
            }
        }
        endVert[1] = endVert[0] = '-';
        return endVert;
    }

    char opposite(char vert, int e){
        int index = getIndex(vert);
        if(index != -1){
            for(int i = 0; i<numOfVertices; i++){
                if(adjMatrix[i][index] == e){
                    return vertex[i];
                }
            }
            for(int i = 0; i<numOfVertices; i++){
                if(adjMatrix[index][i] == e){
                    return vertex[i];
                }
            }
        }
        return '-';
    }

    int outDegree(char source){
        int index = getIndex(source);
        int count = 0;
        if(index != -1){ 
            for(int i = 0; i<numOfVertices; i++){
                if(adjMatrix[index][i] != 0){
                    count++;
                }
            }
        }
        return count;
    }

    int inDegree(char source){
        int index = getIndex(source);
        int count = 0;
        if(index != -1){ 
            for(int i = 0; i<numOfVertices; i++){
                if(adjMatrix[i][index] != 0){
                    count++;
                }
            }
        }
        return count;
    }

    int* outgoingEdges(char source){
        int index = getIndex(source);
        int* outgoing = new int[outDegree(source)];
        int s = 0;
        if(index != -1){ 
            for(int i = 0; i<numOfVertices; i++){
                if(adjMatrix[index][i]!= 0){
                    outgoing[s++] = adjMatrix[index][i];
                }
            }
        }
        return outgoing;
    }

    int* incomingEdges(char source){
        int index = getIndex(source);
        int* incoming = new int[inDegree(source)];
        int s = 0;
        if(index != -1){ 
            for(int i = 0; i<numOfVertices; i++){
                if(adjMatrix[i][index]!= 0){
                    incoming[s++] = adjMatrix[i][index];
                }
            }
        }
        return incoming;
    }

    int removeVertex(char vert){
        int index = getIndex(vert);
        int deletedEdges = 0;
        if(index != -1){ 
            deletedEdges = outDegree(vert) + inDegree(vert);
            numOfEdges -= deletedEdges;

            for(int i = 0; i<numOfVertices; i++){
                for(int j = index; j<numOfVertices - 1; j++){
                    adjMatrix[j][i] = adjMatrix[j + 1][i];
                }
                adjMatrix[numOfVertices - 1][i] = 0;
            }
            for(int i = 0; i<numOfVertices; i++){
                for(int j = index; j<numOfVertices - 1; j++){
                    adjMatrix[i][j] = adjMatrix[i][j + 1];
                }
                adjMatrix[i][numOfVertices - 1] = 0;
            }
            for(int i = index; i<numOfVertices - 1; i++){
                vertex[i] = vertex[i + 1];
            }
            vertex[--numOfVertices] = '-';

        }
        return deletedEdges;
    }

    void print(){
        if(numOfVertices == 0){
            cout << "EMPTY" << endl;
            return;
        }

        printHeader();
        for(int i = 0; i<numOfVertices; i++){
            cout << vertex[i] << "\t";
            for(int j = 0; j<numOfVertices; j++){
                if(adjMatrix[i][j] == 0 ){
                    cout << " \t";
                }else{
                    cout << adjMatrix[i][j] << "\t";
                }
            }
            cout << endl;
        }
    }


};
