#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Human {
public:
    Human(const string& name, const string& type)
        : name_(name)
        , type_(type){}

    string getName() const { return name_; }

    string getType() const { return type_; }

    virtual void Walk(const string& destination) const {
        cout << prefix()      <<
                " walks to: " <<
                destination   <<
                endl;
    }

    string prefix() const {
        return type_ + ": " + name_;
    }

protected:
    const string name_;
    const string type_;
};

class Student : public Human {
public:
    Student(const string& name, const string& favouriteSong)
        : Human(name, "Student")
        , favouriteSong_(favouriteSong){
    }

    void Learn() const{
        cout << prefix()  <<
                " learns" << endl;
    }

    void Walk(const string& destination) const override {
        cout << prefix()      <<
                " walks to: " <<
                destination   << endl;
        SingSong();
    }

    void SingSong() const {
        cout << prefix()          <<
                " sings a song: " <<
                favouriteSong_    << endl;
    }

private:
    const string favouriteSong_;
};


class Teacher : public Human{
public:
    Teacher(const string& name, const string& subject)
        : Human(name, "Teacher")
        , subject_(subject){
    }

    void Teach() const {
        cout << prefix()     <<
                " teaches: " <<
                subject_     << endl;
    }

private:
    const string subject_;
};


class Policeman : public Human{
public:
    Policeman(const string& name) : Human(name, "Policeman"){}

    void Check(const Human& h) const{
        string humanType = h.getType();
        cout << prefix()        <<
                " checks "      <<
                humanType       <<
                ". "            <<
                humanType + "'s"<<
                " name is: "    <<
                h.getName()     <<
                endl;
    }
};

void VisitPlaces(const Human& h, const vector<string>& places) {
    for (auto p : places) {
        h.Walk(p);
    }
}

int main() {
    Teacher t("Jim", "Math");
    Student s("Ann", "We will rock you");
    Policeman p("Bob");

    VisitPlaces(t, {"Moscow", "London"});
    p.Check(s);
    VisitPlaces(s, {"Moscow", "London"});
    return 0;
}
