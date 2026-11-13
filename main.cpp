
#include <iostream>
#include <string>
#include <vector>

#include "include/DocumentStore.h"
#include "include/SearchEngine.h"

using namespace std;

int main() {

    // Load documents
    DocumentStore store;

    store.loadDocument("doc1.txt");
    store.loadDocument("doc2.txt");
    store.loadDocument("doc3.txt");

    // Get loaded documents
    vector<Document> documents = store.getDocuments();

    // Build search engine
    SearchEngine engine;
    engine.buildIndex(documents);

    cout << "\n=================================\n";
    cout << "       MINI SEARCH ENGINE\n";
    cout << "=================================\n";

    engine.displayStatistics();

    while (true) {

        cout << "\n========== SEARCH MENU ==========\n";
        cout << "1. OR Search\n";
        cout << "2. AND Search\n";
        cout << "3. Exact Phrase Search\n";
        cout << "0. Exit\n";

        cout << "Enter choice: ";

        string choice;
        getline(cin, choice);

        if (choice == "0") {

            cout << "\nThank you for using Mini Search Engine!\n";
            break;
        }

        // OR Search
        if (choice == "1") {

            cout << "Enter keywords: ";

            string query;
            getline(cin, query);

            engine.search(query, 1);
        }

        // AND Search
        else if (choice == "2") {

            cout << "Enter keywords: ";

            string query;
            getline(cin, query);

            engine.search(query, 2);
        }

        // Exact Phrase Search
        else if (choice == "3") {

            cout << "Enter exact phrase: ";

            string phrase;
            getline(cin, phrase);

            cout << "\n========== PHRASE SEARCH RESULTS ==========\n";
            cout << "Phrase: \"" << phrase << "\"\n";

            int resultsFound = 0;

            for (const Document& doc : documents) {

                if (engine.containsPhrase(phrase, doc.filename)) {

                    resultsFound++;

                    cout << "\n" << resultsFound << ". "
                         << doc.filename << endl;

                    cout << "   Snippet: "
                         << engine.getSnippet(doc.filename, phrase)
                         << endl;
                }
            }

            if (resultsFound == 0) {
                cout << "\nNo documents contain this exact phrase.\n";
            }

            cout << "\nResults found: " << resultsFound << endl;
        }

        else {

            cout << "\nInvalid choice. Enter 1, 2, 3 or 0.\n";
        }
    }

    return 0;
}
