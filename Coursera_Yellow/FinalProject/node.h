#pragma once

#include "date.h"
#include <memory>

enum class Comparison {
    Less,
    LessOrEqual,
    Greater,
    GreaterOrEqual,
    Equal,
    NotEqual
};

enum class LogicalOperation {
    Or,
    And
};

class Node {
public:
    virtual bool Evaluate(const Date &date, const std::string &event) const = 0;
};

class DateComparisonNode : public Node {
public:
    DateComparisonNode(Comparison cmp, const Date &date);

    bool Evaluate(const Date &date, const std::string &event) const override;

private:
    const Comparison cmp_;
    const Date date_;
};

class EventComparisonNode : public Node{
public:
    EventComparisonNode(Comparison cmp, const std::string &event);

    bool Evaluate(const Date &date, const std::string &event) const override;

private:
    const Comparison cmp_;
    const std::string event_;
};

class LogicalOperationNode : public Node {
public:
    LogicalOperationNode(LogicalOperation lo, std::shared_ptr<Node> l, std::shared_ptr<Node> r);

    bool Evaluate(const Date &date, const std::string &event) const override;

private:
    const LogicalOperation lo_;
    std::shared_ptr<const Node> l_, r_;
};

class EmptyNode : public Node {
public:
    bool Evaluate(const Date&, const std::string&) const override;
};
