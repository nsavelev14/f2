#include "node.h"

template <typename T>
bool compare(Comparison cmp, const T& a, const T& b) {
    switch (cmp) {
        case Comparison::Less:
            return a < b;
            break;
            
        case Comparison::LessOrEqual:
            return a <= b;
            break;
            
        case Comparison::Greater:
            return a > b;
            break;
        
        case Comparison::GreaterOrEqual:
            return a >= b;
            break;
            
        case Comparison::Equal:
            return a == b;
            break;
            
        case Comparison::NotEqual:
            return a != b;
            break;
    }
}


// EmptyNode
bool EmptyNode::Evaluate(const Date& date , const string& event) const {
    return true;
}

// DateComparisonNode
DateComparisonNode::DateComparisonNode(Comparison cmp, const Date& date) : _cmp(cmp), _date(date) {};

bool DateComparisonNode::Evaluate(const Date& date , const string& event) const  {
    return compare(_cmp, date, _date);
}

// EventComparisonNode
EventComparisonNode::EventComparisonNode(Comparison cmp, const string& event) : _cmp(cmp), _event(event) {};

bool EventComparisonNode::Evaluate(const Date& date, const string& event) const  {
    return compare(_cmp, event, _event);
}

// LogicalOperationNode
LogicalOperationNode::LogicalOperationNode(LogicalOperation op, shared_ptr<Node> left, shared_ptr<Node> right) :
                                                                         _op(op), _left(left), _right(right) {};

bool LogicalOperationNode::Evaluate(const Date& date, const string& event) const  {
    switch(_op) {
        case LogicalOperation::And:
            return _left->Evaluate(date, event) && _right->Evaluate(date, event);
            break;
            
        case LogicalOperation::Or:
            return _left->Evaluate(date, event) || _right->Evaluate(date, event);
    };
}
