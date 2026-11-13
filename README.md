
# C++ Mini Search Engine

A console-based mini search engine developed using C++ and Data Structures and Algorithms (DSA).

The project searches through text documents using an inverted index, supports multiple-keyword queries, and ranks matching documents based on keyword frequency.

## Features

- Document loading and storage
- Text preprocessing and normalization
- Inverted index implementation
- Single and multiple-keyword search
- AND and OR Boolean search
- Stop-word removal
- Frequency-based document ranking
- Search result statistics
- Case-insensitive searching

## Technologies Used

- C++
- Standard Template Library (STL)
- Data Structures and Algorithms

## Data Structures Used

| Data Structure | Purpose |
|---|---|
| unordered_map | Inverted index |
| Nested unordered_map | Stores document frequencies |
| unordered_set | Stop-word filtering and duplicate removal |
| vector | Stores documents and search results |
| pair | Stores document names and scores |

## Project Structure

mini-search-engine/
│
├── main.cpp
├── README.md
│
└── documents/
    ├── doc1.txt
    ├── doc2.txt
    └── doc3.txt

## How to Run

### 1. Clone the repository

git clone YOUR_GITHUB_REPOSITORY_URL

### 2. Open the project folder

cd mini-search-engine

### 3. Compile

g++ -std=c++17 -Wall -Wextra main.cpp -o search

### 4. Run

Windows:
.\search.exe

Linux/macOS:
./search

## Search Modes

### OR Search

Returns documents containing at least one of the entered keywords.

Example:
python backend

### AND Search

Returns documents containing all entered keywords.

Example:
python backend

## Ranking Algorithm

Documents are ranked using keyword frequency.

The score of a document is calculated by adding the frequencies of all matching query keywords.

Documents with higher scores appear first.

## Complexity Analysis

Let:
- N = total number of words across all documents
- U = number of unique indexed words
- D = number of matching documents

| Operation | Expected Complexity |
|---|---|
| Build inverted index | O(N) average |
| Single keyword lookup | O(1) average |
| Search result sorting | O(D log D) |
| Space complexity | O(N) |

Actual query processing also depends on the number of query terms and the sizes of their posting lists.

## Future Improvements

- TF-IDF ranking
- Phrase searching
- File upload support
- Persistent index storage
- Graphical user interface
- Larger document collections

## Author

Developed as a C++ and DSA portfolio project.
