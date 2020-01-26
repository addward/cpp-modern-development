#include "node.h"

template<class T>
bool compareTwoElements(const T& lhs, const T& rhs, const Comparison& cmp){
    if (cmp == Comparison::Equal){
        return (lhs == rhs);
    } else
    if (cmp == Comparison::Greater){
        return (lhs > rhs);
    } else
    if (cmp == Comparison::GreaterOrEqual){
        return (lhs >= rhs);
    } else
    if (cmp == Comparison::Less){
        return (lhs < rhs);
    } else
    if (cmp == Comparison::LessOrEqual){
        return (lhs <= rhs);
    } else {
        return (lhs != rhs);
    }
}

bool Node::Evaluate(const Date& date, const string& event) const {
    return true;
}

DateComparisonNode::DateComparisonNode(const Comparison& cmp, const Date& date)
    : date_(date)
    , cmp_(cmp){
}

bool DateComparisonNode::Evaluate(const Date& date, const string& event) const{
    return compareTwoElements(date, date_, cmp_);
}

EventComparisonNode::EventComparisonNode(const Comparison& cmp, const string& event)
    : cmp_(cmp)
    , event_(event){
}

bool EventComparisonNode:: Evaluate(const Date& date, const string& event) const {
    return compareTwoElements(event, event_, cmp_);
}

LogicalOperationNode::LogicalOperationNode(const LogicalOperation& lo, shared_ptr<Node> left, shared_ptr<Node> right)
    : lo_(lo)
    , left_(left)
    , right_(right){
}

bool LogicalOperationNode::Evaluate(const Date& date, const string& event) const {
    bool right_cond = right_->Evaluate(date, event);
    bool left_cond  = left_->Evaluate(date, event);
    if (lo_ == LogicalOperation::And){
        return (left_cond && right_cond);
    } else {
        return (left_cond || right_cond);
    }
}

EmptyNode::EmptyNode(){
}

bool EmptyNode::Evaluate(const Date& date, const string& event) const {
    return true;
}
