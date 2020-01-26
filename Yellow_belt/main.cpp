#include <sstream>
#include <iostream>
#include <string>
#include <vector>
#include <memory>

using namespace std;

class Person {
public:
    Person(const string& name = "anonymous", const string& type = "person") : name_(name), type_(type) {}
    virtual void Walk(string& destination) const {
        cout << type_ << ": " << name_ << " walks to: " << destination << endl;
    }

    string Name() const {
        return name_;
    }

    string Type() const {
        return type_;
    }

    string GetTypeNamePrefix() const {
        ostringstream prefix;
        prefix << type_ << ": " << name_;
        return prefix.str();
    }

private:
    const string name_;
    const string type_;
};

class Student : public Person {
public:
    Student(const string& name, const string& favorite_song) : Person(name, "Student") {
        favorite_song_ = favorite_song;
    }

    void Learn() const {
        cout << GetTypeNamePrefix() << " learns" << endl;
    }

    void Walk(string& destination) const override {
        cout << GetTypeNamePrefix() << " walks to: " << destination << endl;
        SingSong();
    }

    void SingSong() const {
        cout << GetTypeNamePrefix() << " sings a song: " << favorite_song_ << endl;
    }

private:
    string favorite_song_;
};


class Teacher : public Person {
public:
    Teacher(const string& name, const string& subject) : Person(name, "Teacher") {
        subject_ = subject;
    }

    void Teach() const {
        cout << GetTypeNamePrefix() << " teaches: " << subject_ << endl;
    }

private:
    string subject_;
};


class Policeman : public Person {
public:
    Policeman(const string& name) : Person(name, "Policeman") {}

    void Check(Person p) {
        cout << GetTypeNamePrefix() << " checks " << p.Type() << ". " << p.Type() << "'s name is: " << p.Name() << endl;
    }
};


void VisitPlaces(shared_ptr<Person> person, vector<string> places) {
    for (auto p : places) {
        person->Walk(p);
    }
}


int main() {
    Teacher t("Jim", "Math");
    Student s("Ann", "We will rock you");
    Policeman p("Bob");

    VisitPlaces(make_shared<Teacher>(t), {"Moscow", "London"});
    p.Check(s);
    VisitPlaces(make_shared<Student>(s), {"Moscow", "London"});
    return 0;
}
