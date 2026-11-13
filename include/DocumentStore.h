
#ifndef DOCUMENT_STORE_H
#define DOCUMENT_STORE_H

#include "Document.h"
#include <vector>
#include <string>

class DocumentStore {
private:
    std::vector<Document> documents;

public:
    void loadDocument(std::string filename);

    std::vector<Document> getDocuments();

    int getDocumentCount();
};

#endif
