#pragma once

#include <istream>
#include <ostream>
#include <set>
#include <list>
#include <vector>
#include <map>
#include <string>
#include <future>

using namespace std;

class InvertedIndex {
public:
  void Add(const string document);
  const vector<pair<size_t, size_t>>& Lookup(const string& word) const;

  size_t getDocumentCount() const {
    return doc_id;
  }
private:
  size_t doc_id         = 0;

  map<string, vector<pair<size_t, size_t>>> index;
  vector<pair<size_t, size_t>> empty_index;
};

class SearchServer {
public:
  SearchServer() = default;
  explicit SearchServer(istream& document_input);
  void UpdateDocumentBase(istream& document_input);
  void UpdateDocumentBaseSingleThread(istream& document_input);
  void AddQueriesStream(istream& query_input, ostream& search_results_output);
  void AddQueriesStreamSingleThread(istream& query_input, ostream& search_results_output);

private:
  InvertedIndex index;
  mutex addFuture;
  size_t thread_num = 0;
  mutex updateIndex;
  vector<future<void>> futures;
};
