
# C++ Mini Search Engine

A modular document search engine developed using C++17, implementing core Information Retrieval concepts such as inverted indexing, Boolean retrieval, TF-IDF scoring, cosine similarity, exact phrase matching, and search snippets.

## Overview

The Mini Search Engine searches through a collection of text documents and retrieves relevant results based on user queries.

It uses an inverted index for efficient keyword lookup, TF-IDF for term weighting, and cosine similarity for ranking search results.

The project also supports exact phrase searching, document snippets, automated testing, and performance benchmarking.

## Features

### Search and Retrieval
- **Document Loading:** Loads text documents from a local directory.
- **Text Preprocessing:** Converts text to lowercase and removes punctuation.
- **Stop Word Removal:** Filters common words that provide little search value.
- **Inverted Indexing:** Maps keywords to documents and their frequencies.
- **OR Search:** Retrieves documents containing at least one query keyword.
- **AND Search:** Retrieves documents containing all query keywords.
- **Exact Phrase Search:** Finds documents containing an exact sequence of words.

### Ranking and Results
- **TF-IDF Scoring:** Calculates term relevance using Term Frequency and Inverse Document Frequency.
- **Cosine Similarity:** Normalizes document relevance scores.
- **Search Snippets:** Displays text extracts from matching documents.
- **Ranked Results:** Displays documents in descending order of similarity.

### Testing and Performance
- **Automated Tests:** Includes assertion-based tests for indexing and phrase matching.
- **Performance Benchmarking:** Measures indexing and search execution time.
- **Multiple Dataset Sizes:** Benchmarks collections of 100, 1,000, 5,000 and 10,000 documents.
- **Cached Document Norms:** Stores document vector norms to avoid repeated calculations during searches.

## Technologies Used

- C++
- C++17
- Standard Template Library (STL)
- Object-Oriented Programming
- Hash Maps (`unordered_map`)
- Hash Sets (`unordered_set`)
- Vectors
- Information Retrieval Algorithms
- TF-IDF
- Cosine Similarity

## Project Architecture

```text
mini-search-engine/
│
├── include/
│   ├── Document.h
│   ├── DocumentStore.h
│   └── SearchEngine.h
│
├── src/
│   ├── DocumentStore.cpp
│   └── SearchEngine.cpp
│
├── documents/
│   ├── doc1.txt
│   ├── doc2.txt
│   └── doc3.txt
│
├── tests/
│   ├── test_search.cpp
│   └── benchmark.cpp
│
├── main.cpp
├── README.md
└── .gitignore
```

## How It Works

### 1. Document Loading

The `DocumentStore` class reads text files from the documents directory and stores their contents.

### 2. Text Preprocessing

The search engine:
- Converts words to lowercase.
- Removes punctuation.
- Filters common stop words.

### 3. Inverted Index Construction

The engine creates an inverted index that maps each keyword to the documents containing it and its frequency.

### 4. Query Processing

Users can choose between three search modes:

- **OR Search:** Retrieves documents containing at least one query keyword.
- **AND Search:** Retrieves documents containing every query keyword.
- **Exact Phrase Search:** Retrieves documents containing the requested phrase in the same word order.

### 5. Relevance Ranking

TF-IDF calculates the importance of query terms, while cosine similarity normalizes document relevance scores.

### 6. Search Snippets

The engine displays a short extract from each matching document to help users understand the result.

## Installation and Execution

### Prerequisites

- C++ compiler supporting C++17
- GCC or MinGW
- VS Code (recommended)

### Compile the Application

Run this command from the project root directory:

```bash
g++ -std=c++17 -Wall -Wextra -I include main.cpp src/DocumentStore.cpp src/SearchEngine.cpp -o search.exe
```

### Run the Application

On Windows PowerShell:

```powershell
.\search.exe
```

## Running Automated Tests

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
All 12 tests passed successfully!
```

The tests cover:
- Keyword lookup
- Case-insensitive keyword processing
- Stop-word filtering
- Document keyword matching
- Exact phrase matching
- Incorrect phrase order
- Missing documents
- Empty phrases

## Performance Benchmarking

The project includes a benchmark program to evaluate indexing and search performance across different document collection sizes.

### Benchmark Configuration

- Language: C++
- Standard: C++17
- Compiler optimization: `-O2`
- Search iterations: 100
- Dataset sizes: 100, 1,000, 5,000 and 10,000 documents

### Compile the Benchmark

```bash
g++ -std=c++17 -O2 -Wall -Wextra -I include tests/benchmark.cpp src/SearchEngine.cpp -o benchmark.exe
```

### Run the Benchmark

```powershell
.\benchmark.exe
```

### Performance Metrics

- Document indexing time (milliseconds)
- Total search time
- Average search time per query

*Benchmark measurements depend on the hardware, compiler and dataset. Results should be reported with the actual test environment and measurements.*

## Concepts Demonstrated

- Object-Oriented Programming
- Data Structures and Algorithms
- Hash-based indexing
- Text processing and normalization
- Boolean Information Retrieval
- TF-IDF weighting
- Cosine similarity
- Exact phrase matching
- Search result ranking
- Modular software architecture
- Automated testing
- Performance benchmarking

## Future Improvements

- More advanced query processing
- Phrase search optimization
- Search result highlighting
- Better snippet generation
- Persistent index storage
- Multithreaded indexing
- Large-scale document testing
- Search performance optimization
- More comprehensive automated tests

## Author

**Nityusha Pendyala**

GitHub: [Nityushapendyala](https://github.com/Nityushapendyala)

## Repository

[Mini Search Engine - C++](https://github.com/Nityushapendyala/mini-search-engine-cpp)


## Search Quality Evaluation

The search engine evaluates retrieval quality using standard Information Retrieval metrics.

### Evaluation Metrics

- **Precision:** Measures the proportion of retrieved documents that are relevant.
- **Recall:** Measures the proportion of relevant documents successfully retrieved.
- **F1-Score:** Harmonic mean of precision and recall.

### Sample Evaluation Results

| Metric | Result |
|---|---:|
| True Positives | 2 |
| False Positives | 1 |
| False Negatives | 0 |
| Precision | 66.67% |
| Recall | 100% |
| F1-Score | 80% |

These results are based on a small manually labelled sample dataset.

## Performance Benchmarking

The benchmark evaluates indexing and search computation across different dataset sizes.

It measures:
- Indexing time
- Total search time
- Average search time per query

The benchmark uses synthetic documents and results may vary depending on hardware and dataset characteristics.

Run the benchmark using:

```bash
g++ -std=c++17 -Wall -Wextra -I include tests/benchmark.cpp src/SearchEngine.cpp -o benchmark.exe
./benchmark.exe
```

Run the search evaluation using:

```bash
g++ -std=c++17 -Wall -Wextra -I include tests/evaluate_search.cpp src/SearchEngine.cpp -o evaluate_search.exe
./evaluate_search.exe
```
