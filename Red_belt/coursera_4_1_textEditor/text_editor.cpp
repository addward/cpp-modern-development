#include <string>
#include <string_view>
#include <list>
#include "test_runner.h"
#include "profile.h"

using namespace std;

class Editor {
 public:
  // Реализуйте конструктор по умолчанию и объявленные методы
  Editor() {
    coursorPosition_ = text_.begin();
  }
  void Left();
  void Right();
  void Insert(char token);
  void Cut(size_t tokens = 1);
  void Copy(size_t tokens = 1);
  void Paste();
  string GetText() const;
 private:
  list<char> text_;
  list<char> buffer_;
  list<char>::iterator coursorPosition_;
};

void Editor::Left() {
    if (coursorPosition_ != text_.begin()) --coursorPosition_;
}

void Editor::Right() {
    if (coursorPosition_ != text_.end()) ++coursorPosition_;
}

void Editor::Insert(char token) {
    //cout << "inserted: " << token << endl;
    text_.insert(coursorPosition_, token);
}

void Editor::Cut(size_t tokens) {
    //cout << "a1" << endl;
    Copy(tokens);
    //cout << "a2" << endl;
    size_t size = min(tokens,
                      static_cast<size_t>(distance(coursorPosition_, text_.end())));

    coursorPosition_ = text_.erase(coursorPosition_, next(coursorPosition_, size));

    /*if (coursorPosition_ != text_.begin()) {
        --coursorPosition_;
    }*/
    /*size_t size = min(tokens,
                      static_cast<size_t>(distance(coursorPosition_, text_.end())));
    //cout << size << endl;
    buffer_.clear();
    auto it_begin = coursorPosition_;
    auto it_end = next(it_begin, size);
    if (it_end == end(text_)) {
      buffer_.splice(buffer_.begin(), text_, it_begin, it_end);
      coursorPosition_ = end(text_);
    } else {
        coursorPosition_ = next(it_end);
        buffer_.splice(buffer_.begin(), text_, it_begin, it_end);

    ++coursorPosition_;
    */
}

void Editor::Copy(size_t tokens) {
    buffer_.clear();
    size_t size = min(tokens,
                      static_cast<size_t>(distance(coursorPosition_, text_.end())));
    //cout << size << endl;
    auto it_begin = coursorPosition_;
    auto it_end = next(it_begin, size);
    while(it_begin != it_end) {
        //cout << "il" << endl;
        //cout << *it_begin << endl;
        buffer_.push_back(*it_begin);
        ++it_begin;
    }
}

void Editor::Paste() {
    auto it_begin = buffer_.begin();
    while(it_begin != end(buffer_)) {
        //cout << "il" << endl;
        //cout << *it_begin << endl;
        Insert(*it_begin);
        //buffer_.push_back(*it_begin);
        ++it_begin;
    }
    //text_.splice(it_coursor, buffer_, buffer_.begin(), buffer_.end());
    //advance(coursorPosition_, buffer_.size());
}

string Editor::GetText() const {
    string result;
    result.resize(text_.size());
    auto it = text_.begin();
    //cout << "-------------result-------------" << endl;
    for (size_t i = 0; i < text_.size(); ++i) {
        result[i] = *it;
        ++it;
    }
    /*
    for (auto i: text_){
        cout << i;
    }
    cout << endl;
    cout << "-------------buffer-------------" << endl;
    for (auto i: buffer_) {
        cout << i;
    }
    cout << endl << distance(coursorPosition_, text_.end()) << endl;
    cout << "--------------------------------" << endl;
    */
    return result;
}

void TypeText(Editor& editor, const string& text) {
  for(char c : text) {
    editor.Insert(c);
  }
}

void TestEditing() {
  {
    Editor editor;

    const size_t text_len = 12;
    const size_t first_part_len = 7;

    TypeText(editor, "hello, world");

    for(size_t i = 0; i < text_len; ++i) {
      editor.Left();
    }
    //editor.GetText();
    editor.Cut(first_part_len);
    //editor.GetText();

    for(size_t i = 0; i < text_len - first_part_len; ++i) {
      editor.Right();
    }
    TypeText(editor, ", ");
    //editor.GetText();


    //cout << editor.GetText() << endl;
    editor.Paste();

    //cout << editor.GetText() << endl;
    //cout << editor.GetText() << endl;
    editor.Left();
    editor.Left();
    editor.Cut(3);

    ASSERT_EQUAL(editor.GetText(), "world, hello");
  }
  {
    Editor editor;

    TypeText(editor, "misprnit");
    editor.Left();
    editor.Left();
    editor.Left();
    editor.Cut(1);
    //cout << "**" <<editor.GetText() << endl;
    editor.Right();
    editor.Paste();

    ASSERT_EQUAL(editor.GetText(), "misprint");
  }
}

void TestReverse() {
  Editor editor;

  const string text = "esreveR";
  for(char c : text) {
    editor.Insert(c);
    editor.Left();
  }

  ASSERT_EQUAL(editor.GetText(), "Reverse");
}

void TestNoText() {
  Editor editor;
  ASSERT_EQUAL(editor.GetText(), "");

  editor.Left();
  editor.Left();
  editor.Right();
  editor.Right();
  editor.Copy(0);
  editor.Cut(0);
  editor.Paste();

  ASSERT_EQUAL(editor.GetText(), "");
}

void TestEmptyBuffer() {
  Editor editor;

  editor.Paste();
  TypeText(editor, "example");
  editor.Left();
  editor.Left();
  editor.Paste();
  editor.Right();
  editor.Paste();
  editor.Copy(0);
  editor.Paste();
  editor.Left();
  editor.Cut(0);
  editor.Paste();

  ASSERT_EQUAL(editor.GetText(), "example");
}

int main() {
  TestRunner tr;
  RUN_TEST(tr, TestEditing);
  RUN_TEST(tr, TestReverse);
  RUN_TEST(tr, TestNoText);
  RUN_TEST(tr, TestEmptyBuffer);
/*
  Editor ed;
  {  LOG_DURATION("Creation");
      for (size_t i = 0; i < 100'000; ++i) {
        ed.Insert('a');
      }
  }

  {  LOG_DURATION("Left");
      for (size_t i = 0; i < 1'000'000; ++i) {
        ed.Left();
      }
  }

  {  LOG_DURATION("Change content");
      for (size_t i = 0; i < 1'000'000; ++i) {
        ed.Insert('b');
      }
      for (size_t i = 0; i < 100'000; ++i) {
        ed.Left();
      }
  }

  {  LOG_DURATION("Copy");
      for (size_t i = 0; i < 1'000; ++i) {
        ed.Copy(1'000);
      }
  }
  {  LOG_DURATION("Cut + Paste");
      for (size_t i = 0; i < 1'0000; ++i) {
        ed.Right();
        ed.Cut(1'0000);
        ed.Paste();
      }
  }
  {  LOG_DURATION("Get text");
      for (size_t i = 0; i < 100; ++i) {
        ed.GetText();
      }
  }
    */
  /*
  { LOG_DURATION("list_test");
      list<int> kek;
      list<int> copy;
      for (size_t i = 0; i < 200'000; ++i){
        auto it = kek.begin();
        kek.push_back(i);
      }
      auto it = kek.begin();
      advance(it, 100'000);
      for (size_t i = 0; i < 50'000; ++i) {
        //auto it = kek.begin();
        copy.push_back(*it);
        ++it;
      }
  }
  { LOG_DURATION("string");
      string kek;
      for (size_t i = 0; i < 60'000; ++i){
        kek.insert(kek.begin(), 'a');
      }
  }*/
  return 0;
}
