#include <iostream>
#include <memory>
#include <math.h>
#include <vector>
#include <iomanip>

using namespace std;

class Figure{
public:
    virtual string Name() = 0;
    virtual double Area() = 0;
    virtual double Perimeter() = 0;
};

class Triangle : public Figure {
public:
    Triangle(int32_t a, int32_t b, int32_t c): a_(a), b_(b), c_(c){};

    double Area() override {
        return sqrt((a_ + b_ + c_)/16. * (b_ + c_ - a_) * (a_ + b_ - c_) * (a_ + c_ - b_));
    }

    double Perimeter() override {
        return a_ + b_ + c_;
    }

    string Name() override{
        return "TRIANGLE";
    }
private:
    int a_, b_, c_;
};

class Circle : public Figure {
public:
    Circle(int32_t r): r_(r){};

    double Area() override {
        return 3.14 * r_ * r_;
    }

    double Perimeter() override {
        return 2 * 3.14 * r_;
    }
    string Name() override{
        return "CIRCLE";
    }
private:
    int32_t r_;
};

class Rect : public Figure {
public:
    Rect(int32_t w, int32_t h): w_(w), h_(h){}

    double Area() override{
        return w_ * h_;
    }

    double Perimeter() override{
        return 2. * (w_ + h_);
    }

    string Name() override {
        return "RECT";
    }
private:
    int32_t w_, h_;
};

shared_ptr<Figure> CreateFigure(istream& is){
    string name;
    is >> name;
    if (name == "TRIANGLE"){
        int a,b,c;
        is >> a >> b >> c;
        return make_shared<Triangle>(Triangle(a, b, c));
    } else if (name == "CIRCLE"){
        int r;
        is >> r;
        return make_shared<Circle>(Circle(r));
    } else {
        int a,b;
        is >> a >> b;
        return make_shared<Rect>(Rect(a, b));
    }
}

int main() {
  vector<shared_ptr<Figure>> figures;
  for (string line; getline(cin, line); ) {
    istringstream is(line);

    string command;
    is >> command;
    if (command == "ADD") {
      figures.push_back(CreateFigure(is));
    } else if (command == "PRINT") {
      for (const auto& current_figure : figures) {
        cout << fixed << setprecision(3)
             << current_figure->Name() << " "
             << current_figure->Perimeter() << " "
             << current_figure->Area() << endl;
      }
    }
  }
  return 0;
}
