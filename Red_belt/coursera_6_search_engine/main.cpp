#include "search_server.h"
#include "parse.h"
#include "test_runner.h"
#include "profile.h"

#include <algorithm>
#include <iterator>
#include <map>
#include <vector>
#include <string>
#include <sstream>
#include <fstream>
#include <random>
#include <thread>

using namespace std;

void TestFunctionality(
  const vector<string>& docs,
  const vector<string>& queries,
  const vector<string>& expected
) {
  istringstream docs_input(Join('\n', docs));
  istringstream docs_input1(Join('\n', docs));
  istringstream docs_input2(Join('\n', docs));
  istringstream docs_input3(Join('\n', docs));
  istringstream docs_input4(Join('\n', docs));
  istringstream docs_input5(Join('\n', docs));
  istringstream queries_input(Join('\n', queries));
  ostringstream queries_output;
  ostringstream queries_output1;
  ostringstream queries_output2;
  ostringstream queries_output3;
  ostringstream queries_output4;
  ostringstream queries_output5;
  {
    SearchServer srv(docs_input);
    //cout << "1" << endl;
    {
    LOG_DURATION("Creation")
    srv.AddQueriesStream(queries_input, queries_output);
    //srv.UpdateDocumentBase(docs_input2);
    //srv.UpdateDocumentBase(docs_input3);
    //srv.UpdateDocumentBase(docs_input4);
    //srv.UpdateDocumentBase(docs_input5);
    //cout << "2" << endl;
    //cout << "Lets create search thread" << endl;
    //srv.AddQueriesStream(queries_input, queries_output1);
    //srv.UpdateDocumentBase(docs_input);
    //srv.UpdateDocumentBase(docs_input);
    //srv.UpdateDocumentBase(docs_input);
    //srv.UpdateDocumentBase(docs_input);
    //cout << "Lets create search thread" << endl;
    //srv.AddQueriesStream(queries_input, queries_output2);
    //srv.AddQueriesStream(queries_input, queries_output3);
    //srv.UpdateDocumentBase(docs_input1);
    //srv.AddQueriesStream(queries_input, queries_output4);
    //srv.AddQueriesStream(queries_input, queries_output5);
    //srv.UpdateDocumentBase(docs_input);
    //srv.UpdateDocumentBase(docs_input);
    //srv.UpdateDocumentBase(docs_input);
    //srv.UpdateDocumentBase(docs_input);
    //cout << "4" << endl;
    }
    //LOG_DURATION("searching");
    //srv.AddQueriesStream(queries_input, queries_output);
    //srv.AddQueriesStream(queries_input, queries_output1);
    //srv.AddQueriesStream(queries_input, queries_output2);
    //srv.AddQueriesStream(queries_input, queries_output3);
  }


  const string result = queries_output.str();
  const auto lines = SplitBy(Strip(result), '\n');
  if (expected.size() != 0) {
    ASSERT_EQUAL(lines.size(), expected.size());
    for (size_t i = 0; i < lines.size(); ++i) {
        ASSERT_EQUAL(lines[i], expected[i]);
    }
  }
  //cout << "Hey - Hey" << endl;
}

void TestSerpFormat() {
  const vector<string> docs = {
    "london is the capital of great britain",
    "i am travelling down the river"
  };
  const vector<string> queries = {"london", "the"};
  const vector<string> expected = {
    "london: {docid: 0, hitcount: 1}",
    Join(' ', vector{
      "the:",
      "{docid: 0, hitcount: 1}",
      "{docid: 1, hitcount: 1}"
    })
  };

  TestFunctionality(docs, queries, expected);
}

void TestTop5() {
  const vector<string> docs = {
    "milk a",
    "milk b",
    "milk c",
    "milk d",
    "milk e",
    "milk f",
    "milk g",
    "water a",
    "water b",
    "fire and earth"
  };

  const vector<string> queries = {"milk", "water", "rock"};
  const vector<string> expected = {
    Join(' ', vector{
      "milk:",
      "{docid: 0, hitcount: 1}",
      "{docid: 1, hitcount: 1}",
      "{docid: 2, hitcount: 1}",
      "{docid: 3, hitcount: 1}",
      "{docid: 4, hitcount: 1}"
    }),
    Join(' ', vector{
      "water:",
      "{docid: 7, hitcount: 1}",
      "{docid: 8, hitcount: 1}",
    }),
    "rock:",
  };
  TestFunctionality(docs, queries, expected);
}

void TestHitcount() {
  const vector<string> docs = {
    "the river goes through the entire city there is a house near it",
    "the wall",
    "walle",
    "is is is is",
  };
  const vector<string> queries = {"the", "wall", "all", "is", "the is"};
  const vector<string> expected = {
    Join(' ', vector{
      "the:",
      "{docid: 0, hitcount: 2}",
      "{docid: 1, hitcount: 1}",
    }),
    "wall: {docid: 1, hitcount: 1}",
    "all:",
    Join(' ', vector{
      "is:",
      "{docid: 3, hitcount: 4}",
      "{docid: 0, hitcount: 1}",
    }),
    Join(' ', vector{
      "the is:",
      "{docid: 3, hitcount: 4}",
      "{docid: 0, hitcount: 3}",
      "{docid: 1, hitcount: 1}",
    }),
  };
  TestFunctionality(docs, queries, expected);
}

