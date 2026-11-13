
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <sstream>
#include <algorithm>
#include <cctype>

using namespace std;

// Stores document information
class Document {
public:
    string filename;
    string content;
};

// Loads and stores documents
class DocumentStore {
private:
    vector<Document> documents;

public:
    void loadDocument(string filename) {
        ifstream file("documents/" + filename);

        if (!file.is_open()) {
            cout << "Could not open " << filename << endl;
            return;
        }

        Document doc;
        doc.filename = filename;

        string line;

        while (getline(file, line)) {
            doc.content += line + " ";
        }

        documents.push_back(doc);
        file.close();
    }

    vector<Document> getDocuments() {
        return documents;
    }

    int getDocumentCount() {
        return static_cast<int>(documents.size());
    }
};

// Search engine
class SearchEngine {
private:

    // keyword -> document filename -> frequency
    unordered_map<string, unordered_map<string, int>> invertedIndex;

    // Common words to ignore
    unordered_set<string> stopWords = {
        "the", "is", "in", "a", "an",
        "and", "of", "to", "for", "on",
        "with", "are", "was", "were",
        "it", "this", "that", "be",
        "as", "at", "by", "from"
    };

    // Clean and normalize words
    string cleanWord(string word) {
        string result;

        for (char ch : word) {
            unsigned char c = static_cast<unsigned char>(ch);

            if (isalnum(c)) {
                result += static_cast<char>(tolower(c));
            }
        }

        return result;
    }

public:

    // Build inverted index
    void buildIndex(vector<Document> documents) {

        for (const Document& doc : documents) {

            stringstream ss(doc.content);
            string word;

            while (ss >> word) {

                word = cleanWord(word);

                if (!word.empty() &&
                    stopWords.find(word) == stopWords.end()) {

                    invertedIndex[word][doc.filename]++;
                }
            }
        }
    }

    // Display index statistics
    void displayStatistics(int documentCount) {

        cout << "\n========== INDEX STATISTICS ==========\n";
        cout << "Documents indexed: " << documentCount << endl;
        cout << "Unique keywords: " << invertedIndex.size() << endl;
        cout << "Stop words ignored: " << stopWords.size() << endl;
    }

    // Multiple keyword AND / OR search
    void search(string query, int mode) {

        stringstream ss(query);
        string word;

        vector<string> keywords;
        unordered_set<string> seenKeywords;

        // Normalize and remove duplicate query words
        while (ss >> word) {

            word = cleanWord(word);

            if (!word.empty() &&
                stopWords.find(word) == stopWords.end() &&
                seenKeywords.insert(word).second) {

                keywords.push_back(word);
            }
        }

        cout << "\n========== SEARCH RESULTS ==========\n";
        cout << "Query: " << query << endl;

        if (keywords.empty()) {
            cout << "No valid keywords after processing.\n";
            return;
        }

        // Document filename -> relevance score
        unordered_map<string, int> scores;

        // Process each keyword
        for (const string& keyword : keywords) {

            auto it = invertedIndex.find(keyword);

            if (it == invertedIndex.end()) {
                continue;
            }

            for (const auto& entry : it->second) {
                scores[entry.first] += entry.second;
            }
        }

        // Apply AND condition
        if (mode == 2) {

            for (auto it = scores.begin(); it != scores.end();) {

                int matchedKeywords = 0;

                for (const string& keyword : keywords) {

                    auto wordIt = invertedIndex.find(keyword);

                    if (wordIt != invertedIndex.end() &&
                        wordIt->second.find(it->first) != wordIt->second.end()) {

                        matchedKeywords++;
                    }
                }

                if (matchedKeywords != static_cast<int>(keywords.size())) {
                    it = scores.erase(it);
                } else {
                    ++it;
                }
            }
        }

        if (scores.empty()) {
            cout << "No matching documents found.\n";
            cout << "Results found: 0\n";
            return;
        }

        // Convert results into sortable vector
        vector<pair<string, int>> results;

        for (const auto& entry : scores) {
            results.push_back({entry.first, entry.second});
        }

        // Sort by score, highest first
        sort(results.begin(), results.end(),
             [](const pair<string, int>& a,
                const pair<string, int>& b) {

                 if (a.second != b.second) {
                     return a.second > b.second;
                 }

                 return a.first < b.first;
             });

        cout << "\nSearch mode: "
             << (mode == 1 ? "OR Search" : "AND Search")
             << endl;

        cout << "\nRanked documents:\n";

        int rank = 1;

        for (const auto& result : results) {

            cout << rank << ". "
                 << result.first
                 << " | Score: "
                 << result.second << endl;

            rank++;
        }

        cout << "\nResults found: " << results.size() << endl;
    }
};

// Main function
int main() {

    DocumentStore store;

    store.loadDocument("doc1.txt");
    store.loadDocument("doc2.txt");
    store.loadDocument("doc3.txt");

    SearchEngine engine;

    engine.buildIndex(store.getDocuments());

    cout << "=================================\n";
    cout << "       MINI SEARCH ENGINE\n";
    cout << "=================================\n";

    engine.displayStatistics(store.getDocumentCount());

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
