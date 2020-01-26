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
      buffer_.reserve(1'000'000);
      result_.reserve(1'000'000);
  }
  void Left();
  void Right();
  void Insert(char token);
  void Cut(size_t tokens = 1);
  void Copy(size_t tokens = 1);
  void Paste();
  string GetText() const;
 private:
  size_t coursorPosition_ = 0;
  list<char> text_;
  string buffer_ = "";
  string result_ = "";
};

void Editor::Left() {
    coursorPosition_ -= coursorPosition_ == 0 ? 0 : 1;
}

void Editor::Right() {
    coursorPosition_ += coursorPosition_ == text_.size() ? 0 : 1;
}

void Editor::Insert(char token) {
    text_.insert(next(begin(text_), coursorPosition_), token);
    ++coursorPosition_;
}

void Editor::Cut(size_t tokens) {
    size_t size = min(tokens, text_.size() - coursorPosition_);
    buffer_.resize(size);
    auto it_begin = next(text_.begin(), coursorPosition_);
    for (size_t i = 0; i < size; ++i) {
        buffer_[i] = *next(it_begin, i);
    }
    text_.erase(it_begin, next(it_begin, size));
}

void Editor::Copy(size_t tokens) {
    size_t size = min(tokens, text_.size() - coursorPosition_);
    buffer_.resize(size);
    auto it_begin = next(text_.begin(), coursorPosition_);
    for (size_t i = 0; i < size; ++i) {
        buffer_[i] = *next(it_begin, i);
    }
    //text_.copy(buffer_.data(), tokens, coursorPosition_);
}

void Editor::Paste() {
    text_.insert(next(begin(text_), coursorPosition_), buffer_.begin(), buffer_.end());
    //text_.insert(coursorPosition_, buffer_);
    coursorPosition_ += buffer_.size();
}

string Editor::GetText() const {
    string res_;
    res_.reserve(text_.size());
    for (auto a: text_){
        res_.push_back(a);
    }
    return res_;
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
    editor.Cut(first_part_len);
    //cout << editor.GetText() << endl;
    for(size_t i = 0; i < text_len - first_part_len; ++i) {
      editor.Right();
    }
    TypeText(editor, ", ");
    //cout << editor.GetText() << endl;
    editor.Paste();
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
  { LOG_DURATION("Creation");
      Editor ed;
      for (size_t i = 0; i < 100'000; ++i){
        ed.Insert('a');
      }
  }
  return 0;
}
