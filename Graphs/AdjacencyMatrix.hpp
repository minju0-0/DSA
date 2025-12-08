#include <cstdlib>
#include <iostream>
#include "graph.hpp"
using namespace std;

class AdjacencyMatrix : public Graph {
    int matrix[10][10] = {0};
    char s_vertices[10] = {0};
    int num_vert;
    int s_edges[100] = {0};
    int num_edge;
    int inf = 9999;
    
    int getIndex(char vert){
        for(int i = 0; i<num_vert; i++){
            if(s_vertices[i] == vert) return i;
        }
        return -1;
    }
    
    int getIn(int e){
        for(int i = 0; i<num_edge; i++){
            if(s_edges[i] == e) return i;
        }
        return -1;
    }

    int getWeight(char source, char desti){
        int i = getIndex(source);
        int j = getIndex(desti);
        return matrix[i][j];
    }
    
    void deleteEdgeList(int index) {
        if (index >= 0 && index < num_edge) {
            for (int i = index; i < num_edge - 1; i++) {
                s_edges[i] = s_edges[i + 1];
            }
            s_edges[num_edge - 1] = 0; 
            num_edge--;
        }
    }
    
    void deleteEdge(char v){
        int* in = incomingEdges(v);
        int* out = outgoingEdges(v);
        
        int outCount = outDegree(v), inCount = inDegree(v);
        for(int i = 0; i<outCount; i++){
            removeEdge(out[i]);
        }
        
        for(int i = 0; i<inCount; i++){
            removeEdge(in[i]);
        }

        delete[] in;
        delete [] out;
    }

    public:
    AdjacencyMatrix() {
        num_vert = 0;
        num_edge = 0;
    }

    int numVertices() { return num_vert; }  
    int numEdges() { return num_edge; }

    char* vertices() {
        if(num_vert == 0) return nullptr;
        char* vert = new char[num_vert];
        for(int i = 0; i<num_vert; i++){
            vert[i] = s_vertices[i];
        }
        return vert;
    }

    int* edges() {
        if(num_edge == 0) return nullptr;
        int* edge = new int[num_edge];
        for(int i = 0; i<num_edge; i++){
            edge[i] = s_edges[i];
        }
        return edge;
    }

    int getEdge(char u, char v)  {
        int i = getIndex(u);
        int j = getIndex(v);
        if(i != -1 && j != -1) return matrix[i][j];
        return 0;
    }

    char* endVertices(int e)  {
        char* endV = new char[2];
        endV[0] = '-'; endV[1] = '-';

        for(int i = 0; i<num_vert; i++){
            for(int j = 0; j<num_vert; j++){
                if(matrix[i][j] == e){
                    endV[0] = s_vertices[i];
                    endV[1] = s_vertices[j];
                    return endV;
                }
            }
        }
        return endV;
    }

    char opposite(char v, int e)  {
        int index = getIndex(v);
        if(index != -1){
            for(int i = 0; i<num_vert; i++){
                if(matrix[index][i] == e) return s_vertices[i];
            }
            
            for(int i = 0; i<num_vert; i++){
                if(matrix[i][index] == e) return s_vertices[i];
            }
        }
        return '-';
    }

    int outDegree(char v)  {
        int index = getIndex(v);
        int count = 0;
        if(index != -1){
            for(int i = 0; i<num_vert; i++){
                if(matrix[index][i] != 0) count++;
            }
        }
        return count;
    }

    int inDegree(char v)  {
        int index = getIndex(v);
        int count = 0;
        if(index != -1){
            for(int i = 0; i<num_vert; i++){
                if(matrix[i][index] != 0) count++;
            }
        }
        return count;
    }

    int* outgoingEdges(char v) {
        int index = getIndex(v);
        int outCount = outDegree(v);
        if(index != -1 || outCount != 0){
            int* out = new int[outCount];
            int s = 0;
            for(int i = 0; i<num_vert; i++){
                if(matrix[index][i] != 0){
                    out[s++] = matrix[index][i];
                }
            }   
            return out;
        }
        return nullptr;
    }

    int* incomingEdges(char v) {
        int index = getIndex(v);
        int inCount = inDegree(v);
        if(index != -1 || inCount != 0){
            int* in = new int[inCount];
            int s = 0;
            for(int i = 0; i<num_vert; i++){
                if(matrix[i][index] != 0){
                    in[s++] = matrix[i][index];
                }
            }
            return in;
        }
        return nullptr;
    }

    bool insertVertex(char x)  {
        if(getIndex(x) != -1 || num_vert >= 10) return false;
        s_vertices[num_vert++] = x;
        return true;
    }

