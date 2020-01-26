#include "database.h"
#include "test_runner.h"
#include "node.h"

void TestDatabase() {
    {
        ostringstream os, result;
        Database db;
        db.Add({2017,11,21},"Tuesday");
        db.Add({2017,11,20},"Monday");
        db.Add({2017,11,21},"Weekly meeting");
        db.Print(os);
        auto predicate = [](const Date& date, const string& event) {
            return EventComparisonNode(Comparison::NotEqual, "Weekly meeting").Evaluate(date, event);
        };
        vector<string> vec = db.FindIf(predicate);
        for (auto str: vec){
            os << str << endl;
        }
        os << db.Last({2017,11,30}) << endl;
        result <<"2017-11-20 Monday\n"
               <<"2017-11-21 Tuesday\n"
               <<"2017-11-21 Weekly meeting\n"
               <<"2017-11-20 Monday\n"
               <<"2017-11-21 Tuesday\n"
               <<"2017-11-21 Weekly meeting\n";
        AssertEqual(os.str(), result.str(), "1 case (creation) in db test");
        //Deletion
        int removed = db.RemoveIf([](const Date& date, const string& event) {
                        return DateComparisonNode(Comparison::Greater, {2017,11,20}).Evaluate(date, event);
                    });
        AssertEqual(removed, 2, "1 case (deletion) in db test");
        AssertEqual(db.Last({2017,11,30}), "2017-11-20 Monday", "1 case (Last method) in db test");
        AssertEqual(db.Last({2017,11,01}), "No entries",        "1 case (Last method) in db test");
    }

    {
        Database db;
        ostringstream os, result;
        db.Add({2017,01,1}, "Holiday" );
        db.Add({2017,03,8}, "Holiday" );
        db.Add({2017,01,1}, "New Year");
        vector<string> deleted = db.FindIf([](const Date& date, const string& event){
                                          return EventComparisonNode(Comparison::NotEqual,
                                                              "working day").Evaluate(date, event);
        });
        for (auto el: deleted){
            os << el << endl;
        }
        result << "2017-01-01 Holiday\n"
               << "2017-01-01 New Year\n"
               << "2017-03-08 Holiday\n";
        AssertEqual(os.str(), result.str(), "2 case (creation) in db test");
    }
}
