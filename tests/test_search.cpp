
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
    doc1.content = "C++ programming and machine learning";

    Document doc2;
    doc2.filename = "doc2.txt";
    doc2.content = "Python backend development";

    Document doc3;
    doc3.filename = "doc3.txt";
    doc3.content = "Machine learning and data structures";

    // Store documents
    vector<Document> documents = {doc1, doc2, doc3};

    // Build search index
    SearchEngine engine;
    engine.buildIndex(documents);

    // Test 1: Existing keyword
    assert(engine.hasKeyword("python"));

    // Test 2: Case-insensitive keyword
    assert(engine.hasKeyword("PYTHON"));

    // Test 3: Non-existing keyword
    assert(!engine.hasKeyword("java"));

    // Test 4: Stop word filtering
    assert(!engine.hasKeyword("and"));

    // Test 5: Document contains keyword
    assert(engine.containsDocument("python", "doc2.txt"));

    // Test 6: Document does not contain keyword
    assert(!engine.containsDocument("python", "doc1.txt"));

    // Test 7: Exact phrase exists
    assert(engine.containsPhrase("machine learning", "doc1.txt"));

    // Test 8: Exact phrase exists in another document
    assert(engine.containsPhrase("machine learning", "doc3.txt"));

    // Test 9: Wrong word order
    assert(!engine.containsPhrase("learning machine", "doc1.txt"));

    // Test 10: Phrase does not exist
    assert(!engine.containsPhrase("artificial intelligence", "doc2.txt"));

    // Test 11: Non-existing document
    assert(!engine.containsPhrase("machine learning", "unknown.txt"));

    // Test 12: Empty phrase
    assert(!engine.containsPhrase("", "doc1.txt"));

    cout << "All 12 tests passed successfully!" << endl;

    return 0;
}
