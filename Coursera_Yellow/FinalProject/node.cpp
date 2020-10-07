#include "node.h"

DateComparisonNode::DateComparisonNode(Comparison cmp, const Date &date) :
        cmp_(cmp), date_(date) {}

bool DateComparisonNode::Evaluate(const Date &date, const std::string &event) const {
    switch (cmp_) {
        case Comparison::Less:
            return date < date_;
        case Comparison::LessOrEqual:
            return date <= date_;
        case Comparison::Greater:
            return date > date_;
        case Comparison::GreaterOrEqual:
            return date >= date_;
        case Comparison::Equal:
            return date == date_;
        case Comparison::NotEqual:
            return date != date_;
    }
}

EventComparisonNode::EventComparisonNode(Comparison cmp, const std::string &event) :
        cmp_(cmp), event_(event) {}

bool EventComparisonNode::Evaluate(const Date &date, const std::string &event) const {
    switch (cmp_) {
        case Comparison::Less:
            return event < event_;
        case Comparison::LessOrEqual:
            return event <= event_;
        case Comparison::Greater:
            return event > event_;
        case Comparison::GreaterOrEqual:
            return event >= event_;
        case Comparison::Equal:
            return event == event_;
        case Comparison::NotEqual:
            return event != event_;
    }
}

LogicalOperationNode::LogicalOperationNode(LogicalOperation lo, std::shared_ptr<Node> l, std::shared_ptr<Node> r) :
        lo_(lo), l_(l), r_(r) {}

bool LogicalOperationNode::Evaluate(const Date &date, const std::string &event) const {
    if(lo_==LogicalOperation::And){
        return l_->Evaluate(date, event) && r_->Evaluate(date, event);
    }else{
        return l_->Evaluate(date, event) || r_->Evaluate(date, event);
    }
}

bool EmptyNode::Evaluate(const Date &, const std::string &) const {return true;}
