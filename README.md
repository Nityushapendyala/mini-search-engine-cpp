
# C++ Mini Search Engine

A lightweight document search engine built using C++ that demonstrates core Information Retrieval concepts, including inverted indexing, Boolean retrieval, text preprocessing, and TF-IDF ranking.

## Overview

The Mini Search Engine searches through a collection of text documents and retrieves relevant results based on user-provided keywords.

It uses an inverted index to efficiently locate documents and TF-IDF scoring to rank search results by relevance.

## Features

- **Document Loading:** Loads text documents from a local directory.
- **Text Preprocessing:** Converts text to lowercase and removes punctuation.
- **Stop Word Removal:** Filters common words that provide little search value.
- **Inverted Indexing:** Maps keywords to documents and their frequencies.
- **Boolean Retrieval:** Supports AND and OR search operations.
- **TF-IDF Ranking:** Ranks documents based on keyword relevance.
- **Search Statistics:** Displays index statistics.
- **Automated Tests:** Includes assertion-based tests for core indexing functionality.

## Technologies Used

- C++
- C++17
- Standard Template Library (STL)
- Data Structures: Hash Maps, Hash Sets, and Vectors
- Information Retrieval: Inverted Index and TF-IDF

## Project Structure

    mini-search-engine/
    ├── include/
    │   ├── Document.h
    │   ├── DocumentStore.h
    │   └── SearchEngine.h
    ├── src/
    │   ├── DocumentStore.cpp
    │   └── SearchEngine.cpp
    ├── documents/
    │   ├── doc1.txt
    │   ├── doc2.txt
    │   └── doc3.txt
    ├── tests/
    │   └── test_search.cpp
    ├── main.cpp
    ├── README.md
    └── .gitignore

## How It Works

### 1. Document Loading
The DocumentStore class reads text files from the documents directory.

### 2. Text Preprocessing
Text is converted to lowercase, punctuation is removed, and common stop words are filtered.

### 3. Inverted Index Construction
The search engine creates an inverted index that stores each keyword, the documents containing it, and its frequency.

### 4. Query Processing
The user enters keywords and selects either AND or OR search.

- AND Search: Retrieves documents containing all query keywords.
- OR Search: Retrieves documents containing at least one query keyword.

### 5. Relevance Ranking
TF-IDF (Term Frequency-Inverse Document Frequency) is used to calculate document relevance scores and rank the results.

## Installation and Execution

### Prerequisites

- A C++ compiler supporting C++17
- Git (optional)

### Compile the Application

Run the following command from the project root directory:

```bash
g++ -std=c++17 -Wall -Wextra -I include main.cpp src/DocumentStore.cpp src/SearchEngine.cpp -o search.exe
```

### Run the Application

On Windows PowerShell:

```powershell
.\search.exe
```

## Running Tests

Compile the test program:

```bash
g++ -std=c++17 -Wall -Wextra -I include tests/test_search.cpp src/SearchEngine.cpp -o test_search.exe
```

Run the tests:

```powershell
.\test_search.exe
```

Expected output:

```text
All 6 tests passed successfully!
```

## Concepts Demonstrated

- Object-Oriented Programming
- Data Structures and Algorithms
- Hash-based indexing
- Text processing
- Boolean Information Retrieval
- TF-IDF ranking
- Modular C++ project architecture
- Basic automated testing

## Future Improvements

- Phrase searching
- Wildcard searching
- Advanced query processing
- Search result snippets
- Performance benchmarking
- Larger document collections
- More comprehensive automated tests

## Author

**Nityusha Pendyala**

GitHub: [Nityushapendyala](https://github.com/Nityushapendyala)
