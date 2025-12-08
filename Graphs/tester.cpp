#include <iostream>
#include <string>
#include <stdexcept>
#include <vector>
#include <algorithm>
#include "AdjacencyMatrix.hpp"

using namespace std;

// --- TEST FRAMEWORK ---
int passed = 0;
int failed = 0;

void assertTest(bool condition, string testName) {
    if (condition) {
        cout << " [PASS] Test " << (passed + failed + 1) << ": " << testName << endl;
        passed++;
    } else {
        cout << " [FAIL] Test " << (passed + failed + 1) << ": " << testName << endl;
        failed++;
    }
}

int main() {
    AdjacencyMatrix g; // Using your class name
    cout << "============================================" << endl;
    cout << "      GRAPH & SHORTEST PATH TESTER          " << endl;
    cout << "============================================" << endl;

    // --- GROUP 1: BASICS ---
    assertTest(g.numVertices() == 0, "Initial Graph empty");
    g.insertVertex('A');
    g.insertVertex('B');
    g.insertVertex('C');
    assertTest(g.numVertices() == 3, "Insert 3 vertices");
    
    // --- GROUP 2: EDGES ---
    g.insertEdge('A', 'B', 10);
    assertTest(g.getEdge('A', 'B') == 10, "Insert Edge A->B (10)");
    
    // Overwrite behavior test (Your code allows overwrite)
    g.insertEdge('A', 'B', 20); 
    assertTest(g.getEdge('A', 'B') == 20, "Overwrite Edge A->B (20)");

    // --- GROUP 3: DEGREES ---
    // A->B(20)
    g.insertEdge('B', 'C', 5);
    // Graph: A->B->C
    assertTest(g.outDegree('A') == 1, "OutDegree A is 1");
    assertTest(g.inDegree('B') == 1, "InDegree B is 1");

    // --- GROUP 6: SHORTEST PATH TESTS (Testing logic) ---
    // Since your function prints void, we verify output visually or by logic preparation
    
    cout << "\n--- PREPARING SHORTEST PATH SCENARIO ---" << endl;
    // Clearing graph for a clean test using a fresh instance
    AdjacencyMatrix sp; 
    sp.insertVertex('A'); sp.insertVertex('B'); sp.insertVertex('C'); 
    sp.insertVertex('D'); sp.insertVertex('E');

    /*
      Construction of "The Trap":
      A -> B = 10 (Direct is expensive)
      A -> C = 2
      C -> B = 3  (Path A->C->B = 5, which is cheaper than A->B)
      
      B -> D = 1
      B -> E = 100
      D -> E = 1
    */
    
    sp.insertEdge('A', 'B', 10);
    sp.insertEdge('A', 'C', 2);
    sp.insertEdge('C', 'B', 3);
    
    sp.insertEdge('B', 'D', 1);
    sp.insertEdge('B', 'E', 100);
    sp.insertEdge('D', 'E', 1);

    cout << "Graph Structure Created:" << endl;
    cout << " A->B(10), A->C(2)" << endl;
    cout << " C->B(3)  [So A->C->B costs 5]" << endl;
    cout << " B->D(1), B->E(100), D->E(1)" << endl;
    sp.print();

    cout << "\n--------------------------------------------" << endl;
    cout << "TEST 1: Indirect Path is Shorter (A -> B)" << endl;
    cout << "EXPECTED: Shortest distance: 5" << endl;
    cout << "EXPECTED: Path: A -> C -> B" << endl;
    cout << "ACTUAL  : "; 
    sp.shortestPath('A', 'B');
    cout << "--------------------------------------------" << endl;

    cout << "\nTEST 2: Long Chain (A -> E)" << endl;
    cout << "Logic   : A(0)->C(2)->B(3+2=5)->D(5+1=6)->E(6+1=7)" << endl;
    cout << "EXPECTED: Shortest distance: 7" << endl;
    cout << "EXPECTED: Path: A -> C -> B -> D -> E" << endl;
    cout << "ACTUAL  : "; 
    sp.shortestPath('A', 'E');
    cout << "--------------------------------------------" << endl;

    cout << "\nTEST 3: Unreachable Node" << endl;
    sp.insertVertex('Z'); // Z is isolated
    cout << "EXPECTED: No path from A to Z." << endl;
    cout << "ACTUAL  : ";
    sp.shortestPath('A', 'Z');
    cout << "--------------------------------------------" << endl;

    cout << "\nTEST 4: Invalid Inputs" << endl;
    cout << "EXPECTED: Invalid start/end vertex." << endl;
    cout << "ACTUAL  : ";
    sp.shortestPath('A', 'X'); // X does not exist
    cout << "--------------------------------------------" << endl;

    cout << "\nSummary: Check the 'ACTUAL' outputs above matches 'EXPECTED'." << endl;

    return 0;
}