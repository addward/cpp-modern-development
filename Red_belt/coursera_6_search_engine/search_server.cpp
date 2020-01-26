#include "search_server.h"
#include "iterator_range.h"
#include "profile.h"

#include <algorithm>
#include <iterator>
#include <sstream>
#include <iostream>
#include <set>
#include <numeric>

vector<string> SplitIntoWords(const string& line) {
  istringstream words_input(line);
  return {istream_iterator<string>(words_input), istream_iterator<string>()};
}

SearchServer::SearchServer(istream& document_input) {
  UpdateDocumentBaseSingleThread(document_input);
}

void SearchServer::UpdateDocumentBaseSingleThread(istream& document_input) {
  InvertedIndex new_index;

  for (string current_document; getline(document_input, current_document); ) {
    new_index.Add(move(current_document));
  }

  lock_guard<mutex> guard(updateIndex);
  index = move(new_index);
}

void SearchServer::UpdateDocumentBase(istream& document_input) {
  lock_guard<mutex> guard(addFuture);
  futures.push_back(async([&document_input, this] {
        UpdateDocumentBaseSingleThread(document_input);
      }
    )
  );
}

void SearchServer::AddQueriesStream (
  istream& query_input, ostream& search_results_output
) {
    lock_guard<mutex> guard(addFuture);
    futures.push_back(async([&query_input, &search_results_output, this] (){
        AddQueriesStreamSingleThread (query_input, search_results_output);
      }
      )
    );
}

void SearchServer::AddQueriesStreamSingleThread (
  istream& query_input, ostream& search_results_output
) {

    vector<size_t> docid_count;
    vector<size_t> doc_index;
    doc_index.reserve(index.getDocumentCount());
    docid_count.reserve(index.getDocumentCount());

  for (string current_query; getline(query_input, current_query);) {

    const auto words = SplitIntoWords(current_query);

    docid_count.assign(docid_count.size(), 0);
    {
      lock_guard<mutex> guard(updateIndex);

      for (const auto& word : words) {
        for (const auto& docid : index.Lookup(word)) {
          if (docid.first + 1> docid_count.size()) {
            docid_count.resize(docid.first + 1, 0);
          }
          docid_count[docid.first] += docid.second;
        }
      }
    }

    if (doc_index.size() != docid_count.size()) {
      doc_index.resize(docid_count.size(), 0);
    }
    iota(begin(doc_index), end(doc_index), 0);

    partial_sort(
      begin(doc_index),
      begin(doc_index) + min<size_t>(5, doc_index.size()),
      end(doc_index),
      [&docid_count](size_t lhs, size_t rhs) {
        if (docid_count[lhs] > docid_count[rhs]) return true;
        else if (docid_count[lhs] == docid_count[rhs]) {
            return lhs < rhs;
        } else {
            return false;
        }
        return false;
      }
    );

    search_results_output << current_query << ':';

    for (auto i : Head(doc_index, 5)) {
      if (docid_count[i] == 0) continue;
      search_results_output << " {"
        << "docid: " << i << ", "
        << "hitcount: " << docid_count[i] << '}';
    }

    search_results_output << endl;
  }
}

void InvertedIndex::Add(const string document) {
  const size_t docid = doc_id++;
  auto words = SplitIntoWords(move(document));
  map<string, size_t> unique_words;

  for (const auto& word : words) {
    unique_words[word]++;
  }

  for (const auto& word : unique_words) {
    vector<pair<size_t, size_t>>& indexes = index[word.first];
    indexes.push_back(make_pair(docid, word.second));
  }
}

const vector<pair<size_t, size_t>>& InvertedIndex::Lookup(const string& word) const {
  if (auto it =  index.find(word); it != index.end()) {
    return it -> second;
  } else {
    return empty_index;
  }
}
