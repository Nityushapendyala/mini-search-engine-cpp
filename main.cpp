
#include <iostream>
#include <string>

#include "include/DocumentStore.h"
#include "include/SearchEngine.h"

using namespace std;

int main() {

    // Step 1: Create document storage
    DocumentStore store;

    // Step 2: Load text documents
    store.loadDocument("doc1.txt");
    store.loadDocument("doc2.txt");
    store.loadDocument("doc3.txt");

    // Step 3: Create search engine
    SearchEngine engine;

    // Step 4: Build inverted index
    engine.buildIndex(store.getDocuments());

    // Step 5: Display application heading
    cout << "=================================\n";
    cout << "       MINI SEARCH ENGINE\n";
    cout << "=================================\n";

    // Step 6: Display index statistics
    engine.displayStatistics();

    // Step 7: Interactive search menu
    while (true) {

        cout << "\nChoose search mode:\n";
        cout << "1. OR Search\n";
        cout << "2. AND Search\n";
        cout << "0. Exit\n";
        cout << "Enter choice: ";

        string choice;
        getline(cin, choice);

        if (choice == "0") {
            cout << "Thank you for using Mini Search Engine!\n";
            break;
        }

        if (choice != "1" && choice != "2") {
            cout << "Invalid choice. Enter 1, 2 or 0.\n";
            continue;
        }

        cout << "Enter keywords: ";

        string query;
        getline(cin, query);

        engine.search(query, stoi(choice));
    }

    return 0;
}
