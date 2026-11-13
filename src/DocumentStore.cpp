
#include "DocumentStore.h"
#include <iostream>
#include <fstream>

using namespace std;

void DocumentStore::loadDocument(string filename) {

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

    cout << "Loaded: " << filename << endl;
}

vector<Document> DocumentStore::getDocuments() {
    return documents;
}

int DocumentStore::getDocumentCount() {
    return static_cast<int>(documents.size());
}
