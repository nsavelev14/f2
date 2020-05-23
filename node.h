#pragma once
#include "date.h"
#include <string>
#include <memory>

using namespace std;

enum class Comparison {
    Less,
    LessOrEqual,
    Greater,
    GreaterOrEqual,
    Equal,
    NotEqual,
};

enum class LogicalOperation {
    Or,
    And,
};



class Node {
public:
    
    virtual bool Evaluate(const Date& date, const string& event ) const = 0;
};

class EmptyNode : public Node {
public:
    
    EmptyNode() {};
    bool Evaluate(const Date& date, const string& event ) const override;
};


class DateComparisonNode : public Node {
public:
    
    DateComparisonNode(Comparison cmp, const Date& date);
    bool Evaluate(const Date& date, const string& event ) const override ;
private:
    
    Date _date;
    Comparison _cmp;
};

class EventComparisonNode : public Node {
public:
    
    EventComparisonNode(Comparison cmp, const string& event);
    bool Evaluate(const Date& date, const string& event ) const override ;
private:
    
    string _event;
    Comparison _cmp;
};

class LogicalOperationNode : public Node {
public:
    
    LogicalOperationNode(LogicalOperation op, shared_ptr<Node> left, shared_ptr<Node> right);
    bool Evaluate(const Date& date, const string& event ) const override;
private:
    LogicalOperation _op;
    shared_ptr<Node> _left;
    shared_ptr<Node> _right;
};

