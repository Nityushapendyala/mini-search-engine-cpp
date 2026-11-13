
#include <iostream>
#include <cassert>
#include <vector>

#include "../include/Document.h"
#include "../include/SearchEngine.h"

using namespace std;

int main() {

    // Create sample documents
    Document doc1;
    doc1.filename = "doc1.txt";
    doc1.content = "C++ programming and algorithms";

    Document doc2;
    doc2.filename = "doc2.txt";
    doc2.content = "Python backend development";

    Document doc3;
    doc3.filename = "doc3.txt";
    doc3.content = "C++ algorithms and data structures";

    // Store documents in a vector
    vector<Document> documents = {doc1, doc2, doc3};

    // Build the search index
    SearchEngine engine;
    engine.buildIndex(documents);

    // Test 1: Existing keyword
    assert(engine.hasKeyword("python"));

    // Test 2: Case-insensitive keyword search
    assert(engine.hasKeyword("PYTHON"));

    // Test 3: Non-existing keyword
    assert(!engine.hasKeyword("java"));

    // Test 4: Stop words should not be indexed
    assert(!engine.hasKeyword("and"));

    // Test 5: Python exists in doc2
    assert(engine.containsDocument("python", "doc2.txt"));

    // Test 6: Python does not exist in doc1
    assert(!engine.containsDocument("python", "doc1.txt"));

    cout << "All 6 tests passed successfully!" << endl;

    return 0;
}
