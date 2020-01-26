#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

class Human
{
public:
    Human(string name):Name(name) {}

    virtual const string GetOccupation() const =0;

    string GetName() const { return Name; }

    virtual void Walk(const string& destination) const {
        DoAction("walks to", destination);
    }

    void DoAction(const string& actionName) const {
        cout << GetOccupation() << ": " << Name << " " << actionName << endl;
    }

    void DoAction(const string& actionName, const string& targetName) const {
        cout << GetOccupation() << ": " << Name << " " << actionName << ": " << targetName << endl;
    }

protected:
    const string Name;
};


class Student: public Human {
public:
    Student(string name, string favouriteSong) : Human(name), FavouriteSong(favouriteSong) { }

    const string GetOccupation() const override {
        return "Student";
    }

    void SingSong() const {
        DoAction("sings a song", FavouriteSong);
    }

    void Walk(const string& destination) const override {
        Human::Walk(destination);
        SingSong();
    }

    void Learn() const {
        DoAction("learns");
    }

private:
    const string FavouriteSong;
};


class Teacher: public Human {
public:
    Teacher(string name, string subject) : Human(name), Subject(subject) { }

    const string GetOccupation() const override {
        return "Teacher";
    }

    void Teach() const {
        DoAction("teaches", Subject);
    }

private:
    const string Subject;
};


class Policeman: public Human {
public:
    Policeman(string name): Human(name) { }

    const string GetOccupation() const override {
        return "Policeman";
    }

    void Check(const Human& p) const {
        stringstream s;
        s << "checks " << p.GetOccupation() << ". " << p.GetOccupation() << "'s name is";
        DoAction(s.str(), p.GetName());
    }
};


void VisitPlaces(Human& Human, const vector<string>& places) {
    for (auto p : places) {
        Human.Walk(p);
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