    bool insertEdge(char u, char v, int x)  {
        int i = getIndex(u);
        int j = getIndex(v);
        if(i != -1 && j != -1 && num_edge < 100 || matrix[i][j] == 0){
            matrix[i][j] = x;
            s_edges[num_edge++] = x;
            return true;
        }
        return false;
    }

    int removeVertex(char v) {
        int index = getIndex(v);
        int count = 0;
        if(index != -1){
            count += outDegree(v) + inDegree(v);
            deleteEdge(v);


            for(int i = 0; i<num_vert; i++){
                for(int j = index; j<num_vert - 1; j++){
                    matrix[j][i] = matrix[j + 1][i];
                }
                matrix[num_vert - 1][i] = 0;
            }
            
            for(int i = 0; i<num_vert; i++){
                for(int j = index; j<num_vert - 1; j++){
                    matrix[i][j] = matrix[i][j + 1];
                }
                matrix[i][num_vert - 1] = 0;
            }
            
            for(int i = index; i<num_vert - 1; i++){
                s_vertices[i] = s_vertices[i + 1];
            }
            s_vertices[num_vert - 1] = 0; 
            
            num_vert--;
        }
        return count;
    }

    bool removeEdge(int e)  {
        char* endV = endVertices(e);
        if(endV[0] != '-'){
            int i = getIndex(endV[0]);
            int j = getIndex(endV[1]);
            matrix[i][j] = 0;
            deleteEdgeList(getIn(e));
            return true;
        }
        return false;
    }

    void print() {
        cout << "\t";
        for (int i = 0; i < num_vert; i++) {
            cout << s_vertices[i] << "\t";
        }
        cout << endl;
        for (int i = 0; i < num_vert; i++) {
            cout << s_vertices[i] << "\t";
            for (int j = 0; j < num_vert; j++) {
                if (matrix[i][j] != 0) {
                    cout << matrix[i][j];
                }
                cout << "\t";
            }
            cout << endl;
        }
    }


    // void dijkstra(char startNode){
    //     int dist[50];
    //     bool visited[50] = {false};
    //     int parent[50] = {-1};
    //     int n = num_vert;
    //     int startIndex = getIndex(startNode);

    //     if(startIndex == -1) return;

    //     for(int i = 0; i < numVertices(); i++){
    //         dist[i] = inf;
    //     }
    //     dist[startIndex] = 0;

    //     for(int i = 0; i<num_vert; i++){
    //         int u = -1, minValue = inf;
    //         for(int j = 0; i<num_vert; j++){
    //             if(!visited[j] && dist[j] < minValue ) {
    //                 minValue = dist[j];
    //                 u = j;
    //             }
    //         }
    //         if(u == -1) break;
    //         visited[u] = true;

    //         for(int i = 0; i<num_vert; i++){
    //             int weight = getWeight(u, i);

    //             if(weight != 0 && !visited[i] && dist[u] + weight < dist[i]){
    //                 dist[i] = dist[u] + weight;
    //                 parent[i] = u; 
    //             }
    //         }

    //     }


    // }

    void shortestPath(char start, char end) {
        const int INF = 1000000000;
        int n = num_vert;

        int s = getIndex(start);
        int t = getIndex(end);
        if (s == -1 || t == -1) {
            cout << "Invalid start/end vertex.\n";
            return;
        }

        int dist[10];
        int prev[10];
        bool used[10];

        for (int i = 0; i < n; i++) {
            dist[i] = INF;
            prev[i] = -1;
            used[i] = false;
        }
        dist[s] = 0;

        for (int iter = 0; iter < n; iter++) {
            int u = -1;
            int best = INF;
            for (int i = 0; i < n; i++) {
                if (!used[i] && dist[i] < best) {
                    best = dist[i];
                    u = i;
                }
            }
            
            if (u == -1 || best == INF) break; // remaining unreachable
            used[u] = true;
            if (u == t) break; // we already finalized end

            // relax outgoing edges u -> v
            for (int v = 0; v < n; v++) {
                int w = matrix[u][v];
                if (w != 0 && !used[v]) { // 0 means no edge in your structure
                    if (dist[u] + w < dist[v]) {
                        dist[v] = dist[u] + w;
                        prev[v] = u;
                    }
                }
            }
        }

        if (dist[t] == INF) {
            cout << "No path from " << start << " to " << end << ".\n";
            return;
        }

        // reconstruct path (t -> ... -> s)
        cout << "Shortest distance: " << dist[t] << "\nPath: ";
        int stack[10], top = 0;
        for (int x = t; x != -1; x = prev[x]) stack[top++] = x;

        for (int i = top - 1; i >= 0; i--) {
            cout << s_vertices[stack[i]];
            if (i) cout << " -> ";
        }
        cout << "\n";
    }

};