void TestRanking() {
  const vector<string> docs = {
    "london is the capital of great britain",
    "paris is the capital of france",
    "berlin is the capital of germany",
    "rome is the capital of italy",
    "madrid is the capital of spain",
    "lisboa is the capital of portugal",
    "bern is the capital of switzerland",
    "moscow is the capital of russia",
    "kiev is the capital of ukraine",
    "minsk is the capital of belarus",
    "astana is the capital of kazakhstan",
    "beijing is the capital of china",
    "tokyo is the capital of japan",
    "bangkok is the capital of thailand",
    "welcome to moscow the capital of russia the third rome",
    "amsterdam is the capital of netherlands",
    "helsinki is the capital of finland",
    "oslo is the capital of norway",
    "stockgolm is the capital of sweden",
    "riga is the capital of latvia",
    "tallin is the capital of estonia",
    "warsaw is the capital of poland",
  };

  const vector<string> queries = {"moscow is the capital of russia"};
  const vector<string> expected = {
    Join(' ', vector{
      "moscow is the capital of russia:",
      "{docid: 7, hitcount: 6}",
      "{docid: 14, hitcount: 6}",
      "{docid: 0, hitcount: 4}",
      "{docid: 1, hitcount: 4}",
      "{docid: 2, hitcount: 4}",
    })
  };
  TestFunctionality(docs, queries, expected);
}

void TestBasicSearch() {
  const vector<string> docs = {
    "we are ready to go",
    "come on everybody shake you hands",
    "i love this game",
    "just like exception safety is not about writing try catch everywhere in your code move semantics are not about typing double ampersand everywhere in your code",
    "daddy daddy daddy dad dad dad",
    "tell me the meaning of being lonely",
    "just keep track of it",
    "how hard could it be",
    "it is going to be legen wait for it dary legendary",
    "we dont need no education"
  };

  const vector<string> queries = {
    "we need some help",
    "it",
    "i love this game",
    "tell me why",
    "dislike",
    "about",
    "INEEDHELP"
  };

  const vector<string> expected = {
    Join(' ', vector{
      "we need some help:",
      "{docid: 9, hitcount: 2}",
      "{docid: 0, hitcount: 1}"
    }),
    Join(' ', vector{
      "it:",
      "{docid: 8, hitcount: 2}",
      "{docid: 6, hitcount: 1}",
      "{docid: 7, hitcount: 1}",
    }),
    "i love this game: {docid: 2, hitcount: 4}",
    "tell me why: {docid: 5, hitcount: 2}",
    "dislike:",
    "about: {docid: 3, hitcount: 2}",
    "INEEDHELP:"
  };
  TestFunctionality(docs, queries, expected);
}

void TestTime() {
    vector<string> docs_part = {
    "we are ready to go",
    "come on everybody shake you hands",
    "i love this game",
    "just like exception safety is not about writing try catch everywhere in your code move semantics are not about typing double ampersand everywhere in your code",
    "daddy daddy daddy dad dad dad",
    "tell me the meaning of being lonely",
    "just keep track of it",
    "how hard could it be",
    "it is going to be legen wait for it dary legendary",
    "we dont need no education",
    "I have nothing to say about this movie hello, words, adsf, jogging every day",
    "She borrowed the book from him many years ago and hasn't yet returned it",
    "He turned in the research paper on Friday; otherwise, he would have not passed the class",
    "This is a Japanese doll",
    "Wednesday is hump day, but has anyone asked the camel if he is happy about it",
    "I was very proud of my nickname throughout high school but today- I could not be any different to what my nickname was",
    "They got there early, and they got really good seats",
    "The book is in front of the table",
    "A glittering gem is not enough",
    "She did her best to help him",
    "Christmas is coming"
  };

  vector<string> docs;
  for (auto& i: docs_part) {
    i.insert(end(i), begin(i), end(i));
    i.insert(end(i), begin(i), end(i));
    i.insert(end(i), begin(i), end(i));
    i.insert(end(i), begin(i), end(i));
    i.insert(end(i), begin(i), end(i));
  }
  for (auto i = 0; i < 2'500; ++i) {
    docs.insert(docs.end(), begin(docs_part), end(docs_part));
  }


  const vector<string> queries_part = {
    "Cats are good pets for they are clean and are",
    "We need to rent a room for our party",
    "It was getting dark and we were not there yet",
    "The stranger officiates the meal",
    "Last Friday in three weeks time I saw a ",
    "I am never at home on Sundays",
    "Joe made the sugar cookies Susan decorated them",
    "She folded her handkerchief neatly",
    "He didnt want to go to the dentist yet he",
    "I am happy to take your donation",
    "Mary plays the piano",
    "Tom got a small piece of pie",
    "Wednesday is hump day but has",
    "I was very proud of my nickname",
    "I want to buy a onesie… but know it",
    "The old apple revels in its authority",
    "We have a lot of rain in June",
    "She borrowed the book from him many",
    "Let me help you with your baggage",
    "Sixty-Four comes asking for bread",
    "Tom got a small piece of pie",
    "Cats are good pets for they are clean",
    "Christmas is coming",
    "Sometimes it is better to just ",
    "What was the person thinking when they",
    "Last Friday in three week’s time",
    "My Mum tries to be cool by saying",
    "The clock within this blog and",
    "Check back tomorrow; I will see",
    "A song can make or ruin a person day ",
    "We have never been to Asia nor",
    "It was getting dark, and we ",
    "She works two jobs to make ends meet",
    "Where do random thoughts come from",
    "Wow, does that work",
    "The old apple revels in its authority",
    "He ran out of money, so he had",
    "Someone I know recently combined",
    "We need to rent a room for our party"
  };

  vector<string> queries;
  for (auto i = 0; i < 500; ++i) {
    queries.insert(queries.end(), begin(queries_part), end(queries_part));
  }

  const vector<string> expected = {};
  TestFunctionality(docs, queries, expected);
}

int main() {
  TestRunner tr;
  RUN_TEST(tr, TestSerpFormat);
  RUN_TEST(tr, TestTop5);
  RUN_TEST(tr, TestHitcount);
  RUN_TEST(tr, TestRanking);
  RUN_TEST(tr, TestBasicSearch);
  TestTime();
}
