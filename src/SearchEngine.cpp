
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

    invertedIndex.clear();

    // Store original documents for phrase searching
    indexedDocuments = documents;

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

    double tf = 1.0 + log(docIt->second);

    int df = static_cast<int>(wordIt->second.size());

    double idf = log(
        static_cast<double>(totalDocuments + 1) /
        static_cast<double>(df + 1)
    ) + 1.0;

    return tf * idf;
}

// Calculate document vector norm
double SearchEngine::calculateDocumentNorm(
    const string& filename
) {

    double sumSquares = 0.0;

    for (const auto& wordEntry : invertedIndex) {

        double weight = calculateTFIDF(
            wordEntry.first,
            filename
        );

        sumSquares += weight * weight;
    }

    return sqrt(sumSquares);
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

// Perform AND / OR search using cosine similarity
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

    // Calculate query TF-IDF weights
    unordered_map<string, double> queryWeights;

    for (const string& keyword : keywords) {

        auto it = invertedIndex.find(keyword);

        if (it != invertedIndex.end()) {

            double idf = log(
                static_cast<double>(totalDocuments + 1) /
                static_cast<double>(it->second.size() + 1)
            ) + 1.0;

            queryWeights[keyword] = idf;
        }
    }

    if (queryWeights.empty()) {
        cout << "No matching documents found.\n";
        cout << "Results found: 0\n";
        return;
    }

    // Calculate query vector norm
    double queryNorm = 0.0;

    for (const auto& entry : queryWeights) {
        queryNorm += entry.second * entry.second;
    }

    queryNorm = sqrt(queryNorm);

    // Calculate document similarity scores
    unordered_map<string, double> scores;

    for (const auto& queryEntry : queryWeights) {

        const string& keyword = queryEntry.first;

        auto wordIt = invertedIndex.find(keyword);

        for (const auto& documentEntry : wordIt->second) {

            const string& filename = documentEntry.first;

            scores[filename] +=
                calculateTFIDF(keyword, filename) *
                queryEntry.second;
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

    // Normalize scores using cosine similarity
    for (auto& entry : scores) {

        double documentNorm =
            calculateDocumentNorm(entry.first);

        if (documentNorm > 0.0 && queryNorm > 0.0) {
            entry.second /= (documentNorm * queryNorm);
        } else {
            entry.second = 0.0;
        }
    }

    // Convert scores into sortable vector
    vector<pair<string, double>> results;

    for (const auto& entry : scores) {
        results.push_back({entry.first, entry.second});
    }

    // Sort by highest similarity
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

    cout << "\nCosine Similarity Ranked Documents:\n";

    int rank = 1;

    for (const auto& result : results) {

        cout << rank << ". "
             << result.first
             << " | Similarity Score: "
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

// Check whether an exact phrase exists in a document
bool SearchEngine::containsPhrase(
    const string& phrase,
    const string& filename
) {

    // Find the requested document
    auto docIt = find_if(
        indexedDocuments.begin(),
        indexedDocuments.end(),
        [&filename](const Document& doc) {
            return doc.filename == filename;
        }
    );

    if (docIt == indexedDocuments.end()) {
        return false;
    }

    // Normalize the phrase
    string normalizedPhrase;
    stringstream phraseStream(phrase);
    string word;

    while (phraseStream >> word) {

        word = cleanWord(word);

        if (!word.empty()) {

            if (!normalizedPhrase.empty()) {
                normalizedPhrase += " ";
            }

            normalizedPhrase += word;
        }
    }

    if (normalizedPhrase.empty()) {
        return false;
    }

    // Normalize document content
    string normalizedContent;
    stringstream contentStream(docIt->content);

    while (contentStream >> word) {

        word = cleanWord(word);

        if (!word.empty()) {

            if (!normalizedContent.empty()) {
                normalizedContent += " ";
            }

            normalizedContent += word;
        }
    }

    // Check exact phrase
    return normalizedContent.find(normalizedPhrase)
           != string::npos;
}
