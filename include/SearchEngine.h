
#ifndef SEARCH_ENGINE_H
#define SEARCH_ENGINE_H

#include "Document.h"

#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <string>

class SearchEngine {
private:

    // Inverted index: keyword -> document -> frequency
    std::unordered_map<
        std::string,
        std::unordered_map<std::string, int>
    > invertedIndex;

    // Stop words
    std::unordered_set<std::string> stopWords = {
        "the", "is", "in", "a", "an",
        "and", "of", "to", "for", "on",
        "with", "are", "was", "were",
        "it", "this", "that", "be",
        "as", "at", "by", "from"
    };

    int totalDocuments = 0;

    // Store original documents for phrase searching
    std::vector<Document> indexedDocuments;

    // Helper functions
    std::string cleanWord(std::string word);

    double calculateTFIDF(
        std::string word,
        std::string filename
    );

    double calculateDocumentNorm(
        const std::string& filename
    );

public:

    // Build and display index
    void buildIndex(const std::vector<Document>& documents);

    void displayStatistics();

    // Search functionality
    void search(std::string query, int mode);

    // Testing functions
    bool hasKeyword(const std::string& keyword);

    bool containsDocument(
        const std::string& keyword,
        const std::string& filename
    );

    // Exact phrase searching
    bool containsPhrase(
        const std::string& phrase,
        const std::string& filename
    );
};

#endif
