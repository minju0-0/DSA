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

// --- MAIN TESTER ---
int main() {
    MyGraph g;
    cout << "============================================" << endl;
    cout << "      20-POINT COMPREHENSIVE TESTER         " << endl;
    cout << "============================================" << endl;

    // --- GROUP 1: BASICS & INSERTION ---
    
    // Test 1: Empty State
    assertTest(g.numVertices() == 0 && g.numEdges() == 0, "Initial Graph should be empty");

    // Test 2: Insert Vertices
    g.insertVertex('A');
    g.insertVertex('B');
    g.insertVertex('C');
    assertTest(g.numVertices() == 3, "Insert 3 vertices (A, B, C)");

    // Test 3: Duplicate Vertex Check
    g.insertVertex('A'); // Should be ignored
    assertTest(g.numVertices() == 3, "Duplicate vertex 'A' should not increase count");

    // Test 4: Insert Edge
    g.insertEdge('A', 'B', 10);
    assertTest(g.numEdges() == 1 && g.getEdge('A', 'B') == 10, "Insert Edge A->B (10)");

    // Test 5: Graph Connectivity
    g.insertEdge('B', 'C', 20);
    g.insertEdge('C', 'A', 30); // Cycle
    assertTest(g.numEdges() == 3, "Insert B->C and C->A (Total edges: 3)");

    // --- GROUP 2: EXCEPTIONS & BOUNDARIES ---

    // Test 6: Duplicate Edge Exception
    bool caught = false;
    try {
        g.insertEdge('A', 'B', 999);
    } catch (logic_error &e) {
        if (string(e.what()) == "Not Null") caught = true;
    }
    assertTest(caught, "Insert Duplicate Edge should throw 'Not Null'");

    // Test 7: Edge Integrity
    assertTest(g.getEdge('A', 'B') == 10, "Duplicate attempt should not overwrite existing value (10)");

    // Test 8: Invalid Vertex Edge Insertion
    g.insertEdge('A', 'Z', 50); // Z doesn't exist
    assertTest(g.numEdges() == 3, "Insert Edge to non-existent vertex 'Z' should fail silently/safely");

    // Test 9: Self-Loop Insertion
    g.insertEdge('B', 'B', 100);
    assertTest(g.getEdge('B', 'B') == 100 && g.numEdges() == 4, "Insert Self-Loop B->B (100)");

    // Test 10: Directed Logic
    assertTest(g.getEdge('B', 'A') == 0, "Graph is Directed: A->B exists, but B->A should be 0");

    // --- GROUP 3: DEGREES & ARRAYS ---

    // Test 11: OutDegree Calculation
    // B goes to C (20) and B (100). Total 2.
    assertTest(g.outDegree('B') == 2, "OutDegree of B should be 2");

    // Test 12: InDegree Calculation
    // A comes from C (30).
    assertTest(g.inDegree('A') == 1, "InDegree of A should be 1");

    // Test 13: Outgoing Edges Array
    int* outB = g.outgoingEdges('B');
    // We expect values 100 and 20 (order depends on implementation, usually insertion order or index order)
    bool found20 = false, found100 = false;
    for(int i=0; i<2; i++) {
        if(outB[i] == 20) found20 = true;
        if(outB[i] == 100) found100 = true;
    }
    assertTest(found20 && found100, "outgoingEdges('B') contains 20 and 100");

    // Test 14: Incoming Edges Array
    int* inB = g.incomingEdges('B');
    // B comes from A (10) and B (100).
    bool found10 = false; 
    found100 = false;
    for(int i=0; i<2; i++) { // InDegree B is 2
        if(inB[i] == 10) found10 = true;
        if(inB[i] == 100) found100 = true;
    }
    assertTest(found10 && found100, "incomingEdges('B') contains 10 and 100");

    // --- GROUP 4: HELPER FUNCTIONS ---

    // Test 15: EndVertices (Checking for Index vs Char bug)
    char* ends = g.endVertices(30); // Edge 30 is C->A
    assertTest(ends[0] == 'C' && ends[1] == 'A', "endVertices(30) returns chars 'C' and 'A'");

    // Test 16: Opposite (Checking for Index vs Char bug)
    // Edge 10 is A->B. Opposite of A is B.
    assertTest(g.opposite('A', 10) == 'B', "opposite('A', 10) returns 'B'");

    // --- GROUP 5: REMOVAL & MATRIX SHIFTING ---

    // Test 17: Remove Self-Loop Vertex (Crucial Logic Check)
    // Removing B. B has self-loop.
    // Logic: outDegree(2) + inDegree(2) = 4. 
    // BUT actual edges involving B are: A->B, B->C, B->B. Total 3.
    // If your code subtracts 4, it's a bug. If it subtracts 3, it's correct.
    int edgesBefore = g.numEdges(); // 4
    int removedCount = g.removeVertex('B'); 
    assertTest(removedCount == 3, "removeVertex('B') with self-loop should return 3 edges removed");

    // Test 18: Global Count Update
    // 4 edges - 3 removed = 1 edge remaining (C->A is the only one left)
    assertTest(g.numEdges() == 1, "Global numEdges should be 1 after removing B");

    // Test 19: Matrix Shifting Integrity
    // Vertices Remaining: A (idx 0), C (idx 1).
    // Edge C->A (30) should still exist.
    // Since B was index 1, C shifted from 2 to 1.
    assertTest(g.getEdge('C', 'A') == 30, "Edge C->A (30) survives matrix shifting");

    // Test 20: Final Clean
    g.removeVertex('A');
    g.removeVertex('C');
    assertTest(g.numVertices() == 0 && g.numEdges() == 0, "Removing all vertices results in clean empty graph");

    cout << "\n============================================" << endl;
    cout << "TEST RESULTS: " << passed << " PASSED, " << failed << " FAILED" << endl;
    cout << "============================================" << endl;

    return 0;
}