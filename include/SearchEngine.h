
#ifndef SEARCH_ENGINE_H
#define SEARCH_ENGINE_H

#include "Document.h"

#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <string>

class SearchEngine {
private:

    std::unordered_map<
        std::string,
        std::unordered_map<std::string, int>
    > invertedIndex;

    std::unordered_set<std::string> stopWords = {
        "the", "is", "in", "a", "an",
        "and", "of", "to", "for", "on",
        "with", "are", "was", "were",
        "it", "this", "that", "be",
        "as", "at", "by", "from"
    };

    int totalDocuments = 0;

    std::vector<Document> indexedDocuments;

    std::string cleanWord(std::string word);

    double calculateTFIDF(
        std::string word,
        std::string filename
    );

    double calculateDocumentNorm(
        const std::string& filename
    );

public:

    void buildIndex(const std::vector<Document>& documents);

    void displayStatistics();

    void search(std::string query, int mode);

    bool hasKeyword(const std::string& keyword);

    bool containsDocument(
        const std::string& keyword,
        const std::string& filename
    );

    bool containsPhrase(
        const std::string& phrase,
        const std::string& filename
    );

    // Generate a text snippet from a matching document
    std::string getSnippet(
        const std::string& filename,
        const std::string& query
    );
};

#endif
