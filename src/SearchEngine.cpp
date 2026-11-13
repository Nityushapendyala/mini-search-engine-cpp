
#include "SearchEngine.h"

#include <iostream>
#include <sstream>
#include <algorithm>
#include <cctype>
#include <cmath>
#include <iomanip>

using namespace std;

// Clean words: lowercase and remove punctuation
string SearchEngine::cleanWord(string word) {

    string result;

    for (char ch : word) {

        unsigned char c = static_cast<unsigned char>(ch);

        if (isalnum(c)) {
            result += static_cast<char>(tolower(c));
        }
    }

    return result;
}

// Build the inverted index
void SearchEngine::buildIndex(const vector<Document>& documents) {

    totalDocuments = static_cast<int>(documents.size());

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

// Calculate TF-IDF score
double SearchEngine::calculateTFIDF(
    string word,
    string filename
) {

    auto wordIt = invertedIndex.find(word);

    if (wordIt == invertedIndex.end()) {
        return 0.0;
    }

    auto docIt = wordIt->second.find(filename);

    if (docIt == wordIt->second.end()) {
        return 0.0;
    }

    // Term frequency
    double tf = 1.0 + log(docIt->second);

    // Document frequency
    int df = static_cast<int>(wordIt->second.size());

    // Inverse document frequency
    double idf = log(
        static_cast<double>(totalDocuments + 1) /
        static_cast<double>(df + 1)
    ) + 1.0;

    return tf * idf;
}

// Display index statistics
void SearchEngine::displayStatistics() {

    cout << "\n========== INDEX STATISTICS ==========\n";

    cout << "Documents indexed: "
         << totalDocuments << endl;

    cout << "Unique keywords: "
         << invertedIndex.size() << endl;

    cout << "Stop words ignored: "
         << stopWords.size() << endl;
}

// Perform AND / OR search with TF-IDF ranking
void SearchEngine::search(string query, int mode) {

    stringstream ss(query);
    string word;

    vector<string> keywords;
    unordered_set<string> seenKeywords;

    // Process query words
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

    // Document filename -> TF-IDF score
    unordered_map<string, double> scores;

    // Calculate relevance scores
    for (const string& keyword : keywords) {

        auto it = invertedIndex.find(keyword);

        if (it == invertedIndex.end()) {
            continue;
        }

        for (const auto& entry : it->second) {

            scores[entry.first] +=
                calculateTFIDF(keyword, entry.first);
        }
    }

    // Apply AND search
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

    // Convert scores into sortable vector
    vector<pair<string, double>> results;

    for (const auto& entry : scores) {
        results.push_back({entry.first, entry.second});
    }

    // Sort by highest TF-IDF score
    sort(results.begin(), results.end(),
         [](const pair<string, double>& a,
            const pair<string, double>& b) {

             if (a.second != b.second) {
                 return a.second > b.second;
             }

             return a.first < b.first;
         });

    cout << "\nSearch mode: "
         << (mode == 1 ? "OR Search" : "AND Search")
         << endl;

    cout << "\nTF-IDF Ranked Documents:\n";

    int rank = 1;

    for (const auto& result : results) {

        cout << rank << ". "
             << result.first
             << " | TF-IDF Score: "
             << fixed << setprecision(4)
             << result.second << endl;

        rank++;
    }

    cout << "\nResults found: "
         << results.size() << endl;
}

// Check whether a keyword exists in the index
bool SearchEngine::hasKeyword(const string& keyword) {

    string cleaned = cleanWord(keyword);

    return invertedIndex.find(cleaned) != invertedIndex.end();
}

// Check whether a document contains a particular keyword
bool SearchEngine::containsDocument(
    const string& keyword,
    const string& filename
) {

    string cleaned = cleanWord(keyword);

    auto it = invertedIndex.find(cleaned);

    if (it == invertedIndex.end()) {
        return false;
    }

    return it->second.find(filename) != it->second.end();
}
