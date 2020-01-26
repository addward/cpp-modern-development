#pragma once

#include <memory>
#include "date.h"

enum class Comparison{
    Less,
    LessOrEqual,
    Greater,
    GreaterOrEqual,
    Equal,
    NotEqual
};

enum class LogicalOperation{
    Or,
    And
};

class Node{
public:
    virtual bool Evaluate(const Date& date ,const string& event) const = 0;
};

class DateComparisonNode : public Node{
public:
    DateComparisonNode(const Comparison& cmp, const Date& date);
    bool Evaluate(const Date& date, const string& event) const override;
private:
    const Date date_;
    const Comparison cmp_;
};

class EventComparisonNode : public Node{
public:
    EventComparisonNode(const Comparison& cmp, const string& event);
    bool Evaluate(const Date& date, const string& event) const override;
private:
    const Comparison cmp_;
    const string event_;
};

class EmptyNode: public Node {
public:
    EmptyNode();
    bool Evaluate(const Date& date, const string& event) const;
};

class LogicalOperationNode: public Node {
public:
    LogicalOperationNode(const LogicalOperation& lo, shared_ptr<Node> left, shared_ptr<Node> right);
    bool Evaluate(const Date& date, const string& event) const override;
private:
    const LogicalOperation lo_;
    const shared_ptr<Node> left_;
    const shared_ptr<Node> right_;
};

template<class T>
bool compareTwoElements(const T& lhs, const T& rhs, const Comparison& cmp);

